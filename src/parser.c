#include "parser.h"

bool parser_isType(Parser *parser);

AstNode *parser_parseType(Parser *parser);

bool parser_isTypeSpecifier(Parser *parser);

AstNode *parser_parseTypeSpecifiers(Parser *parser);

bool parser_isFullType(Parser *parser);

AstNode *parser_parseFullType(Parser *parser);

bool parser_isLiteral(Parser *parser);

AstNode *parser_parseLiteral(Parser *parser);

AstNode *parser_parseProgram(Parser *parser);

AstNode *parser_parseImport(Parser *parser);

AstNode *parser_parseIdentifierList(Parser *parser);

AstNode *parser_parseFunctionDefinition(Parser *parser);

AstNode *parser_parseReturnParameterList(Parser *parser);

AstNode *parser_parseFunctionParameterList(Parser *parser);

AstNode *parser_parseFunctionParameter(Parser *parser);

AstNode *parser_parseGlobalVariableDeclaration(Parser *parser);

AstNode *parser_parseStructDeclaration(Parser *parser);

AstNode *parser_parseUnionDeclaration(Parser *parser);

AstNode *parser_parseStructUnionMemberDeclaration(Parser *parser);

AstNode *parser_parseStructUniondeclarator(Parser *parser);

AstNode *parser_parseStructUnionIndirectDeclarator(Parser *parser);

AstNode *parser_parseStructUnionDirectDeclarator(Parser *parser);

AstNode *parser_parseEnumDeclaration(Parser *parser);

AstNode *parser_parseEnumValueDeclaration(Parser *parser);

AstNode *parser_parseTypedefDeclaration(Parser *parser);

AstNode *parser_parseStatement(Parser *parser);

AstNode *parser_parseBranchStatement(Parser *parser);

AstNode *parser_parseIfStatement(Parser *parser);

AstNode *parser_parseSwitchStatement(Parser *parser);

AstNode *parser_parseSwitchCase(Parser *parser);

AstNode *parser_parseSwitchDefault(Parser *parser);

AstNode *parser_parseLoopStatement(Parser *parser);

AstNode *parser_parseForStatement(Parser *parser);

AstNode *parser_parseForInitializer(Parser *parser);

AstNode *parser_parseForCondition(Parser *parser);

AstNode *parser_parseForIncrementation(Parser *parser);

AstNode *parser_parseForeachStatement(Parser *parser);

AstNode *parser_parseWhileStatement(Parser *parser);

AstNode *parser_parseDoWhileStatement(Parser *parser);

AstNode *parser_parseCompoundStatement(Parser *parser);

AstNode *parser_parseLabel(Parser *parser);

AstNode *parser_parseExpressionStatement(Parser *parser);

AstNode *parser_parseVariableDeclaration(Parser *parser);

AstNode *parser_parseJumpStatement(Parser *parser);

AstNode *parser_parseGotoStatement(Parser *parser);

AstNode *parser_parseReturnStatement(Parser *parser);

AstNode *parser_parseBreakStatement(Parser *parser);

AstNode *parser_parseContinueStatement(Parser *parser);

AstNode *parser_parseExpression(Parser *parser);

AstNode *parser_parseAssignmentExpression(Parser *parser); // TODO

AstNode *parser_parseLogicalOrExpression(Parser *parser); // TODO

AstNode *parser_parseLogicalAndExpression(Parser *parser); // TODO

AstNode *parser_parseBitwiseOrExpression(Parser *parser); // TODO

AstNode *parser_parseBitwiseXorExpression(Parser *parser); // TODO

AstNode *parser_parseBitwiseAndExpression(Parser *parser); // TODO

AstNode *parser_parseEqualityExpression(Parser *parser); // TODO

AstNode *parser_parseRelationalExpression(Parser *parser); // TODO

AstNode *parser_parseShiftExpression(Parser *parser); // TODO

AstNode *parser_parseAdditiveExpression(Parser *parser); // TODO

AstNode *parser_parseMultiplicativeExpression(Parser *parser); // TODO

AstNode *parser_parseTypeCastExpression(Parser *parser);

AstNode *parser_parseUnaryExpression(Parser *parser);

AstNode *parser_parsePostfixExpression(Parser *parser);

bool parser_isPostfixPrimeExpression(Parser *parser);

AstNode *parser_parsePostfixPrimeExpression(Parser *parser);

AstNode *parser_parseArrayIndexingExpression(Parser *parser);

AstNode *parser_parseFunctionCallExpression(Parser *parser);

AstNode *parser_parsePrimaryExpression(Parser *parser);

// --------------------------------------------------------------------------------

bool parser_isType(Parser *parser)
{
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_isType: No tokens available to check type.\n");
        return false;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    switch (currentTokenType)
    {
    case TOKEN_KEYWORD_INT_64:
    case TOKEN_KEYWORD_INT_32:
    case TOKEN_KEYWORD_INT_16:
    case TOKEN_KEYWORD_INT_8:
    case TOKEN_KEYWORD_UINT_64:
    case TOKEN_KEYWORD_UINT_32:
    case TOKEN_KEYWORD_UINT_16:
    case TOKEN_KEYWORD_UINT_8:
    case TOKEN_KEYWORD_FLOAT_64:
    case TOKEN_KEYWORD_FLOAT_32:
    case TOKEN_KEYWORD_CHAR:
    case TOKEN_KEYWORD_STRING:
    case TOKEN_KEYWORD_BOOL:
    case TOKEN_KEYWORD_VOID:
    case TOKEN_IDENTIFIER:
    case TOKEN_KEYWORD_STRUCT:
    case TOKEN_KEYWORD_UNION:
    case TOKEN_KEYWORD_ENUM:
        return true;
    default:
        return false; 
    }
}

