#include "parser.h"

/*****************************************************************************************************
                            PRIVATE PARSER FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

static int getBinaryPrecedence(TokenType type);

static int getUnaryPrecedence(TokenType type, int isPostfix);

static Token *nextToken(const Parser *const parser);

static Token *peekToken(const Parser *const parser, const size_t offset);

static void consumeToken(Parser *const parser, const size_t count);

static Token *matchToken(Parser *parser, TokenType type);

static ASTNode *parseProgram(Parser *parser);

static ASTNode *parseGlobalDeclaration(Parser *parser);

static ASTNode *parseEnum(Parser *parser);

static ASTNode *parseStruct(Parser *parser);

static ASTNode *parseUnion(Parser *parser);

static ASTNode *parseParameterList(Parser *parser);

static ASTNode *parseEnumList(Parser *parser);

static ASTNode *parseMemberList(Parser *parser);

static ASTNode *parseStatement(Parser *parser);

static ASTNode *parseExpressionStatement(Parser *parser);

static ASTNode *parseIfStatement(Parser *parser);

static ASTNode *parseSwitchStatement(Parser *parser);

static ASTNode *parseSwitchBody(Parser *parser);

static ASTNode *parseForStatement(Parser *parser);

static ASTNode *parseWhileStatement(Parser *parser);

static ASTNode *parseDoStatement(Parser *parser);

static ASTNode *parseCompoundStatement(Parser *parser);

static ASTNode *parseExpression(Parser *parser);

static ASTNode *parseFunctionCall(Parser *parser);

static ASTNode *parseFucntionCallParameterList(Parser *parser);

static ASTNode *parseAssignementExpression(Parser *parser);

static ASTNode *parseBinaryExpression(Parser *parser, int parentPrecedence);

static ASTNode *parseTypeCastExpression(Parser *parser);

static ASTNode *parseUnaryExpression(Parser *parser, int parentPrecedence);

static ASTNode *parsePrimaryExpression(Parser *parser);

static ASTNode *parseLiteral(Parser *parser);

/*****************************************************************************************************
                                PRIVATE PARSER FUNCTIONS START HERE
 *****************************************************************************************************/

static int getBinaryPrecedence(TokenType type)
{
    switch (type)
    {
    case TOKEN_DOT:
    case TOKEN_ARROW:
        return 13;
    case TOKEN_STAR:
    case TOKEN_SLASH:
    case TOKEN_PERCENT:
        return 11;
    case TOKEN_PLUS:
    case TOKEN_MINUS:
        return 10;
    case TOKEN_BITWISE_LEFT_SHIFT:
    case TOKEN_BITWISE_RIGHT_SHIFT:
        return 9;
    case TOKEN_LESS_THAN:
    case TOKEN_GREATER_THAN:
    case TOKEN_LESS_THAN_OR_EQUAL:
    case TOKEN_GREATER_THAN_OR_EQUAL:
        return 8;
    case TOKEN_DOUBLE_EQUALS:
    case TOKEN_NOT_EQUALS:
        return 7;
    case TOKEN_BITWISE_AND:
        return 6;
    case TOKEN_BITWISE_XOR:
        return 5;
    case TOKEN_BITWISE_OR:
        return 4;
    case TOKEN_AND:
        return 3;
    case TOKEN_OR:
        return 2;
    default:
        return 0;
    }
}

static int getUnaryPrecedence(TokenType type, int isPostfix)
{
    switch (type)
    {
    case TOKEN_DOUBLE_PLUS:
        if (isPostfix)
        {
            return 13;
        }
        return 12;
    case TOKEN_DOUBLE_MINUS:
        if (isPostfix)
        {
            return 13;
        }
        return 12;
    case TOKEN_PLUS:
    case TOKEN_MINUS:
    case TOKEN_NOT:
    case TOKEN_BITWISE_NOT:
        return 12;
    default:
        return 0;
    }
}

/**
 * Retrieves the token at the current position in the parser's token array.
 * 
 * This function accesses the token at the parser's current position in the token array.
 * It does not modify the state of the parser.
 * 
 * If the parser is NULL or the position is out of bounds, an error message is
 * printed, and the function returns NULL to indicate an invalid state or error.
 * 
 * @param parser Pointer to the `Parser` object. This pointer is const and should not be modified by this function.
 * 
 * @return A pointer to the token at the current position in the parser's token array, or NULL if the position is invalid.
 */
static Token *nextToken(const Parser *const parser)
{
    if(parser == NULL || parser->position > parser->tokenCount)
    {
        fprintf(stderr, "Invalid Parser state or position out of bounds!\n");
        return NULL;
    }

    return parser->tokens[parser->position];
}

