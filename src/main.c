#include <stdio.h>
#include <stdbool.h>

#include "utils/logger.h"
#include "fileSystem.h"
#include "utils/error.h"
#include "utils/arena.h"
#include "utils/hashTable.h"
#include "utils/linkedList.h"
#include "options.h"
#include "lexer.h"
#include "parser.h"

bool createArenasAndStringTable(Arena **alphaArena, Arena **betaArena, Arena **stringInterningArena, HashTable **stringInterningTable);

LinkedList *lexFile(Arena *alphaArena, Arena *betaArena, HashTable *stringInterningTable, File file);

AstNode *parseFile(Arena *alphaArena, Arena *betaArena, LinkedList *tokens);

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
        fprintf(stderr, "Error: Failed to parse command line arguments.\n");
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
            fprintf(stderr, "Error: Failed to read file '%s'.\n", options.files[i]);
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
            fprintf(stderr, "Error: Failed to create arenas and string interning table for file: %s.\n", options.files[i]);
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
            fprintf(stderr, "Error: Failed to lex file '%s'.\n", options.files[i]);
            options_free(&options);
            fileSystem_free(&file);
            arena_destroy(&stringInterningArena);
            arena_destroy(&alphaArena);
            arena_destroy(&betaArena);
            logger_close();
            return 1;
        }

        linkedList_printRecursive(tokens, (PrintFunction)token_print);

        #ifdef DEBUG
        return 0; // Exit early in debug mode to avoid parsing
        #endif

        // Alpha ast and token copys
        // Beta stores tokens and utils (gets emptied after parsing)
        AstNode *ast = parseFile(alphaArena, betaArena, tokens);
        if (ast == NULL)
        {
            fprintf(stderr, "Error: Failed to parse file '%s'.\n", options.files[i]);
            options_free(&options);
            fileSystem_free(&file);
            arena_destroy(&stringInterningArena);
            arena_destroy(&alphaArena);
            arena_destroy(&betaArena);
            logger_close();
            return 1;
        }

        astNode_printTree(ast, "", true);

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
     Arena *createdAlphaArena = arena_create();
    if (createdAlphaArena == NULL)
    {
        fprintf(stderr, "Error: Failed to create alpha arena.\n");
        return false;
    }
    *alphaArena = createdAlphaArena;

    Arena *createdBetaArena = arena_create();
    if (createdBetaArena == NULL)
    {
        fprintf(stderr, "Error: Failed to create beta arena.\n");
        arena_destroy(&createdAlphaArena);
        return false;
    }
    *betaArena = createdBetaArena;

    Arena *createdStringInterningArena = arena_create();
    if (createdStringInterningArena == NULL)
    {
        fprintf(stderr, "Error: Failed to create string interning arena.\n");
        arena_destroy(&createdAlphaArena);
        arena_destroy(&createdBetaArena);
        return false;
    }
    *stringInterningArena = createdStringInterningArena;

    HashTable *createdStringInterningTable = hashTable_create(createdStringInterningArena);
    if (createdStringInterningTable == NULL)
    {
        fprintf(stderr, "Error: Failed to create string interning table.\n");
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
        fprintf(stderr, "Error: Alpha arena is NULL.\n");
        return NULL;
    }

    if (betaArena == NULL)
    {
        fprintf(stderr, "Error: Beta arena is NULL.\n");
        return NULL;
    }

    if (stringInterningTable == NULL)
    {
        fprintf(stderr, "Error: String interning table is NULL.\n");
        return NULL;
    }

    if (file.sourceBuffer == NULL || file.sourceBufferSize == 0)
    {
        fprintf(stderr, "Error: Source buffer is NULL or empty for file: %s.\n", file.name);
        return NULL;
    }

    Lexer *lexer = lexer_create(alphaArena, betaArena, stringInterningTable, file.sourceBuffer, file.sourceBufferSize);
    if (lexer == NULL)
    {
        fprintf(stderr, "Error: Failed to create lexer for file: %s.\n", file.name);
        return NULL;
    }

    lexer_lex(lexer);
    if (errno != 0)
    {
        fprintf(stderr, "Error: Lexer encountered an error while processing file '%s': %s.\n", file.name, strerror(errno));
        if (lexer->error != NULL)
        {
            linkedList_print(lexer->error, (PrintFunction)error_print); // TODO print errors in a better way
        }
        return NULL;
    }

    if (lexer->error != NULL)
    {
        fprintf(stderr, "Error: Lexer encountered errors while processing file '%s'.\n", file.name);
        linkedList_print(lexer->error, (PrintFunction)error_print); // TODO print errors in a better way
        return NULL;
    }

    LinkedList *tokens = lexer->tokens;
    arena_reset(alphaArena);
    return tokens;
}

AstNode *parseFile(Arena *alphaArena, Arena *betaArena, LinkedList *tokens)
{
    if (alphaArena == NULL)
    {
        fprintf(stderr, "Error: Alpha arena is NULL.\n");
        return NULL;
    }

    if (betaArena == NULL)
    {
        fprintf(stderr, "Error: Beta arena is NULL.\n");
        return NULL;
    }

    if (tokens == NULL)
    {
        fprintf(stderr, "Error: Tokens list is NULL.\n");
        return NULL;
    }

    Parser *parser = parser_create(betaArena, alphaArena, tokens);
    if (parser == NULL)
    {
        fprintf(stderr, "Error: Failed to create parser.\n");
        return NULL;
    }

    parser_parse(parser);
    if (errno != 0)
    {
        fprintf(stderr, "Error: Parser encountered an error: %s.\n", strerror(errno));
        if (parser->errors != NULL)
        {
            linkedList_print(parser->errors, (PrintFunction)error_print); // TODO print errors in a better way
        }
        return NULL;
    }

    if (parser->errors != NULL)
    {
        fprintf(stderr, "Error: Parser encountered errors.\n");
        linkedList_print(parser->errors, (PrintFunction)error_print); // TODO print errors in a better way
        return NULL;
    }

    AstNode *ast = parser->ast;
    arena_reset(betaArena);
    return ast;
}