#include "parser.h"

/*****************************************************************************************************
                            PRIVATE PARSER FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

static Token *nextToken(const Parser *const parser);

static void consumeToken(Parser *const parser, const size_t count);

static Token *matchToken(Parser *parser, TokenType type);

static int isNextTokenTypeOf(Parser *parser, TokenType type, int consumeOnSuccess);

static int isNextTokenKeywordWord(Parser *parser, Keywords keyword, int consumeOnSuccess);

static int addError(Parser *parser, Error *error);

static ASTNode *parseProgram(Parser *parser);

static int isGlobalDeclaration(Parser *parser, const int resetOnSuccess);

static ASTNode *parseGlobalDeclaration(Parser *parser);

static int isFunctionDefinition(Parser *parser, const int resetOnSuccess);

static ASTNode *parseFunctionDefinition(Parser *parser);

static int isDeclarationSpecifiers(Parser *parser, const int resetOnSuccess);

static ASTNode *parseDeclarationSpecifiers(Parser *parser);

static int isStorageClassSpecifier(Parser *parser, const int consumeOnSuccess);

static int isTypeSpecifier(Parser *parser, const int resetOnSuccess);

static ASTNode *parseTypeSpecifier(Parser *parser);

static int isStructOrUnionSpecifier(Parser *parser, const int resetOnSuccess);

static ASTNode *parseStructOrUnionSpecifier(Parser *parser);

static int isStructDeclaration(Parser *parser, const int resetOnSuccess);

static ASTNode *parseStructDeclaration(Parser *parser);

static int isSpecifierQualifier(Parser *parser, const int resetOnSuccess);

static ASTNode *parseSpecifierQualifier(Parser *parser);

static int isTypeQualifier(Parser *parser, const int consumeOnSuccess);

static int isStructDeclaratorList(Parser *parser, const int resetOnSuccess);

static ASTNode *parseStructDeclaratorList(Parser *parser);

static int isStructDeclarator(Parser *parser, const int resetOnSuccess);

static ASTNode *parseStructDeclarator(Parser *parser);

static int isDeclarator(Parser *parser, const int resetOnSuccess);

static ASTNode *parseDeclarator(Parser *parser);

static int isPointer(Parser *parser, const int resetOnSuccess);

static ASTNode *parsePointer(Parser *parser);

static int isDirectDeclarator(Parser *parser, const int resetOnSuccess);

static ASTNode *parseDirectDeclarator(Parser *parser);

static int isDirectDeclaratorPrime(Parser *parser, const int resetOnSuccess);

static ASTNode *parseDirectDeclaratorPrime(Parser *parser);

static int isAssignmentExpression(Parser *parser, const int resetOnSuccess);

static int isAssignmentOperator(Parser *parser, int consumeOnSuccess);

static ASTNode *parseAssignmentExpression(Parser *parser);

static int isConditionalExpression(Parser *parser, const int resetOnSuccess);

static ASTNode *parseConditionalExpression(Parser *parser);

static int isLogicalORExpression(Parser *parser, const int resetOnSuccess);

static ASTNode *parseLogicalORExpression(Parser *parser);

static int isLogicalANDExpression(Parser *parser, const int resetOnSuccess);

static ASTNode *parseLogicalANDExpression(Parser *parser);

static int isBitwiseORExpression(Parser *parser, const int resetOnSuccess);

static ASTNode *parseBitwiseORExpression(Parser *parser);

static int isBitwiseXORExpression(Parser *parser, const int resetOnSuccess);

static ASTNode *parseBitwiseXORExpression(Parser *parser);

static int isBitwiseANDExpression(Parser *parser, const int resetOnSuccess);

static ASTNode *parseBitwiseANDExpression(Parser *parser);

static int isEqualityExpression(Parser *parser, const int resetOnSuccess);

static int isEqualityOperator(Parser *parser, int consumeOnSuccess);

static ASTNode *parseEqualityExpression(Parser *parser);

static int isRelationalExpression(Parser *parser, const int resetOnSuccess);

static int isRelationalOperator(Parser *parser, int consumeOnSuccess);

static ASTNode *parseRelationalExpression(Parser *parser);

static int isShiftExpression(Parser *parser, const int resetOnSuccess);

static int isShiftOperator(Parser *parser, int consumeOnSuccess);

static ASTNode *parseShiftExpression(Parser *parser);

static int isAdditiveExpression(Parser *parser, const int resetOnSuccess);

static int isAdditiveOperator(Parser *parser, int consumeOnSuccess);

static ASTNode *parseAdditiveExpression(Parser *parser);

static int isMultiplicativeExpression(Parser *parser, const int resetOnSuccess);

static int isMultiplicativeOperator(Parser *parser, int consumeOnSuccess);

static ASTNode *parserMultiplicativeExpression(Parser *parser);

static int isCastExpression(Parser *parser, const int resetOnSuccess);

static ASTNode *parseCastExpression(Parser *parser);

static int isUnaryExpression(Parser *parser, const int resetOnSuccess);

static int isPrefixUnaryOperator(Parser *parser, int consumeOnSuccess);

static int isUnaryOperator(Parser *parser, int consumeOnSuccess);

static ASTNode *parseUnaryExpression(Parser *parser);

static int isPostfixExpression(Parser *parser, const int resetOnSuccess);

static ASTNode *parsePostfixExpression(Parser *parser);

static int isPostfixExpressionPrime(Parser *parser, const int resetOnSuccess);

static ASTNode *parsePostfixExpressionPrime(Parser *parser);

static int isPrimaryExpression(Parser *parser, const int resetOnSuccess);

static ASTNode *parsePrimaryExpression(Parser *parser);

static int isLiteral(Parser *parser, const int resetOnSuccess);

static ASTNode *parseLiteral(Parser *parser);

static int isExpression(Parser *parser, const int resetOnSuccess);

static ASTNode *parseExpression(Parser *parser);

static int isTypeName(Parser *parser, const int resetOnSuccess);

static ASTNode *parseTypeName(Parser *parser);

static int isAbstractDeclarator(Parser *parser, const int resetOnSuccess);

static ASTNode *parseAbstractDeclarator(Parser *parser);

static int isDirectAbstractDeclarator(Parser *parser, const int resetOnSuccess);

static ASTNode *parseDirectAbstractDeclarator(Parser *parser);

static int isDirectAbstractDeclaratorPrime(Parser *parser, const int resetOnSuccess);

static ASTNode *parseDirectAbstractDeclaratorPrime(Parser *parser);

static int isParameterList(Parser *parser, const int resetOnSuccess);

static ASTNode *parseParameterList(Parser *parser);

static int isParameterDeclaration(Parser *parser, const int resetOnSuccess);

static ASTNode *parseParameterDeclaration(Parser *parser);

static int isInitializerList(Parser *parser, const int resetOnSuccess);

static ASTNode *parseInitializerList(Parser *parser);

static int isDesignation(Parser *parser, const int resetOnSuccess);

static ASTNode *parseDesignation(Parser *parser);

static int isDesignator(Parser *parser, const int resetOnSucces);

static ASTNode *parseDesignator(Parser *parser);

static int isConstantExpression(Parser *parser, const int resetOnSuccess);

static ASTNode *parseConstantExpression(Parser *parser);

static int isInitializer(Parser *parser, const int resetOnSuccess);

static ASTNode *parseInitializer(Parser *parser);

static int isIdentifierList(Parser *parser, const int resetOnSuccess);

static ASTNode *parseIdentifierList(Parser *parser);

static int isEnumSpecifier(Parser *parser, const int resetOnSuccess);

static ASTNode *parseEnumSpecifier(Parser *parser);

static int isEnumeratorList(Parser *parser, const int resetOnSuccess);

static ASTNode *parseEnumeratorList(Parser *parser);

static int isEnumerator(Parser *parser, const int resetOnSuccess);

static ASTNode *parseEnumerator(Parser *parser);

static int isDeclaration(Parser *parser, const int resetOnSuccess);

static ASTNode *parseDeclaration(Parser *parser);

static int isInitDeclaratorList(Parser *parser, const int resetOnSuccess);

static ASTNode *parseInitDeclaratorList(Parser *parser);

static int isInitDeclarator(Parser *parser, const int resetOnSuccess);

static ASTNode *parseInitDeclarator(Parser *parser);

static int isStatement(Parser *parser, const int resetOnSuccess);

static ASTNode *parseStatement(Parser *parser);

static int isLabeledStatement(Parser *parser, const int resetOnSuccess);

static ASTNode *parseLabeledStatement(Parser *parser);

static int isCompoundStatement(Parser *parser, const int resetOnSuccess);

static ASTNode *parseCompoundStatement(Parser *parser);

static int isExpressionStatement(Parser *parser, const int resetOnSuccess);

static ASTNode *parseExpressionStatement(Parser *parser);

static int isSelectionStatement(Parser *parser, const int resetOnSuccess);

static ASTNode *parseSelectionStatement(Parser *parser);

static int isIterationStatement(Parser *parser, const int resetOnSucces);

static ASTNode *parseIterationStatement(Parser *parser);

static int isForControl(Parser *parser, const int resetOnSuccess);

static ASTNode *parseForControl(Parser *parser);

static int isJumpStatement(Parser *parser, const int resetOnSuccess);

static ASTNode *parseJumpStatement(Parser *parser);

/*****************************************************************************************************
                                PRIVATE PARSER FUNCTIONS START HERE
 *****************************************************************************************************/

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
    if(parser == NULL)
    {
        fprintf(stderr, "Parser is NULL!\n");
        return NULL;
    }

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
    Token *token = createTokenNone(text, nextToken(parser)->start ,TOKEN_UNKNOWN);

    addError(parser, createError(ERROR_PARSING, "Wrong token!", token));
    return token;
}

