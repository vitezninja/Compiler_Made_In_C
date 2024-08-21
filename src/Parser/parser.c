#include "parser.h"

/*****************************************************************************************************
                            PRIVATE PARSER FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

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

static ASTNode *parseBinaryExpression(Parser *parser);

static ASTNode *parseUnaryExpression(Parser *parser);

static ASTNode *parsePrimaryExpression(Parser *parser);

static ASTNode *parseLiteral(Parser *parser);

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

    while (nextToken(parser)->type != TOKEN_EOF)
    {
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
        if (strcmp(nextToken(parser)->text, "enum"))
        {
            free(tokens);
            free(children);
            return parseEnum(parser);
        }
        else if (strcmp(nextToken(parser)->text, "struct"))
        {
            free(tokens);
            free(children);
            return parseStruct(parser);
        }
        else if (strcmp(nextToken(parser)->text, "union"))
        {
            free(tokens);
            free(children);
            return parseUnion(parser);
        }

        //Handle const keyword
        if (strcmp(nextToken(parser)->text, "const"))
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

        children[childCount++] = parseParameterList(parser);

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
        if (strcmp(nextToken(parser)->text, "const"))
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

    while (nextToken(parser)->type == TOKEN_COMMA)
    {
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
            if (strcmp(nextToken(parser)->text, "const"))
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

    while (nextToken(parser)->type == TOKEN_COMMA)
    {
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
    if (nextToken(parser)->type == TOKEN_KEYWORD && strcmp(nextToken(parser)->text, "const"))
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

    while (nextToken(parser)->type == TOKEN_KEYWORD || nextToken(parser)->type == TOKEN_IDENTIFIER)
    {
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
        if (nextToken(parser)->type == TOKEN_KEYWORD && strcmp(nextToken(parser)->text, "const"))
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
    else if (nextToken(parser)->type == TOKEN_IDENTIFIER)
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        tokens[tokenCount++] = matchToken(parser, TOKEN_COLON);
        children[childCount++] = parseStatement(parser);

        return createASTNode(AST_LABELED_STATEMENT, tokens, tokenCount, children, childCount);
    }
    else if (nextToken(parser)->type == TOKEN_KEYWORD)
    {
        if(strcmp(nextToken(parser)->text, "return"))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
            children[childCount++] = parseExpressionStatement(parser);
            return createASTNode(AST_RETURN_STATEMENT, tokens, tokenCount, children, childCount);
        }
        else if (strcmp(nextToken(parser)->text, "break"))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
            tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
            return createASTNode(AST_BREAK_STATEMENT, tokens, tokenCount, children, childCount);
        }
        else if (strcmp(nextToken(parser)->text, "continue"))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
            tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
            return createASTNode(AST_CONTINUE_STATEMENT, tokens, tokenCount, children, childCount);
        }
        else if (strcmp(nextToken(parser)->text, "goto"))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
            tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
            tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
            return createASTNode(AST_GOTO_STATEMENT, tokens, tokenCount, children, childCount);
        }
        else if (strcmp(nextToken(parser)->text, "if"))
        {
            free(tokens);
            free(children);
            return parseIfStatement(parser);
        }
        else if (strcmp(nextToken(parser)->text, "switch"))
        {
            free(tokens);
            free(children);
            return parseSwitchStatement(parser);
        }
        else if (strcmp(nextToken(parser)->text, "for"))
        {
            free(tokens);
            free(children);
            return parseForStatement(parser);
        }
        else if (strcmp(nextToken(parser)->text, "while"))
        {
            free(tokens);
            free(children);
            return parseWhileStatement(parser);
        }
        else if (strcmp(nextToken(parser)->text, "do"))
        {
            free(tokens);
            free(children);
            return parseDoStatement(parser);
        }

        //Handle const keyword
        if (nextToken(parser)->type == TOKEN_KEYWORD && strcmp(nextToken(parser)->text, "const"))
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

    while (nextToken(parser)->type == TOKEN_KEYWORD && strcmp(nextToken(parser)->text, "case"))
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

        while (nextToken(parser)->type == TOKEN_KEYWORD && (strcmp(nextToken(parser)->text, "case") || strcmp(nextToken(parser)->text, "default")))
        {
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
        }
    }

    if (nextToken(parser)->type == TOKEN_KEYWORD && strcmp(nextToken(parser)->text, "default"))
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

        while (nextToken(parser)->type == TOKEN_KEYWORD && (strcmp(nextToken(parser)->text, "case") || strcmp(nextToken(parser)->text, "default")))
        {
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
        }
    }

    while (nextToken(parser)->type == TOKEN_KEYWORD && strcmp(nextToken(parser)->text, "case"))
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

        while (nextToken(parser)->type == TOKEN_KEYWORD && (strcmp(nextToken(parser)->text, "case") || strcmp(nextToken(parser)->text, "default")))
        {
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

    while (nextToken(parser)->type != TOKEN_CLOSE_CURLY)
    {
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

    fprintf(stderr, "Not implemented yet!\n");
    return NULL;
}

static ASTNode *parseBinaryExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    fprintf(stderr, "Not implemented yet!\n");
    return NULL;
}

static ASTNode *parseUnaryExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    fprintf(stderr, "Not implemented yet!\n");
    return NULL;
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

Parser *createParser(Token **const tokens, const size_t tokenCount)
{
    if (tokens == NULL)
    {
        fprintf(stderr, "Tokens is NULL!\n");
        return NULL;
    }

    Parser *parser = (Parser*)malloc(sizeof(Parser));
    if (parser == NULL)
    {
        fprintf(stderr, "Memory allocation for Parser failed!\n");
        return NULL;
    }

    parser->tokens = (Token**)malloc(tokenCount * sizeof(Token*));
    if (parser->tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for Parser->tokens failed!\n");
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
    
    parser->tokens = (Token**)realloc(parser->tokens, newCount * sizeof(Token*));
    if (parser->tokens == NULL)
    {
        fprintf(stderr, "Memory reallocation for Parser->tokens failed!\n");
        free(parser->tokens);
        return NULL;
    }

    parser->tokenCount = newCount;
    parser->position = 0;

    return parser;
}

void deleteParser(Parser *const parser)
{
    if (parser == NULL)
    {
        return;
    }

    free(parser->ASTroot);
    free(parser);
}

ASTNode *getCopyAST(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    return duplicateASTNode(parser->ASTroot);
}

//TODO:
void parse(Parser *parser)
{
    if(parser == NULL)
    {
        fprintf(stderr, "Parser is NULL!\n");
        return;
    }

    if (parser->ASTroot != NULL)
    {
        fprintf(stderr, "Already parsed the input tokens!\n");
        return;
    }

    parser->ASTroot = parseProgram(parser);
}

//TODO:
//Curently just prints out all the used tokens
void printParseTrees(const Parser *const parser)
{
    if(parser == NULL)
    {
        fprintf(stderr, "Parser is NULL!\n");
        exit(-1);
    }

    printf("Parser:\n");
    Token *tok = peekToken(parser, 0);
    printToken(tok);
    for (size_t i = 0; i < parser->tokenCount; i++)
    {
        printf("%d: ", i);
        printToken(parser->tokens[i]);
    }
    
}