/**
 * Retrieves the token at a specified offset from the current position in the parser's token array.
 * 
 * This function allows peeking at the token at a given offset from the current position
 * in the parser's token array without advancing the position. It provides a way to look
 * ahead in the token stream for parsing purposes.
 * 
 * If the parser is NULL, an error message is printed, and the function returns `NULL`.
 * If the specified offset is beyond the end of the token array, the function returns `NULL`.
 * 
 * @param parser Pointer to the `Parser` object. This pointer is const and should not be modified by this function.
 * 
 * @param offset The offset from the current position to look ahead in the token array.
 * 
 * @return A pointer to the token at the specified offset from the current position in the parser's token array,
 *         or `NULL` if the parser is NULL or if the offset is out of bounds.
 */
static Token *peekToken(const Parser *const parser, const size_t offset)
{
    if(parser == NULL)
    {
        fprintf(stderr, "Parser is NULL!\n");
        return NULL;
    }

    if (parser->position + offset > parser->tokenCount)
    {
        return parser->tokens[parser->tokenCount];
    }

    return parser->tokens[parser->position + offset];
}

/**
 * Advances the position in the parser’s token array by a specified number of tokens.
 * 
 * This function moves the parser's current position forward by the given count of tokens.
 * If the new position exceeds the end of the token array, it is set to the end of the token array.
 * 
 * If the parser is NULL, an error message is printed, and the function returns without making any changes.
 * 
 * @param parser Pointer to the `Parser` object. This pointer is non-const and will be modified by this function.
 * 
 * @param count The number of tokens to advance the position by.
 */
static void consumeToken(Parser *const parser, const size_t count)
{
    if(parser == NULL)
    {
        fprintf(stderr, "Parser is NULL!\n");
        return;
    }
    
    if (parser->position + count >= parser->tokenCount)
    {
        parser->position = parser->tokenCount - 1;
        return;
    }

    parser->position += count;
}

/**
 * Attempts to match the next token in the parser’s token array with a specified type.
 * 
 * This function checks if the next token in the parser's token stream matches the given token type.
 * If it does, the function advances the parser’s position by one token and returns the matched token.
 * If the token does not match, a placeholder token with type `TOKEN_UNKNOWN` is created and returned.
 * 
 * If memory allocation fails for the placeholder token, an error message is printed, and the function 
 * returns NULL. The `nextToken` function is used to retrieve the current token without advancing the position.
 * 
 * @param parser Pointer to the `Parser` object. This pointer is non-const and will be modified by this function.
 * 
 * @param type The type of token to match.
 * 
 * @return A pointer to the matched token if the type matches, or a placeholder token with type `TOKEN_UNKNOWN` if it does not.
 *         Returns NULL if memory allocation fails for the placeholder token.
 */
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
        fprintf(stderr, "Memory allocation for Token text failed!\n");
        return NULL;
    }
    return createTokenNone(text, TOKEN_UNKNOWN);
}

static ASTNode *parseProgram(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    size_t startingPos;
    while (nextToken(parser)->type != TOKEN_EOF)
    {
        startingPos = parser->position;
        children[childCount++] = parseGlobalDeclaration(parser);
        if (childCount == childrenSize)
        {
            childrenSize *= 2;
            ASTNode **newChildren = realloc(children, childrenSize * sizeof(ASTNode *));
            if (newChildren == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode children failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            children = newChildren;
        }

        if (parser->position == startingPos)
        {
            fprintf(stderr, "Parsing failed and token position didn't advance!\n");
            free(tokens);
            free(children);
            return NULL;
        }
    }
    
    tokens[tokenCount++] = matchToken(parser, TOKEN_EOF);

    return createASTNode(AST_PROGRAM, tokens, tokenCount, children, childCount);
}

static ASTNode *parseGlobalDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 6;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    if (nextToken(parser)->type == TOKEN_KEYWORD)
    {
        if (strcmp(nextToken(parser)->text, "enum") == 0)
        {
            free(tokens);
            free(children);
            return parseEnum(parser);
        }
        else if (strcmp(nextToken(parser)->text, "struct") == 0)
        {
            free(tokens);
            free(children);
            return parseStruct(parser);
        }
        else if (strcmp(nextToken(parser)->text, "union") == 0)
        {
            free(tokens);
            free(children);
            return parseUnion(parser);
        }

        //Handle const keyword
        else if (strcmp(nextToken(parser)->text, "const") == 0)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        }
    }

    //Handle built in type and custom type
    if (nextToken(parser)->type == TOKEN_KEYWORD)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
    }
    else
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
    }

    //Handle function / variable name
    tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);

    //Handle function
    if (nextToken(parser)->type == TOKEN_OPEN_PARENTHESIS)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);

        if (nextToken(parser)->type != TOKEN_CLOSE_PARENTHESIS)
        {
            children[childCount++] = parseParameterList(parser);
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);

        if (nextToken(parser)->type == TOKEN_SEMICOLON)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
            return createASTNode(AST_FUNCTION_DECLARATION, tokens, tokenCount ,children, childCount);
        }

        children[childCount++] = parseCompoundStatement(parser);

        return createASTNode(AST_FUNCTION_DEFINITION, tokens, tokenCount, children, childCount);
    }

    //Handle variable declaration
    if (nextToken(parser)->type == TOKEN_EQUALS)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_EQUALS);
        children[childCount++] = parseExpression(parser);
    }

    tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
    return createASTNode(AST_GLOBAL_VARIABLE_DECLARATION, tokens, tokenCount, children, childCount);
}

