#include "parser.h"

/*****************************************************************************************************
                            PRIVATE PARSER FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

static Token *nextToken(const Parser *const parser);

static Token *peekToken(const Parser *const parser, const size_t offset);

static void consumeToken(Parser *const parser, const size_t count);

static Token *matchToken(Parser *parser, TokenType type);

/*****************************************************************************************************
                                PRIVATE PARSER FUNCTIONS START HERE
 *****************************************************************************************************/

static Token *nextToken(const Parser *const parser)
{
    if(parser == NULL || parser->position > parser->tokenCount)
    {
        fprintf(stderr, "Invalid Parser state or position out of bounds!\n");
        return NULL;
    }

    return parser->tokens[parser->position];
}

static Token *peekToken(const Parser *const parser, const size_t offset)
{
    if(parser == NULL)
    {
        fprintf(stderr, "Parser is NULL!\n");
        exit(-1);
    }

    if (parser->position + offset > parser->tokenCount)
    {
        return parser->tokens[parser->tokenCount];
    }

    return parser->tokens[parser->position + offset];
}

static void consumeToken(Parser *const parser, const size_t count)
{
    if(parser == NULL)
    {
        fprintf(stderr, "Parser is NULL!\n");
        exit(-1);
    }
    
    if (parser->position + count >= parser->tokenCount)
    {
        parser->position = parser->tokenCount;
        return;
    }

    parser->position += count;
}

static Token *matchToken(Parser *parser, const TokenType type)
{
    if (nextToken(parser)->type == type)
    {
        Token *token = nextToken(parser);
        consumeToken(parser, 1);
        return token;
    }

    const char *text = (char *)malloc(1 * sizeof(char));
    text = "";
    if (text == NULL)
    {
        fprintf(stderr, "Memory allocation for Token text failed!");
        return NULL;
    }
    return createTokenNone(text, TOKEN_UNKNOWN);
}

/*****************************************************************************************************
                                PUBLIC PARSER FUNCTIONS START HERE                                
 *****************************************************************************************************/

Parser *createParser(Token **tokens, const size_t tokenCount)
{
    if (tokens == NULL)
    {
        fprintf(stderr, "Tokens is NULL!\n");
        exit(-1);
    }

    Parser *parser = (Parser*)malloc(sizeof(Parser));
    if (parser == NULL)
    {
        fprintf(stderr, "Memory allocation for Parser failed!");
        exit(-1);
    }

    parser->tokens = (Token**)malloc(tokenCount * sizeof(Token*));
    if (parser->tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for Parser->tokens failed!");
        exit(-1);
    }

    size_t newCount = 0;
    for (size_t i = 0; i < tokenCount; i++)
    {
        if (tokens[i]->type != TOKEN_WHITESPACE && tokens[i]->type != TOKEN_BLOCK_COMMENT && tokens[i]->type != TOKEN_LINE_COMMENT)
        {
            parser->tokens[newCount++] = tokens[i];
        }
    }
    
    parser->tokens = (Token**)realloc(parser->tokens, newCount * sizeof(Token*));
    if (parser->tokens == NULL)
    {
        fprintf(stderr, "Memory reallocation for Parser->tokens failed!");
        exit(-1);
    }

    parser->tokenCount = newCount;
    parser->position = 0;

    return parser;
}

void deleteParser(Parser *parser)
{
    if (parser == NULL)
    {
        return;
    }

    free(parser->tokens);
    free(parser);
}

//TODO:
void parse(Parser *parser)
{
    if(parser == NULL)
    {
        fprintf(stderr, "Parser is NULL!\n");
        exit(-1);
    }
}

//TODO:
//Curently just prints out all the used tokens
void printParseTree(Parser *parser)
{
    if(parser == NULL)
    {
        fprintf(stderr, "Parser is NULL!\n");
        exit(-1);
    }

    printf("Parser:\n");
    for (size_t i = 0; i < parser->tokenCount; i++)
    {
        printf("%d: ", i);
        printToken(parser->tokens[i]);
    }
}