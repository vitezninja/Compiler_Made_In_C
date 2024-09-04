#include "vm.h"


/*****************************************************************************************************
                            PRIVATE MY_STRING FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

/* Inital token capacity for lexing */
#define INITIAL_TOKEN_CAPACITY 100

/*****************************************************************************************************
                                PRIVATE MY_STRING FUNCTIONS START HERE
 *****************************************************************************************************/

/*****************************************************************************************************
                                PUBLIC MY_STRING FUNCTIONS START HERE                                
 *****************************************************************************************************/

int runVM(int argc, char **argv)
{
    //Parse arguments
    Flags *flags = parseArgs(argc, argv);
    if (flags == NULL)
    {
        return -1;
    }

    //Read the contents of the files
    char **fileContents = readFromFiles(flags->files, flags->fileCount);
    //TODO:
    //Handle multiple files, we only handle one file for now
    const char *const input = fileContents[0];

    //Create the tokens array
    size_t tokenCapacity = INITIAL_TOKEN_CAPACITY;
    Token **tokens = malloc(tokenCapacity * sizeof(Token));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for Tokens failed!\n");
        freeFileContent(fileContents, flags->fileCount);
        freeFlags(flags);
        return -1;
    }
    size_t tokenCount = 0;

    //Create the lexer
    Lexer *lexer = createLexer(input);
    if (lexer == NULL)
    {
        fprintf(stderr, "Failed to create Lexer.\n");
        freeFileContent(fileContents, flags->fileCount);
        freeFlags(flags);
        return -1;
    }

    //Lex the input
    while (1)
    {
        Token *ctoken = lex(lexer);
        if (ctoken == NULL)
        {
            fprintf(stderr, "Error lexing input or end of input.\n");
            freeFileContent(fileContents, flags->fileCount);
            freeFlags(flags);
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
                freeFileContent(fileContents, flags->fileCount);
                freeFlags(flags);
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

    //If lexer had errors, print them and return
    if (lexer->errorCount > 0)
    {
        fprintf(stderr, "Lexing failed!\n");
        for (size_t i = 0; i < lexer->errorCount; i++)
        {
            printError(lexer->errors[i]);
        }
        
        freeFileContent(fileContents, flags->fileCount);
        freeFlags(flags);
        deleteTokens(tokens, tokenCount);
        deleteLexer(lexer);
        return -1;
    }

    //If only lexing is requested, print the tokens and return
    if (flags->onlyLex)
    {
        for (size_t i = 0; i < tokenCount; i++)
        {
            printToken(tokens[i]);
        }
        freeFileContent(fileContents, flags->fileCount);
        freeFlags(flags);
        deleteTokens(tokens, tokenCount);
        deleteLexer(lexer);
        return 0;
    }

    freeFileContent(fileContents, flags->fileCount);
    deleteLexer(lexer);

    //Create the parser
    Parser *parser = createParser(tokens, tokenCount);
    if (parser == NULL)
    {
        fprintf(stderr, "Failed to create Parser.\n");
        freeFlags(flags);
        deleteTokens(tokens, tokenCount);
        return -1;
    }

    //Parse the tokens
    int err = parse(parser);
    if (!err)
    {
        fprintf(stderr, "Parsing failed!\n");
        for (size_t i = 0; i < parser->errorCount; i++)
        {
            printError(parser->errors[i]);
        }

        freeFlags(flags);
        deleteTokens(tokens, tokenCount);
        deleteParser(parser);
        return -1;
    }

    //Get the AST root
    ASTNode *root = getCopyAST(parser);
    deleteParser(parser);

    //Print the AST
    printASTNode(root, "", 0);

    //TODO:
    //Do things with the AST

    //Free memory
    freeFlags(flags);
    deleteASTNode(root);
    deleteTokens(tokens, tokenCount);
    return 0;
}