static ASTNode *parseEnum(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 5;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);

    if (nextToken(parser)->type == TOKEN_IDENTIFIER)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
    }

    tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_CURLY);

    children[childCount++] = parseEnumList(parser);

    tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_CURLY);

    return createASTNode(AST_ENUM, tokens, tokenCount, children, childCount);
}

static ASTNode *parseStruct(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 5;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);

    if (nextToken(parser)->type == TOKEN_IDENTIFIER)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
    }

    tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_CURLY);

    children[childCount++] = parseMemberList(parser);

    tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_CURLY);

    return createASTNode(AST_STRUCT, tokens, tokenCount, children, childCount);
}

static ASTNode *parseUnion(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 5;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);

    if (nextToken(parser)->type == TOKEN_IDENTIFIER)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
    }

    tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_CURLY);

    children[childCount++] = parseMemberList(parser);

    tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_CURLY);

    return createASTNode(AST_UNION, tokens, tokenCount, children, childCount);
}

static ASTNode *parseParameterList(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 3;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 0;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    //Handle const keyword
    if (nextToken(parser)->type == TOKEN_KEYWORD)
    {
        if (strcmp(nextToken(parser)->text, "const") == 0)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        }
    }

    //Handle built in type and custom type
    if (nextToken(parser)->type == TOKEN_KEYWORD)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
    }
    else
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
    }

    //variable name
    tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);

    size_t startingPos;
    while (nextToken(parser)->type == TOKEN_COMMA)
    {
        startingPos = parser->position;
        if (tokenCount + 4 >= tokensSize)
        {
            tokensSize *= 2;
            Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
            if (newTokens == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode tokens failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            tokens = newTokens;
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);

        //Handle const keyword
        if (nextToken(parser)->type == TOKEN_KEYWORD)
        {
            if (strcmp(nextToken(parser)->text, "const") == 0)
            {
                tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
            }
        }

        //Handle built in type and custom type
        if (nextToken(parser)->type == TOKEN_KEYWORD)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        }
        else
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        }

        //variable name
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);

        if (parser->position == startingPos)
        {
            fprintf(stderr, "Parsing failed and token position didn't advance!\n");
            free(tokens);
            free(children);
            return NULL;
        }
    }

    return createASTNode(AST_PARAMETER_LIST, tokens, tokenCount, children, childCount);
}

static ASTNode *parseEnumList(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 3;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);

    if (nextToken(parser)->type == TOKEN_EQUALS)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_EQUALS);
        children[childCount++] = parseExpression(parser);
    }

    size_t startingPos;
    while (nextToken(parser)->type == TOKEN_COMMA)
    {
        startingPos = parser->position;
        if (tokenCount + 4 >= tokensSize)
        {
            tokensSize *= 2;
            Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
            if (newTokens == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode tokens failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            tokens = newTokens;
        }

        if (childCount + 1 >= childrenSize)
        {
            childrenSize *= 2;
            ASTNode **newChildren = realloc(children, childrenSize * sizeof(ASTNode *));
            if (newChildren == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode children failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            children = newChildren;
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);

        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);

        if (nextToken(parser)->type == TOKEN_EQUALS)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_EQUALS);
            children[childCount++] = parseExpression(parser);
        }

        if (parser->position == startingPos)
        {
            fprintf(stderr, "Parsing failed and token position didn't advance!\n");
            free(tokens);
            free(children);
            return NULL;
        }
    }

    if (nextToken(parser)->type == TOKEN_COMMA)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);
    }

    return createASTNode(AST_ENUM_LIST, tokens, tokenCount, children, childCount);
}

static ASTNode *parseMemberList(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 4;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 0;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    //Handle const keyword
    if (nextToken(parser)->type == TOKEN_KEYWORD && strcmp(nextToken(parser)->text, "const") == 0)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
    }

    //Handle built in type and custom type
    if (nextToken(parser)->type == TOKEN_KEYWORD)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
    }
    else
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
    }

    //Handle function / variable name
    tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);

    tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);

    size_t startingPos;
    while (nextToken(parser)->type == TOKEN_KEYWORD || nextToken(parser)->type == TOKEN_IDENTIFIER)
    {
        startingPos = parser->position;
        if (tokenCount + 4 >= tokensSize)
        {
            tokensSize *= 2;
            Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
            if (newTokens == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode tokens failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            tokens = newTokens;
        }

        //Handle const keyword
        if (nextToken(parser)->type == TOKEN_KEYWORD && strcmp(nextToken(parser)->text, "const") == 0)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        }

        //Handle built in type and custom type
        if (nextToken(parser)->type == TOKEN_KEYWORD)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        }
        else
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        }

        //Handle function / variable name
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);

        tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);

        if (parser->position == startingPos)
        {
            fprintf(stderr, "Parsing failed and token position didn't advance!\n");
            free(tokens);
            free(children);
            return NULL;
        }
    }

    return createASTNode(AST_MEMBER_LIST, tokens, tokenCount, children, childCount);
}

