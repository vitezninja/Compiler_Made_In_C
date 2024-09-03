#include "Lexer/lexer.h"
#include "Parser/parser.h"
#include "utils/file_reading.h"

#define INITIAL_TOKEN_CAPACITY 100

int main(int argc, char *argv[])
{
    int onlyLexer = 0;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <path_to_file_to_compile>\n", argv[0]);
        return -1;
    }

    int fileCount = argc - 1;
    int fileOffset = 1;
    //Only lexer mode
    if (strcmp(argv[1], "-l") == 0)
    {
        if (argc < 3)
        {
            fprintf(stderr, "Usage: %s -l <path_to_file_to_compile>\n", argv[0]);
            return -1;
        }
        fileCount -= 1;
        fileOffset += 1;
        onlyLexer = 1;
    }

    char **files = malloc(fileCount * sizeof(char *));
    if (files == NULL)
    {
        fprintf(stderr, "Memory allocation for file paths failed!\n");
        return -1;
    }

    for (size_t i = 0; (int)i < fileCount; i++)
    {
        files[i] = argv[i + fileOffset];
    }
    
    char **fileContents = readFromFiles(files, fileCount);
    free(files);
    const char *const input = fileContents[0];

    size_t tokenCapacity = INITIAL_TOKEN_CAPACITY;
    Token **tokens = malloc(tokenCapacity * sizeof(Token));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for Tokens failed!\n");
        freeFileContent(fileContents, fileCount);
        return -1;
    }

    size_t tokenCount = 0;
    Lexer *lexer = createLexer(input);
    if (lexer == NULL)
    {
        fprintf(stderr, "Failed to create Lexer.\n");
        freeFileContent(fileContents, fileCount);
        free(tokens);
        return -1;
    }

    while (1)
    {
        Token *ctoken = lex(lexer);
        if (ctoken == NULL)
        {
            fprintf(stderr, "Error lexing input or end of input.\n");
            freeFileContent(fileContents, fileCount);
            deleteTokens(tokens, tokenCount);
            deleteLexer(lexer);
            return -1;
        }

        if (tokenCount >= tokenCapacity)
        {
            tokenCapacity *= 2;
            Token **newTokens = realloc(tokens, tokenCapacity * sizeof(Token *));
            if (newTokens == NULL)
            {
                fprintf(stderr, "Memory allocation for tokens array failed!\n");
                freeFileContent(fileContents, fileCount);
                deleteTokens(tokens, tokenCount);
                deleteLexer(lexer);
                return -1;
            }
            tokens = newTokens;
        }

        tokens[tokenCount++] = ctoken;

        if (ctoken->type == TOKEN_EOF)
        {
            break;
        }
    }

    if (lexer->errorCount > 0)
    {
        for (size_t i = 0; i < lexer->errorCount; i++)
        {
            printError(lexer->errors[i]);
        }
        
        freeFileContent(fileContents, fileCount);
        deleteTokens(tokens, tokenCount);
        deleteLexer(lexer);
        return -1;
    }

    freeFileContent(fileContents, fileCount);
    deleteLexer(lexer);

    if (onlyLexer)
    {
        deleteTokens(tokens, tokenCount);
        printf("END\n");
        return 0;
    }

    Parser *parser = createParser(tokens, tokenCount);
    int err = parse(parser);
    if (!err)
    {
        printf("Parsing failed!\n");
        if (parser->errorCount > 0)
        {
            for (size_t i = 0; i < parser->errorCount; i++)
            {
                printError(parser->errors[i]);
            }
            
            deleteTokens(tokens, tokenCount);
            deleteParser(parser);
            return -1;    
        }
        deleteTokens(tokens, tokenCount);    
        deleteParser(parser);
        return -1;
    }

    if (parser->errorCount > 0)
    {
        for (size_t i = 0; i < parser->errorCount; i++)
        {
            printError(parser->errors[i]);
        }
        
        deleteTokens(tokens, tokenCount);
        deleteParser(parser);
        return -1;    
    }

    ASTNode *astNodeRoot = getCopyAST(parser);
    printParseTrees(parser);

    deleteParser(parser);

    
    deleteTokens(tokens, tokenCount);
    deleteASTNode(astNodeRoot);
    printf("END\n");
    return 0;
}