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

        Arena *stringInterningArena = arena_create();
        if (stringInterningArena == NULL)
        {
            fprintf(stderr, "Error: Failed to create string interning arena for file: %s.\n", options.files[i]);
            options_free(&options);
            fileSystem_free(&file);
            logger_close();
            return 1;
        }

        HashTable *stringInterningTable = hashTable_create(stringInterningArena);
        if (stringInterningTable == NULL)
        {
            fprintf(stderr, "Error: Failed to create string interning table for file: %s.\n", options.files[i]);
            options_free(&options);
            fileSystem_free(&file);
            arena_destroy(&stringInterningArena);
            logger_close();
            return 1;
        }

        Arena *alphaArena = arena_create();
        if (alphaArena == NULL)
        {
            fprintf(stderr, "Error: Failed to create alpha arena for file: %s.\n", options.files[i]);
            options_free(&options);
            fileSystem_free(&file);
            arena_destroy(&stringInterningArena);
            logger_close();
            return 1;
        }

        Arena *betaArena = arena_create();
        if (betaArena == NULL)
        {
            fprintf(stderr, "Error: Failed to create beta arena for file: %s.\n", options.files[i]);
            options_free(&options);
            fileSystem_free(&file);
            arena_destroy(&stringInterningArena);
            arena_destroy(&alphaArena);
            logger_close();
            return 1;
        }

        // Alpha stores utils
        // Beta stores tokens
        // String interning table is used for storing unique strings
        Lexer *lexer = lexer_create(alphaArena, betaArena, stringInterningTable, file.sourceBuffer, file.sourceBufferSize);
        if (lexer == NULL)
        {
            fprintf(stderr, "Error: Failed to create lexer for file: %s.\n", options.files[i]);
            options_free(&options);
            fileSystem_free(&file);
            arena_destroy(&stringInterningArena);
            arena_destroy(&alphaArena);
            arena_destroy(&betaArena);
            logger_close();
            return 1;
        }

        lexer_lex(lexer);
        if (errno != 0)
        {
            fprintf(stderr, "Error: Lexer encountered an error while processing file '%s': %s.\n", options.files[i], strerror(errno));
            if (lexer->error != NULL)
            {
                linkedList_print(lexer->error, (PrintFunction)error_print); // TODO print errors in a better way
            }
            options_free(&options);
            fileSystem_free(&file);
            arena_destroy(&stringInterningArena);
            arena_destroy(&alphaArena);
            arena_destroy(&betaArena);
            logger_close();
            return 1;
        }

        if (lexer->error != NULL)
        {
            fprintf(stderr, "Error: Lexer encountered errors while processing file '%s'.\n", options.files[i]);
            linkedList_print(lexer->error, (PrintFunction)error_print); // TODO print errors in a better way
            options_free(&options);
            fileSystem_free(&file);
            arena_destroy(&stringInterningArena);
            arena_destroy(&alphaArena);
            arena_destroy(&betaArena);
            logger_close();
            return 1;
        }

        linkedList_printRecursive(lexer->tokens, (PrintFunction)token_print);

        arena_print(alphaArena);
        arena_print(betaArena);

        arena_reset(alphaArena);

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