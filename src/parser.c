#include "parser.h"

AstNode *parser_parseProgram(Parser *parser);

AstNode *parser_parseImport(Parser *parser);

AstNode *parser_parseFunctionDefinition(Parser *parser); // TODO

AstNode *parser_parseStructDeclaration(Parser *parser); // TODO

AstNode *parser_parseUnionDeclaration(Parser *parser); // TODO

AstNode *parser_parseEnumDeclaration(Parser *parser); // TODO

AstNode *parser_parseTypedefDeclaration(Parser *parser); // TODO

AstNode *parser_parseGlobalDeclaration(Parser *parser); // TODO

// --------------------------------------------------------------------------------

AstNode *parser_parseProgram(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseProgram: Parser is NULL.\n");
        return NULL;
    }

    LinkedList *tokens = NULL;
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
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with unknown error\n");
            }
            return NULL;
        }
        children = head;
    }

    while (parser->tokens != NULL && ((Token *)parser->tokens->data)->type != TOKEN_EOF)
    {
        LinkedList *currentTokenNode = parser->tokens;
        if (((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_EXPORT)
        {
            currentTokenNode = currentTokenNode->next; // Look past the export keyword as other statements will handle it
        }
    
        if (((Token *)currentTokenNode->data)->type == TOKEN_OPEN_PARENTHESIS)
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
                if (errno == ENOMEM)
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                }
                else
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with unknown error\n");
                }
                return NULL;
            }
            children = head;
        }
        else if (((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_STRUCT)
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
                if (errno == ENOMEM)
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                }
                else
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with unknown error\n");
                }
                return NULL;
            }
            children = head;
        }
        else if (((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_UNION)
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
                if (errno == ENOMEM)
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                }
                else
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with unknown error\n");
                }
                return NULL;
            }
            children = head;
        }
        else if (((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_ENUM)
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
                if (errno == ENOMEM)
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                }
                else
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with unknown error\n");
                }
                return NULL;
            }
            children = head;
        }
        else if (((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_TYPEDEF)
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
                if (errno == ENOMEM)
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                }
                else
                {
                    DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with unknown error\n");
                }
                return NULL;
            }
            children = head;
        }
        else
        {
            while (((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_CONST || ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_CONST_PTR || ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_PTR)
            {
                currentTokenNode = currentTokenNode->next; // Look past const, const ptr, or ptr keywords as variable declaration will handle it
            }

            if (((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_INT_64 || 
                ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_INT_32 ||
                ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_INT_16 ||
                ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_INT_8 ||
                ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_UINT_64 ||
                ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_UINT_32 ||
                ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_UINT_16 ||
                ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_UINT_8 ||
                ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_FLOAT_64 ||
                ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_FLOAT_32 ||
                ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_CHAR ||
                ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_STRING ||
                ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_BOOL ||
                ((Token *)currentTokenNode->data)->type == TOKEN_KEYWORD_VOID)
            {
                AstNode *globalDeclaration = parser_parseGlobalDeclaration(parser); // Sets parser->tokens to the next token after the global declaration statement
                if (globalDeclaration == NULL)
                {
                    DEBUG_PRINT("parser_parseProgram: Failed to parse global declaration.\n");
                    return NULL;
                }

                LinkedList *head = linkedList_Ast_create(parser->astArena, children, globalDeclaration);
                if (head == NULL)
                {
                    if (errno == ENOMEM)
                    {
                        DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with errno %d\n", errno);
                    }
                    else
                    {
                        DEBUG_PRINT("parser_parseProgram: linkedList_Ast_create failed with unknown error\n");
                    }
                    return NULL;
                }
                children = head;
            }
            else
            {
                Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)currentTokenNode->data)->length, ((Token *)currentTokenNode->data)->line, ((Token *)currentTokenNode->data)->column, "Unexpected token in program.");
                if (error == NULL)
                {
                    if (errno == ENOMEM)
                    {
                        DEBUG_PRINT("parser_parseProgram: error_create failed with errno %d\n", errno);
                    }
                    else
                    {
                        DEBUG_PRINT("parser_parseProgram: error_create failed with unknown error\n");
                    }

                    return NULL;
                }

                LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
                if (head == NULL)
                {
                    if (errno == ENOMEM)
                    {
                        DEBUG_PRINT("parser_parseProgram: linkedList_Error_create failed with errno %d\n", errno);
                    }
                    else
                    {
                        DEBUG_PRINT("parser_parseProgram: linkedList_Error_create failed with unknown error\n");
                    }

                    return NULL;
                }
                parser->errors = head;

                parser->tokens = currentTokenNode->next; // Skip the unexpected token
            }
        }

        currentTokenNode = parser->tokens;
    }

    if (((Token *)parser->tokens->data)->type != TOKEN_EOF)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "End of file not found in the program.");
        if (error == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("parser_parseProgram: error_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("parser_parseProgram: error_create failed with unknown error\n");
            }

            return NULL;
        }

        LinkedList *head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Error_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("parser_parseProgram: linkedList_Error_create failed with unknown error\n");
            }

            return NULL;
        }
        parser->errors = head;
    }

    Token *eofToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (eofToken == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("parser_parseProgram: token_copy failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("parser_parseProgram: token_copy failed with unknown error\n");
        }

        return NULL;
    }

    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, eofToken);
    if (head == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("parser_parseProgram: linkedList_Token_create failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("parser_parseProgram: linkedList_Token_create failed with unknown error\n");
        }

        return NULL;
    }
    tokens = head;

    AstNode *program = astNode_create(parser->astArena, AST_PROGRAM, tokens, children);
    if (program == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("parser_parseProgram: astNode_create failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("parser_parseProgram: astNode_create failed with unknown error\n");
        }

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
    
    Token *importToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (importToken == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("parser_parseImport: token_copy failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("parser_parseImport: token_copy failed with unknown error\n");
        }
        return NULL;
    }

    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, importToken);
    if (head == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with unknown error\n");
        }
        return NULL;
    }
    tokens = head;

    parser->tokens = parser->tokens->next; // Move past the import token

    bool isFrom = false;
    if (((Token *)parser->tokens->data)->type == TOKEN_LITERAL_STRING)
    {
        Token *stringLiteralToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (stringLiteralToken == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("parser_parseImport: token_copy failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("parser_parseImport: token_copy failed with unknown error\n");
            }
            return NULL;
        }
    
        head = linkedList_Token_create(parser->astArena, tokens, stringLiteralToken);
        if (head == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with unknown error\n");
            }
            return NULL;
        }

        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the string literal token
    }
    else if (((Token *)parser->tokens->data)->type == TOKEN_IDENTIFIER)
    {
        isFrom = true; // Indicates that this is an import from statement

        bool hasCommaSuffix = false;
        Token* CommaToken = NULL;
        while (parser->tokens != NULL && ((Token *)parser->tokens->data)->type == TOKEN_IDENTIFIER)
        {
            Token *identifierToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
            if (identifierToken == NULL)
            {
                if (errno == ENOMEM)
                {
                    DEBUG_PRINT("parser_parseImport: token_copy failed with errno %d\n", errno);
                }
                else
                {
                    DEBUG_PRINT("parser_parseImport: token_copy failed with unknown error\n");
                }
                return NULL;
            }

            head = linkedList_Token_create(parser->astArena, tokens, identifierToken);
            if (head == NULL)
            {
                if (errno == ENOMEM)
                {
                    DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with errno %d\n", errno);
                }
                else
                {
                    DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with unknown error\n");
                }
                return NULL;
            }
            tokens = head;

            parser->tokens = parser->tokens->next; // Move past the identifier token
            if (((Token *)parser->tokens->data)->type == TOKEN_COMMA)
            {
                hasCommaSuffix = true; 
                CommaToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
                if (CommaToken == NULL)
                {
                    if (errno == ENOMEM)
                    {
                        DEBUG_PRINT("parser_parseImport: token_copy failed with errno %d\n", errno);
                    }
                    else
                    {
                        DEBUG_PRINT("parser_parseImport: token_copy failed with unknown error\n");
                    }
                    return NULL;
                }

                head = linkedList_Token_create(parser->astArena, tokens, CommaToken);
                if (head == NULL)
                {
                    if (errno == ENOMEM)
                    {
                        DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with errno %d\n", errno);
                    }
                    else
                    {
                        DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with unknown error\n");
                    }
                    return NULL;
                }
                tokens = head;

                parser->tokens = parser->tokens->next; // Move past the comma token
            }            
            else
            {
                hasCommaSuffix = false;
            }
        }

        if (hasCommaSuffix)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, CommaToken->length, CommaToken->line, CommaToken->column, "Unexpected colon after identifier in import from statement.");
            if (error == NULL)
            {
                if (errno == ENOMEM)
                {
                    DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
                }
                else
                {
                    DEBUG_PRINT("parser_parseImport: error_create failed with unknown error\n");
                }
                return NULL;
            }

            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                if (errno == ENOMEM)
                {
                    DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
                }
                else
                {
                    DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with unknown error\n");
                }
                return NULL;
            }
            parser->errors = head;

            return NULL;
        }

        if (((Token *)parser->tokens->data)->type != TOKEN_KEYWORD_FROM)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected 'from' keyword after import identifiers.");
            if (error == NULL)
            {
                if (errno == ENOMEM)
                {
                    DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
                }
                else
                {
                    DEBUG_PRINT("parser_parseImport: error_create failed with unknown error\n");
                }
                return NULL;
            }

            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                if (errno == ENOMEM)
                {
                    DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
                }
                else
                {
                    DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with unknown error\n");
                }
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        Token *fromToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (fromToken == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("parser_parseImport: token_copy failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("parser_parseImport: token_copy failed with unknown error\n");
            }
            return NULL;
        }

        head = linkedList_Token_create(parser->astArena, tokens, fromToken);
        if (head == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with unknown error\n");
            }
            return NULL;
        }
        tokens = head;

        parser->tokens = parser->tokens->next; // Move past the 'from' keyword token

        if (((Token *)parser->tokens->data)->type != TOKEN_LITERAL_STRING)
        {
            Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected string literal after 'from' keyword.");
            if (error == NULL)
            {
                if (errno == ENOMEM)
                {
                    DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
                }
                else
                {
                    DEBUG_PRINT("parser_parseImport: error_create failed with unknown error\n");
                }
                return NULL;
            }

            head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
            if (head == NULL)
            {
                if (errno == ENOMEM)
                {
                    DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
                }
                else
                {
                    DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with unknown error\n");
                }
                return NULL;
            }
            parser->errors = head;

            parser->tokens = parser->tokens->next; // Skip the unexpected token
            return NULL;
        }

        Token *stringLiteralToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
        if (stringLiteralToken == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("parser_parseImport: token_copy failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("parser_parseImport: token_copy failed with unknown error\n");
            }
            return NULL;
        }

        head = linkedList_Token_create(parser->astArena, tokens, stringLiteralToken);
        if (head == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with unknown error\n");
            }
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
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("parser_parseImport: error_create failed with unknown error\n");
            }
            return NULL;
        }

        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with unknown error\n");
            }
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }


    if (((Token *)parser->tokens->data)->type != TOKEN_SEMICOLON)
    {
        Error *error = error_create(parser->utilsArena, ERROR_ERROR, ((Token *)parser->tokens->data)->length, ((Token *)parser->tokens->data)->line, ((Token *)parser->tokens->data)->column, "Expected semicolon after import statement.");
        if (error == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("parser_parseImport: error_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("parser_parseImport: error_create failed with unknown error\n");
            }
            return NULL;
        }

        head = linkedList_Error_create(parser->utilsArena, parser->errors, error);
        if (head == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("parser_parseImport: linkedList_Error_create failed with unknown error\n");
            }
            return NULL;
        }
        parser->errors = head;

        parser->tokens = parser->tokens->next; // Skip the unexpected token
        return NULL;
    }

    Token *semicolonToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (semicolonToken == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("parser_parseImport: token_copy failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("parser_parseImport: token_copy failed with unknown error\n");
        }
        return NULL;
    }

    head = linkedList_Token_create(parser->astArena, tokens, semicolonToken);
    if (head == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("parser_parseImport: linkedList_Token_create failed with unknown error\n");
        }
        return NULL;
    }
    tokens = head;
    parser->tokens = parser->tokens->next; // Move past the semicolon token

    AstType importType = isFrom ? AST_IMPORT_FROM : AST_IMPORT;
    AstNode *importNode = astNode_create(parser->astArena, importType, tokens, NULL);
    if (importNode == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("parser_parseImport: astNode_create failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("parser_parseImport: astNode_create failed with unknown error\n");
        }
        return NULL;
    }

    return importNode;
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