static int isNextTokenTypeOf(Parser *parser, TokenType type, int consumeOnSuccess)
{
    if(parser == NULL)
    {
        fprintf(stderr, "Parser is NULL!\n");
        return 0;
    }

    if (nextToken(parser)->type == type)
    {
        if (consumeOnSuccess)
        {
            consumeToken(parser, 1);
        }
        return 1;
    }

    return 0;
}

static int isNextTokenKeywordWord(Parser *parser, Keywords keyword, int consumeOnSuccess)
{
    if(parser == NULL)
    {
        fprintf(stderr, "Parser is NULL!\n");
        return 0;
    }

    if (nextToken(parser)->type == TOKEN_KEYWORD && nextToken(parser)->value.keyword == keyword)
    {
        if (consumeOnSuccess)
        {
            consumeToken(parser, 1);
        }
        return 1;
    }

    return 0;
}

/**
 * Adds an `Error` object to the `Parser`'s error list.
 * 
 * This function appends a new error to the `Parser`'s list of errors. If the internal
 * error storage array is full, it will be dynamically resized to accommodate additional
 * errors. The function ensures that the error list is properly maintained and expanded 
 * as needed.
 * 
 * @param parser Pointer to the `Parser` object that maintains the list of errors. 
 *               The `Parser` must be initialized before being passed to this function.
 * 
 * @param error  Pointer to the `Error` object to be added to the list. 
 *               The `Error` object must be valid and properly initialized.
 * 
 * @return 1 if the error was successfully added to the list; 0 if there was a problem 
 *         (e.g., if the `parser` or `error` is NULL, or if memory allocation fails).
 * 
 * @note If memory needs to be reallocated for the error list and the reallocation fails, 
 *       the function reports the error and returns 0. It is the caller's responsibility to 
 *       ensure that the `Error` objects are managed and freed appropriately.
 */
static int addError(Parser *parser, Error *error)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    if (error == NULL)
    {
        fprintf(stderr, "Error is not initialized.\n");
        return 0;
    }

    if (parser->errorCount + 1 >= parser->errorsSize)
    {
        parser->errorsSize *= 2;
        Error **newErrors = realloc(parser->errors, parser->errorsSize * sizeof(Error *));
        if (newErrors == NULL)
        {
            fprintf(stderr, "Memory reallocation for Errors failed!\n");
            return 0;
        }
        parser->errors = newErrors;
    }

    parser->errors[parser->errorCount++] = error;
    return 1;
}

static ASTNode *parseProgram(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    while (isGlobalDeclaration(parser, 1))
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

        children[childCount++] = parseGlobalDeclaration(parser);
    }

    tokens[tokenCount++] = matchToken(parser, TOKEN_EOF);
    return createASTNode(AST_PROGRAM, tokens, tokenCount, children, childCount);
}

