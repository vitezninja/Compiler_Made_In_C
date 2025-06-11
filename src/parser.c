#include "parser.h"

bool parser_isType(Parser *parser);

AstNode *parser_parseType(Parser *parser);

bool parser_isTypeSpecifier(Parser *parser);

AstNode *parser_parseTypeSpecifiers(Parser *parser);

bool parser_isLiteral(Parser *parser);

AstNode *parser_parseLiteral(Parser *parser);

AstNode *parser_parseProgram(Parser *parser);

AstNode *parser_parseImport(Parser *parser);

AstNode *parser_parseIdentifierList(Parser *parser);

AstNode *parser_parseFunctionDefinition(Parser *parser);

AstNode *parser_parseReturnParameterList(Parser *parser);

AstNode *parser_parseReturnParameter(Parser *parser);

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

AstNode *parser_parseStatement(Parser *parser); // TODO

AstNode *parser_parseBranchStatement(Parser *parser); // TODO

AstNode *parser_parseIfStatement(Parser *parser); // TODO

AstNode *parser_parseSwitchStatement(Parser *parser); // TODO

AstNode *parser_parseLoopStatement(Parser *parser); // TODO

AstNode *parser_parseForStatement(Parser *parser); // TODO

AstNode *parser_parseForeachStatement(Parser *parser); // TODO

AstNode *parser_parseWhileStatement(Parser *parser); // TODO

AstNode *parser_parseDoWhileStatement(Parser *parser); // TODO

AstNode *parser_parseCompoundStatement(Parser *parser); // TODO

AstNode *parser_parseLabel(Parser *parser); // TODO

AstNode *parser_parseExpressionStatement(Parser *parser); // TODO

AstNode *parser_parseVariableDeclaration(Parser *parser); // TODO

AstNode *parser_parseJumpStatement(Parser *parser); // TODO

AstNode *parser_parseExpression(Parser *parser); // TODO

AstNode *parser_parseFunctionCall(Parser *parser); // TODO

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

AstNode *parser_parseTypeCastExpression(Parser *parser); // TODO

AstNode *parser_parseUnaryExpression(Parser *parser); // TODO

AstNode *parser_parsePostfixExpression(Parser *parser); // TODO

AstNode *parser_parseArrayIndexing(Parser *parser); // TODO