static ASTNode *parseStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 5;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    if (nextToken(parser)->type == TOKEN_OPEN_CURLY)
    {
        free(tokens);
        free(children);
        return parseCompoundStatement(parser);
    }
    else if (nextToken(parser)->type == TOKEN_IDENTIFIER && peekToken(parser, 1)->type == TOKEN_COLON)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        tokens[tokenCount++] = matchToken(parser, TOKEN_COLON);
        children[childCount++] = parseStatement(parser);

        return createASTNode(AST_LABELED_STATEMENT, tokens, tokenCount, children, childCount);
    }
    else if (nextToken(parser)->type == TOKEN_KEYWORD)
    {
        if(strcmp(nextToken(parser)->text, "return") == 0)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
            children[childCount++] = parseExpressionStatement(parser);
            return createASTNode(AST_RETURN_STATEMENT, tokens, tokenCount, children, childCount);
        }
        else if (strcmp(nextToken(parser)->text, "break") == 0)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
            tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
            return createASTNode(AST_BREAK_STATEMENT, tokens, tokenCount, children, childCount);
        }
        else if (strcmp(nextToken(parser)->text, "continue") == 0)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
            tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
            return createASTNode(AST_CONTINUE_STATEMENT, tokens, tokenCount, children, childCount);
        }
        else if (strcmp(nextToken(parser)->text, "goto") == 0)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
            tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
            tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
            return createASTNode(AST_GOTO_STATEMENT, tokens, tokenCount, children, childCount);
        }
        else if (strcmp(nextToken(parser)->text, "if") == 0)
        {
            free(tokens);
            free(children);
            return parseIfStatement(parser);
        }
        else if (strcmp(nextToken(parser)->text, "switch") == 0)
        {
            free(tokens);
            free(children);
            return parseSwitchStatement(parser);
        }
        else if (strcmp(nextToken(parser)->text, "for") == 0)
        {
            free(tokens);
            free(children);
            return parseForStatement(parser);
        }
        else if (strcmp(nextToken(parser)->text, "while") == 0)
        {
            free(tokens);
            free(children);
            return parseWhileStatement(parser);
        }
        else if (strcmp(nextToken(parser)->text, "do") == 0)
        {
            free(tokens);
            free(children);
            return parseDoStatement(parser);
        }

        //Handle const keyword
        if (nextToken(parser)->type == TOKEN_KEYWORD && strcmp(nextToken(parser)->text, "const") == 0)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        }

        //Handle built in type and custom type
        if (nextToken(parser)->type == TOKEN_KEYWORD)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        }
        else
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        }

        //Handle variable name
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);

        if (nextToken(parser)->type == TOKEN_EQUALS)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_EQUALS);
            children[childCount++] = parseExpression(parser);
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);

        return createASTNode(AST_LOCAL_VARIABLE_DECLARATION, tokens, tokenCount, children, childCount);
    }

    free(tokens);
    free(children);
    return parseExpressionStatement(parser);
}

static ASTNode *parseExpressionStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    if (nextToken(parser)->type != TOKEN_SEMICOLON)
    {
        children[childCount++] = parseExpression(parser);
    }

    tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
    return createASTNode(AST_EXPRESSION_STATEMENT, tokens, tokenCount, children, childCount);
}

static ASTNode *parseIfStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 4;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 3;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);

    tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
    children[childCount++] = parseExpression(parser);
    tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);

    children[childCount++] = parseStatement(parser);

    if (nextToken(parser)->type == TOKEN_KEYWORD)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        children[childCount++] = parseStatement(parser);
    }

    return createASTNode(AST_IF_STATEMENT, tokens, tokenCount, children, childCount);
}

static ASTNode *parseSwitchStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 5;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);

    tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
    children[childCount++] = parseExpression(parser);
    tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);

    tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_CURLY);
    children[childCount++] = parseSwitchBody(parser);
    tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_CURLY);

    return createASTNode(AST_SWITCH_STATEMENT, tokens, tokenCount, children, childCount);
}