static int isGlobalDeclaration(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isFunctionDefinition(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }
    else if (isDeclaration(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseGlobalDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isGlobalDeclaration(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Global Declaration but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Parsing
    if (isFunctionDefinition(parser, 1))
    {
        return parseFunctionDefinition(parser);
    }
    else if (isDeclaration(parser, 1))
    {
        return parseDeclaration(parser);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Global Declaration but found:", duplicateToken(nextToken(parser))));
    return NULL;
}

static int isFunctionDefinition(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isDeclarationSpecifiers(parser, 0))
    {
        if (isDeclarator(parser, 0))
        {
            while (isDeclaration(parser, 0));

            if (isCompoundStatement(parser, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseFunctionDefinition(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isFunctionDefinition(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Function Definition but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 3;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isDeclarationSpecifiers(parser, 0))
    {
        children[childCount++] = parseDeclarationSpecifiers(parser);
        children[childCount++] = parseDeclarator(parser);

        while (isDeclaration(parser, 0))
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

            children[childCount++] = parseDeclaration(parser);
        }

        children[childCount++] = parseCompoundStatement(parser);

        return createASTNode(AST_FUNCTION_DEFINITION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Function Definition but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isDeclarationSpecifiers(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isStorageClassSpecifier(parser, 1))
    { }
    else if (isSpecifierQualifier(parser, 0))
    { }
    else if (isNextTokenKeywordWord(parser, KEYWORD_INLINE, 1))
    { }
    else
    {
        parser->position = lookaheadPosition;
        return 0;
    }

    while (isStorageClassSpecifier(parser, 1) || isSpecifierQualifier(parser, 0) || isNextTokenKeywordWord(parser, KEYWORD_INLINE, 1));

    if (resetOnSuccess)
    {
        parser->position = lookaheadPosition;
    }
    return 1;
}

static ASTNode *parseDeclarationSpecifiers(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isDeclarationSpecifiers(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected Declaration Specifiers but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isStorageClassSpecifier(parser, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
    }
    else if (isSpecifierQualifier(parser, 1))
    {
        children[childCount++] = parseSpecifierQualifier(parser);
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_INLINE, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
    }
    else
    {
        //Error
        addError(parser, createError(ERROR_PARSING, "Expected Declaration Specifiers but found:", duplicateToken(nextToken(parser))));
        free(tokens);
        free(children);
        return NULL;
    }
    
    while (isStorageClassSpecifier(parser, 0) || isSpecifierQualifier(parser, 1) || isNextTokenKeywordWord(parser, KEYWORD_INLINE, 0))
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
        if (tokenCount + 1 >= tokensSize)
        {
            tokensSize *= 2;
            Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
            if (newTokens == NULL)
            {
                fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                free(tokens);
                free(children);
                return NULL;
            }
            tokens = newTokens;
        }

        if (isStorageClassSpecifier(parser, 0) || isNextTokenKeywordWord(parser, KEYWORD_INLINE, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        }
        else if (isSpecifierQualifier(parser, 1))
        {
            children[childCount++] = parseSpecifierQualifier(parser);
        }
    }

    return createASTNode(AST_DECLARATION_SPECIFIERS, tokens, tokenCount, children, childCount);
}

static int isStorageClassSpecifier(Parser *parser, const int consumeOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    if (isNextTokenTypeOf(parser, TOKEN_KEYWORD, 0))
    {
        switch (nextToken(parser)->value.keyword)
        {
        case KEYWORD_TYPEDEF:
        case KEYWORD_EXTERN:
        case KEYWORD_STATIC:
        case KEYWORD_AUTO:
        case KEYWORD_REGISTER:
            if (consumeOnSuccess)
            {
                consumeToken(parser, 1);
            }
            return 1;
        default:
            break;
        }
    }

    return 0;
}

static int isTypeSpecifier(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isStructOrUnionSpecifier(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }
    else if (isEnumSpecifier(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }
    else if (isNextTokenTypeOf(parser, TOKEN_KEYWORD, 0))
    {
        switch (nextToken(parser)->value.keyword)
        {
        case KEYWORD_VOID:
        case KEYWORD_CHAR:
        case KEYWORD_SHORT:
        case KEYWORD_INT:
        case KEYWORD_LONG:
        case KEYWORD_FLOAT:
        case KEYWORD_DOUBLE:
        case KEYWORD_SIGNED:
        case KEYWORD_UNSIGNED:
        case KEYWORD_STRING:
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            else
            {
                consumeToken(parser, 1);
            }
            return 1;
        default:
            break;
        }
    }
    else
    {
        if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 0) && !isDeclarator(parser, 0))
        {
            consumeToken(parser, 1);
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseTypeSpecifier(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isTypeSpecifier(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Type Specifier but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isStructOrUnionSpecifier(parser, 1))
    {
        children[childCount++] = parseStructOrUnionSpecifier(parser);
        return createASTNode(AST_TYPE_SPECIFIER, tokens, tokenCount, children, childCount);
    }
    else if (isEnumSpecifier(parser , 1))
    {
        children[childCount++] = parseEnumSpecifier(parser);
        return createASTNode(AST_TYPE_SPECIFIER, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        return createASTNode(AST_TYPE_SPECIFIER, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenTypeOf(parser, TOKEN_KEYWORD, 0))
    {
        switch (nextToken(parser)->value.keyword)
        {
        case KEYWORD_VOID:
        case KEYWORD_CHAR:
        case KEYWORD_SHORT:
        case KEYWORD_INT:
        case KEYWORD_LONG:
        case KEYWORD_FLOAT:
        case KEYWORD_DOUBLE:
        case KEYWORD_SIGNED:
        case KEYWORD_UNSIGNED:
        case KEYWORD_STRING:
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
            return createASTNode(AST_TYPE_SPECIFIER, tokens, tokenCount, children, childCount);
        default:
            break;
        }
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Type Specifier but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isStructOrUnionSpecifier(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenKeywordWord(parser, KEYWORD_STRUCT, 1) || isNextTokenKeywordWord(parser, KEYWORD_UNION, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 1))
        {
            if (!isNextTokenTypeOf(parser, TOKEN_OPEN_CURLY, 0))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }

        if (isNextTokenTypeOf(parser, TOKEN_OPEN_CURLY, 1))
        {
            if (isStructDeclaration(parser, 0))
            {
                while (isStructDeclaration(parser, 0));

                if (isNextTokenTypeOf(parser, TOKEN_CLOSE_CURLY, 1))
                {
                    if (resetOnSuccess)
                    {
                        parser->position = lookaheadPosition;
                    }
                    return 1;
                }
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseStructOrUnionSpecifier(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isStructOrUnionSpecifier(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Struct or Union Specifier but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 4;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenKeywordWord(parser, KEYWORD_STRUCT, 0) || isNextTokenKeywordWord(parser, KEYWORD_UNION, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
            if (!isNextTokenTypeOf(parser, TOKEN_OPEN_CURLY, 0))
            {
                printf("Here\n");
                return createASTNode(AST_STRUCT_OR_UNION_SPECIFIER, tokens, tokenCount, children, childCount);
            }
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_CURLY);
        children[childCount++] = parseStructDeclaration(parser);

        while (isStructDeclaration(parser, 1))
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

            children[childCount++] = parseStructDeclaration(parser);
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_CURLY);
        return createASTNode(AST_STRUCT_OR_UNION_SPECIFIER, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Struct or Union Specifier but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isStructDeclaration(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isSpecifierQualifier(parser, 0))
    {
        while (isSpecifierQualifier(parser, 0));

        if (isStructDeclaratorList(parser, 0))
        {
            if (isNextTokenTypeOf(parser, TOKEN_SEMICOLON, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseStructDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isStructDeclaration(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Struct Declaration but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isSpecifierQualifier(parser, 1))
    {
        children[childCount++] = parseSpecifierQualifier(parser);

        while (isSpecifierQualifier(parser, 1))
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

            children[childCount++] = parseSpecifierQualifier(parser);
        }

        if (isStructDeclaratorList(parser, 1))
        {
            children[childCount++] = parseStructDeclaratorList(parser);
            tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
            return createASTNode(AST_STRUCT_DECLARATION, tokens, tokenCount, children, childCount);
        }
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Struct Declaration but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isSpecifierQualifier(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isTypeSpecifier(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    if (isTypeQualifier(parser, 1))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseSpecifierQualifier(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isSpecifierQualifier(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Specifier Qualifier but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isTypeSpecifier(parser, 1))
    {
        children[childCount++] = parseTypeSpecifier(parser);
        return createASTNode(AST_SPECIFIER_QUALIFIER, tokens, tokenCount, children, childCount);
    }
    else if (isTypeQualifier(parser, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        return createASTNode(AST_SPECIFIER_QUALIFIER, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Specifier Qualifier but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isTypeQualifier(Parser *parser, const int consumeOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    if (isNextTokenKeywordWord(parser, KEYWORD_CONST, consumeOnSuccess))
    {
        return 1;
    }

    if (isNextTokenKeywordWord(parser, KEYWORD_RESTRICT, consumeOnSuccess))
    {
        return 1;
    }

    if (isNextTokenKeywordWord(parser, KEYWORD_VOLATILE, consumeOnSuccess))
    {
        return 1;
    }

    return 0;
}

static int isStructDeclaratorList(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isStructDeclarator(parser, 0))
    {
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 1))
        {
            if (!isStructDeclarator(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseStructDeclaratorList(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isStructDeclaratorList(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Struct Declarator List but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    while (isStructDeclarator(parser, 1))
    {
        children[childCount++] = parseStructDeclarator(parser);
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 1))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);
            children[childCount++] = parseStructDeclarator(parser);
        }

        return createASTNode(AST_STRUCT_DECLARATOR_LIST, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Struct Declarator List but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isStructDeclarator(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isDeclarator(parser, 0))
    {
        if (isNextTokenTypeOf(parser, TOKEN_COLON, 1))
        {
            if (isConstantExpression(parser, 0))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }

            parser->position = lookaheadPosition;
            return 0;
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseStructDeclarator(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isStructDeclarator(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Struct Declarator but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isDeclarator(parser, 1))
    {
        children[childCount++] = parseDeclarator(parser);
        if (isNextTokenTypeOf(parser, TOKEN_COLON, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_COLON);
            children[childCount++] = parseConstantExpression(parser);
            return createASTNode(AST_STRUCT_DECLARATOR, tokens, tokenCount, children, childCount);
        }

        return createASTNode(AST_STRUCT_DECLARATOR, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Struct Declarator but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isDeclarator(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    isPointer(parser, 0);

    if (isDirectDeclarator(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseDeclarator(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isDeclarator(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Declarator but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isPointer(parser, 1))
    {
        children[childCount++] = parsePointer(parser);
    }

    if (isDirectDeclarator(parser, 1))
    {
        children[childCount++] = parseDirectDeclarator(parser);
        return createASTNode(AST_DECLARATOR, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Declarator but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isPointer(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenTypeOf(parser, TOKEN_STAR, 1))
    {
        while (isTypeQualifier(parser, 1));

        while (isNextTokenTypeOf(parser, TOKEN_STAR, 1))
        {
            while (isTypeQualifier(parser, 1));
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parsePointer(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isPointer(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Pointer but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenTypeOf(parser, TOKEN_STAR, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_STAR);
        while (isTypeQualifier(parser, 0))
        {
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
        }

        while (isNextTokenTypeOf(parser, TOKEN_STAR, 0))
        {
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, TOKEN_STAR);
            while (isTypeQualifier(parser, 0))
            {
                if (tokenCount + 1 >= tokensSize)
                {
                    tokensSize *= 2;
                    Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                    if (newTokens == NULL)
                    {
                        fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                        free(tokens);
                        free(children);
                        return NULL;
                    }
                    tokens = newTokens;
                }

                tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
            }
        }

        return createASTNode(AST_POINTER, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Pointer but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isDirectDeclarator(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 1))
    {
        while (isDirectDeclaratorPrime(parser, 0));

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))
    {
        if (isDeclarator(parser, 0))
        {
            if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
            {
                while (isDirectDeclaratorPrime(parser, 0));

                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseDirectDeclarator(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isDirectDeclarator(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Direct Declarator but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        while (isDirectDeclaratorPrime(parser, 1))
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

            children[childCount++] = parseDirectDeclaratorPrime(parser);
        }

        return createASTNode(AST_DIRECT_DECLARATOR, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        children[childCount++] = parseDeclarator(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        while (isDirectDeclaratorPrime(parser, 1))
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

            children[childCount++] = parseDirectDeclaratorPrime(parser);
        }

        return createASTNode(AST_DIRECT_DECLARATOR, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Direct Declarator but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isDirectDeclaratorPrime(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenTypeOf(parser, TOKEN_OPEN_BRACKET, 1))
    {
        if (isNextTokenKeywordWord(parser, KEYWORD_STATIC, 1))
        {
            while (isTypeQualifier(parser, 1));

            if (isAssignmentExpression(parser, 0))
            {
                if (isNextTokenTypeOf(parser, TOKEN_CLOSE_BRACKET, 1))
                {
                    if (resetOnSuccess)
                    {
                        parser->position = lookaheadPosition;
                    }
                    return 1;
                }
            }

            parser->position = lookaheadPosition;
            return 0;
        }

        if (isTypeQualifier(parser, 1))
        {
            while (isTypeQualifier(parser, 1));

            if (isNextTokenKeywordWord(parser, KEYWORD_STATIC, 1))
            {
                if (isAssignmentExpression(parser, 0))
                {
                    if (isNextTokenTypeOf(parser, TOKEN_CLOSE_BRACKET, 1))
                    {
                        if (resetOnSuccess)
                        {
                            parser->position = lookaheadPosition;
                        }
                        return 1;
                    }
                }

                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (isNextTokenTypeOf(parser, TOKEN_STAR, 1))
        {
            if (isNextTokenTypeOf(parser, TOKEN_CLOSE_BRACKET, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }

            parser->position = lookaheadPosition;
            return 0;
        }

        isAssignmentExpression(parser, 0);

        if (isNextTokenTypeOf(parser, TOKEN_CLOSE_BRACKET, 1))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))
    {
        if (isParameterList(parser, 0))
        {
            if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
        else
        {
            isIdentifierList(parser, 0);

            if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseDirectDeclaratorPrime(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isDirectDeclaratorPrime(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Direct Declarator Prime but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 4;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenTypeOf(parser, TOKEN_OPEN_BRACKET, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_BRACKET);
        if (isNextTokenKeywordWord(parser, KEYWORD_STATIC, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);

            while (isTypeQualifier(parser, 0))
            {
                if (tokenCount + 2 >= tokensSize)
                {
                    tokensSize *= 2;
                    Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                    if (newTokens == NULL)
                    {
                        fprintf(stderr, "Memory reallocation for tokens failed!\n");
                        free(tokens);
                        free(children);
                        return NULL;
                    }
                    tokens = newTokens;
                }
                
                tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
            }

            children[childCount++] = parseAssignmentExpression(parser);
            tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_BRACKET);
            return createASTNode(AST_DIRECT_DECLARATOR_PRIME, tokens, tokenCount, children, childCount);
        }
        
        if (isTypeQualifier(parser, 0))
        {
            tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);

            while (isTypeQualifier(parser, 0))
            {
                if (tokenCount + 2 >= tokensSize)
                {
                    tokensSize *= 2;
                    Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                    if (newTokens == NULL)
                    {
                        fprintf(stderr, "Memory reallocation for tokens failed!\n");
                        free(tokens);
                        free(children);
                        return NULL;
                    }
                    tokens = newTokens;
                }
                
                tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
            }

            if (isNextTokenKeywordWord(parser, KEYWORD_STATIC, 0))
            {
                tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
                children[childCount++] = parseAssignmentExpression(parser);
                tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_BRACKET);
                return createASTNode(AST_DIRECT_DECLARATOR_PRIME, tokens, tokenCount, children, childCount);
            }
        }

        if (isNextTokenTypeOf(parser, TOKEN_STAR, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_STAR);
            tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_BRACKET);
            return createASTNode(AST_DIRECT_DECLARATOR_PRIME, tokens, tokenCount, children, childCount);
        }
        
        if (isAssignmentExpression(parser, 1))
        {
            children[childCount++] = parseAssignmentExpression(parser);
        }

        if (isNextTokenTypeOf(parser, TOKEN_CLOSE_BRACKET, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_BRACKET);
            return createASTNode(AST_DIRECT_DECLARATOR_PRIME, tokens, tokenCount, children, childCount);
        }
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        if (isParameterList(parser, 1))
        {
            children[childCount++] = parseParameterList(parser);
            tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
            return createASTNode(AST_DIRECT_DECLARATOR_PRIME, tokens, tokenCount, children, childCount);
        }
        
        if (isIdentifierList(parser, 1))
        {
            children[childCount++] = parseIdentifierList(parser);
        }
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        return createASTNode(AST_DIRECT_DECLARATOR_PRIME, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Direct Declarator Prime but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isAssignmentExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isUnaryExpression(parser, 0))
    {
        if (isAssignmentOperator(parser, 1))
        {
            if (isAssignmentExpression(parser, 0))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }

            parser->position = lookaheadPosition;
            return 0;
        }
        else 
        {
            parser->position = lookaheadPosition;
        }
    }

    if (isConditionalExpression(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static int isAssignmentOperator(Parser *parser, int consumeOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    switch (nextToken(parser)->type)
    {
    case TOKEN_EQUALS:
    case TOKEN_STAR_EQUALS:
    case TOKEN_SLASH_EQUALS:
    case TOKEN_PERCENT_EQUALS:
    case TOKEN_PLUS_EQUALS:
    case TOKEN_MINUS_EQUALS:
    case TOKEN_BITWISE_LEFT_SHIFT_EQUALS:
    case TOKEN_BITWISE_RIGHT_SHIFT_EQUALS:
    case TOKEN_BITWISE_AND_EQUALS:
    case TOKEN_BITWISE_XOR_EQUALS:
    case TOKEN_BITWISE_OR_EQUALS:
        if (consumeOnSuccess)
        {
            consumeToken(parser, 1);
        }
        return 1;
    default:
        return 0;
    }
}

static ASTNode *parseAssignmentExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isAssignmentExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Assignment Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    int lookaheadPosition = parser->position;
    if (isUnaryExpression(parser, 0))
    {
        if (isAssignmentOperator(parser, 0))
        {
            parser->position = lookaheadPosition;
            children[childCount++] = parseUnaryExpression(parser);
            tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
            children[childCount++] = parseAssignmentExpression(parser);
            return createASTNode(AST_ASSIGNMENT_EXPRESSION, tokens, tokenCount, children, childCount);
        }
    }
    parser->position = lookaheadPosition;

    if (isConditionalExpression(parser, 1))
    {
        free(tokens);
        free(children);
        return parseConditionalExpression(parser);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Assignment Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isConditionalExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isLogicalORExpression(parser, 0))
    {
        if (isNextTokenTypeOf(parser, TOKEN_QUESTION_MARK, 1))
        {
            if (isExpression(parser, 0))
            {
                if (isNextTokenTypeOf(parser, TOKEN_COLON, 1))
                {
                    if (isConditionalExpression(parser, 0))
                    {
                        if (resetOnSuccess)
                        {
                            parser->position = lookaheadPosition;
                        }
                        return 1;
                    }
                }    
            }

            parser->position = lookaheadPosition;
            return 0;
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseConditionalExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isConditionalExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Conditional Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 3;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isLogicalORExpression(parser, 1))
    {
        ASTNode *child = parseLogicalORExpression(parser);
        if (!isNextTokenTypeOf(parser, TOKEN_QUESTION_MARK, 0))
        {
            free(tokens);
            free(children);
            return child;
        }

        children[childCount++] = child;
        tokens[tokenCount++] = matchToken(parser, TOKEN_QUESTION_MARK);
        children[childCount++] = parseExpression(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_COLON);
        children[childCount++] = parseConditionalExpression(parser);
        return createASTNode(AST_CONDITIONAL_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Conditional Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isLogicalORExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isLogicalANDExpression(parser, 0))
    {
        while (isNextTokenTypeOf(parser, TOKEN_OR, 1))
        {
            if (!isLogicalANDExpression(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseLogicalORExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isLogicalORExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Logical OR Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isLogicalANDExpression(parser, 1))
    {
        ASTNode *child = parseLogicalANDExpression(parser);
        if (!isNextTokenTypeOf(parser, TOKEN_OR, 0))
        {
            free(tokens);
            free(children);
            return child;
        }

        children[childCount++] = child;
        while (isNextTokenTypeOf(parser, TOKEN_OR, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, TOKEN_OR);
            children[childCount++] = parseLogicalANDExpression(parser);
        }

        return createASTNode(AST_LOGICAL_OR_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Logical OR Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isLogicalANDExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isBitwiseORExpression(parser, 0))
    {
        while (isNextTokenTypeOf(parser, TOKEN_AND, 1))
        {
            if (!isBitwiseORExpression(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseLogicalANDExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isLogicalANDExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Logical AND Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isBitwiseORExpression(parser, 1))
    {
        ASTNode *child = parseBitwiseORExpression(parser);
        if (!isNextTokenTypeOf(parser, TOKEN_AND, 0))
        {
            free(tokens);
            free(children);
            return child;
        }

        children[childCount++] = child;
        while (isNextTokenTypeOf(parser, TOKEN_AND, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, TOKEN_AND);
            children[childCount++] = parseBitwiseORExpression(parser);
        }

        return createASTNode(AST_LOGICAL_AND_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Logical AND Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isBitwiseORExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isBitwiseXORExpression(parser, 0))
    {
        while (isNextTokenTypeOf(parser, TOKEN_BITWISE_OR, 1))
        {
            if (!isBitwiseXORExpression(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseBitwiseORExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isBitwiseORExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Bitwise OR Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isBitwiseXORExpression(parser, 1))
    {
        ASTNode *child = parseBitwiseXORExpression(parser);
        if (!isNextTokenTypeOf(parser, TOKEN_BITWISE_OR, 0))
        {
            free(tokens);
            free(children);
            return child;
        }

        children[childCount++] = child;
        while (isNextTokenTypeOf(parser, TOKEN_BITWISE_OR, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, TOKEN_BITWISE_OR);
            children[childCount++] = parseBitwiseXORExpression(parser);
        }

        return createASTNode(AST_BITWISE_OR_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Bitwise OR Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isBitwiseXORExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isBitwiseANDExpression(parser, 0))
    {
        while (isNextTokenTypeOf(parser, TOKEN_BITWISE_XOR, 1))
        {
            if (!isBitwiseANDExpression(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseBitwiseXORExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isBitwiseXORExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Bitwise XOR Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isBitwiseANDExpression(parser, 1))
    {
        ASTNode *child = parseBitwiseANDExpression(parser);
        if (!isNextTokenTypeOf(parser, TOKEN_BITWISE_XOR, 0))
        {
            free(tokens);
            free(children);
            return child;
        }

        children[childCount++] = child;
        while (isNextTokenTypeOf(parser, TOKEN_BITWISE_XOR, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, TOKEN_BITWISE_XOR);
            children[childCount++] = parseBitwiseANDExpression(parser);
        }

        return createASTNode(AST_BITWISE_XOR_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Bitwise XOR Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isBitwiseANDExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isEqualityExpression(parser, 0))
    {
        while (isNextTokenTypeOf(parser, TOKEN_BITWISE_AND, 1))
        {
            if (!isEqualityExpression(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseBitwiseANDExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isBitwiseANDExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Bitwise AND Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isEqualityExpression(parser, 1))
    {
        ASTNode *child = parseEqualityExpression(parser);
        if (!isNextTokenTypeOf(parser, TOKEN_BITWISE_AND, 0))
        {
            free(tokens);
            free(children);
            return child;
        }

        children[childCount++] = child;
        while (isNextTokenTypeOf(parser, TOKEN_BITWISE_AND, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, TOKEN_BITWISE_AND);
            children[childCount++] = parseEqualityExpression(parser);
        }

        return createASTNode(AST_BITWISE_AND_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Bitwise AND Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isEqualityExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isRelationalExpression(parser, 0))
    {
        while (isEqualityOperator(parser, 1))
        {
            if (!isRelationalExpression(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static int isEqualityOperator(Parser *parser, int consumeOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    switch (nextToken(parser)->type)
    {
    case TOKEN_DOUBLE_EQUALS:
    case TOKEN_NOT_EQUALS:
        if (consumeOnSuccess)
        {
            consumeToken(parser, 1);
        }
        return 1;
    default:
        return 0;
    }
}

static ASTNode *parseEqualityExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isEqualityExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Equality Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isRelationalExpression(parser, 1))
    {
        ASTNode *child = parseRelationalExpression(parser);
        if (!isEqualityOperator(parser, 0))
        {
            free(tokens);
            free(children);
            return child;
        }

        children[childCount++] = child;
        while (isEqualityOperator(parser, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
            children[childCount++] = parseRelationalExpression(parser);
        }

        return createASTNode(AST_EQUALITY_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Equality Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isRelationalExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isShiftExpression(parser, 0))
    {
        while (isRelationalOperator(parser, 1))
        {
            if (!isShiftExpression(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static int isRelationalOperator(Parser *parser, int consumeOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    switch (nextToken(parser)->type)
    {
    case TOKEN_LESS_THAN:
    case TOKEN_LESS_THAN_OR_EQUALS:
    case TOKEN_GREATER_THAN:
    case TOKEN_GREATER_THAN_OR_EQUALS:
        if (consumeOnSuccess)
        {
            consumeToken(parser, 1);
        }
        return 1;
    default:
        return 0;
    }
}

static ASTNode *parseRelationalExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isRelationalExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Relational Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isShiftExpression(parser, 1))
    {
        ASTNode *child = parseShiftExpression(parser);
        if (!isRelationalOperator(parser, 0))
        {
            free(tokens);
            free(children);
            return child;
        }

        children[childCount++] = child;
        while(isRelationalOperator(parser, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
            children[childCount++] = parseShiftExpression(parser);
        }

        return createASTNode(AST_RELATIONAL_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Relational Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isShiftExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isAdditiveExpression(parser, 0))
    {
        while (isShiftOperator(parser, 1))
        {
            if (!isAdditiveExpression(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static int isShiftOperator(Parser *parser, int consumeOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    switch (nextToken(parser)->type)
    {
    case TOKEN_BITWISE_LEFT_SHIFT:
    case TOKEN_BITWISE_RIGHT_SHIFT:
        if (consumeOnSuccess)
        {
            consumeToken(parser, 1);
        }
        return 1;
    default:
        return 0;
    }
}

static ASTNode *parseShiftExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isShiftExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Shift Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isAdditiveExpression(parser, 1))
    {
        ASTNode *child = parseAdditiveExpression(parser);
        if (!isShiftOperator(parser, 0))
        {
            free(tokens);
            free(children);
            return child;
        }

        children[childCount++] = child;
        while (isShiftOperator(parser, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
            children[childCount++] = parseAdditiveExpression(parser);
        }

        return createASTNode(AST_SHIFT_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Shift Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isAdditiveExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isMultiplicativeExpression(parser, 0))
    {
        while (isAdditiveOperator(parser, 1))
        {
            if (!isMultiplicativeExpression(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }
        
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static int isAdditiveOperator(Parser *parser, int consumeOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    switch (nextToken(parser)->type)
    {
    case TOKEN_PLUS:
    case TOKEN_MINUS:
        if (consumeOnSuccess)
        {
            consumeToken(parser, 1);
        }
        return 1;
    default:
        return 0;
    }
}

static ASTNode *parseAdditiveExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isAdditiveExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Additive Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isMultiplicativeExpression(parser, 1))
    {
        ASTNode *child = parserMultiplicativeExpression(parser);
        if (!isAdditiveOperator(parser, 0))
        {
            free(tokens);
            free(children);
            return child;
        }

        children[childCount++] = child;
        while (isAdditiveOperator(parser, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
            children[childCount++] = parserMultiplicativeExpression(parser);
        }

        return createASTNode(AST_ADDITIVE_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Additive Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isMultiplicativeExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isCastExpression(parser, 0))
    {
        while (isMultiplicativeOperator(parser, 1))
        {
            if (!isCastExpression(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }
        
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static int isMultiplicativeOperator(Parser *parser, int consumeOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    switch (nextToken(parser)->type)
    {
    case TOKEN_STAR:
    case TOKEN_SLASH:
    case TOKEN_PERCENT:
        if (consumeOnSuccess)
        {
            consumeToken(parser, 1);
        }
        return 1;
    default:
        return 0;
    }
}

static ASTNode *parserMultiplicativeExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isMultiplicativeExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Multiplicative Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isCastExpression(parser, 1))
    {
        ASTNode *child = parseCastExpression(parser);
        if (!isMultiplicativeOperator(parser, 0))
        {
            free(tokens);
            free(children);
            return child;
        }

        children[childCount++] = child;
        while (isMultiplicativeOperator(parser, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
            children[childCount++] = parseCastExpression(parser);
        }

        return createASTNode(AST_MULTIPLICATIVE_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Multiplicative Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isCastExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isUnaryExpression(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))
    {
        if (isTypeName(parser, 0))
        {
            if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseCastExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isCastExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Cast Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isUnaryExpression(parser, 1))
    {
        free(tokens);
        free(children);
        return parseUnaryExpression(parser);
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        children[childCount++] = parseTypeName(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        children[childCount++] = parseCastExpression(parser);
        return createASTNode(AST_CAST_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Cast Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isUnaryExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isPostfixExpression(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }
    else if (isPrefixUnaryOperator(parser, 1))
    {
        if (isUnaryExpression(parser, 0))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }
    else if (isUnaryOperator(parser, 1))
    {
        if (isCastExpression(parser, 0))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_SIZEOF, 1))
    {
        if (isUnaryExpression(parser, 0))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
        else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))
        {
            if (isTypeName(parser, 0))
            {
                if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
                {
                    if (resetOnSuccess)
                    {
                        parser->position = lookaheadPosition;
                    }
                    return 1;
                }
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static int isPrefixUnaryOperator(Parser *parser, int consumeOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    switch (nextToken(parser)->type)
    {
    case TOKEN_DOUBLE_PLUS:
    case TOKEN_DOUBLE_MINUS:
        if (consumeOnSuccess)
        {
            consumeToken(parser, 1);
        }
        return 1;    
    default:
        return 0;
    }
}

static int isUnaryOperator(Parser *parser, int consumeOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    switch (nextToken(parser)->type)
    {
    case TOKEN_BITWISE_AND:
    case TOKEN_STAR:
    case TOKEN_PLUS:
    case TOKEN_MINUS:
    case TOKEN_BITWISE_NOT:
    case TOKEN_NOT:
        if (consumeOnSuccess)
        {
            consumeToken(parser, 1);
        }
        return 1;
    default:
        return 0;
    }
}

static ASTNode *parseUnaryExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isUnaryExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Unary Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isPostfixExpression(parser, 1))
    {
        free(tokens);
        free(children);
        return parsePostfixExpression(parser);
    }
    else if (isPrefixUnaryOperator(parser, 0))
    {
        tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
        children[childCount++] = parseUnaryExpression(parser);
        return createASTNode(AST_UNARY_EXPRESSION, tokens, tokenCount, children, childCount);
    }
    else if (isUnaryOperator(parser, 0))
    {
        tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
        children[childCount++] = parseCastExpression(parser);
        return createASTNode(AST_UNARY_EXPRESSION, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_SIZEOF, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        if (isUnaryExpression(parser, 1))
        {
            children[childCount++] = parseUnaryExpression(parser);
        }
        else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
            children[childCount++] = parseTypeName(parser);
            tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        }
        return createASTNode(AST_UNARY_EXPRESSION, tokens, tokenCount, children, childCount);
    }
    
    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Unary Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isPostfixExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isPrimaryExpression(parser, 0)) 
    {
        while (isPostfixExpressionPrime(parser, 0));

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))
    {
        if (isTypeName(parser, 0))
        {
            if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
            {
                if (isNextTokenTypeOf(parser, TOKEN_OPEN_CURLY, 1))
                {
                    if (isInitializerList(parser, 0))
                    {
                        isNextTokenTypeOf(parser, TOKEN_COMMA, 1);

                        if (isNextTokenTypeOf(parser, TOKEN_CLOSE_CURLY, 1))
                        {
                            while (isPostfixExpressionPrime(parser, 0));

                            if (resetOnSuccess)
                            {
                                parser->position = lookaheadPosition;
                            }
                            return 1;
                        }
                    }
                }
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parsePostfixExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isPostfixExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Postfix Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 5;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 3;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isPrimaryExpression(parser, 1))
    {
        ASTNode *child = parsePrimaryExpression(parser);

        if (!isPostfixExpressionPrime(parser, 1))
        {
            free(tokens);
            free(children);
            return child;
        }

        children[childCount++] = child;
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        children[childCount++] = parseTypeName(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_CURLY);
        children[childCount++] = parseInitializerList(parser);
        if (isNextTokenTypeOf(parser, TOKEN_COMMA, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);
        }
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_CURLY);
    }
    else
    {
        //Error
        addError(parser, createError(ERROR_PARSING, "Expected a Primary Expression but found:", duplicateToken(nextToken(parser))));
        free(tokens);
        free(children);
        return NULL;
    }
    
    while (isPostfixExpressionPrime(parser, 1))
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

        children[childCount++] = parsePostfixExpressionPrime(parser);
    }
    
    return createASTNode(AST_POSTFIX_EXPRESSION, tokens, tokenCount, children, childCount);
}

static int isPostfixExpressionPrime(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenTypeOf(parser, TOKEN_OPEN_BRACKET, 1))
    {
        if (isExpression(parser, 0))
        {
            if (isNextTokenTypeOf(parser, TOKEN_CLOSE_BRACKET, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }

        if (isExpression(parser, 0))
        {
            if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }
    else if (isNextTokenTypeOf(parser, TOKEN_DOT, 1) || isNextTokenTypeOf(parser, TOKEN_ARROW, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 1))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }
    else if (isNextTokenTypeOf(parser, TOKEN_DOUBLE_PLUS, 1) || isNextTokenTypeOf(parser, TOKEN_DOUBLE_MINUS, 1))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parsePostfixExpressionPrime(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if(!isPostfixExpressionPrime(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Postfix Expression Prime but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenTypeOf(parser, TOKEN_OPEN_BRACKET, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_BRACKET);
        children[childCount++] = parseExpression(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_BRACKET);
        return createASTNode(AST_POSTFIX_EXPRESSION_PRIME, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        if (isExpression(parser, 1))
        {
            children[childCount++] = parseExpression(parser);
        }
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        return createASTNode(AST_POSTFIX_EXPRESSION_PRIME, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenTypeOf(parser, TOKEN_DOT, 0) || isNextTokenTypeOf(parser, TOKEN_ARROW, 0))
    {
        tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        return createASTNode(AST_POSTFIX_EXPRESSION_PRIME, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenTypeOf(parser, TOKEN_DOUBLE_PLUS, 0) || isNextTokenTypeOf(parser, TOKEN_DOUBLE_MINUS, 0))
    {
        tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
        return createASTNode(AST_POSTFIX_EXPRESSION_PRIME, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Postfix Expression Prime but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isPrimaryExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 1))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))
    {
        if (isExpression(parser, 0))
        {
            if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }
    else if (isLiteral(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parsePrimaryExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isPrimaryExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Primary Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        return createASTNode(AST_PRIMARY_EXPRESSION, tokens, tokenCount, children, childCount);
    }
    else if (isLiteral(parser, 1))
    {
        free(tokens);
        free(children);
        return parseLiteral(parser);
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        children[childCount++] = parseExpression(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        return createASTNode(AST_PRIMARY_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    free(tokens);
    free(children);
    addError(parser, createError(ERROR_PARSING, "Expected a primary expression but found:", duplicateToken(nextToken(parser))));
    return NULL;
}

static int isLiteral(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    switch (nextToken(parser)->type)
    {
    case TOKEN_INTEGER:
    case TOKEN_FLOATINGPOINT:
    case TOKEN_CHARACTER:
    case TOKEN_STRING:
    case TOKEN_HEXADECIMAL:
    case TOKEN_OCTAL:
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        else
        {
            consumeToken(parser, 1);
        }
        return 1;
    default:
        parser->position = lookaheadPosition;
        return 0;
    }
}

static ASTNode *parseLiteral(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if(isLiteral(parser, 1))
    {
        tokens[tokenCount++] = matchToken(parser, nextToken(parser)->type);
        return createASTNode(AST_LITERAL, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a literal but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isAssignmentExpression(parser, 0))
    {
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 1))
        {
            if (!isAssignmentExpression(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isAssignmentExpression(parser, 1))
    {
        children[childCount++] = parseAssignmentExpression(parser);
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);
            children[childCount++] = parseAssignmentExpression(parser);
        }

        return createASTNode(AST_EXPRESSION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Expression but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isTypeName(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isSpecifierQualifier(parser, 0))
    {
        while (isSpecifierQualifier(parser, 0));

        isAbstractDeclarator(parser, 0);
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseTypeName(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isTypeName(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Type Name but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 3;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isSpecifierQualifier(parser, 1))
    {
        children[childCount++] = parseSpecifierQualifier(parser);
        while (isSpecifierQualifier(parser, 1))
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

            children[childCount++] = parseSpecifierQualifier(parser);
        }

        if (isAbstractDeclarator(parser, 1))
        {
            children[childCount++] = parseAbstractDeclarator(parser);
        }

        return createASTNode(AST_TYPE_NAME, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Type Name but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isAbstractDeclarator(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isPointer(parser, 0))
    {
        if (!isDirectAbstractDeclarator(parser, 1))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
            
        }
        
    }

    if (isDirectAbstractDeclarator(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseAbstractDeclarator(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isAbstractDeclarator(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Abstract Declarator but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isPointer(parser, 1))
    {
        children[childCount++] = parsePointer(parser);
        if (!isDirectAbstractDeclarator(parser, 1))
        {
            return createASTNode(AST_ABSTRACT_DECLARATOR, tokens, tokenCount, children, childCount);
        }
    }

    if (isDirectAbstractDeclarator(parser, 1))
    {
        children[childCount++] = parseDirectAbstractDeclarator(parser);
        return createASTNode(AST_ABSTRACT_DECLARATOR, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Abstract Declarator but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isDirectAbstractDeclarator(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))
    {
        if (isAbstractDeclarator(parser, 0))
        {
            if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
            {
                while (isDirectAbstractDeclaratorPrime(parser, 0));

                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseDirectAbstractDeclarator(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isDirectAbstractDeclarator(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Direct Abstract Declarator but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 3;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        children[childCount++] = parseAbstractDeclarator(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        while (isDirectAbstractDeclaratorPrime(parser, 1))
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

            children[childCount++] = parseDirectAbstractDeclaratorPrime(parser);
        }

        return createASTNode(AST_DIRECT_ABSTRACT_DECLARATOR, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Direct Abstract Declarator but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isDirectAbstractDeclaratorPrime(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))   
    {
        isParameterList(parser, 0);

        if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_BRACKET, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_STAR, 1))
        {
            if (isNextTokenTypeOf(parser, TOKEN_CLOSE_BRACKET, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }

            parser->position = lookaheadPosition;
            return 0;
        }
        
        isAssignmentExpression(parser, 0);

        if (isNextTokenTypeOf(parser, TOKEN_CLOSE_BRACKET, 1))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseDirectAbstractDeclaratorPrime(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 3;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        if (isParameterList(parser, 1))
        {
            children[childCount++] = parseParameterList(parser);
        }
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        return createASTNode(AST_DIRECT_ABSTRACT_DECLARATOR_PRIME, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_BRACKET, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_BRACKET);
        if (isNextTokenTypeOf(parser, TOKEN_STAR, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_STAR);
            tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_BRACKET);
            return createASTNode(AST_DIRECT_ABSTRACT_DECLARATOR_PRIME, tokens, tokenCount, children, childCount);
        }

        if (isAssignmentExpression(parser, 1))
        {
            children[childCount++] = parseAssignmentExpression(parser);
        }
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_BRACKET);
        return createASTNode(AST_DIRECT_ABSTRACT_DECLARATOR_PRIME, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Direct Abstract Declarator Prime but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isParameterList(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isParameterDeclaration(parser, 0))
    {
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 1))
        {
            if (!isParameterDeclaration(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseParameterList(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isParameterList(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Parameter List but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 3;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isParameterDeclaration(parser, 1))
    {
        children[childCount++] = parseParameterDeclaration(parser);
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);
            children[childCount++] = parseParameterDeclaration(parser);
        }

        return createASTNode(AST_PARAMETER_LIST, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Parameter List but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isParameterDeclaration(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isDeclarationSpecifiers(parser, 0))
    {
        if (isDeclarator(parser, 0))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }

        isAbstractDeclarator(parser, 0);
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseParameterDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isParameterDeclaration(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Parameter Declaration but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isDeclarationSpecifiers(parser, 1))
    {
        children[childCount++] = parseDeclarationSpecifiers(parser);
        if (isDeclarator(parser, 1))
        {
            children[childCount++] = parseDeclarator(parser);
            return createASTNode(AST_PARAMETER_DECLARATION, tokens, tokenCount, children, childCount);
        }

        if (isAbstractDeclarator(parser, 1))
        {
            children[childCount++] = parseAbstractDeclarator(parser);
        }

        return createASTNode(AST_PARAMETER_DECLARATION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Parameter Declaration but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isInitializerList(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    isDesignation(parser, 0);

    if (isInitializer(parser, 0))
    {
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 1))
        {
            isDesignation(parser, 0);

            if (!isInitializer(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseInitializerList(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isInitializerList(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Initializer List but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 5;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isDesignation(parser, 1))
    {
        children[childCount++] = parseDesignation(parser);
    }

    if (isInitializer(parser, 1))
    {
        children[childCount++] = parseInitializer(parser);
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);
            if (isDesignation(parser, 1))
            {
                children[childCount++] = parseDesignation(parser);
            }

            children[childCount++] = parseInitializer(parser);
        }

        return createASTNode(AST_INITIALIZER_LIST, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Initializer List but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isDesignation(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isDesignator(parser, 0))
    {
        while (isDesignator(parser, 0));

        if (isNextTokenTypeOf(parser, TOKEN_EQUALS, 1))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseDesignation(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isDesignation(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Designation but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isDesignator(parser, 1))
    {
        children[childCount++] = parseDesignator(parser);

        while (isDesignator(parser, 1))
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

            children[childCount++] = parseDesignator(parser);
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_EQUALS);
        return createASTNode(AST_DESIGNATION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Designation but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isDesignator(Parser *parser, const int resetOnSucces)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenTypeOf(parser, TOKEN_OPEN_BRACKET, 1))
    {
        if (isConstantExpression(parser, 0))
        {
            if (isNextTokenTypeOf(parser, TOKEN_CLOSE_BRACKET, 1))
            {
                if (resetOnSucces)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }
    else if (isNextTokenTypeOf(parser, TOKEN_DOT, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 1))
        {
            if (resetOnSucces)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseDesignator(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isDesignator(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Designator but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        children[childCount++] = parseConstantExpression(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
    }
    else if (isNextTokenTypeOf(parser, TOKEN_DOT, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_DOT);
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Designator but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isConstantExpression(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isConditionalExpression(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseConstantExpression(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isConstantExpression(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Constant Expression but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Parsing
    if (isConditionalExpression(parser, 1))
    {
        return parseConditionalExpression(parser);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Constant Expression but found:", duplicateToken(nextToken(parser))));
    return NULL;
}

static int isInitializer(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isAssignmentExpression(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_BRACKET, 1))
    {
        if (isInitializerList(parser, 1))
        {
            isNextTokenTypeOf(parser, TOKEN_COMMA, 0);
            if (isNextTokenTypeOf(parser, TOKEN_CLOSE_BRACKET, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

    static ASTNode *parseInitializer(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isInitializer(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Initializer but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 3;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isAssignmentExpression(parser, 1))
    {
        free(tokens);
        free(children);
        return parseAssignmentExpression(parser);
    }
    else if (isNextTokenTypeOf(parser, TOKEN_OPEN_BRACKET, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_BRACKET);
        children[childCount++] = parseInitializerList(parser);
        if (isNextTokenTypeOf(parser, TOKEN_COMMA, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);
        }
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_BRACKET);
        return createASTNode(AST_INITIALIZER, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Initializer but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isIdentifierList(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 1))
    {
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 1))
        {
            if (!isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 1))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseIdentifierList(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isIdentifierList(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Identifier List but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 4;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 0))
        {
            if (tokenCount + 2 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);
            tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        }

        return createASTNode(AST_IDENTIFIER_LIST, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Identifier List but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isEnumSpecifier(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenKeywordWord(parser, KEYWORD_ENUM, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 1))
        {
            if (!isNextTokenTypeOf(parser, TOKEN_OPEN_CURLY, 0))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }

        if (isNextTokenTypeOf(parser, TOKEN_OPEN_CURLY, 1))
        {
            if (isEnumeratorList(parser, 0))
            {
                isNextTokenTypeOf(parser, TOKEN_COMMA, 1);
                if (isNextTokenTypeOf(parser, TOKEN_CLOSE_CURLY, 1))
                {
                    if (resetOnSuccess)
                    {
                        parser->position = lookaheadPosition;
                    }
                    return 1;
                }
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseEnumSpecifier(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isEnumSpecifier(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Enum Specifier but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 5;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenKeywordWord(parser, KEYWORD_ENUM, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
            if (!isNextTokenTypeOf(parser, TOKEN_OPEN_CURLY, 0))
            {
                return createASTNode(AST_ENUM_SPECIFIER, tokens, tokenCount, children, childCount);
            }
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_CURLY);
        children[childCount++] = parseEnumeratorList(parser);
        if (isNextTokenTypeOf(parser, TOKEN_COMMA, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);
        }
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_CURLY);
        return createASTNode(AST_ENUM_SPECIFIER, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Enum Specifier but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isEnumeratorList(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isEnumerator(parser, 0))
    {
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 1))
        {
            if (!isEnumerator(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseEnumeratorList(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isEnumeratorList(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Enumerator List but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isEnumerator(parser, 1))
    {
        children[childCount++] = parseEnumerator(parser);
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);
            children[childCount++] = parseEnumerator(parser);
        }

        return createASTNode(AST_ENUMERATOR_LIST, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Enumerator List but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isEnumerator(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 1))
    {
        while (isNextTokenTypeOf(parser, TOKEN_EQUALS, 1))
        {
            if (!isConstantExpression(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseEnumerator(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isEnumerator(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Enumerator but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 3;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);    
        while (isNextTokenTypeOf(parser, TOKEN_EQUALS, 1))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, TOKEN_EQUALS);
            children[childCount++] = parseConstantExpression(parser);
        }

        return createASTNode(AST_ENUMERATOR, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Enumerator but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isDeclaration(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isDeclarationSpecifiers(parser, 0))
    {
        isInitDeclaratorList(parser, 0);
        if (isNextTokenTypeOf(parser, TOKEN_SEMICOLON, 1))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isDeclaration(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Declaration but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isDeclarationSpecifiers(parser, 1))
    {
        children[childCount++] = parseDeclarationSpecifiers(parser);
        if (isInitDeclaratorList(parser, 1))
        {
            children[childCount++] = parseInitDeclaratorList(parser);
        }
        
        tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
        return createASTNode(AST_DECLARATION, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Declaration but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isInitDeclaratorList(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isInitDeclarator(parser, 0))
    {
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 1))
        {
            if (!isInitDeclarator(parser, 0))
            {
                parser->position = lookaheadPosition;
                return 0;
            }
        }

        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseInitDeclaratorList(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isInitDeclaratorList(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Init Declarator List but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 3;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isInitDeclarator(parser, 1))
    {
        children[childCount++] = parseInitDeclarator(parser);
        while (isNextTokenTypeOf(parser, TOKEN_COMMA, 0))
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
            if (tokenCount + 1 >= tokensSize)
            {
                tokensSize *= 2;
                Token **newTokens = realloc(tokens, tokensSize * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory reallocation for tokens failed!\n");
                    free(tokens);
                    free(children);
                    return NULL;
                }
                tokens = newTokens;
            }

            tokens[tokenCount++] = matchToken(parser, TOKEN_COMMA);
            children[childCount++] = parseInitDeclarator(parser);
        }

        return createASTNode(AST_INIT_DECLARATOR_LIST, tokens, tokenCount, children, childCount);
    }


    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Init Declarator List but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isInitDeclarator(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isDeclarator(parser, 0))
    {
        if(isNextTokenTypeOf(parser, TOKEN_EQUALS, 1))
        {
            if (isInitializer(parser, 0))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
        else
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseInitDeclarator(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isInitDeclarator(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Init Declarator but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isDeclarator(parser, 1))
    {
        children[childCount++] = parseDeclarator(parser);
        if (isNextTokenTypeOf(parser, TOKEN_EQUALS, 0))
        {
            tokens[tokenCount++] = matchToken(parser, TOKEN_EQUALS);
            children[childCount++] = parseInitializer(parser);
        }

        return createASTNode(AST_INIT_DECLARATOR, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Init Declarator but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isStatement(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isLabeledStatement(parser, 0) || isCompoundStatement(parser, 0) || isExpressionStatement(parser, 0) || isSelectionStatement(parser, 0) || isIterationStatement(parser, 0) || isJumpStatement(parser, 0))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }
    
    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isStatement(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Statement but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Parsing
    if (isLabeledStatement(parser, 1))
    {
        return parseLabeledStatement(parser);
    }
    else if (isCompoundStatement(parser, 1))
    {
        return parseCompoundStatement(parser);
    }
    else if (isExpressionStatement(parser, 1))
    {
        return parseExpressionStatement(parser);
    }
    else if (isSelectionStatement(parser, 1))
    {
        return parseSelectionStatement(parser);
    }
    else if (isIterationStatement(parser, 1))
    {
        return parseIterationStatement(parser);
    }
    else if (isJumpStatement(parser, 1))
    {
        return parseJumpStatement(parser);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Statement but found:", duplicateToken(nextToken(parser))));
    return NULL;
}

static int isLabeledStatement(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_COLON, 1))
        {
            if (isStatement(parser, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_CASE, 1))
    {
        if (isConstantExpression(parser, 0))
        {
            if (isNextTokenTypeOf(parser, TOKEN_COLON, 1))
            {
                if (isStatement(parser, 1))
                {
                    if (resetOnSuccess)
                    {
                        parser->position = lookaheadPosition;
                    }
                    return 1;
                }
            }
        }
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_DEFAULT, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_COLON, 1))
        {
            if (isStatement(parser, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseLabeledStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isLabeledStatement(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Labeled Statement but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        tokens[tokenCount++] = matchToken(parser, TOKEN_COLON);
        children[childCount++] = parseStatement(parser);
        return createASTNode(AST_LABELED_STATEMENT, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_CASE, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        children[childCount++] = parseConstantExpression(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_COLON);
        children[childCount++] = parseStatement(parser);
        return createASTNode(AST_LABELED_STATEMENT, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_DEFAULT, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        tokens[tokenCount++] = matchToken(parser, TOKEN_COLON);
        children[childCount++] = parseStatement(parser);
        return createASTNode(AST_LABELED_STATEMENT, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Labeled Statement but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isCompoundStatement(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenTypeOf(parser, TOKEN_OPEN_CURLY, 1))
    {
        while (isDeclaration(parser, 0) || isStatement(parser, 0));
        
        if (isNextTokenTypeOf(parser, TOKEN_CLOSE_CURLY, 1))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseCompoundStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isCompoundStatement(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Compound Statement but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 4;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenTypeOf(parser, TOKEN_OPEN_CURLY, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_CURLY);
        while (isDeclaration(parser, 1) || isStatement(parser, 1))
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

            if (isDeclaration(parser, 1))
            {
                children[childCount++] = parseDeclaration(parser);
            }
            else
            {
                children[childCount++] = parseStatement(parser);
            }
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_CURLY);
        return createASTNode(AST_COMPOUND_STATEMENT, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Compound Statement but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isExpressionStatement(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    isExpression(parser, 0);
    
    if (isNextTokenTypeOf(parser, TOKEN_SEMICOLON, 1))
    {
        if (resetOnSuccess)
        {
            parser->position = lookaheadPosition;
        }
        return 1;
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseExpressionStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isExpressionStatement(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Expression Statement but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 1;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isExpression(parser, 1))
    {
        children[childCount++] = parseExpression(parser);
    }

    tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
    return createASTNode(AST_EXPRESSION_STATEMENT, tokens, tokenCount, children, childCount);
}

static int isSelectionStatement(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenKeywordWord(parser, KEYWORD_IF, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))
        {
            if (isExpression(parser, 0))
            {
                if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
                {
                    if (isStatement(parser, 0))
                    {
                        if (isNextTokenKeywordWord(parser, KEYWORD_ELSE, 1))
                        {
                            if (isStatement(parser, 0))
                            {
                                if (resetOnSuccess)
                                {
                                    parser->position = lookaheadPosition;
                                }
                                return 1;
                            }
                        }
                        else
                        {
                            if (resetOnSuccess)
                            {
                                parser->position = lookaheadPosition;
                            }
                            return 1;
                        }
                    }
                }
            }
        }
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_SWITCH, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))
        {
            if (isExpression(parser, 0))
            {
                if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
                {
                    if (isStatement(parser, 0))
                    {
                        if (resetOnSuccess)
                        {
                            parser->position = lookaheadPosition;
                        }
                        return 1;
                    }
                }
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseSelectionStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isSelectionStatement(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Selection Statement but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 4;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 3;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenKeywordWord(parser, KEYWORD_IF, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        children[childCount++] = parseExpression(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        children[childCount++] = parseStatement(parser);
        if (!isNextTokenKeywordWord(parser, KEYWORD_ELSE, 0))
        {
            return createASTNode(AST_SELECTION_STATEMENT, tokens, tokenCount, children, childCount);
        }

        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        children[childCount++] = parseStatement(parser);
        return createASTNode(AST_SELECTION_STATEMENT, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_SWITCH, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        children[childCount++] = parseExpression(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        children[childCount++] = parseStatement(parser);
        return createASTNode(AST_SELECTION_STATEMENT, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Selection Statement but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isIterationStatement(Parser *parser, const int resetOnSucces)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenKeywordWord(parser, KEYWORD_FOR, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))
        {
            if (isForControl(parser, 0))
            {
                if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
                {
                    if (isStatement(parser, 0))
                    {
                        if (resetOnSucces)
                        {
                            parser->position = lookaheadPosition;
                        }
                        return 1;
                    }
                }
            }
        }
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_WHILE, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))
        {
            if (isExpression(parser, 0))
            {
                if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
                {
                    if (isStatement(parser, 0))
                    {
                        if (resetOnSucces)
                        {
                            parser->position = lookaheadPosition;
                        }
                        return 1;
                    }
                }
            }
        }
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_DO, 1))
    {
        if (isStatement(parser, 0))
        {
            if (isNextTokenKeywordWord(parser, KEYWORD_WHILE, 1))
            {
                if (isNextTokenTypeOf(parser, TOKEN_OPEN_PARENTHESIS, 1))
                {
                    if (isExpression(parser, 0))
                    {
                        if (isNextTokenTypeOf(parser, TOKEN_CLOSE_PARENTHESIS, 1))
                        {
                            if (isNextTokenTypeOf(parser, TOKEN_SEMICOLON, 1))
                            {
                                if (resetOnSucces)
                                {
                                    parser->position = lookaheadPosition;
                                }
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }

    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseIterationStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isIterationStatement(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected an Iteration Statement but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 5;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 2;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenKeywordWord(parser, KEYWORD_FOR, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        children[childCount++] = parseForControl(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        children[childCount++] = parseStatement(parser);
        return createASTNode(AST_ITERATION_STATEMENT, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_WHILE, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        children[childCount++] = parseExpression(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        children[childCount++] = parseStatement(parser);
        return createASTNode(AST_ITERATION_STATEMENT, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_DO, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        children[childCount++] = parseStatement(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        tokens[tokenCount++] = matchToken(parser, TOKEN_OPEN_PARENTHESIS);
        children[childCount++] = parseExpression(parser);
        tokens[tokenCount++] = matchToken(parser, TOKEN_CLOSE_PARENTHESIS);
        tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
        return createASTNode(AST_ITERATION_STATEMENT, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected an Iteration Statement but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

static int isForControl(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isDeclaration(parser, 0))
    {
        isExpression(parser, 0);
        if (isNextTokenTypeOf(parser, TOKEN_SEMICOLON, 1))
        {
            isExpression(parser, 0);
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }
    
    isExpression(parser, 0);
    if (isNextTokenTypeOf(parser, TOKEN_SEMICOLON, 1))
    {
        isExpression(parser, 0);
        if (isNextTokenTypeOf(parser, TOKEN_SEMICOLON, 1))
        {
            isExpression(parser, 0);
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }
    
    parser->position = lookaheadPosition;
    return 0;
}

static ASTNode *parseForControl(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isForControl(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a For Control but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 2;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 3;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isDeclaration(parser, 1))
    {
        children[childCount++] = parseDeclaration(parser);
        if (isExpression(parser, 1))
        {
            children[childCount++] = parseExpression(parser);
        }
        tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
        if (isExpression(parser, 1))
        {
            children[childCount++] = parseExpression(parser);
        }
        return createASTNode(AST_FOR_CONTROL, tokens, tokenCount, children, childCount);
    }

    if (isExpression(parser, 1))
    {
        children[childCount++] = parseExpression(parser);
    }

    tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
    if (isExpression(parser, 1))
    {
        children[childCount++] = parseExpression(parser);
    }

    tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
    if (isExpression(parser, 1))
    {
        children[childCount++] = parseExpression(parser);
    }
    return createASTNode(AST_FOR_CONTROL, tokens, tokenCount, children, childCount);
}

static int isJumpStatement(Parser *parser, const int resetOnSuccess)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return 0;
    }

    int lookaheadPosition = parser->position;
    if (isNextTokenKeywordWord(parser, KEYWORD_GOTO, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_IDENTIFIER, 1))
        {
            if (isNextTokenTypeOf(parser, TOKEN_SEMICOLON, 1))
            {
                if (resetOnSuccess)
                {
                    parser->position = lookaheadPosition;
                }
                return 1;
            }
        }
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_CONTINUE, 1) || isNextTokenKeywordWord(parser, KEYWORD_BREAK, 1))
    {
        if (isNextTokenTypeOf(parser, TOKEN_SEMICOLON, 1))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_RETURN, 1))
    {
        isExpression(parser, 0);
        if (isNextTokenTypeOf(parser, TOKEN_SEMICOLON, 1))
        {
            if (resetOnSuccess)
            {
                parser->position = lookaheadPosition;
            }
            return 1;
        }
    }

    return 0;
}

static ASTNode *parseJumpStatement(Parser *parser)
{
    if (parser == NULL)
    {
        fprintf(stderr, "Parser is not initialized.\n");
        return NULL;
    }

    if (!isJumpStatement(parser, 1))
    {
        addError(parser, createError(ERROR_PARSING, "Expected a Jump Statement but found:", duplicateToken(nextToken(parser))));
        return NULL;
    }

    //Allocating memory
    size_t tokensSize = 3;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = 1;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;

    //Parsing
    if (isNextTokenKeywordWord(parser, KEYWORD_GOTO, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        tokens[tokenCount++] = matchToken(parser, TOKEN_IDENTIFIER);
        tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
        return createASTNode(AST_JUMP_STATEMENT, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_CONTINUE, 0) || isNextTokenKeywordWord(parser, KEYWORD_BREAK, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
        return createASTNode(AST_JUMP_STATEMENT, tokens, tokenCount, children, childCount);
    }
    else if (isNextTokenKeywordWord(parser, KEYWORD_RETURN, 0))
    {
        tokens[tokenCount++] = matchToken(parser, TOKEN_KEYWORD);
        if (isExpression(parser, 1))
        {
            children[childCount++] = parseExpression(parser);
        }
        tokens[tokenCount++] = matchToken(parser, TOKEN_SEMICOLON);
        return createASTNode(AST_JUMP_STATEMENT, tokens, tokenCount, children, childCount);
    }

    //Error
    addError(parser, createError(ERROR_PARSING, "Expected a Jump Statement but found:", duplicateToken(nextToken(parser))));
    free(tokens);
    free(children);
    return NULL;
}

/*****************************************************************************************************
                                PUBLIC PARSER FUNCTIONS START HERE                                
 *****************************************************************************************************/

Parser *createParser(Token **const tokens, const size_t tokenCount)
{
    if (tokens == NULL)
    {
        fprintf(stderr, "Token list provided to parser is NULL!\n");
        return NULL;
    }

    Parser *parser = malloc(sizeof(Parser));
    if (parser == NULL)
    {
        fprintf(stderr, "Memory allocation for Parser failed!\n");
        return NULL;
    }

    parser->tokens = malloc(tokenCount * sizeof(Token*));
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
    
    Token **newTokens = realloc(parser->tokens, newCount * sizeof(Token*));
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

    parser->errorsSize = 1;
    parser->errors = malloc(parser->errorsSize * sizeof(Error *));
    if (parser->errors == NULL)
    {
        fprintf(stderr, "Memory allocation for Parser->errors failed!\n");
        free(parser->tokens);
        free(parser);
        return NULL;
    }
    parser->errorCount = 0;

    return parser;
}

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

    deleteErrors(parser->errors, parser->errorCount);
    free(parser->errors);

    free(parser);
}

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