AstNode *parser_parseType(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseType: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseType: No tokens available to parse type.\n");
        return NULL;
    }

    if (!parser_isType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a type, got.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseType: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseType: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType == TOKEN_KEYWORD_INT_64 ||
        currentTokenType == TOKEN_KEYWORD_INT_32 ||
        currentTokenType == TOKEN_KEYWORD_INT_16 ||
        currentTokenType == TOKEN_KEYWORD_INT_8 ||
        currentTokenType == TOKEN_KEYWORD_UINT_64 ||
        currentTokenType == TOKEN_KEYWORD_UINT_32 ||
        currentTokenType == TOKEN_KEYWORD_UINT_16 ||
        currentTokenType == TOKEN_KEYWORD_UINT_8 ||
        currentTokenType == TOKEN_KEYWORD_FLOAT_64 ||
        currentTokenType == TOKEN_KEYWORD_FLOAT_32 ||
        currentTokenType == TOKEN_KEYWORD_CHAR ||
        currentTokenType == TOKEN_KEYWORD_STRING ||
        currentTokenType == TOKEN_KEYWORD_BOOL ||
        currentTokenType == TOKEN_KEYWORD_VOID || 
        currentTokenType == TOKEN_IDENTIFIER)
    {
        Token *typeToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (typeToken == NULL)
        {
            DEBUG_PRINT("parser_parseType: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, typeToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseType: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the type token
    }
    else // stuct or union or enum case
    {
        Token *structUnionEnumToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (structUnionEnumToken == NULL)
        {
            DEBUG_PRINT("parser_parseType: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, structUnionEnumToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseType: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the struct/union/enum token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseType: No tokens available after struct/union/enum keyword.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after struct/union/enum keyword.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseType: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseType: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseType: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseType: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
    }

    AstNode *typeNode = astNode_create(parser->astArena, AST_TYPE, tokens, NULL);
    if (typeNode == NULL)
    {
        DEBUG_PRINT("parser_parseType: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return typeNode;
}

bool parser_isTypeSpecifier(Parser *parser)
{
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_isTypeSpecifier: No tokens available to check type specifier.\n");
        return false;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    switch (currentTokenType)
    {
    case TOKEN_KEYWORD_CONST:
    case TOKEN_KEYWORD_CONST_PTR:
    case TOKEN_KEYWORD_PTR:
        return true;    
    default:
        return false;
    }
}

AstNode *parser_parseTypeSpecifiers(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseTypeSpecifiers: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseTypeSpecifiers: No tokens available to parse type specifiers.\n");
        return NULL;
    }

    if (!parser_isTypeSpecifier(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a type specifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseTypeSpecifiers: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseTypeSpecifiers: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;
        
        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;

    bool isFirst = true;
    while (parser_isTypeSpecifier(parser))
    {
        My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
        if (!isFirst && currentTokenType == TOKEN_KEYWORD_CONST)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Only the first type specifier can be 'const'.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseTypeSpecifiers: error_create failed with errno %d\n", errno);
                return NULL;
            }
            LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseTypeSpecifiers: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            Token *constToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
            if (constToken == NULL)
            {
                DEBUG_PRINT("parser_parseTypeSpecifiers: token_copy failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Token_create(parser->astArena, tokens, constToken);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseTypeSpecifiers: linkedList_Token_create failed with errno %d\n", errno);
                return NULL;
            }
            tokens = head;
        }

        isFirst = false;
        Token *typeSpecifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (typeSpecifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseTypeSpecifiers: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, typeSpecifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseTypeSpecifiers: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the type specifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseTypeSpecifiers: No tokens available after type specifier.\n");
            return NULL;
        }
    }

    AstNode *typeSpecifierNode = astNode_create(parser->astArena, AST_TYPE_SPECIFIERS, tokens, NULL);
    if (typeSpecifierNode == NULL)
    {
        DEBUG_PRINT("parser_parseTypeSpecifiers: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return typeSpecifierNode;
}

bool parser_isFullType(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_isFullType: Parser is NULL.\n");
        return false;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_isFullType: No tokens available to check full type.\n");
        return false;
    }

    if (parser_isTypeSpecifier(parser) || parser_isType(parser))
    {
        return true;
    }

    return false;
}

AstNode *parser_parseFullType(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parse_fullType: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parse_fullType: No tokens available to parse full type.\n");
        return NULL;
    }

    if (!parser_isTypeSpecifier(parser) && !parser_isType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a type or type specifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parse_fullType: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parse_fullType: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    if (parser_isTypeSpecifier(parser))
    {
        AstNode *typeSpecifiersNode = parser_parseTypeSpecifiers(parser);
        if (typeSpecifiersNode == NULL)
        {
            DEBUG_PRINT("parse_fullType: Failed to parse type specifiers.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeSpecifiersNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parse_fullType: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parse_fullType: No tokens available after type specifiers.\n");
            return NULL;
        }
    }

    AstNode *typeNode = parser_parseType(parser);
    if (typeNode == NULL)
    {
        DEBUG_PRINT("parse_fullType: Failed to parse type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parse_fullType: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *fullTypeNode = astNode_create(parser->astArena, AST_FULL_TYPE, NULL, children);
    if (fullTypeNode == NULL)
    {
        DEBUG_PRINT("parse_fullType: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return fullTypeNode;
}

bool parser_isLiteral(Parser *parser)
{
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_isLiteral: No tokens available to check literal.\n");
        return false;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    switch (currentTokenType)
    {
    case TOKEN_LITERAL_INTEGER:
    case TOKEN_LITERAL_BINARY:
    case TOKEN_LITERAL_OCTAL:
    case TOKEN_LITERAL_HEXADECIMAL:
    case TOKEN_LITERAL_FLOATINGPOINT:
    case TOKEN_LITERAL_CHARACTER:
    case TOKEN_LITERAL_STRING:
    case TOKEN_LITERAL_BOOLEAN:
    case TOKEN_LITERAL_NULL:
        return true;
    default:
        return false; 
    }
}

AstNode *parser_parseLiteral(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseLiteral: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseLiteral: No tokens available to parse literal.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_LITERAL_INTEGER &&
        currentTokenType != TOKEN_LITERAL_BINARY &&
        currentTokenType != TOKEN_LITERAL_OCTAL &&
        currentTokenType != TOKEN_LITERAL_HEXADECIMAL &&
        currentTokenType != TOKEN_LITERAL_FLOATINGPOINT &&
        currentTokenType != TOKEN_LITERAL_CHARACTER &&
        currentTokenType != TOKEN_LITERAL_STRING &&
        currentTokenType != TOKEN_LITERAL_BOOLEAN &&
        currentTokenType != TOKEN_LITERAL_NULL)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a literal.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseLiteral: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLiteral: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;

    Token *literalToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (literalToken == NULL)
    {
        DEBUG_PRINT("parser_parseLiteral: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, literalToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseLiteral: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the literal token

    AstNode *literalNode = astNode_create(parser->astArena, AST_LITERAL, tokens, NULL);
    if (literalNode == NULL)
    {
        DEBUG_PRINT("parser_parseLiteral: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return literalNode;
}

AstNode *parser_parseProgram(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseProgram: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseProgram: No tokens available to parse the program.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    while (parser->tokens != NULL && ((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_IMPORT)
    {
        AstNode *import = parser_parseImport(parser); // Sets parser->tokens to the next token after the import statement
        if (import == NULL)
        {
            DEBUG_PRINT("parser_parseProgram: Failed to parse import.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, import);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseProgram: No tokens available to parse the program.\n");
        return NULL;
    }

    while (parser->tokens != NULL && ((Token *)parser->tokens->data)->type != TOKEN_EOF)
    {
        LinkedList *currentTokenNode = parser->tokens;
        if (((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_EXPORT)
        {
            currentTokenNode = currentTokenNode->next; // Look past the export keyword as other statements will handle it
        }

        if (currentTokenNode == NULL)
        {
            DEBUG_PRINT("parser_parseProgram: No tokens available after export keyword.\n");
            return NULL;
        }
        
        My_TokenType currentTokenType = ((Token *)currentTokenNode->data)->type;
        if (currentTokenType == TOKEN_OPEN_PARENTHESIS)
        {
            AstNode *function = parser_parseFunctionDefinition(parser);
            if (function == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: Failed to parse function.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, function);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }
        else if (currentTokenType == TOKEN_KEYWORD_STRUCT)
        {
            AstNode *structDeclaration = parser_parseStructDeclaration(parser);
            if (structDeclaration == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: Failed to parse struct declaration.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, structDeclaration);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }
        else if (currentTokenType == TOKEN_KEYWORD_UNION)
        {
            AstNode *unionDeclaration = parser_parseUnionDeclaration(parser);
            if (unionDeclaration == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: Failed to parse union declaration.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, unionDeclaration);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }
        else if (currentTokenType == TOKEN_KEYWORD_ENUM)
        {
            AstNode *enumDeclaration = parser_parseEnumDeclaration(parser);
            if (enumDeclaration == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: Failed to parse enum declaration.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, enumDeclaration);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }
        else if (currentTokenType == TOKEN_KEYWORD_TYPEDEF)
        {
            AstNode *typedefDeclaration = parser_parseTypedefDeclaration(parser);
            if (typedefDeclaration == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: Failed to parse typedef declaration.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, typedefDeclaration);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }
        else if (parser_isFullType(parser))
        {
            AstNode *globalDeclaration = parser_parseGlobalVariableDeclaration(parser);
            if (globalDeclaration == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: Failed to parse global declaration.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, globalDeclaration);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }
        else
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)currentTokenNode->data)->length, ((Token *)currentTokenNode->data)->line, ((Token *)currentTokenNode->data)->column, "Unexpected token in program.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: error_create failed with errno %d\n", errno);
                return NULL;
            }
            LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
        }

        currentTokenNode = parser->tokens;
    }

    if (parser->tokens == NULL || ((Token *)parser->tokens->data)->type != TOKEN_EOF)
    {
        Error *error;
        if (parser->tokens == NULL)
        {
            error = error_create(parser->utilsArena, ERROR_FATAL, 0, 0, 0, "End of file not found in the program.");
        }
        else
        {
            error = error_create(parser->utilsArena, ERROR_FATAL, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "End of file not found in the program.");
        }
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseProgram: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseProgram: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;
        return NULL;
    }

    AstNode *program = astNode_create(parser->astArena, AST_PROGRAM, NULL, children);
    if (program == NULL)
    {
        DEBUG_PRINT("parser_parseProgram: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return program;
}

AstNode *parser_parseImport(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseImport: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseImport: No tokens available to parse.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_IMPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'import' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Move to the next token
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;
    
    parser->tokens = parser->tokens->next; // Move past the import token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseImport: No tokens available after import keyword.\n");
        return NULL;
    }

    bool isFrom = false;
    if (((Token *)parser->tokens->data)->type == TOKEN_LITERAL_STRING)
    {
        Token *stringLiteralToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (stringLiteralToken == NULL)
        {
            DEBUG_PRINT("parser_parseImport: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, stringLiteralToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the string literal token
    }
    else if (((Token *)parser->tokens->data)->type == TOKEN_IDENTIFIER)
    {
        isFrom = true; // Indicates that this is an import from statement

        AstNode *identifierListNode = parser_parseIdentifierList(parser);
        if (identifierListNode == NULL)
        {
            DEBUG_PRINT("parser_parseImport: Failed to parse identifier list.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, identifierListNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseImport: No tokens available after import identifiers.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_FROM)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'from' keyword after import identifiers.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the 'from' keyword token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseImport: No tokens available after 'from' keyword.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_LITERAL_STRING)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected string literal after 'from' keyword.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        Token *stringLiteralToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (stringLiteralToken == NULL)
        {
            DEBUG_PRINT("parser_parseImport: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, stringLiteralToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the string literal token
    }
    else
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected string literal or identifier after import keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseImport: No tokens available after import statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected semicolon after import statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstType importType = isFrom ? AST_IMPORT_FROM : AST_IMPORT;
    AstNode *importNode = astNode_create(parser->astArena, importType, tokens, children);
    if (importNode == NULL)
    {
        DEBUG_PRINT("parser_parseImport: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return importNode;
}

AstNode *parser_parseIdentifierList(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseIdentifierList: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIdentifierList: No tokens available to parse.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier in identifier list.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseIdentifierList: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIdentifierList: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseIdentifierList: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseIdentifierList: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIdentifierList: No tokens available after identifier.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseIdentifierList: No tokens available after comma.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after comma in identifier list.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseIdentifierList: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseIdentifierList: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseIdentifierList: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIdentifierList: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseIdentifierList: No tokens available after identifier.\n");
            return NULL;
        }
    }

    AstNode *identifierListNode = astNode_create(parser->astArena, AST_IDENTIFIER_LIST, tokens, NULL);
    if (identifierListNode == NULL)
    {
        DEBUG_PRINT("parser_parseIdentifierList: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return identifierListNode;
}

AstNode *parser_parseFunctionDefinition(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseImport: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseImport: No tokens available to parse function definition.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_OPEN_PARENTHESIS && currentTokenType != TOKEN_KEYWORD_EXPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'export' keyword or open parenthesis for function definition.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens= NULL;
    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_EXPORT)
    {
        Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (exportToken == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, NULL, exportToken);
        if (tokens == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the export token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after export keyword.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected open parenthesis after function name.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *functionReturnParameterListNode = parser_parseReturnParameterList(parser);
    if (functionReturnParameterListNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: Failed to parse return parameter list.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, functionReturnParameterListNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after return parameter list.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected close parenthesis after function name.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after close parenthesis.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected function name after close parenthesis.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    Token *functionNameToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (functionNameToken == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, functionNameToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the function name token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after function name.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected open parenthesis after function name.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *functionParameterListNode = parser_parseFunctionParameterList(parser);
    if (functionParameterListNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: Failed to parse function parameter list.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, functionParameterListNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;
    
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after function parameter list.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected close parenthesis after function parameter list.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: No tokens available after close parenthesis.\n");
        return NULL;
    }

    AstNode *statementNode = parser_parseStatement(parser);
    if (statementNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: Failed to parse function statement.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, statementNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *functionDefinitionNode = astNode_create(parser->astArena, AST_FUNCTION_DEFINITION, tokens, children);
    if (functionDefinitionNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionDefinition: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return functionDefinitionNode;
}

AstNode *parser_parseReturnParameterList(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameterList: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameterList: No tokens available to parse return parameter list.\n");
        return NULL;
    }

    if (!parser_isFullType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a type or type specifier in return parameter list.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameterList: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameterList: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameterList: Failed to parse return parameter.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameterList: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameterList: No tokens available after return parameter.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameterList: No tokens available after comma.\n");
            return NULL;
        }

        if (!parser_isFullType(parser))
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a full type after comma in return parameter list.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseReturnParameterList: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseReturnParameterList: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        fullTypeNode = parser_parseFullType(parser);
        if (fullTypeNode == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameterList: Failed to parse return parameter.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameterList: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameterList: No tokens available to parse return parameter list.\n");
            return NULL;
        }
    }

    AstNode *returnParameterListNode = astNode_create(parser->astArena, AST_RETURN_PARAMETER_LIST, NULL, children);
    if (returnParameterListNode == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameterList: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return returnParameterListNode;
}

AstNode *parser_parseFunctionParameterList(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameterList: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameterList: No tokens available to parse function parameter list.\n");
        return NULL;
    }

    if (!parser_isFullType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a full type in function parameter list.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameterList: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameterList: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    AstNode *functionParameterNode = parser_parseFunctionParameter(parser);
    if (functionParameterNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameterList: Failed to parse first function parameter.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, functionParameterNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameterList: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameterList: No tokens available after first function parameter.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameterList: No tokens available after comma.\n");
            return NULL;
        }

        if (!parser_isFullType(parser))
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a full type after comma in function parameter list.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseFunctionParameterList: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseFunctionParameterList: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        functionParameterNode = parser_parseFunctionParameter(parser);
        if (functionParameterNode == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameterList: Failed to parse function parameter.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, functionParameterNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameterList: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameterList: No tokens available to parse function parameter list.\n");
            return NULL;
        }
    }

    AstNode *functionParameterListNode = astNode_create(parser->astArena, AST_FUNCTION_PARAMETER_LIST, NULL, children);
    if (functionParameterListNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameterList: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return functionParameterListNode;
}

AstNode *parser_parseFunctionParameter(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: No tokens available to parse function parameter.\n");
        return NULL;
    }

    if (!parser_isFullType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a full type for function parameter.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameter: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameter: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: No tokens available after type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after type in function parameter.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameter: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameter: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: token_copy failed with errno %d\n", errno);
        return NULL;
    }

    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;
    parser->tokens = parser->tokens->next; // Move past the identifier token

    AstNode *functionParameterNode = astNode_create(parser->astArena, AST_FUNCTION_PARAMETER, tokens, children);
    if (functionParameterNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return functionParameterNode;
}

AstNode *parser_parseGlobalVariableDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseImport: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseImport: No tokens available to parse variable global declaration.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (!parser_isFullType(parser) && currentTokenType != TOKEN_KEYWORD_EXPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a full type for global variable declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }
    
    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_EXPORT)
    {
        Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (exportToken == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, NULL, exportToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the export token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after export keyword.\n");
            return NULL;
        }
    }

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after type in global variable declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after identifier.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after comma.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_EXPORT)
        {
            Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
            if (exportToken == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclaration: token_copy failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Token_create(parser->astArena, tokens, exportToken);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
                return NULL;
            }
            tokens = head;

            parser->tokens = parser->tokens->next; // Move past the export token
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after export keyword.\n");
                return NULL;
            }
        }

        AstNode *fullTypeNode = parser_parseFullType(parser);
        if (fullTypeNode == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: Failed to parse full type after comma.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available to parse global variable declaration.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after type in global variable declaration.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclaration: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after additional identifier.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type == TOKEN_EQUALS)
    {
        parser->tokens = parser->tokens->next; // Move past the equals token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after equals sign.\n");
            return NULL;
        }

        AstNode *expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: Failed to parse expression after equals sign.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected semicolon after global variable identifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *globalVariableDeclarationNode = astNode_create(parser->astArena, AST_GLOBAL_VARIABLE_DECLARATION, tokens, children);
    if (globalVariableDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return globalVariableDeclarationNode;
}

AstNode *parser_parseStructDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: No tokens available to parse.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_KEYWORD_STRUCT && currentTokenType != TOKEN_KEYWORD_EXPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'struct' or 'export' keyword for struct declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_EXPORT)
    {
        Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (exportToken == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, exportToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the export token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseTypedefDeclaration: No tokens available after export keyword.\n");
            return NULL;
        }
    }

    parser->tokens = parser->tokens->next; // Move past the struct token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: No tokens available after struct keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after struct keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: No tokens available after struct identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '{' after struct identifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: No tokens available after open curly brace.\n");
        return NULL;
    }

    AstNode *members = parser_parseStructUnionMemberDeclaration(parser);
    if (members == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: Failed to parse struct members declaration.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, members);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: No tokens available after struct members declaration.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '}' to close struct declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close curly brace token

    AstNode *structNode = astNode_create(parser->astArena, AST_STRUCT_DECLARATION, tokens, children);
    if (structNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return structNode;
}

AstNode *parser_parseUnionDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: No tokens available to parse.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_KEYWORD_UNION && currentTokenType != TOKEN_KEYWORD_EXPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'union' or 'export' keyword for union declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_EXPORT)
    {
        Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (exportToken == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, exportToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the export token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseTypedefDeclaration: No tokens available after export keyword.\n");
            return NULL;
        }
    }

    parser->tokens = parser->tokens->next; // Move past the union token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: No tokens available after union keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after union keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: No tokens available after union identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '{' after union identifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: No tokens available after open curly brace.\n");
        return NULL;
    }

    AstNode *members = parser_parseStructUnionMemberDeclaration(parser);
    if (members == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: Failed to parse union member declaration.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, members);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: No tokens available after union member declaration.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '}' to close union declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close curly brace token

    AstNode *unionNode = astNode_create(parser->astArena, AST_UNION_DECLARATION, tokens, children);
    if (unionNode == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return unionNode;
}

AstNode *parser_parseStructUnionMemberDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available to parse struct/union member declaration.\n");
        return NULL;
    }

    if (!parser_isFullType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a full type for struct/union member declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after type in struct/union member declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected semicolon after struct/union member identifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after semicolon.\n");
        return NULL;
    }

    while (parser_isFullType(parser))
    {
        fullTypeNode = parser_parseFullType(parser);
        if (fullTypeNode == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: Failed to parse full type.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after type.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after type in struct/union member declaration.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after identifier.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected semicolon after struct/union member identifier.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the semicolon token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after semicolon.\n");
            return NULL;
        }
    }

    AstNode *structUnionMemberDeclarationNode = astNode_create(parser->astArena, AST_STRUCT_UNION_MEMBER_DECLARATION, tokens, children);
    if (structUnionMemberDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return structUnionMemberDeclarationNode;
}

AstNode *parser_parseStructUniondeclarator(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseStructUniondeclarator: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUniondeclarator: No tokens available to parse struct/union declarator.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '{' to start struct/union declarator.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUniondeclarator: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUniondeclarator: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUniondeclarator: No tokens available after open curly brace.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type == TOKEN_DOT)
    {
        AstNode *directDeclaratorNode = parser_parseStructUnionDirectDeclarator(parser);
        if (directDeclaratorNode == NULL)
        {
            DEBUG_PRINT("parser_parseStructUniondeclarator: Failed to parse struct/union direct declarator.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, directDeclaratorNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUniondeclarator: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        AstNode *indirectDeclaratorNode = parser_parseStructUnionIndirectDeclarator(parser);
        if (indirectDeclaratorNode == NULL)
        {
            DEBUG_PRINT("parser_parseStructUniondeclarator: Failed to parse struct/union indirect declarator.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, indirectDeclaratorNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUniondeclarator: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '}' to close struct/union declarator.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUniondeclarator: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUniondeclarator: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close curly brace token

    AstNode *structUniondeclarator = astNode_create(parser->astArena, AST_STRUCT_UNION_DECLARATOR, NULL, children);
    if (structUniondeclarator == NULL)
    {
        DEBUG_PRINT("parser_parseStructUniondeclarator: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return structUniondeclarator;
}

AstNode *parser_parseStructUnionIndirectDeclarator(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: No tokens available to parse struct/union indirect declarator.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    AstNode *expressionNode = parser_parseExpression(parser);
    if (expressionNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: Failed to parse expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, expressionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: No tokens available after expression.\n");
        return NULL;
    }
    
    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: No tokens available after comma.\n");
            return NULL;
        }

        expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: Failed to parse expression after comma.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: No tokens available after expression.\n");
            return NULL;
        }
    }

    AstNode *indirectDeclaratorNode = astNode_create(parser->astArena, AST_STRUCT_UNION_INDIRECT_DECLARATOR, NULL, children);
    if (indirectDeclaratorNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionIndirectDeclarator: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return indirectDeclaratorNode;
}

AstNode *parser_parseStructUnionDirectDeclarator(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available to parse struct/union direct declarator.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_DOT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '.' to start struct/union direct declarator.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the dot token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after dot.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected identifier after '.' in struct/union direct declarator.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_EQUALS)
    {
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected '=' after identifier in struct/union direct declarator.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the equals token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after equals.\n");
        return NULL;
    }

    AstNode *expressionNode = parser_parseExpression(parser);
    if (expressionNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: Failed to parse expression after '='.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, expressionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after expression.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after comma.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_DOT)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '.' after comma in struct/union direct declarator.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the dot token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after dot.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after '.' in struct/union direct declarator.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after identifier.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_EQUALS)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '=' after identifier in struct/union direct declarator.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the equals token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after equals.\n");
            return NULL;
        }

        expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: Failed to parse expression after '='.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: No tokens available after expression.\n");
            return NULL;
        }
    }

    AstNode *structUnionDirectDeclaratorNode = astNode_create(parser->astArena, AST_STRUCT_UNION_DIRECT_DECLARATOR, tokens, children);
    if (structUnionDirectDeclaratorNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionDirectDeclarator: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return structUnionDirectDeclaratorNode; 
}

AstNode *parser_parseEnumDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseImport: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: No tokens available to parse enum declaration.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_KEYWORD_ENUM && currentTokenType != TOKEN_KEYWORD_EXPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'enum' keyword to start enum declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_EXPORT)
    {
        Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (exportToken == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, exportToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the export token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: No tokens available after export keyword.\n");
            return NULL;
        }
    }

    parser->tokens = parser->tokens->next; // Move past the enum keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: No tokens available after enum keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after 'enum' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '{' to start enum body.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: No tokens available after open curly brace.\n");
        return NULL;
    }

    AstNode *enumValueDeclarationNode = parser_parseEnumValueDeclaration(parser);
    if (enumValueDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: Failed to parse enum value declaration.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, enumValueDeclarationNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: No tokens available after enum value declaration.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '}' to close enum body.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close curly brace token

    AstNode *enumDeclarationNode = astNode_create(parser->astArena, AST_ENUM_DECLARATION, tokens, children);
    if (enumDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseEnumDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return enumDeclarationNode;
}

AstNode *parser_parseEnumValueDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclaration: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclaration: No tokens available to parse enum value declaration.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier for enum value.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclaration: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type == TOKEN_EQUALS)
    {
        parser->tokens = parser->tokens->next; // Move past the equals token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: No tokens available after equals.\n");
            return NULL;
        }

        AstNode *expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: Failed to parse expression after '='.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: No tokens available after expression.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_COMMA)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ',' after enum value declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the comma token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclaration: No tokens available after comma.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_IDENTIFIER)
    {
        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: No tokens available after identifier.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type == TOKEN_EQUALS)
        {
            parser->tokens = parser->tokens->next; // Move past the equals token
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseEnumValueDeclaration: No tokens available after equals.\n");
                return NULL;
            }

            AstNode *expressionNode = parser_parseExpression(parser);
            if (expressionNode == NULL)
            {
                DEBUG_PRINT("parser_parseEnumValueDeclaration: Failed to parse expression after '='.\n");
                return NULL;
            }
            head = linkedList_Ast_create(parser->astArena, children, expressionNode);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseEnumValueDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;

            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseEnumValueDeclaration: No tokens available after expression.\n");
                return NULL;
            }
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_COMMA)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ',' after enum value declaration.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseEnumValueDeclaration: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseEnumValueDeclaration: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseEnumValueDeclaration: No tokens available after comma.\n");
            return NULL;
        }
    }

    AstNode *enumValueDeclarationNode = astNode_create(parser->astArena, AST_ENUM_VALUE_DECLARATION, tokens, children);
    if (enumValueDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseEnumValueDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return enumValueDeclarationNode;
}

AstNode *parser_parseTypedefDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseImport: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseTypedefDeclaration: No tokens available to parse.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType == TOKEN_KEYWORD_TYPEDEF && currentTokenType != TOKEN_KEYWORD_EXPORT)
    {
        DEBUG_PRINT("parser_parseTypedefDeclaration: Expected TOKEN_KEYWORD_TYPEDEF, got %s.\n", token_typeToString(((Token *)parser->tokens->data)->type));
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_EXPORT)
    {
        Token *exportToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (exportToken == NULL)
        {
            DEBUG_PRINT("parser_parseTypedefDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }

        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, exportToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseTypedefDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the export token
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseTypedefDeclaration: No tokens available after export keyword.\n");
        return NULL;
    }
    parser->tokens = parser->tokens->next; // Move past the typedef token

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseTypedefDeclaration: No tokens available after typedef keyword.\n");
        return NULL;
    }

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        DEBUG_PRINT("parser_parseTypedefDeclaration: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseTypedefDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseTypedefDeclaration: No tokens available after type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected identifier after type in typedef declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseTypedefDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }

        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseTypedefDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseTypedefDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }

    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseTypedefDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    AstNode *typedefNode = astNode_create(parser->astArena, AST_TYPEDEF, tokens, children);
    if (typedefNode == NULL)
    {
        DEBUG_PRINT("parser_parseTypedefDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }

    return typedefNode;
}

AstNode *parser_parseStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStatement: No tokens available to parse statement.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType == TOKEN_KEYWORD_IF ||
        currentTokenType == TOKEN_KEYWORD_SWITCH )
    {
        AstNode *branchStatementNode = parser_parseBranchStatement(parser);
        if (branchStatementNode == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: Failed to parse branch statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, branchStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (   currentTokenType == TOKEN_KEYWORD_FOR ||
                currentTokenType == TOKEN_KEYWORD_FOREACH ||
                currentTokenType == TOKEN_KEYWORD_WHILE ||
                currentTokenType == TOKEN_KEYWORD_DO )
    {
        AstNode *loopStatementNode = parser_parseLoopStatement(parser);
        if (loopStatementNode == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: Failed to parse loop statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, loopStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_OPEN_CURLY)
    {
        AstNode *compoundStatementNode = parser_parseCompoundStatement(parser);
        if (compoundStatementNode == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: Failed to parse compound statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, compoundStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (   currentTokenType == TOKEN_KEYWORD_GOTO ||
                currentTokenType == TOKEN_KEYWORD_RETURN ||
                currentTokenType == TOKEN_KEYWORD_BREAK ||
                currentTokenType == TOKEN_KEYWORD_CONTINUE)
    {
        AstNode *jumpStatementNode = parser_parseJumpStatement(parser);
        if (jumpStatementNode == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: Failed to parse jump statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, jumpStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        AstNode *expressionStatementNode = parser_parseExpressionStatement(parser);
        if (expressionStatementNode == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: Failed to parse expression statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, expressionStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *statementNode = astNode_create(parser->astArena, AST_STATEMENT, NULL, children);
    if (statementNode == NULL)
    {
        DEBUG_PRINT("parser_parseStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return statementNode;
}

AstNode *parser_parseBranchStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseBranchStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseBranchStatement: No tokens available to parse branch statement.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_KEYWORD_IF &&
        currentTokenType != TOKEN_KEYWORD_SWITCH)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'if' or 'switch' keyword to start branch statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseBranchStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseBranchStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_IF)
    {
        AstNode *ifStatement = parser_parseIfStatement(parser);
        if (ifStatement == NULL)
        {
            DEBUG_PRINT("parser_parseBranchStatement: Failed to parse if condition.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, ifStatement);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseBranchStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        AstNode *switchStatement = parser_parseSwitchStatement(parser);
        if (switchStatement == NULL)
        {
            DEBUG_PRINT("parser_parseBranchStatement: Failed to parse switch condition.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, switchStatement);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseBranchStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *branchStatementNode = astNode_create(parser->astArena, AST_BRANCH_STATEMENT, NULL, children);
    if (branchStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseBranchStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return branchStatementNode;
}

AstNode *parser_parseIfStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available to parse if statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_IF)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'if' keyword to start if statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'if' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available after 'if' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '(' after 'if' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *conditionNode = parser_parseExpression(parser);
    if (conditionNode == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: Failed to parse condition expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, conditionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available after condition expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ')' to close condition expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available after close parenthesis.\n");
        return NULL;
    }

    AstNode *ifBodyNode = parser_parseStatement(parser);
    if (ifBodyNode == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: Failed to parse if body statement.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, ifBodyNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available after if body statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_ELSE)
    {
        parser->tokens = parser->tokens->next; // Move past the 'else' keyword
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: No tokens available after 'else' keyword.\n");
            return NULL;
        }

        AstNode *elseBodyNode = parser_parseStatement(parser);
        if (elseBodyNode == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: Failed to parse else body statement.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, elseBodyNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: No tokens available after else body statement.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_ENDIF)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'endif' keyword to end if statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseIfStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the 'endif' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: No tokens available after 'endif' keyword.\n");
        return NULL;
    }

    AstNode *ifStatementNode = astNode_create(parser->astArena, AST_IF_STATEMENT, NULL, children);
    if (ifStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseIfStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return ifStatementNode;
}

AstNode *parser_parseSwitchStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: No tokens available to parse switch statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_SWITCH)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'switch' keyword to start switch statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'switch' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: No tokens available after 'switch' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '(' after 'switch' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *conditionNode = parser_parseExpression(parser);
    if (conditionNode == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: Failed to parse switch condition expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, conditionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: No tokens available after switch condition expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ')' to close switch condition expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: No tokens available after close parenthesis.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '{' to start switch body.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: No tokens available after open curly brace.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_CASE ||
           ((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_DEFAULT)
    {
        AstNode *caseNode;
        if (((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_CASE)
        {
            caseNode = parser_parseSwitchCase(parser);
        }
        else
        {
            caseNode = parser_parseSwitchDefault(parser);
        }
        if (caseNode == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: Failed to parse case statement.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, caseNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: No tokens available after case statement.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '}' to close switch body.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close curly brace token

    AstNode *switchNode = astNode_create(parser->astArena, AST_SWITCH_STATEMENT, NULL, children);
    if (switchNode == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return switchNode;
}

AstNode *parser_parseSwitchCase(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: No tokens available to parse case statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_CASE)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'case' keyword to start case statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchCase: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchCase: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'case' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: No tokens available after 'case' keyword.\n");
        return NULL;
    }

    AstNode *caseValueNode = parser_parseExpression(parser);
    if (caseValueNode == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: Failed to parse case value expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, caseValueNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: No tokens available after case value expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_COLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ':' after case value expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchCase: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchCase: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the colon token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: No tokens available after colon.\n");
        return NULL;
    }

    AstNode *caseBodyNode = parser_parseStatement(parser);
    if (caseBodyNode == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: Failed to parse case body statement.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, caseBodyNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *caseNode = astNode_create(parser->astArena, AST_SWITCH_CASE, NULL, children);
    if (caseNode == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchCase: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return caseNode;
}

AstNode *parser_parseSwitchDefault(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchDefault: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchDefault: No tokens available to parse default statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_DEFAULT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'default' keyword to start default statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchDefault: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchDefault: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'default' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchDefault: No tokens available after 'default' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_COLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ':' after 'default' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchDefault: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseSwitchDefault: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the colon token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchDefault: No tokens available after colon.\n");
        return NULL;
    }

    AstNode *defaultBodyNode = parser_parseStatement(parser);
    if (defaultBodyNode == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchDefault: Failed to parse default body statement.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, defaultBodyNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchDefault: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *defaultNode = astNode_create(parser->astArena, AST_SWITCH_DEFAULT, NULL, children);
    if (defaultNode == NULL)
    {
        DEBUG_PRINT("parser_parseSwitchDefault: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return defaultNode;
}

AstNode *parser_parseLoopStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseLoopStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseLoopStatement: No tokens available to parse loop statement.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_KEYWORD_FOR &&
        currentTokenType != TOKEN_KEYWORD_FOREACH &&
        currentTokenType != TOKEN_KEYWORD_WHILE &&
        currentTokenType != TOKEN_KEYWORD_DO)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'for', 'foreach', 'while', or 'do' keyword to start loop statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_FOR)
    {
        AstNode *forStatementNode = parser_parseForStatement(parser);
        if (forStatementNode == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: Failed to parse for statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, forStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_KEYWORD_FOREACH)
    {
        AstNode *foreachStatementNode = parser_parseForeachStatement(parser);
        if (foreachStatementNode == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: Failed to parse foreach statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, foreachStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_KEYWORD_WHILE)
    {
        AstNode *whileStatementNode = parser_parseWhileStatement(parser);
        if (whileStatementNode == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: Failed to parse while statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, whileStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else // DO_WHILE
    {
        AstNode *doWhileStatementNode = parser_parseDoWhileStatement(parser);
        if (doWhileStatementNode == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: Failed to parse do-while statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, doWhileStatementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLoopStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *loopStatementNode = astNode_create(parser->astArena, AST_LOOP_STATEMENT, NULL, children);
    if (loopStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseLoopStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return loopStatementNode;
}

AstNode *parser_parseForStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: No tokens available to parse for statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_FOR)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'for' keyword to start for statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'for' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: No tokens available after 'for' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '(' after 'for' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: No tokens available after open parenthesis.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        AstNode *initNode = parser_parseForInitializer(parser);
        if (initNode == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: Failed to parse for initializer.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, initNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: No tokens available after first part of for statement.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ';' after first part of for statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;
    }

    parser->tokens = parser->tokens->next; // Move past the first semicolon token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: No tokens available after first part of for statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        AstNode *conditionNode = parser_parseForCondition(parser);
        if (conditionNode == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: Failed to parse condition expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, conditionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: No tokens available after condition expression.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ';' after condition expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the second semicolon token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: No tokens available after second semicolon.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        AstNode *incrementNode = parser_parseForIncrementation(parser);
        if (incrementNode == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: Failed to parse increment expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, incrementNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: No tokens available after increment expression.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ')' to close for statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: No tokens available after close parenthesis.\n");
        return NULL;
    }

    AstNode *bodyNode = parser_parseStatement(parser);
    if (bodyNode == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: Failed to parse for statement body.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, bodyNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *forStatementNode = astNode_create(parser->astArena, AST_FOR_STATEMENT, NULL, children);
    if (forStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseForStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return forStatementNode;
}

AstNode *parser_parseForInitializer(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseForInitializer: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForInitializer: No tokens available to parse for initializer.\n");
        return NULL;
    }

    if (parser->tokens->next == NULL)
    {
        DEBUG_PRINT("parser_parseForInitializer: Reached end of tokens while parsing for initializer.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    if (parser_isTypeSpecifier(parser) || ( parser_isType(parser) && (((Token *)parser->tokens->next->data)->type == TOKEN_IDENTIFIER)))
    {
        AstNode *variableDeclarationNode = parser_parseVariableDeclaration(parser);
        if (variableDeclarationNode == NULL)
        {
            DEBUG_PRINT("parser_parseForInitializer: Failed to parse variable declaration.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, variableDeclarationNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForInitializer: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        AstNode *assignementExpretionNode = parser_parseAssignmentExpression(parser);
        if (assignementExpretionNode == NULL)
        {
            DEBUG_PRINT("parser_parseForInitializer: Failed to parse expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, assignementExpretionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForInitializer: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *initializerNode = astNode_create(parser->astArena, AST_FOR_INITIALIZER, NULL, children);
    if (initializerNode == NULL)
    {
        DEBUG_PRINT("parser_parseForInitializer: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return initializerNode;
}

AstNode *parser_parseForCondition(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseForCondition: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForCondition: No tokens available to parse for condition.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    AstNode *conditionNode = parser_parseExpression(parser);
    if (conditionNode == NULL)
    {
        DEBUG_PRINT("parser_parseForCondition: Failed to parse condition expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, conditionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForCondition: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *conditionAstNode = astNode_create(parser->astArena, AST_FOR_CONDITION, NULL, children);
    if (conditionAstNode == NULL)
    {
        DEBUG_PRINT("parser_parseForCondition: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return conditionAstNode;
}

AstNode *parser_parseForIncrementation(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseForIncrementation: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForIncrementation: No tokens available to parse for incrementation.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    AstNode *incrementNode = parser_parseExpression(parser);
    if (incrementNode == NULL)
    {
        DEBUG_PRINT("parser_parseForIncrementation: Failed to parse increment expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, incrementNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForIncrementation: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *incrementationAstNode = astNode_create(parser->astArena, AST_FOR_INCREMENTATION, NULL, children);
    if (incrementationAstNode == NULL)
    {
        DEBUG_PRINT("parser_parseForIncrementation: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return incrementationAstNode;
}

AstNode *parser_parseForeachStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available to parse foreach statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_FOREACH)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'foreach' keyword to start foreach statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'foreach' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after 'foreach' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '(' after 'foreach' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after open parenthesis.\n");
        return NULL;
    }

   AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected an identifier after type in foreach statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_COLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ':' after identifier in foreach statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the colon token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after colon.\n");
        return NULL;
    }

    identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the second identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after second identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ')' to close foreach statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseForeachStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: No tokens available after close parenthesis.\n");
        return NULL;
    }

    AstNode *bodyStatementNode = parser_parseStatement(parser);
    if (bodyStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: Failed to parse foreach statement body.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, bodyStatementNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *foreachStatementNode = astNode_create(parser->astArena, AST_FOREACH_STATEMENT, tokens, children);
    if (foreachStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseForeachStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return foreachStatementNode;
}

AstNode *parser_parseWhileStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: No tokens available to parse while statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_WHILE)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'while' keyword to start while statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'while' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: No tokens available after 'while' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '(' after 'while' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *conditionNode = parser_parseExpression(parser);
    if (conditionNode == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: Failed to parse condition expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, conditionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: No tokens available after condition expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ')' to close while statement condition.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: No tokens available after close parenthesis.\n");
        return NULL;
    }

    AstNode *bodyNode = parser_parseStatement(parser);
    if (bodyNode == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: Failed to parse while statement body.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, bodyNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *whileStatementNode = astNode_create(parser->astArena, AST_WHILE_STATEMENT, NULL, children);
    if (whileStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseWhileStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return whileStatementNode;
}

AstNode *parser_parseDoWhileStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available to parse do-while statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_DO)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'do' keyword to start do-while statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'do' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available after 'do' keyword.\n");
        return NULL;
    }

    AstNode *bodyNode = parser_parseStatement(parser);
    if (bodyNode == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: Failed to parse do-while statement body.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, bodyNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available after do-while body.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_WHILE)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'while' keyword after do-while body.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the 'while' keyword
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available after 'while' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '(' after 'while' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available after open parenthesis.\n");
        return NULL;
    }

    AstNode *conditionNode = parser_parseExpression(parser);
    if (conditionNode == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: Failed to parse condition expression.\n");
        return NULL;
    }
    head = linkedList_Ast_create(parser->astArena, children, conditionNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available after condition expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ')' to close do-while statement condition.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: No tokens available after close parenthesis.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ';' after do-while condition.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseDoWhileStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *doWhileStatementNode = astNode_create(parser->astArena, AST_DO_WHILE_STATEMENT, NULL, children);
    if (doWhileStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseDoWhileStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return doWhileStatementNode;
}

AstNode *parser_parseCompoundStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseCompoundStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseCompoundStatement: No tokens available to parse compound statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '{' to start compound statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the open curly brace token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseCompoundStatement: No tokens available after open curly brace.\n");
        return NULL;
    }

    if (parser->tokens->next == NULL)
    {
        DEBUG_PRINT("parser_parseCompoundStatement: No next token available after open curly brace.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        if (((Token *)parser->tokens->data)->type == TOKEN_IDENTIFIER && ((Token *)parser->tokens->next->data)->type == TOKEN_COLON)
        {
            AstNode *labelNode = parser_parseLabel(parser);
            if (labelNode == NULL)
            {
                DEBUG_PRINT("parser_parseCompoundStatement: Failed to parse label.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, labelNode);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseCompoundStatement: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }
        else
        {
            AstNode *statementNode = parser_parseStatement(parser);
            if (statementNode == NULL)
            {
                DEBUG_PRINT("parser_parseCompoundStatement: Failed to parse statement.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, statementNode);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseCompoundStatement: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;
        }

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: No tokens available while parsing compound statement.\n");
            return NULL;
        }

        if (parser->tokens->next == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: Reached end of tokens while parsing compound statement.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '}' to close compound statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '}' to close compound statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseCompoundStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close curly brace token

    AstNode *compoundStatementNode = astNode_create(parser->astArena, AST_COMPOUND_STATEMENT, NULL, children);
    if (compoundStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseCompoundStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return compoundStatementNode;
}

AstNode *parser_parseLabel(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseLabel: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseLabel: No tokens available to parse label.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier to start label.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseLabel: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLabel: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseLabel: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->utilsArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseLabel: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseLabel: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_COLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ':' after label identifier.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseLabel: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseLabel: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the colon token

    AstNode *labelNode = astNode_create(parser->astArena, AST_LABEL, tokens, NULL);
    if (labelNode == NULL)
    {
        DEBUG_PRINT("parser_parseLabel: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return labelNode;
}

AstNode *parser_parseExpressionStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseExpressionStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseExpressionStatement: No tokens available to parse expression statement.\n");
        return NULL;
    }

    if (parser->tokens->next == NULL)
    {
        DEBUG_PRINT("parser_parseExpressionStatement: No next token available after current token.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    if (parser_isTypeSpecifier(parser) || (parser_isType(parser) && (((Token *)parser->tokens->next->data)->type == TOKEN_IDENTIFIER)))
    {
        AstNode *variableDeclarationNode = parser_parseVariableDeclaration(parser);
        if (variableDeclarationNode == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: Failed to parse variable declaration.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, variableDeclarationNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: No tokens available after variable declaration.\n");
            return NULL;
        }
    }
    else if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        AstNode *expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: Failed to parse expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: No tokens available after expression.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ';' after variable declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseExpressionStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *expressionStatementNode = astNode_create(parser->astArena, AST_EXPRESSION_STATEMENT, NULL, children);
    if (expressionStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseExpressionStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return expressionStatementNode;
}

AstNode *parser_parseVariableDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available to parse variable declaration.\n");
        return NULL;
    }

    if (!parser_isFullType(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected full type to start variable declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    AstNode *fullTypeNode = parser_parseFullType(parser);
    if (fullTypeNode == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: Failed to parse full type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after type.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after type in variable declaration.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after identifier.\n");
        return NULL;
    }

    while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
    {
        parser->tokens = parser->tokens->next; // Move past the comma token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after comma.\n");
            return NULL;
        }

        AstNode *fullTypeNode = parser_parseFullType(parser);
        if (fullTypeNode == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: Failed to parse full type after comma.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after type.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after comma in variable declaration.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseVariableDeclaration: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after identifier.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type == TOKEN_EQUALS)
    {
        parser->tokens = parser->tokens->next; // Move past the assignment token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: No tokens available after assignment.\n");
            return NULL;
        }

        AstNode *expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: Failed to parse assignment expression.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *variableDeclarationNode = astNode_create(parser->astArena, AST_VARIABLE_DECLARATION, tokens, children);
    if (variableDeclarationNode == NULL)
    {
        DEBUG_PRINT("parser_parseVariableDeclaration: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return variableDeclarationNode;
}

AstNode *parser_parseJumpStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseJumpStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseJumpStatement: No tokens available to parse jump statement.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_KEYWORD_GOTO &&
        currentTokenType != TOKEN_KEYWORD_RETURN &&
        currentTokenType != TOKEN_KEYWORD_BREAK &&
        currentTokenType != TOKEN_KEYWORD_CONTINUE)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'goto', 'return', 'break', or 'continue' keyword to start jump statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_KEYWORD_GOTO)
    {
        AstNode *gotoNode = parser_parseGotoStatement(parser);
        if (gotoNode == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: Failed to parse goto statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, gotoNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_KEYWORD_RETURN)
    {
        AstNode *returnNode = parser_parseReturnStatement(parser);
        if (returnNode == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: Failed to parse return statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, returnNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_KEYWORD_BREAK)
    {
        AstNode *breakNode = parser_parseBreakStatement(parser);
        if (breakNode == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: Failed to parse break statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, breakNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_KEYWORD_CONTINUE)
    {
        AstNode *continueNode = parser_parseContinueStatement(parser);
        if (continueNode == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: Failed to parse continue statement.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, continueNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseJumpStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *jumpStatementNode = astNode_create(parser->astArena, AST_JUMP_STATEMENT, NULL, children);
    if (jumpStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseJumpStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return jumpStatementNode;
}

AstNode *parser_parseGotoStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: No tokens available to parse goto statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_GOTO)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'goto' keyword to start goto statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'goto' keyword token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: No tokens available after 'goto' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after 'goto' keyword.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (identifierToken == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: token_copy failed with errno %d\n", errno);
        return NULL;
    }
    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: linkedList_Token_create failed with errno %d\n", errno);
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the identifier token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: No tokens available after identifier.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_WHEN)
    {
        parser->tokens = parser->tokens->next; // Move past the 'when' keyword token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: No tokens available after 'when' keyword.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '(' after 'when' keyword in goto statement.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseGotoStatement: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseGotoStatement: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the open parenthesis token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: No tokens available after open parenthesis.\n");
            return NULL;
        }

        AstNode *conditionNode = parser_parseExpression(parser);
        if (conditionNode == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: Failed to parse condition expression.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, conditionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ')' to close condition in goto statement.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseGotoStatement: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseGotoStatement: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the close parenthesis token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: No tokens available after close parenthesis.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ';' to end goto statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGotoStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *gotoStatementNode = astNode_create(parser->astArena, AST_GOTO_STATEMENT, tokens, children);
    if (gotoStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseGotoStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return gotoStatementNode;
}

AstNode *parser_parseReturnStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseReturnStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseReturnStatement: No tokens available to parse return statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_RETURN)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'return' keyword to start return statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseReturnStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseReturnStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the 'return' keyword token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseReturnStatement: No tokens available after 'return' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        AstNode *expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseReturnStatement: Failed to parse return expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseReturnStatement: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseReturnStatement: No tokens available after return expression.\n");
            return NULL;
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ';' to end return statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseReturnStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseReturnStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *returnStatementNode = astNode_create(parser->astArena, AST_RETURN_STATEMENT, NULL, children);
    if (returnStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseReturnStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return returnStatementNode;
}

AstNode *parser_parseBreakStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseBreakStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseBreakStatement: No tokens available to parse break statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_BREAK)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'break' keyword to start break statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseBreakStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseBreakStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the 'break' keyword token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseBreakStatement: No tokens available after 'break' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ';' to end break statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseBreakStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseBreakStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *breakStatementNode = astNode_create(parser->astArena, AST_BREAK_STATEMENT, NULL, NULL);
    if (breakStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseBreakStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return breakStatementNode;
}

AstNode *parser_parseContinueStatement(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseContinueStatement: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseContinueStatement: No tokens available to parse continue statement.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_CONTINUE)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'continue' keyword to start continue statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseContinueStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseContinueStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the 'continue' keyword token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseContinueStatement: No tokens available after 'continue' keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ';' to end continue statement.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseContinueStatement: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseContinueStatement: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstNode *continueStatementNode = astNode_create(parser->astArena, AST_CONTINUE_STATEMENT, NULL, NULL);
    if (continueStatementNode == NULL)
    {
        DEBUG_PRINT("parser_parseContinueStatement: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return continueStatementNode;
}

AstNode *parser_parseExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseExpression: No tokens available to parse expression.\n");
        return NULL;
    }

    LinkedList *children = NULL;


    AstNode *assignmentNode = parser_parseLogicalOrExpression(parser);
    if (assignmentNode == NULL)
    {
        DEBUG_PRINT("parser_parseExpression: Failed to parse logical or expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, assignmentNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseExpression: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    
    AstNode *expressionNode = astNode_create(parser->astArena, AST_EXPRESSION, NULL, children);
    if (expressionNode == NULL)
    {
        DEBUG_PRINT("parser_parseExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return expressionNode;
}

// TODO
AstNode *parser_parseAssignmentExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseLogicalOrExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseLogicalAndExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseBitwiseOrExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseBitwiseXorExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseBitwiseAndExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseEqualityExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseRelationalExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseShiftExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseAdditiveExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseMultiplicativeExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseTypeCastExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseTypeCastExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseTypeCastExpression: No tokens available to parse type cast expression.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    if (((Token *)parser->tokens->data)->type == TOKEN_OPEN_PARENTHESIS)
    {
        parser->tokens = parser->tokens->next; // Move past the open parenthesis token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseTypeCastExpression: No tokens available after open parenthesis.\n");
            return NULL;
        }

        AstNode *fullTypeNode = parser_parseFullType(parser);
        if (fullTypeNode == NULL)
        {
            DEBUG_PRINT("parser_parseTypeCastExpression: Failed to parse full type.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, fullTypeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseTypeCastExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseTypeCastExpression: No tokens available after full type.\n");
            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ')' to close type cast expression.");
            if (error == NULL)
            {
                DEBUG_PRINT("parser_parseTypeCastExpression: error_create failed with errno %d\n", errno);
                return NULL;
            }
            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseTypeCastExpression: linkedList_Error_create failed with errno %d\n", errno);
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the close parenthesis token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseTypeCastExpression: No tokens available after close parenthesis.\n");
            return NULL;
        }

        AstNode *typeCastExpressionNode = parser_parseTypeCastExpression(parser);
        if (typeCastExpressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseTypeCastExpression: Failed to parse type cast expression after type.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, typeCastExpressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseTypeCastExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        AstNode *unaryExpressionNode = parser_parseUnaryExpression(parser);
        if (unaryExpressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseTypeCastExpression: Failed to parse unary expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, unaryExpressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseTypeCastExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *typeCastExpression = astNode_create(parser->astArena, AST_TYPE_CAST_EXPRESSION, NULL, children);
    if (typeCastExpression == NULL)
    {
        DEBUG_PRINT("parser_parseTypeCastExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return typeCastExpression;
}

AstNode *parser_parseUnaryExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseUnaryExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnaryExpression: No tokens available to parse unary expression.\n");
        return NULL;
    }

    LinkedList *children = NULL;

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType == TOKEN_DOUBLE_PLUS || currentTokenType == TOKEN_DOUBLE_MINUS)
    {
        Token *operatorToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (operatorToken == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, children, operatorToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        parser->tokens = parser->tokens->next; // Move past the unary operator token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: No tokens available after unary operator.\n");
            return NULL;
        }

        AstNode *unaryExpressionNode = parser_parseUnaryExpression(parser);
        if (unaryExpressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: Failed to parse unary expression after operator.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, unaryExpressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (   currentTokenType == TOKEN_PLUS || currentTokenType == TOKEN_MINUS || 
                currentTokenType == TOKEN_STAR || currentTokenType == TOKEN_AMPERSAND ||
                currentTokenType == TOKEN_TILDE || currentTokenType == TOKEN_EXCLAMATION)
    {
        Token *operatorToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (operatorToken == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, children, operatorToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        parser->tokens = parser->tokens->next; // Move past the unary operator token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: No tokens available after unary operator.\n");
            return NULL;
        }

        AstNode *typeCastExpressionNode = parser_parseTypeCastExpression(parser);
        if (typeCastExpressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: Failed to parse unary expression after operator.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, typeCastExpressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_KEYWORD_SIZEOF)
    {
        AstNode *sizeofExpressionNode = parser_parseSizeofExpression(parser);
        if (sizeofExpressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: Failed to parse sizeof expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, sizeofExpressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_KEYWORD_TYPEOF)
    {
        AstNode *typeofExpressionNode = parser_parseTypeofExpression(parser);
        if (typeofExpressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: Failed to parse typeof expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeofExpressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        AstNode *postfixExpressionNode = parser_parsePostfixExpression(parser);
        if (postfixExpressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: Failed to parse postfix expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, postfixExpressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnaryExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    AstNode *unaryExpressionNode = astNode_create(parser->astArena, AST_UNARY_EXPRESSION, NULL, children);
    if (unaryExpressionNode == NULL)
    {
        DEBUG_PRINT("parser_parseUnaryExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return unaryExpressionNode;
}

AstNode *parser_parsePostfixExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixExpression: No tokens available to parse postfix expression.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_OPEN_CURLY && currentTokenType != TOKEN_IDENTIFIER && !parser_isLiteral(parser) && currentTokenType != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier, literal, or '(' to start postfix expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    if (((Token *)parser->tokens->data)->type == TOKEN_OPEN_CURLY)
    {
        AstNode *structUnionDeclaration = parser_parseStructUnionDeclaration(parser);
        if (structUnionDeclaration == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixExpression: Failed to parse struct or union declaration.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, structUnionDeclaration);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        AstNode *primaryExpressionNode = parser_parsePrimaryExpression(parser);
        if (primaryExpressionNode == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixExpression: Failed to parse primary expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, primaryExpressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixExpression: No tokens available after primary expression.\n");
            return NULL;
        }

        while (parser_isPostfixPrimeExpression(parser))
        {
            AstNode *postfixPrimeNode = parser_parsePostfixPrimeExpression(parser);
            if (postfixPrimeNode == NULL)
            {
                DEBUG_PRINT("parser_parsePostfixExpression: Failed to parse postfix prime expression.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Ast_create(parser->astArena, children, postfixPrimeNode);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parsePostfixExpression: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;

            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parsePostfixExpression: No tokens available after postfix prime expression.\n");
                return NULL;
            }
        }
    }

    AstNode *postfixExpressionNode = astNode_create(parser->astArena, AST_POSTFIX_EXPRESSION, NULL, children);
    if (postfixExpressionNode == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return postfixExpressionNode;
}

bool parser_isPostfixPrimeExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_isPostfixPrimeExpression: Parser is NULL.\n");
        return false;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_isPostfixPrimeExpression: No tokens available to check for postfix prime expression.\n");
        return false;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    return (currentTokenType == TOKEN_OPEN_PARENTHESIS || currentTokenType == TOKEN_OPEN_BRACKET || currentTokenType == TOKEN_DOT ||
            currentTokenType == TOKEN_DOUBLE_PLUS || currentTokenType == TOKEN_DOUBLE_MINUS);
}

AstNode *parser_parsePostfixPrimeExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixPrimeExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixPrimeExpression: No tokens available to parse postfix prime expression.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (parser_isPostfixPrimeExpression(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '(', '[', '.', '++', or '--' to start postfix prime expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixPrimeExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixPrimeExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;    
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_OPEN_PARENTHESIS)
    {
        AstNode *functionCallNode = parser_parseFunctionCallExpression(parser);
        if (functionCallNode == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixPrimeExpression: Failed to parse function call.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, functionCallNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixPrimeExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_OPEN_BRACKET)
    {
        AstNode *arrayIndexingNode = parser_parseArrayIndexingExpression(parser);
        if (arrayIndexingNode == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixPrimeExpression: Failed to parse array indexing.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, arrayIndexingNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePostfixPrimeExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        if (currentTokenType == TOKEN_DOT)
        {
            parser->tokens = parser->tokens->next; // Move past the dot token
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parsePostfixPrimeExpression: No tokens available after dot.\n");
                return NULL;
            }

            if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
            {
                Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier after '.' in postfix prime expression.");
                if (error == NULL)
                {
                    DEBUG_PRINT("parser_parsePostfixPrimeExpression: error_create failed with errno %d\n", errno);
                    return NULL;
                }
                LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
                if (head == NULL)
                {
                    DEBUG_PRINT("parser_parsePostfixPrimeExpression: linkedList_Error_create failed with errno %d\n", errno);
                    return NULL;
                }
                parser->errors = head;

                parser->tokens = parser->tokens->next; // Skip the unexpected token
                return NULL;
            }

            Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
            if (identifierToken == NULL)
            {
                DEBUG_PRINT("parser_parsePostfixPrimeExpression: token_copy failed with errno %d\n", errno);
                return NULL;
            }
            LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parsePostfixPrimeExpression: linkedList_Token_create failed with errno %d\n", errno);
                return NULL;
            }
            tokens = head;

            parser->tokens = parser->tokens->next; // Move past the dot token
        }
        else
        {
            Token *operatorToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
            if (operatorToken == NULL)
            {
                DEBUG_PRINT("parser_parsePostfixPrimeExpression: token_copy failed with errno %d\n", errno);
                return NULL;
            }
            LinkedList *head = linkedList_Token_create(parser->astArena, tokens, operatorToken);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parsePostfixPrimeExpression: linkedList_Token_create failed with errno %d\n", errno);
                return NULL;
            }
            tokens = head;

            parser->tokens = parser->tokens->next; // Move past the operator token
        }
    }

    AstNode *postfixPrimeNode = astNode_create(parser->astArena, AST_POSTFIX_PRIME_EXPRESSION, tokens, children);
    if (postfixPrimeNode == NULL)
    {
        DEBUG_PRINT("parser_parsePostfixPrimeExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return postfixPrimeNode;
}

AstNode *parser_parseArrayIndexingExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseArrayIndexingExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseArrayIndexingExpression: No tokens available to parse array indexing expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_BRACKET)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '[' to start array indexing expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseArrayIndexingExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseArrayIndexingExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the open bracket token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseArrayIndexingExpression: No tokens available after open bracket.\n");
        return NULL;
    }

    AstNode *indexNode = parser_parseExpression(parser);
    if (indexNode == NULL)
    {
        DEBUG_PRINT("parser_parseArrayIndexingExpression: Failed to parse array index expression.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, indexNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseArrayIndexingExpression: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseArrayIndexingExpression: No tokens available after array index expression.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_BRACKET)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ']' to close array indexing expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseArrayIndexingExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseArrayIndexingExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close bracket token

    AstNode *arrayIndexingNode = astNode_create(parser->astArena, AST_ARRAY_INDEXING_EXPRESSION, NULL, children);
    if (arrayIndexingNode == NULL)
    {
        DEBUG_PRINT("parser_parseArrayIndexingExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return arrayIndexingNode;
}

AstNode *parser_parseFunctionCallExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionCallExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionCallExpression: No tokens available to parse function call.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected '(' to start function call.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionCallExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionCallExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;
        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the open parenthesis token
    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionCallExpression: No tokens available after open parenthesis.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        AstNode *expressionNode = parser_parseExpression(parser);
        if (expressionNode == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionCallExpression: Failed to parse function call expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, expressionNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionCallExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionCallExpression: No tokens available after function call expression.\n");
            return NULL;
        }

        while (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
        {
            parser->tokens = parser->tokens->next; // Move past the comma token
            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseFunctionCallExpression: No tokens available after comma.\n");
                return NULL;
            }

            expressionNode = parser_parseExpression(parser);
            if (expressionNode == NULL)
            {
                DEBUG_PRINT("parser_parseFunctionCallExpression: Failed to parse function call expression.\n");
                return NULL;
            }
            head = linkedList_Ast_create(parser->astArena, children, expressionNode);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseFunctionCallExpression: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;

            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseFunctionCallExpression: No tokens available after function call expression.\n");
                return NULL;
            }
        }
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected ')' to close function call.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionCallExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionCallExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    parser->tokens = parser->tokens->next; // Move past the close parenthesis token

    AstNode *functionCallNode = astNode_create(parser->astArena, AST_FUNCTION_CALL_EXPRESSION, NULL, children);
    if (functionCallNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionCallExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return functionCallNode;
}

AstNode *parser_parsePrimaryExpression(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parsePrimaryExpression: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parsePrimaryExpression: No tokens available to parse primary expression.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType != TOKEN_IDENTIFIER && !parser_isLiteral(parser) && currentTokenType != TOKEN_OPEN_PARENTHESIS)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected identifier, literal, or '(' to start primary expression.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: linkedList_Error_create failed with errno %d\n", errno);
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    if (currentTokenType == TOKEN_IDENTIFIER)
    {
        Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (identifierToken == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: token_copy failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: linkedList_Token_create failed with errno %d\n", errno);
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the identifier token
    }
    else if (parser_isLiteral(parser))
    {
        AstNode *literalNode = parser_parseLiteral(parser);
        if (literalNode == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: Failed to parse literal.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, literalNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else if (currentTokenType == TOKEN_OPEN_PARENTHESIS)
    {
        parser->tokens = parser->tokens->next; // Move past the open parenthesis token
        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: No tokens available after open parenthesis.\n");
            return NULL;
        }

        AstNode *groupedExprNode = parser_parseExpression(parser);
        if (groupedExprNode == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: Failed to parse grouped expression.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, groupedExprNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parsePrimaryExpression: No tokens available after grouped expression.\n");
            return NULL;
        }

        parser->tokens = parser->tokens->next; // Move past the close parenthesis token
    }

    AstNode *primaryExpressionNode = astNode_create(parser->astArena, AST_PRIMARY_EXPRESSION, tokens, children);
    if (primaryExpressionNode == NULL)
    {
        DEBUG_PRINT("parser_parsePrimaryExpression: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return primaryExpressionNode;
}

// --------------------------------------------------------------------------------

Parser *parser_create(Arena *utilsArena, Arena *astArena, LinkedList *tokens)
{
    if (utilsArena == NULL)
    {
        DEBUG_PRINT("parser_create: utilsArena is NULL.\n");
        return NULL;
    }

    if (astArena == NULL)
    {
        DEBUG_PRINT("parser_create: astArena is NULL.\n");
        return NULL;
    }

    if (tokens == NULL)
    {
        DEBUG_PRINT("parser_create: tokens is NULL.\n");
        return NULL;
    }

    Parser *parser = (Parser *)arena_alloc(utilsArena, sizeof(Parser), alignof(Parser));
    if (parser == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("parser_create: arena_alloc failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("parser_create: arena_alloc failed with unknown error\n");
        }
        return NULL;
    }

    parser->utilsArena = utilsArena;
    parser->astArena = astArena;
    parser->errors = NULL; // Initialize errors list as NULL
    parser->tokens = tokens; // Set the provided tokens list
    parser->ast = NULL; // Initialize AST as NULL

    return parser;
}

void parser_parse(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parse: Parser is NULL.\n");
        return;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parse: No tokens to parse.\n");
        return;
    }

    AstNode *program = parser_parseProgram(parser);
    if (program == NULL)
    {
        DEBUG_PRINT("parser_parse: Failed to parse program.\n");
        return;
    }

    parser->ast = program;
}

void parser_print(const Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_print: Parser is NULL.\n");
        return;
    }

    printf("Parser: {\n");
    printf("    utilsArena:\n");
    arena_print(parser->utilsArena);
    printf("    astArena:\n");
    arena_print(parser->astArena);
    printf("    errors: ");
    if (parser->errors == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        linkedList_print(parser->errors, (PrintFunction)error_print);
    }
    printf("    tokens: ");
    if (parser->tokens == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        linkedList_print(parser->tokens, (PrintFunction)token_print);
    }
    printf("    ast: ");
    if (parser->ast == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        // Assuming ast_print is a function that prints the AST node
        astNode_printTree(parser->ast, "", false);
    }
    printf("}\n");
}