static ASTNode *parseSwitchBody(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 6;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 5;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    size_t startingPos;
    while (nextToken(parser)->type == TOKEN_KEYWORD && strcmp(nextToken(parser)->text, "case") == 0)
    {
        startingPos = parser->position;
        if (tokenCount + 2 >= tokensSize)
        {
            tokensSize *= 2;
            Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
            if (newTokens == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode tokens failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            tokens = newTokens;
        }

        if (childCount + 2 >= childrenSize)
        {
            childrenSize *= 2;
            ASTNode **newChildren = realloc(children, childrenSize * sizeof(ASTNode *));
            if (newChildren == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode children failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            children = newChildren;
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        children[childCount++] = parseLiteral(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_COLON);

        size_t startingPos2;
        while (nextToken(parser)->type == TOKEN_KEYWORD && (strcmp(nextToken(parser)->text, "case") == 0 || strcmp(nextToken(parser)->text, "default") == 0))
        {
            startingPos2 = parser->position;
            if (childCount + 2 >= childrenSize)
            {
                childrenSize *= 2;
                ASTNode **newChildren = realloc(children, childrenSize * sizeof(ASTNode *));
                if (newChildren == NULL)
                {
                    fprintf(stderr, "Memory reallocation for ASTNode children failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                children = newChildren;
            }

            children[childCount++] = parseStatement(parser);

            if (parser->position == startingPos2)
            {
                fprintf(stderr, "Parsing failed and token position didn't advance!\n");
                free(tokens);
                free(children);
                return NULL;
            }
        }

        if (parser->position == startingPos)
        {
            fprintf(stderr, "Parsing failed and token position didn't advance!\n");
            free(tokens);
            free(children);
            return NULL;
        }
    }

    if (nextToken(parser)->type == TOKEN_KEYWORD && strcmp(nextToken(parser)->text, "default") == 0)
    {
        if (tokenCount + 2 >= tokensSize)
        {
            tokensSize *= 2;
            Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
            if (newTokens == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode tokens failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            tokens = newTokens;
        }

        if (childCount + 1 >= childrenSize)
        {
            childrenSize *= 2;
            ASTNode **newChildren = realloc(children, childrenSize * sizeof(ASTNode *));
            if (newChildren == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode children failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            children = newChildren;
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        tokens[tokenCount++] = matchToken(parser, TOKEN_COLON);

        while (nextToken(parser)->type == TOKEN_KEYWORD && (strcmp(nextToken(parser)->text, "case") == 0 || strcmp(nextToken(parser)->text, "default") == 0))
        {
            startingPos = parser->position;
            if (childCount + 2 >= childrenSize)
            {
                childrenSize *= 2;
                ASTNode **newChildren = realloc(children, childrenSize * sizeof(ASTNode *));
                if (newChildren == NULL)
                {
                    fprintf(stderr, "Memory reallocation for ASTNode children failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                children = newChildren;
            }

            children[childCount++] = parseStatement(parser);

            if (parser->position == startingPos)
            {
                fprintf(stderr, "Parsing failed and token position didn't advance!\n");
                free(tokens);
                free(children);
                return NULL;
            }
        }
    }

    while (nextToken(parser)->type == TOKEN_KEYWORD && strcmp(nextToken(parser)->text, "case") == 0)
    {
        startingPos = parser->position;
        if (tokenCount + 2 >= tokensSize)
        {
            tokensSize *= 2;
            Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
            if (newTokens == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode tokens failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            tokens = newTokens;
        }

        if (childCount + 2 >= childrenSize)
        {
            childrenSize *= 2;
            ASTNode **newChildren = realloc(children, childrenSize * sizeof(ASTNode *));
            if (newChildren == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode children failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            children = newChildren;
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        children[childCount++] = parseLiteral(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_COLON);

        size_t startingPos2;
        while (nextToken(parser)->type == TOKEN_KEYWORD && (strcmp(nextToken(parser)->text, "case") == 0 || strcmp(nextToken(parser)->text, "default") == 0))
        {
            startingPos2 = parser->position;
            if (childCount + 2 >= childrenSize)
            {
                childrenSize *= 2;
                ASTNode **newChildren = realloc(children, childrenSize * sizeof(ASTNode *));
                if (newChildren == NULL)
                {
                    fprintf(stderr, "Memory reallocation for ASTNode children failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                children = newChildren;
            }

            children[childCount++] = parseStatement(parser);

            if (parser->position == startingPos2)
            {
                fprintf(stderr, "Parsing failed and token position didn't advance!\n");
                free(tokens);
                free(children);
                return NULL;
            }
        }

        if (parser->position == startingPos)
        {
            fprintf(stderr, "Parsing failed and token position didn't advance!\n");
            free(tokens);
            free(children);
            return NULL;
        }
    }

    return createASTNode(AST_SWITCH_BODY, tokens, tokenCount, children, childCount);
}

static ASTNode *parseForStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 3;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 4;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
    
    tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
    children[childCount++] = parseExpressionStatement(parser);
    children[childCount++] = parseExpressionStatement(parser);

    if (nextToken(parser)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        children[childCount++] = parseExpression(parser);
    }

    tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
    children[childCount++] = parseStatement(parser);

    return createASTNode(AST_FOR_ITERATION_STATEMENT, tokens, tokenCount, children, childCount);
}

static ASTNode *parseWhileStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 3;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);

    tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
    children[childCount++] = parseExpression(parser);
    tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);

    children[childCount++] = parseStatement(parser);

    return createASTNode(AST_WHILE_ITERATION_STATEMENT, tokens, tokenCount, children, childCount);
}

static ASTNode *parseDoStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 4;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);

    children[tokenCount++] = parseStatement(parser);

    tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);

    tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
    children[childCount++] = parseExpression(parser);
    tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);

    return createASTNode(AST_DO_ITERATION_STATEMENT, tokens, tokenCount, children, childCount);
}

static ASTNode *parseCompoundStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_CURLY);

    size_t startingPos;
    while (nextToken(parser)->type != TOKEN_CLOSE_CURLY)
    {
        startingPos = parser->position;
        if (childCount + 1 >= childrenSize)
        {
            childrenSize *= 2;
            ASTNode **newChildren = realloc(children, childrenSize * sizeof(ASTNode *));
            if (newChildren == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode children failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            children = newChildren;
        }

        children[childCount++] = parseStatement(parser);

        if (parser->position == startingPos)
        {
            fprintf(stderr, "Parsing failed and token position didn't advance!\n");
            free(tokens);
            free(children);
            return NULL;
        }
    }

    tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_CURLY);

    return createASTNode(AST_COMPOUND_STATEMENT, tokens, tokenCount, children, childCount);
}

static ASTNode *parseExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (nextToken(parser)->type == TOKEN_IDENTIFIER && peekToken(parser, 1)->type == TOKEN_OPEN_PARENTHESIS)
    {
        return parseFunctionCall(parser);
    }

    return parseAssignementExpression(parser);
}

static ASTNode *parseFunctionCall(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 3;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);

    tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
    if (nextToken(parser)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        children[childCount++] = parseFucntionCallParameterList(parser);
    }
    tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);

    return createASTNode(AST_FUNCTION_CALL, tokens, tokenCount, children, childCount);
}

static ASTNode *parseFucntionCallParameterList(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    children[childCount++] = parseExpression(parser);

    size_t startingPos;
    while (nextToken(parser)->type == TOKEN_COMMA)
    {
        startingPos = parser->position;
        if (tokenCount + 1 >= tokensSize)
        {
            tokensSize *= 2;
            Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
            if (newTokens == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode tokens failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            tokens = newTokens;
        }
        if (childCount + 1 >= childrenSize)
        {
            childrenSize *= 2;
            ASTNode **newChildren = realloc(children, childrenSize * sizeof(ASTNode *));
            if (newChildren == NULL)
            {
                fprintf(stderr, "Memory reallocation for ASTNode children failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            children = newChildren;
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);

        children[childCount++] = parseExpression(parser);

        if (parser->position == startingPos)
        {
            fprintf(stderr, "Parsing failed and token position didn't advance!\n");
            free(tokens);
            free(children);
            return NULL;
        }
    }

    return createASTNode(AST_FUNCTION_CALL_PARAMETER_LIST, tokens, tokenCount, children, childCount);
}

static ASTNode *parseAssignementExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    if (nextToken(parser)->type == TOKEN_IDENTIFIER && peekToken(parser, 1)->type == TOKEN_EQUALS)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        tokens[tokenCount++] = matchToken(parser, TOKEN_EQUALS);
        children[childCount++] = parseExpression(parser);
        return createASTNode(AST_ASSIGNEMENT_EXPRESION, tokens, tokenCount, children, childCount);
    }

    free(tokens);
    free(children);
    return parseBinaryExpression(parser, 0);
}

static ASTNode *parseBinaryExpression(Parser *parser, int parentPrecedence)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    ASTNode *left = parseUnaryExpression(parser, parentPrecedence);

    while (1)
    {
        int precedence = getBinaryPrecedence(nextToken(parser)->type);
        if (precedence == 0 || precedence <= parentPrecedence)
        {
            break;
        }

        tokens[tokenCount++] = nextToken(parser);
        consumeToken(parser, 1);
        ASTNode *right = parseBinaryExpression(parser, precedence);
        children[childCount++] = left;
        children[childCount++] = right;
        left = createASTNode(AST_BINARY_EXPRESSION, tokens, tokenCount, children, childCount);
        tokens = malloc(tokensSize * sizeof(Token *));
        tokenCount = 0;
        children = malloc(childrenSize * sizeof(ASTNode *));
        childCount = 0;
    }
    
    free(tokens);
    free(children);
    return left;
}

static ASTNode *parseTypeCastExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 4;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);

    //Handle const keyword
    if (nextToken(parser)->type == TOKEN_KEYWORD)
    {
        if (strcmp(nextToken(parser)->text, "const") == 0)
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        }
    }

    //Handle built in type and custom type
    if (nextToken(parser)->type == TOKEN_KEYWORD)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
    }
    else
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
    }

    tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);

    children[childCount++] = parseBinaryExpression(parser, 12);

    return createASTNode(AST_TYPE_CAST_EXPRESION, tokens, tokenCount, children, childCount);
}

