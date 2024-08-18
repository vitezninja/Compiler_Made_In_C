#include "Lexer/lexer.h"

#define INITIAL_TOKEN_CAPACITY 100

int main()
{
    //Test inputs:
    char* input = "+-->*/===!=!<=<<<>=>>>&&&|||^~()[]{},;:. 123 077 0x1b72 1.5 'a' \"alma\" '\n' \"alma\n\" _Hello  break    /*Hello\r\n we are*/ //the best\r\n";
    //char* input = "a + b - 42 * (c / 2)";
    //char* input = "\"Hello, world!\" 'a' 'b'";
    //char* input = "123 0x1A 075 3.14";
    //char* input = "+ - * / == != <= >= && || ! ^ ~ () {} [] , ; : .";
    //char* input = "int main() { /* this is a comment */ int x = 42; // another comment\r\n}";
    //char* input = "unknown_token # $ % ^";
    //char* input = "";
    //char* input = "if else while return";


    size_t tokenCapacity = INITIAL_TOKEN_CAPACITY;
    Token **tokens = malloc(tokenCapacity * sizeof(Token));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for Tokens failed!\n");
        return 1;
    }

    size_t tokenCount = 0;
    Lexer *lexer = createLexer(input);
    if (lexer == NULL)
    {
        fprintf(stderr, "Failed to create Lexer.\n");
        free(tokens);
        return 1;
    }

    printf("Input: %s\n", lexer->input);
    printf("Input chararcter count: %d\n", lexer->charCount);

    while (1)
    {
        Token *ctoken = lex(lexer);
        if (ctoken == NULL)
        {
            fprintf(stderr, "Error lexing input or end of input.\n");
            deleteLexer(lexer);
            deleteTokens(tokens, tokenCount);
            return 1;
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
                return 1;
            }
            tokens = newTokens;
        }

        if (ctoken->type != TOKEN_WHITESPACE)
        {
            tokens[tokenCount++] = ctoken;
        }

        if (ctoken->type == TOKEN_EOF)
        {
            break;
        }
    }
    deleteLexer(lexer);

    printf("Lexer:\n");
    for (size_t i = 0; i < tokenCount; i++)
    {
        printf("%u ", i);
        printToken(tokens[i]);
    }

    deleteTokens(tokens, tokenCount);
    return 0;
}