AstNode *parser_parsePrimaryExpression(Parser *parser); // TODO

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
        else if (parser_isType(parser) || parser_isTypeSpecifier(parser))
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

    if (!parser_isType(parser) && !parser_isTypeSpecifier(parser))
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

    AstNode *returnParameterNode = parser_parseReturnParameter(parser);
    if (returnParameterNode == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameterList: Failed to parse return parameter.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, returnParameterNode);
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

        if (!parser_isType(parser) && !parser_isTypeSpecifier(parser))
        {
            Token *unexpectedToken = (Token *)parser->tokens->data;
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected a type or type specifier after comma in return parameter list.");
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

        returnParameterNode = parser_parseReturnParameter(parser);
        if (returnParameterNode == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameterList: Failed to parse return parameter.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, returnParameterNode);
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

AstNode *parser_parseReturnParameter(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameter: Parser is NULL.\n");
        return NULL;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameter: No tokens available to parse return parameter.\n");
        return NULL;
    }

    if (!parser_isType(parser) && !parser_isTypeSpecifier(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a type or type specifier for return parameter.");
        if (error == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameter: error_create failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameter: linkedList_Error_create failed with errno %d\n", errno);
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
            DEBUG_PRINT("parser_parseReturnParameter: Failed to parse type specifiers.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeSpecifiersNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameter: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseReturnParameter: No tokens available after type specifier.\n");
            return NULL;
        }
    }

    AstNode *typeNode = parser_parseType(parser);
    if (typeNode == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameter: Failed to parse type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeNode);
    if (head == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameter: linkedList_Ast_create failed with errno %d\n", errno);
        return NULL;
    }
    children = head;

    AstNode *retunrParameterNode = astNode_create(parser->astArena, AST_RETURN_PARAMETER, NULL, children);
    if (retunrParameterNode == NULL)
    {
        DEBUG_PRINT("parser_parseReturnParameter: astNode_create failed with errno %d\n", errno);
        return NULL;
    }
    return retunrParameterNode;
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

    if (!parser_isType(parser) && !parser_isTypeSpecifier(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a type or type specifier in function parameter list.");
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

        if (!parser_isType(parser) && !parser_isTypeSpecifier(parser))
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a type or type specifier after comma in function parameter list.");
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

    if (!parser_isType(parser) && !parser_isTypeSpecifier(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a type specifier or identifier for function parameter.");
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

    if (parser_isTypeSpecifier(parser))
    {
        AstNode *typeSpecifiersNode = parser_parseTypeSpecifiers(parser);
        if (typeSpecifiersNode == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameter: Failed to parse type specifiers.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeSpecifiersNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameter: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseFunctionParameter: No tokens available after type specifier.\n");
            return NULL;
        }
    }

    AstNode *typeNode = parser_parseType(parser);
    if (typeNode == NULL)
    {
        DEBUG_PRINT("parser_parseFunctionParameter: Failed to parse type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeNode);
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
    if (!parser_isType(parser) && !parser_isTypeSpecifier(parser) && currentTokenType != TOKEN_KEYWORD_EXPORT)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a type or type specifier for global variable declaration.");
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

    if (parser_isTypeSpecifier(parser))
    {
        AstNode *typeSpecifiersNode = parser_parseTypeSpecifiers(parser);
        if (typeSpecifiersNode == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: Failed to parse type specifiers.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeSpecifiersNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseGlobalVariableDeclaration: No tokens available after type specifier.\n");
            return NULL;
        }
    }

    AstNode *typeNode = parser_parseType(parser);
    if (typeNode == NULL)
    {
        DEBUG_PRINT("parser_parseGlobalVariableDeclaration: Failed to parse type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeNode);
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

    if (!parser_isType(parser) && !parser_isTypeSpecifier(parser))
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected a type or type specifier for struct/union member declaration.");
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

    if (parser_isTypeSpecifier(parser))
    {
        AstNode *typeSpecifiersNode = parser_parseTypeSpecifiers(parser);
        if (typeSpecifiersNode == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: Failed to parse type specifiers.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeSpecifiersNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;

        if (parser->tokens == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after type specifier.\n");
            return NULL;
        }
    }

    AstNode *typeNode = parser_parseType(parser);
    if (typeNode == NULL)
    {
        DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: Failed to parse type.\n");
        return NULL;
    }
    LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeNode);
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

    while (parser_isTypeSpecifier(parser) || parser_isType(parser))
    {
        if (parser_isTypeSpecifier(parser))
        {
            AstNode *typeSpecifiersNode = parser_parseTypeSpecifiers(parser);
            if (typeSpecifiersNode == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: Failed to parse type specifiers.\n");
                return NULL;
            }
            head = linkedList_Ast_create(parser->astArena, children, typeSpecifiersNode);
            if (head == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
                return NULL;
            }
            children = head;

            if (parser->tokens == NULL)
            {
                DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: No tokens available after type specifier.\n");
                return NULL;
            }
        }

        typeNode = parser_parseType(parser);
        if (typeNode == NULL)
        {
            DEBUG_PRINT("parser_parseStructUnionMemberDeclaration: Failed to parse type.\n");
            return NULL;
        }
        head = linkedList_Ast_create(parser->astArena, children, typeNode);
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

    currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType == TOKEN_KEYWORD_CONST || 
        currentTokenType == TOKEN_KEYWORD_CONST_PTR || 
        currentTokenType == TOKEN_KEYWORD_PTR )
    {
        AstNode *typeSpecifierNode = parser_parseTypeSpecifiers(parser);
        if (typeSpecifierNode == NULL)
        {
            DEBUG_PRINT("parser_parseTypedefDeclaration: Failed to parse type specifier.\n");
            return NULL;
        }

        LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeSpecifierNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseTypedefDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseTypedefDeclaration: No tokens available after type specifier.\n");
        return NULL;
    }

    currentTokenType = ((Token *)parser->tokens->data)->type;
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
        currentTokenType == TOKEN_IDENTIFIER )
    {
        AstNode *typeNode = parser_parseType(parser);
        if (typeNode == NULL)
        {
            DEBUG_PRINT("parser_parseTypedefDeclaration: Failed to parse type.\n");
            return NULL;
        }

        LinkedList *head = linkedList_Ast_create(parser->astArena, children, typeNode);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseTypedefDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }

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

// TODO
AstNode *parser_parseStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseBranchStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseIfStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseSwitchStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseLoopStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseForStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseForeachStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseWhileStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseDoWhileStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseCompoundStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseLabel(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseExpressionStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseVariableDeclaration(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseJumpStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseFunctionCall(Parser *parser)
{
    return NULL; // TODO: Implement 
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

// TODO
AstNode *parser_parseTypeCastExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseUnaryExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parsePostfixExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parseArrayIndexing(Parser *parser)
{
    return NULL; // TODO: Implement 
}

// TODO
AstNode *parser_parsePrimaryExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
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