static ASTNode *parseUnaryExpression(Parser *parser, int parentPrecedence)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    int precedence = getUnaryPrecedence(nextToken(parser)->type, 0);
    if (precedence != 0 && precedence >= parentPrecedence)
    {
        tokens[tokenCount++] = nextToken(parser);
        consumeToken(parser, 1);
        children[childCount++] = parseBinaryExpression(parser, precedence);
        return createASTNode(AST_UNARY_EXPRESSION, tokens, tokenCount, children, childCount);
    }
    else if (precedence == 0 && 12 >= parentPrecedence && nextToken(parser)->type == TOKEN_OPEN_PARENTHESIS)
    {
            //const keyword / const identifier / keyword case:
        if((peekToken(parser, 1)->type == TOKEN_KEYWORD && (peekToken(parser, 2)->type == TOKEN_CLOSE_PARENTHESIS || peekToken(parser, 3)->type == TOKEN_CLOSE_PARENTHESIS)) ||
            //identifier case:
            (peekToken(parser, 1)->type == TOKEN_IDENTIFIER && peekToken(parser, 2)->type == TOKEN_CLOSE_PARENTHESIS))
        {
            free(tokens);
            free(children);
            return parseTypeCastExpression(parser);
        }
    }

    free(tokens);
    free(children);
    return parsePrimaryExpression(parser);
}

