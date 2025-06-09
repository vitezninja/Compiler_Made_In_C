#include "parser.h"

AstNode *parser_parseType(Parser *parser); // TODO

AstNode *parser_parseTypeSpecifier(Parser *parser); // TODO

AstNode *parser_parseLiteral(Parser *parser); // TODO

AstNode *parser_parseProgram(Parser *parser);

AstNode *parser_parseImport(Parser *parser);

AstNode *parser_parseIdentifierList(Parser *parser);

AstNode *parser_parseFunctionDefinition(Parser *parser); // TODO

AstNode *parser_parseReturnParameterList(Parser *parser); // TODO

AstNode *parser_parseReturnParameter(Parser *parser); // TODO

AstNode *parser_parseFunctionParameterList(Parser *parser); // TODO

AstNode *parser_parseFunctionParameter(Parser *parser); // TODO

AstNode *parser_parseVariableGlobalDeclaration(Parser *parser); // TODO

AstNode *parser_parseStructDeclaration(Parser *parser);

AstNode *parser_parseUnionDeclaration(Parser *parser);

AstNode *parser_parseStructUnionMemberDeclaration(Parser *parser); // TODO

AstNode *parser_parseStructUniondeclarator(Parser *parser); // TODO

AstNode *parser_parseEnumDeclaration(Parser *parser); // TODO

AstNode *parser_parseEnumValueDeclaration(Parser *parser); // TODO

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

AstNode *parser_parseType(Parser *parser)
{
    return NULL; // TODO: Implement type parsing
}

AstNode *parser_parseTypeSpecifier(Parser *parser)
{
    return NULL; // TODO: Implement type specifier parsing
}

AstNode *parser_parseLiteral(Parser *parser)
{
    return NULL; // TODO: Implement literal parsing
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
            AstNode *function = parser_parseFunctionDefinition(parser); // Sets parser->tokens to the next token after the function declaration statement
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
            AstNode *structDeclaration = parser_parseStructDeclaration(parser); // Sets parser->tokens to the next token after the struct declaration statement
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
            AstNode *unionDeclaration = parser_parseUnionDeclaration(parser); // Sets parser->tokens to the next token after the union declaration statement
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
            AstNode *enumDeclaration = parser_parseEnumDeclaration(parser); // Sets parser->tokens to the next token after the enum declaration statement
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
            AstNode *typedefDeclaration = parser_parseTypedefDeclaration(parser); // Sets parser->tokens to the next token after the typedef declaration statement
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
        else if (   currentTokenType == TOKEN_KEYWORD_CONST || 
                    currentTokenType == TOKEN_KEYWORD_CONST_PTR || 
                    currentTokenType == TOKEN_KEYWORD_PTR ||
                    currentTokenType == TOKEN_KEYWORD_INT_64 ||
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
            AstNode *globalDeclaration = parser_parseVariableGlobalDeclaration(parser); // Sets parser->tokens to the next token after the global declaration statement
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
            Token *unexpectedToken = (Token *)currentTokenNode->data;
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Unexpected token in program.");
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

            parser->tokens = currentTokenNode->next; // Skip the unexpected token
            return NULL;
        }

        currentTokenNode = parser->tokens;
    }

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseProgram: No tokens available to parse the program.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_EOF)
    {
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "End of file not found in the program.");
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
        DEBUG_PRINT("parser_parseImport: Expected TOKEN_KEYWORD_IMPORT, got %s.\n", token_typeToString(((Token *)parser->tokens->data)->type));
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
            Token *unexpectedToken = (Token *)parser->tokens->data;
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected 'from' keyword after import identifiers.");
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
            Token * unexpectedToken = (Token *)parser->tokens->data;
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected string literal after 'from' keyword.");
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
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected string literal or identifier after import keyword.");
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
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected semicolon after import statement.");
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
        DEBUG_PRINT("parser_parseIdentifierList: Expected TOKEN_IDENTIFIER, got %s.\n", token_typeToString(((Token *)parser->tokens->data)->type));
        return NULL;
    }

    LinkedList *tokens = NULL;

    bool hasCommaSuffix = false;
    while (parser->tokens != NULL && ((Token *)parser->tokens->data)->type == TOKEN_IDENTIFIER)
    {
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

        if (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
        {
            hasCommaSuffix = true;
            parser->tokens = parser->tokens->next; // Move past the comma token
        }
        else
        {
            hasCommaSuffix = false;
        }
    }

    if (hasCommaSuffix)
    {
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Unexpected comma after identifier in identifier list.");
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
        return NULL;
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

    // LinkedList *tokens;
    // LinkedList *children;

    return NULL;
}

AstNode *parser_parseReturnParameterList(Parser *parser)
{
    return NULL; // TODO: Implement return parameter list parsing
}

AstNode *parser_parseReturnParameter(Parser *parser)
{
    return NULL; // TODO: Implement return parameter parsing
}

AstNode *parser_parseFunctionParameterList(Parser *parser)
{
    return NULL; // TODO: Implement function parameter list parsing
}

AstNode *parser_parseFunctionParameter(Parser *parser)
{
    return NULL; // TODO: Implement function parameter parsing
}

AstNode *parser_parseVariableGlobalDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseImport: Parser is NULL.\n");
        return NULL;
    }

    // LinkedList *tokens;
    // LinkedList *children;

    return NULL;
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

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_IMPORT)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: Expected TOKEN_KEYWORD_STRUCT, got %s.\n", token_typeToString(((Token *)parser->tokens->data)->type));
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the struct token

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: No tokens available after struct keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected identifier after struct keyword.");
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
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected '{' after struct identifier.");
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

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        AstNode *member = parser_parseStructUnionMemberDeclaration(parser);
        if (member == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: Failed to parse struct member declaration.\n");
            return NULL;
        }

        head = linkedList_Ast_create(parser->astArena, children, member);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected struct member declaration before '}' in struct declaration.");
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

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseStructDeclaration: No tokens available after struct member declaration.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected '}' to close struct declaration.");
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

    if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_UNION)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: Expected TOKEN_KEYWORD_UNION, got %s.\n", token_typeToString(((Token *)parser->tokens->data)->type));
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the union token

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: No tokens available after union keyword.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_IDENTIFIER)
    {
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected identifier after union keyword.");
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
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected '{' after union identifier.");
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

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        AstNode *member = parser_parseStructUnionMemberDeclaration(parser);
        if (member == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: Failed to parse union member declaration.\n");
            return NULL;
        }

        head = linkedList_Ast_create(parser->astArena, children, member);
        if (head == NULL)
        {
            DEBUG_PRINT("parser_parseUnionDeclaration: linkedList_Ast_create failed with errno %d\n", errno);
            return NULL;
        }
        children = head;
    }
    else
    {
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected union member declaration before '}' in union declaration.");
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

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseUnionDeclaration: No tokens available after union member declaration.\n");
        return NULL;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_CLOSE_CURLY)
    {
        Token *unexpectedToken = (Token *)parser->tokens->data;
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, unexpectedToken->length, unexpectedToken->line, unexpectedToken->column, "Expected '}' to close union declaration.");
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
    return NULL; // Placeholder for the actual implementation
}

