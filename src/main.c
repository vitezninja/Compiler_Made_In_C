/**
 * @file main.c
 * @brief Main entry point for the compiler.
 * 
 * This file contains the main function that initializes the compiler,
 * processes command line arguments, reads source files, and performs lexing and parsing.
 */

#include <stdio.h>
#include <stdbool.h>

#include "utils/logger.h"
#include "utils/error.h"
#include "utils/arena.h"
#include "utils/hashTable.h"
#include "utils/linkedList.h"
#include "fileSystem.h"
#include "options.h"
#include "lexer.h"
#include "parser.h"

/**
 * @brief Creates the necessary arenas and string interning table for the compiler.
 * 
 * This function initializes three arenas: one for alpha (utility storage), one for beta (token storage),
 * and one for string interning. It also creates a hash table for string interning.
 * 
 * @param alphaArena Pointer to the pointer for the alpha arena.
 * @param betaArena Pointer to the pointer for the beta arena.
 * @param stringInterningArena Pointer to the pointer for the string interning arena.
 * @param stringInterningTable Pointer to the pointer for the string interning hash table.
 * 
 * @return true if the arenas and string interning table were created successfully, false otherwise.
 */
bool createArenasAndStringTable(Arena **alphaArena, Arena **betaArena, Arena **stringInterningArena, HashTable **stringInterningTable);

/**
 * @brief Lexes a source file and returns a linked list of tokens.
 * 
 * This function initializes a lexer with the provided arenas and string interning table,
 * lexes the source file, and returns a linked list of tokens. If any errors occur during lexing,
 * it prints the errors and returns NULL.
 * 
 * @param alphaArena Pointer to the alpha arena for utility storage.
 * @param betaArena Pointer to the beta arena for token storage.
 * @param stringInterningTable Pointer to the hash table for string interning.
 * @param file The source file to be lexed, containing the source buffer and its size.
 * 
 * @return A linked list of tokens generated during lexing, or NULL if an error occurred.
 */
LinkedList *lexFile(Arena *alphaArena, Arena *betaArena, HashTable *stringInterningTable, File file);

/**
 * @brief Parses a linked list of tokens and returns the abstract syntax tree (AST).
 * 
 * This function initializes a parser with the provided arenas and tokens,
 * parses the tokens, and returns the resulting AST. If any errors occur during parsing,
 * it prints the errors and returns NULL.
 *
 * @param alphaArena Pointer to the alpha arena for utility storage.
 * @param betaArena Pointer to the beta arena for token storage.
 * @param tokens The linked list of tokens to be parsed.
 * @param file The source file being parsed.
 *
 * @return The abstract syntax tree (AST) generated from the tokens, or NULL if an error occurred.
 */
AstNode *parseFile(Arena *alphaArena, Arena *betaArena, LinkedList *tokens, File file);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <source files>\n", argv[0]);
        return 1;
    }    
    
    logger_init();

    // Process command line arguments
    Options options = options_create(argc, argv);
    if (options.files == NULL)
    {
        fprintf(stderr, "[Error] : Failed to parse command line arguments.\n");
        logger_close();
        return 1;
    }

    bool hadHelp = options_tryPrintHelp(&options);
    if (hadHelp)
    {
        options_free(&options);
        logger_close();
        return 0;
    }
    
    for (size_t i = 0; i < options.fileCount; i++)
    {
        File file = fileSystem_readFile(options.files[i]);
        if (file.sourceBuffer == NULL)
        {
            fprintf(stderr, "[Error] : Failed to read file '%s'.\n", options.files[i]);
            options_free(&options);
            logger_close();
            return 1;
        }

        Arena *alphaArena = NULL;
        Arena *betaArena = NULL;
        Arena *stringInterningArena = NULL;
        HashTable *stringInterningTable = NULL;
        bool success = createArenasAndStringTable(&alphaArena, &betaArena, &stringInterningArena, &stringInterningTable);
        if (!success)
        {
            fprintf(stderr, "[Error] : Failed to create arenas and string interning table for file: %s.\n", options.files[i]);
            options_free(&options);
            fileSystem_free(&file);
            logger_close();
            return 1;
        }

        // Alpha stores utils (gets emptied after lexing)
        // Beta stores tokens
        // String interning table is used for storing unique strings
        LinkedList *tokens = lexFile(alphaArena, betaArena, stringInterningTable, file);
        if (tokens == NULL)
        {
            options_free(&options);
            fileSystem_free(&file);
            arena_destroy(&stringInterningArena);
            arena_destroy(&alphaArena);
            arena_destroy(&betaArena);
            logger_close();
            return 1;
        }

        #ifdef OLEX
        linkedList_printRecursive(tokens, (PrintFunction)token_print);
        fileSystem_free(&file);
        arena_destroy(&stringInterningArena);
        arena_destroy(&alphaArena);
        arena_destroy(&betaArena);
        break; // Exit after lexing if OLEX is defined
        #endif

        // Alpha ast and token copys
        // Beta stores tokens and utils (gets emptied after parsing)
        AstNode *ast = parseFile(alphaArena, betaArena, tokens, file);
        if (ast == NULL)
        {
            options_free(&options);
            fileSystem_free(&file);
            arena_destroy(&stringInterningArena);
            arena_destroy(&alphaArena);
            arena_destroy(&betaArena);
            logger_close();
            return 1;
        }

        #ifdef OPARSE
        astNode_printTree(ast, "", true);
        fileSystem_free(&file);
        arena_destroy(&stringInterningArena);
        arena_destroy(&alphaArena);
        arena_destroy(&betaArena);
        break; // Exit after parsing if OPARSE is defined
        #endif

        fileSystem_free(&file);
        arena_destroy(&stringInterningArena);
        arena_destroy(&alphaArena);
        arena_destroy(&betaArena);
    }
    
    // Exiting the program, free allocated resources
    options_free(&options);
    logger_close();
    return 0;
}