static ASTNode *parsePrimaryExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    if (nextToken(parser)->type == TOKEN_IDENTIFIER)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        return createASTNode(AST_IDENTIFIER_EXPRESSION, tokens, tokenCount, children, childCount);
    }
    else if (nextToken(parser)->type == TOKEN_OPEN_PARENTHESIS)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        children[childCount++] = parseExpression(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        return createASTNode(AST_PARENTHESES_EXPRESION, tokens, tokenCount, children, childCount);
    }

    free(tokens);
    free(children);
    return parseLiteral(parser);
}

static ASTNode *parseLiteral(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    size_t tokenCount = 0;

    size_t childrenSize = 0;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    size_t childCount = 0;

    tokens[tokenCount++] = nextToken(parser);
    consumeToken(parser, 1);

    return createASTNode(AST_LITERAL, tokens, tokenCount, children, childCount);
}


/*****************************************************************************************************
                                PUBLIC PARSER FUNCTIONS START HERE                                
 *****************************************************************************************************/

/**
 * Creates a new `Parser` object and initializes it with a filtered list of tokens.
 * 
 * Allocates memory for a `Parser` structure and initializes it with the tokens provided. 
 * The function filters out whitespace and comment tokens and reallocates the token array 
 * to match the number of relevant tokens.
 * 
 * @param tokens      A pointer to an array of `Token` pointers. The `Parser` will store 
 *                    a filtered version of this array, excluding whitespace and comments.
 * 
 * @param tokenCount  The total number of tokens in the `tokens` array.
 * 
 * @return A pointer to the newly created `Parser`, or NULL if memory allocation fails 
 *         or if the `tokens` array is NULL.
 * 
 * @note The caller is responsible for cleaning up the `Parser` object when it is no longer needed.
 *       This should be done using `deleteParser`. The caller is also responsible for managing 
 *       the lifecycle of the individual `Token` objects provided in the `tokens` array.
 * 
 * @note The `Parser` holds a copy of the filtered token array but does not take ownership 
 *       of the individual `Token` objects or the original `tokens` array. The caller is 
 *       responsible for managing the lifecycle of the `Token` objects and should free 
 *       them when no longer needed. The `Parser` object itself should be freed using 
 *       `deleteParser` when it is no longer needed.
 */
Parser *createParser(Token **const tokens, const size_t tokenCount)
{
    if (tokens == NULL)
    {
        fprintf(stderr, "Token list provided to parser is NULL!\n");
        return NULL;
    }

    Parser *parser = (Parser *)malloc(sizeof(Parser));
    if (parser == NULL)
    {
        fprintf(stderr, "Memory allocation for Parser failed!\n");
        return NULL;
    }

    parser->tokens = (Token **)malloc(tokenCount * sizeof(Token*));
    if (parser->tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for Parser->tokens failed!\n");
        free(parser);
        return NULL;
    }

    size_t newCount = 0;
    for (size_t i = 0; i < tokenCount; i++)
    {
        if (tokens[i]->type != TOKEN_WHITESPACE && tokens[i]->type != TOKEN_BLOCK_COMMENT && tokens[i]->type != TOKEN_LINE_COMMENT)
        {
            parser->tokens[newCount++] = tokens[i];
        }
    }
    
    Token **newTokens = (Token **)realloc(parser->tokens, newCount * sizeof(Token*));
    if (newTokens == NULL && newCount > 0)
    {
        fprintf(stderr, "Memory reallocation for Parser->tokens failed!\n");
        free(parser->tokens);
        free(parser);
        return NULL;
    }
    parser->tokens = newTokens;

    parser->tokenCount = newCount;
    parser->position = 0;
    parser->ASTroot = NULL;

    return parser;
}

