#include "Lexer/lexer.h"
#include "Parser/parser.h"
#include "utils/file_reading.h"

#define INITIAL_TOKEN_CAPACITY 100

int main(int argc, char *argv[])
{
    // 1 if we only want to run the lexer, 0 if we also want to parse
    int onlyLexer = 1;

    int fileCount = argc - 1;
    if (fileCount < 1)
    {
        fprintf(stderr, "Usage: %s <path_to_file_to_compile>\n", argv[0]);
        exit(-1);
    }

    char **files = malloc(fileCount * sizeof(char *));
    if (files == NULL)
    {
        fprintf(stderr, "Memory allocation for file paths failed!\n");
        exit(-1);
    }

    for (size_t i = 0; (int)i < fileCount; i++)
    {
        files[i] = argv[i + 1];
    }
    
    char **fileContents = readFromFiles(files, fileCount);
    const char *const input = fileContents[0];

    size_t tokenCapacity = INITIAL_TOKEN_CAPACITY;
    Token **tokens = malloc(tokenCapacity * sizeof(Token));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for Tokens failed!\n");
        freeFileContent(fileContents, fileCount);
        exit(-1);
    }

    size_t tokenCount = 0;
    Lexer *lexer = createLexer(input);
    if (lexer == NULL)
    {
        fprintf(stderr, "Failed to create Lexer.\n");
        free(tokens);
        freeFileContent(fileContents, fileCount);
        exit(-1);
    }

    printf("Input: %s\n", lexer->input);
    printf("Input chararcter count: %d\n", (int)lexer->charCount);

    while (1)
    {
        Token *ctoken = lex(lexer);
        if (ctoken == NULL)
        {
            fprintf(stderr, "Error lexing input or end of input.\n");
            deleteLexer(lexer);
            deleteTokens(tokens, tokenCount);
            freeFileContent(fileContents, fileCount);
            exit(-1);
        }

        if (tokenCount >= tokenCapacity)
        {
            tokenCapacity *= 2;
            Token **newTokens = realloc(tokens, tokenCapacity * sizeof(Token *));
            if (newTokens == NULL)
            {
                fprintf(stderr, "Memory allocation for tokens array failed!\n");
                deleteLexer(lexer);
                deleteTokens(tokens, tokenCount);
                freeFileContent(fileContents, fileCount);
                exit(-1);
            }
            tokens = newTokens;
        }

        tokens[tokenCount++] = ctoken;

        if (ctoken->type == TOKEN_EOF)
        {
            break;
        }
    }
    deleteLexer(lexer);

    printf("Lexer:\n");
    for (size_t i = 0; i < tokenCount; i++)
    {
        if(tokens[i]->type != TOKEN_WHITESPACE)
        {
            printf("%d ", (int)i);
            printToken(tokens[i]);
        }
    }

    if (onlyLexer)
    {
        deleteTokens(tokens, tokenCount);
        freeFileContent(fileContents, fileCount);
        printf("END\n");
        return 0;
    }

    Parser *parser = createParser(tokens, tokenCount);
    int err = parse(parser);
    if (!err)
    {
        printf("Parsing failed!\n");
        deleteParser(parser);
        deleteTokens(tokens, tokenCount);    
    }
    ASTNode *astNodeRoot = getCopyAST(parser);

    printParseTrees(parser);
    deleteParser(parser);
    deleteASTNode(astNodeRoot);

    deleteTokens(tokens, tokenCount);
    freeFileContent(fileContents, fileCount);
    printf("END\n");
    return 0;
}