AstNode *parser_parseStructDeclaration(Parser *parser)
{
    if (parser == NULL)
    {
        DEBUG_PRINT("parser_parseImport: Parser is NULL.\n");
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

    LinkedList *tokens;
    LinkedList *children;

    Token *structToken = token_copy(parser->astArena, (Token *)parser->tokens->data);
    if (structToken == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: token_copy failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("parser_parseStructDeclaration: token_copy failed with unknown error\n");
        }
        return NULL;
    }

    LinkedList *head = linkedList_Token_create(parser->astArena, tokens, structToken);
    if (head == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Token_create failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("parser_parseStructDeclaration: linkedList_Token_create failed with unknown error\n");
        }
        return NULL;
    }
    tokens = head;
    
    parser->tokens = parser->tokens->next; // Move past the struct token


    AstNode *structNode = astNode_create(parser->astArena, AST_STRUCT_OR_UNION_SPECIFIER, tokens, children);
    if (structNode == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("parser_parseStructDeclaration: astNode_create failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("parser_parseStructDeclaration: astNode_create failed with unknown error\n");
        }
        return NULL;
    }

    return structNode;
}

AstNode *parser_parseUnionDeclaration(Parser *parser)
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

AstNode *parser_parseTypedefDeclaration(Parser *parser)
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

AstNode *parser_parseGlobalDeclaration(Parser *parser)
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