/**
 * Deletes a `Parser` object and frees its memory.
 * 
 * Frees the memory allocated for the `Parser` structure and its associated resources.
 * The function will free the memory for the filtered token array held by the `Parser`.
 * If an Abstract Syntax Tree (AST) root node exists, it will also be freed.
 * 
 * @param parser The `Parser` object to be deleted. If the parser is NULL, the function does nothing.
 * 
 * @note The `Parser` holds a copy of the filtered token array but does not own the individual 
 *       `Token` objects. It is the caller's responsibility to manage and free the memory 
 *       for the `Token` objects separately.
 *       Additionally, the `Parser` only owns a copy of the AST root node. To avoid memory leaks, 
 *       it is advised that the caller calls `getCopyAST` to obtain a copy of the AST before 
 *       deleting the parser.
 */
void deleteParser(Parser *const parser)
{
    if (parser == NULL)
    {
        return;
    }

    free(parser->tokens);

    if (parser->ASTroot != NULL)
    {
        free(parser->ASTroot);
    }

    free(parser);
}

/**
 * Retrieves a copy of the Abstract Syntax Tree (AST) from the `Parser`.
 * 
 * This function creates a duplicate of the AST root node held by the `Parser`.
 * It ensures that a new `ASTNode` structure is returned, which is a copy of the 
 * current AST root. If the `Parser` is not initialized or the AST root is NULL, 
 * the function will report an error and return NULL.
 * 
 * @param parser A pointer to the `Parser` object from which to copy the AST.
 *               The `Parser` must be initialized and must contain a valid AST root.
 * 
 * @return A pointer to a newly created `ASTNode` that is a copy of the parser's 
 *         AST root, or NULL if the `Parser` is not initialized, or if the AST root is NULL.
 * 
 * @note To avoid memory leaks, ensure that the returned `ASTNode` is properly managed
 *       and freed when no longer needed.
 */
ASTNode *getCopyAST(const Parser *const parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (parser->ASTroot == NULL)
    {
        fprintf(stderr, "Parser's AST root is NULL, no AST to copy.\n");
        return NULL;
    }

    return duplicateASTNode(parser->ASTroot);
}

/**
 * Parses the input tokens and generates an Abstract Syntax Tree (AST) from them.
 * 
 * This function processes the tokens held by the `Parser` to construct an AST. It
 * initializes the parsing process, which creates a structured representation of
 * the source code. If parsing has already been performed or if an error occurs
 * during parsing, the function will report the issue and return 0. If parsing is
 * successful, it will return 1.
 * 
 * @param parser A pointer to the `Parser` object containing the tokens to be parsed.
 *               The `Parser` must be initialized and should not have an existing
 *               AST root before parsing.
 * 
 * @return 1 if parsing is successful and the AST is created; 0 if there is an error
 *         (e.g., if the `Parser` is NULL, parsing has already been performed, or
 *         if parsing fails).
 * 
 * @note If parsing fails, the function will report an error to `stderr`. To ensure
 *       proper management of the resulting AST, the caller should check the return
 *       value and handle the AST accordingly.
 */
int parse(Parser *parser)
{
    if(parser == NULL)
    {
        fprintf(stderr, "Parser is NULL!\n");
        return 0;
    }

    if (parser->ASTroot != NULL)
    {
        fprintf(stderr, "Already parsed the input tokens!\n");
        return 0;
    }

    parser->ASTroot = parseProgram(parser);
    if (parser->ASTroot == NULL)
    {
        fprintf(stderr, "Failed to parse the input tokens!\n");
        return 0;
    }

    return 1;
}


/**
 * Prints the Abstract Syntax Tree (AST) to the standard output.
 * 
 * This function outputs a visual representation of the AST generated by the parser.
 * It starts by checking the validity of the `Parser` object and whether the AST has
 * been generated. If the `Parser` is NULL or the AST root is not yet set, it reports
 * the issue to `stderr`. Otherwise, it proceeds to print the AST using the `printASTNode`
 * function.
 * 
 * @param parser A pointer to the `Parser` object containing the AST to be printed.
 *               The `Parser` must be initialized and have a valid AST root.
 * 
 * @return void
 * 
 * @note The function will report errors to `stderr` if:
 * 
 *       - The `Parser` is NULL.
 * 
 *       - The AST root has not been set (indicating that parsing has not yet occurred).
 * 
 * The function does not modify the `Parser` or its contents.
 */
void printParseTrees(const Parser *const parser)
{
    if(parser == NULL)
    {
        fprintf(stderr, "Parser is NULL!\n");
        return;
    }

    if(parser->ASTroot == NULL)
    {
        fprintf(stderr, "The input hasn't been parsed yet!\n");
        return;
    }

    printf("Parser:\n");
    printASTNode(parser->ASTroot, "", 0);
}