bool createArenasAndStringTable(Arena **alphaArena, Arena **betaArena, Arena **stringInterningArena, HashTable **stringInterningTable)
{
    Arena *createdAlphaArena = arena_create(ARENA_ONE_MB * 2);
    if (createdAlphaArena == NULL)
    {
        DEBUG_PRINT("createArenasAndStringTable: Failed to create alpha arena.\n");
        return false;
    }
    *alphaArena = createdAlphaArena;

    Arena *createdBetaArena = arena_create(ARENA_ONE_MB * 2);
    if (createdBetaArena == NULL)
    {
        DEBUG_PRINT("createArenasAndStringTable: Failed to create beta arena.\n");
        arena_destroy(&createdAlphaArena);
        return false;
    }
    *betaArena = createdBetaArena;

    Arena *createdStringInterningArena = arena_create(ARENA_ONE_MB);
    if (createdStringInterningArena == NULL)
    {
        DEBUG_PRINT("createArenasAndStringTable: Failed to create string interning arena.\n");
        arena_destroy(&createdAlphaArena);
        arena_destroy(&createdBetaArena);
        return false;
    }
    *stringInterningArena = createdStringInterningArena;

    HashTable *createdStringInterningTable = hashTable_create(createdStringInterningArena);
    if (createdStringInterningTable == NULL)
    {
        DEBUG_PRINT("createArenasAndStringTable: Failed to create string interning table.\n");
        arena_destroy(&createdAlphaArena);
        arena_destroy(&createdBetaArena);
        arena_destroy(&createdStringInterningArena);
        return false;
    }
    *stringInterningTable = createdStringInterningTable;

    return true;
}

LinkedList *lexFile(Arena *alphaArena, Arena *betaArena, HashTable *stringInterningTable, File file)
{
    if (alphaArena == NULL)
    {
        DEBUG_PRINT("lexFile: Alpha arena is NULL.\n");
        return NULL;
    }

    if (betaArena == NULL)
    {
        DEBUG_PRINT("lexFile: Beta arena is NULL.\n");
        return NULL;
    }

    if (stringInterningTable == NULL)
    {
        DEBUG_PRINT("lexFile: String interning table is NULL.\n");
        return NULL;
    }

    if (file.sourceBuffer == NULL || file.sourceBufferSize == 0)
    {
        DEBUG_PRINT("lexFile: Source buffer is NULL or empty.\n");
        return NULL;
    }

    Lexer *lexer = lexer_create(alphaArena, betaArena, stringInterningTable, file.name, file.sourceBuffer, file.sourceBufferSize);
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexFile: Failed to create lexer for file: %s.\n", file.name);
        return NULL;
    }

    lexer_lex(lexer);
    if (errno != 0 || lexer->error != NULL)
    {
        LinkedList *error = lexer->error;
        while (error != NULL)
        {
            error_print((Error *)error->data, file.sourceBuffer);
            error = error->next;
        }
        return NULL;
    }

    LinkedList *tokens = lexer->tokens;
#ifdef DEBUG
    arena_print(alphaArena);
    arena_print(betaArena);
#endif
    arena_reset(alphaArena);
    return tokens;
}

AstNode *parseFile(Arena *alphaArena, Arena *betaArena, LinkedList *tokens, File file)
{
    if (alphaArena == NULL)
    {
        DEBUG_PRINT("parseFile: Alpha arena is NULL.\n");
        return NULL;
    }

    if (betaArena == NULL)
    {
        DEBUG_PRINT("parseFile: Beta arena is NULL.\n");
        return NULL;
    }

    if (tokens == NULL)
    {
        DEBUG_PRINT("parseFile: Tokens list is NULL.\n");
        return NULL;
    }

    Parser *parser = parser_create(betaArena, alphaArena, tokens);
    if (parser == NULL)
    {
        DEBUG_PRINT("parseFile: Failed to create parser.\n");
        return NULL;
    }

    parser_parse(parser);
    if (errno != 0 || parser->ast == NULL || parser->errors != NULL)
    {
        LinkedList *error = parser->errors;
        while (error != NULL)
        {
            error_print((Error *)error->data, file.sourceBuffer);
            error = error->next;
        }
        return NULL;
    }

    AstNode *ast = parser->ast;
#ifdef DEBUG
    arena_print(alphaArena);
    arena_print(betaArena);
#endif
    arena_reset(betaArena);
    return ast;
}  