AstNode *parser_parseStructUniondeclarator(Parser *parser)
{
    return NULL; // Placeholder for the actual implementation
}

AstNode *parser_parseEnumDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseImport: Parser is NULL.\n");
        return NULL;
    }

    // LinkedList *tokens;
    // LinkedList *children;

    return NULL;
}

AstNode *parser_parseEnumValueDeclaration(Parser *parser)
{
    return NULL; // Placeholder for the actual implementation
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

    if (((Token *)parser->tokens->data)->type == TOKEN_KEYWORD_TYPEDEF)
    {
        DEBUG_PRINT("parser_parseTypedefDeclaration: Expected TOKEN_KEYWORD_TYPEDEF, got %s.\n", token_typeToString(((Token *)parser->tokens->data)->type));
        return NULL;
    }

    LinkedList *tokens = NULL;
    LinkedList *children = NULL;

    parser->tokens = parser->tokens->next; // Move past the typedef token

    if (parser->tokens == NULL)
    {
        DEBUG_PRINT("parser_parseTypedefDeclaration: No tokens available after typedef keyword.\n");
        return NULL;
    }

    My_TokenType currentTokenType = ((Token *)parser->tokens->data)->type;
    if (currentTokenType == TOKEN_KEYWORD_CONST || 
        currentTokenType == TOKEN_KEYWORD_CONST_PTR || 
        currentTokenType == TOKEN_KEYWORD_PTR )
    {
        AstNode *typeSpecifierNode = parser_parseTypeSpecifier(parser);
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

AstNode *parser_parseStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseBranchStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseIfStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseSwitchStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseLoopStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseForStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseForeachStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseWhileStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseDoWhileStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseCompoundStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseLabel(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseExpressionStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseVariableDeclaration(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseJumpStatement(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseFunctionCall(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseAssignmentExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseLogicalOrExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseLogicalAndExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseBitwiseOrExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseBitwiseXorExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseBitwiseAndExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseEqualityExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseRelationalExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseShiftExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseAdditiveExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseMultiplicativeExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseTypeCastExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseUnaryExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parsePostfixExpression(Parser *parser)
{
    return NULL; // TODO: Implement 
}

AstNode *parser_parseArrayIndexing(Parser *parser)
{
    return NULL; // TODO: Implement 
}

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