#include "Lexer/lexer.h"
#include "Parser/parser.h"

#define INITIAL_TOKEN_CAPACITY 100

int main()
{
    int lexerTest = 1;
    //Test inputs for lexer:
    //const char *const input = "+ ++ - -- ->*/ % ===!=!<=<<<>=>>>&&&|||^~()[]{},;:. 123 077 0x1b72 1.5 'a' \"alma\" '\n' \"alma\n\" _Hello  break    /*Hello\r\n we are*/ //the best\r\n";
    //const char *const input = "a + b - 42 * (c / 2)";
    //const char *const input = "\"Hello, world!\" 'a' 'b'";
    //const char *const input = "123 0x1A 075 3.14";
    //const char *const input = "+ - * / == != <= >= && || ! ^ ~ () {} [] , ; : .";
    //const char *const input = "int main() { /* this is a comment */ int x = 42; // another comment\r\n}";
    //const char *const input = "unknown_token # $ % ^";
    //const char *const input = "";
    //const char *const input = "if else while return";
    //const char *const input = "printf(\"Hello World!\");";

    //Test inputs for parser:
    lexerTest = 0;
    //const char *const input = "int main() { int x = 5; x = \"Hello World!\"; if (x == 5) { printf(\"Hello World!\"); } }";
    //const char *const input = "int x = 5; void hello(); int main() { int x = 5; }";
    const char *const input = "int x = 5; void hello(); int main() { main: int x = 5; return 0; } void hello() { for(;;) { if (1) { break; } else if (2) { goto main; } } }";

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
    printf("Input chararcter count: %d\n", (int)lexer->charCount);

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

    if (lexerTest)
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
        deleteParser(parser);
        deleteTokens(tokens, tokenCount);    
    }
    ASTNode *astNodeRoot = getCopyAST(parser);

    printParseTrees(parser);
    deleteParser(parser);
    deleteASTNode(astNodeRoot);

    deleteTokens(tokens, tokenCount);
    printf("END\n");
    return 0;
}