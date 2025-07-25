#include "validator.h"

/**
 * @brief Initializes the base types in the validator's type table.
 * 
 * This function creates the standard base types (int, float, bool, char, string, void)
 * and inserts them into the validator's type table.
 * 
 * @param validator Pointer to the Validator instance.
 */
void validator_initializeBaseTypes(Validator *validator);

/**
 * @brief Performs the first pass of validation.
 * 
 * This pass is responsible for importing symbols from the AST into the validator's symbol stack.
 * 
 * @param validator Pointer to the Validator instance.
 */
void validator_firstPass(Validator *validator);

/**
 * @brief Performs the second pass of validation.
 * 
 * This pass validates struct names, union names and enum names.
 * 
 * @param validator Pointer to the Validator instance.
 */
void validator_secondPass(Validator *validator);

/** 
 * @brief Performs the third pass of validation.
 * 
 * This pass validates function names, variable names, struct/union members and enum values.
 * 
 * @param validator Pointer to the Validator instance.
*/
void validator_thirdPass(Validator *validator);

/**
 * @brief Performs the fourth pass of validation.
 * 
 * This pass validates function definitions and checks for correct usage of types.
 * 
 * @param validator Pointer to the Validator instance.
 */
void validator_fourthPass(Validator *validator);

/**
 * @brief Creates a CmcType from an AST full type node.
 * 
 * This function extracts the type information from an AST node representing a full type
 * and returns a corresponding CmcType. It handles type specifiers and array types.
 * 
 * @param validator Pointer to the Validator instance.
 * @param node Pointer to the AST node representing the full type.
 * @return Pointer to the created CmcType, or NULL if an error occurs.
 */
CmcType *validator_cmcTypeFromAstFullTypeNode(Validator *validator, AstNode *node);

/**
 * @brief Converts a token type to a TypeSpecEnum.
 * 
 * This function maps the token type of a type specifier to the corresponding
 * TypeSpecEnum value.
 * 
 * @param tokenType The token type to convert.
 * @return The corresponding TypeSpecEnum value.
 */
TypeSpecEnum validator_typeSpecEnumFromTokenType(My_TokenType tokenType);

CmcType *validator_validateConstExpression(Validator *validator, AstNode *constExpressionNode, bool *isConst);

CmcType *validator_matchType(Validator *validator, CmcType *expectedType, CmcType *actualType);

CmcType *validator_matchTypeNumber(Validator *validator, CmcType *actualType);

CmcType *validator_matchConstBinaryType(Validator *validator, CmcType *leftType, CmcType *rightType, Token *operatorToken);

CmcType *validator_matchConstUnaryType(Validator *validator, CmcType *unaryType, Token *operatorToken);

CmcType *validator_matchConstTypeCast(Validator *validator, CmcType *typeToCastTo, CmcType *expressionToCastType);

CmcType *validator_matchConstPostfixType(Validator *validator, CmcType *primaryType, CmcType *postfixType, AstNode *postfixPrimeNode);

CmcType *validator_getConstPostfixPrimeType(Validator *validator, Token *postfixPrimeNode);

CmcType *validator_matchConstArrayIndexingType(Validator *validator, CmcType *arrayType);

CmcType *validator_getConstPrimaryType(Validator *validator, Symbol *primarySymbol);

CmcType *validator_getLiteralType(Validator *validator, Token *literalToken);

//------------------------------------------------------------

void validator_initializeBaseTypes(Validator *validator)
{
    if (validator == NULL) 
    {
        DEBUG_PRINT("validator_initializeBaseTypes: Validator is NULL.\n");
        return;
    }

    const size_t baseTypeCount = 14;
    CmcTypeEnum baseTypes[14] = {
        CMC_TYPE_INT_64, CMC_TYPE_INT_32, CMC_TYPE_INT_16, CMC_TYPE_INT_8,
        CMC_TYPE_UINT_64, CMC_TYPE_UINT_32, CMC_TYPE_UINT_16, CMC_TYPE_UINT_8,
        CMC_TYPE_FLOAT_64, CMC_TYPE_FLOAT_32, CMC_TYPE_BOOL, CMC_TYPE_CHAR,
        CMC_TYPE_STRING, CMC_TYPE_VOID
    };

    for (size_t i = 0; i < baseTypeCount; i++) 
    {
        CmcType *baseType = cmcType_base_create(validator->utilsArena, baseTypes[i], (TypeSpec){0});
        if (baseType == NULL) 
        {
            DEBUG_PRINT("validator_initializeBaseTypes: Failed to create base type.\n");
            return;
        }
        bool success = hashTable_CmcType_tryInsert(validator->typeTable, baseType);
        if (!success) 
        {
            DEBUG_PRINT("validator_initializeBaseTypes: Failed to insert base type into type table.\n");
            return;
        }
    }
}

void validator_firstPass(Validator *validator)
{
    UNIMPLEMENTED();

    if (validator == NULL) 
    {
        DEBUG_PRINT("validator_firstPass: Validator is NULL.\n");
        return;
    }

    if (validator->ast == NULL) 
    {
        DEBUG_PRINT("validator_firstPass: AST is NULL.\n");
        return;
    }
}

void validator_secondPass(Validator *validator)
{
    if (validator == NULL) 
    {
        DEBUG_PRINT("validator_secondPass: Validator is NULL.\n");
        return;
    }

    if (validator->ast == NULL) 
    {
        DEBUG_PRINT("validator_secondPass: AST is NULL.\n");
        return;
    }

    LinkedList *current = validator->ast->children;
    while(current != NULL)
    {
        AstNode *node = (AstNode *)current->data;
        Token *nameToken = (Token *)node->tokens->data;
        if (nameToken->type == TOKEN_KEYWORD_EXPORT)
        {
            // Skip export keyword
            nameToken = (Token *)node->tokens->next->data;
        }

        if (node->type == AST_STRUCT_DECLARATION)
        {        
            CmcType *structType = cmcType_structOrUnion_create(validator->utilsArena, CMC_TYPE_STRUCT, nameToken->text, (CmcTypeStructUnionValue){0});
            if (structType == NULL) 
            {
                DEBUG_PRINT("validator_secondPass: Failed to create struct type for struct declaration.\n");
                return;
            }

            if(!hashTable_CmcType_tryInsert(validator->typeTable, structType))
            {
                Error *error = error_create(validator->utilsArena, ERROR_ERROR, nameToken->location, "Struct name already exists.");
                if (error == NULL) 
                {
                    DEBUG_PRINT("validator_secondPass: Failed to create error for struct name conflict.\n");
                    return;
                }
                LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                if (head == NULL) 
                {
                    DEBUG_PRINT("validator_secondPass: Failed to create error linked list.\n");
                    return;
                }
                validator->errors = head;
            }
        }
        else if (node->type == AST_UNION_DECLARATION)
        {
            CmcType *unionType = cmcType_structOrUnion_create(validator->utilsArena, CMC_TYPE_UNION, nameToken->text, (CmcTypeStructUnionValue){0});
            if (unionType == NULL) 
            {
                DEBUG_PRINT("validator_secondPass: Failed to create union type for union declaration.\n");
                return;
            }

            if(!hashTable_CmcType_tryInsert(validator->typeTable, unionType))
            {
                Error *error = error_create(validator->utilsArena, ERROR_ERROR, nameToken->location, "Union name already exists.");
                if (error == NULL) 
                {
                    DEBUG_PRINT("validator_secondPass: Failed to create error for union name conflict.\n");
                    return;
                }
                LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                if (head == NULL) 
                {
                    DEBUG_PRINT("validator_secondPass: Failed to create error linked list.\n");
                    return;
                }
                validator->errors = head;
            }
        }
        else if (node->type == AST_ENUM_DECLARATION)
        {
            CmcType *enumType = cmcType_enum_create(validator->utilsArena, nameToken->text);
            if (enumType == NULL) 
            {
                DEBUG_PRINT("validator_secondPass: Failed to create enum type for enum declaration.\n");
                return;
            }

            if(!hashTable_CmcType_tryInsert(validator->typeTable, enumType))
            {
                Error *error = error_create(validator->utilsArena, ERROR_ERROR, nameToken->location, "Enum name already exists.");
                if (error == NULL) 
                {
                    DEBUG_PRINT("validator_secondPass: Failed to create error for enum name conflict.\n");
                    return;
                }
                LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                if (head == NULL) 
                {
                    DEBUG_PRINT("validator_secondPass: Failed to create error linked list.\n");
                    return;
                }
                validator->errors = head;
            }
        }

        current = current->next;
    }
}

void validator_thirdPass(Validator *validator)
{
    if (validator == NULL) 
    {
        DEBUG_PRINT("validator_thirdPass: Validator is NULL.\n");
        return;
    }

    if (validator->ast == NULL) 
    {
        DEBUG_PRINT("validator_thirdPass: AST is NULL.\n");
        return;
    }

    LinkedList *current = validator->ast->children;
    while (current != NULL) 
    {
        AstNode *node = (AstNode *)current->data;
        Token *nameToken = (Token *)node->tokens->data;
        if (nameToken->type == TOKEN_KEYWORD_EXPORT)
        {
            // Skip export keyword
            nameToken = (Token *)node->tokens->next->data;
        }

        if (node->type == AST_FUNCTION_DEFINITION) 
        {
            Symbol **returnSymbolsArray = NULL;
            size_t returnCount = 0;
            Symbol **paramSymbolsArray = NULL;
            size_t arity = 0;

            HashTable *functionSymbolTable = hashTable_create(validator->utilsArena);
            if (functionSymbolTable == NULL) 
            {
                DEBUG_PRINT("validator_thirdPass: Failed to create function symbol table.\n");
                return;
            }
            Symbol *functionSymbol = symbol_function_create(validator->utilsArena, nameToken->text, (FunctionValue){.arity = arity, .returnCount = returnCount, .returnSymbols = returnSymbolsArray, .paramSymbols = paramSymbolsArray});
            if (functionSymbol == NULL) 
            {
                DEBUG_PRINT("validator_thirdPass: Failed to create function symbol.\n");
                return;
            }
            if(!hashTable_Symbol_tryInsert(functionSymbolTable, functionSymbol))
            {
                DEBUG_PRINT("validator_thirdPass: Failed to insert function symbol into symbol table.\n");
                return;
            }

            {
                AstNode *returnParameterListNode = node->children->data;

                LinkedList *currentFullTypeNode = returnParameterListNode->children;
                while (currentFullTypeNode != NULL) 
                {
                    returnCount++;
                    currentFullTypeNode = currentFullTypeNode->next;
                }
    
                returnSymbolsArray = arena_alloc(validator->utilsArena, sizeof(Symbol *) * returnCount, alignof(Symbol *));
                if (returnSymbolsArray == NULL) 
                {
                    DEBUG_PRINT("validator_thirdPass: Failed to allocate memory for return symbols array.\n");
                    return;
                }

                size_t index = 0;
                currentFullTypeNode = returnParameterListNode->children;
                while (currentFullTypeNode != NULL) 
                {
                    AstNode *currentFullType = currentFullTypeNode->data;
                    CmcType *currentCmcType = validator_cmcTypeFromAstFullTypeNode(validator, currentFullType);
                    if (currentCmcType == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create CmcType from AST full type node.\n");
                        return;
                    }

                    Symbol *returnSymbol = symbol_variable_create(validator->utilsArena, "", currentCmcType);
                    if (returnSymbol == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create symbol for return type.\n");
                        return;
                    }

                    returnSymbolsArray[index++] = returnSymbol;
                    currentFullTypeNode = currentFullTypeNode->next;
                }
            }

            if (node->children->next != NULL && ((AstNode *)node->children->next->data)->type == AST_FUNCTION_PARAMETER_LIST)
            {
                AstNode *functionParameterListNode = node->children->next->data;

                LinkedList *functionParameterNode = functionParameterListNode->children;
                while (functionParameterNode != NULL) 
                {
                    arity++;
                    functionParameterNode = functionParameterNode->next;
                }

                paramSymbolsArray = arena_alloc(validator->utilsArena, sizeof(Symbol *) * arity, alignof(Symbol *));
                if (paramSymbolsArray == NULL) 
                {
                    DEBUG_PRINT("validator_thirdPass: Failed to allocate memory for params symbols array.\n");
                    return;
                }
                functionParameterNode = functionParameterListNode->children;
                size_t index = 0;
                while (functionParameterNode != NULL) 
                {
                    AstNode *fullType = ((AstNode *)functionParameterNode->data)->children->data;
                    CmcType *paramCmcType = validator_cmcTypeFromAstFullTypeNode(validator, fullType);
                    if (paramCmcType == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create CmcType from AST full type node.\n");
                        return;
                    }

                    Token *paramNameToken = ((AstNode *)functionParameterNode->data)->tokens->data;
                    Symbol *paramSymbol = symbol_variable_create(validator->utilsArena, paramNameToken->text, paramCmcType);
                    if (paramSymbol == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create symbol for function parameter.\n");
                        return;
                    }

                    if (!hashTable_Symbol_tryInsert(functionSymbolTable, paramSymbol)) 
                    {
                        Error *error = error_create(validator->utilsArena, ERROR_ERROR, paramNameToken->location, "Function parameter name already exists.");
                        if (error == NULL) 
                        {
                            DEBUG_PRINT("validator_thirdPass: Failed to create error for function parameter name conflict.\n");
                            return;
                        }
                        LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                        if (head == NULL) 
                        {
                            DEBUG_PRINT("validator_thirdPass: Failed to create error linked list.\n");
                            return;
                        }
                        validator->errors = head;
                    }
                    else
                    {
                        paramSymbolsArray[index++] = paramSymbol;
                    }

                    functionParameterNode = functionParameterNode->next;
                }
            }

            functionSymbol->value.function.arity = arity;
            functionSymbol->value.function.returnCount = returnCount;
            functionSymbol->value.function.returnSymbols = returnSymbolsArray;
            functionSymbol->value.function.paramSymbols = paramSymbolsArray;

            CmcType *typeWithSameName = hashTable_CmcType_find(validator->typeTable, functionSymbol->name);
            if (typeWithSameName != NULL) 
            {
                Error *error = error_create(validator->utilsArena, ERROR_ERROR, nameToken->location, "Function name conflicts with a type.");
                if (error == NULL) 
                {
                    DEBUG_PRINT("validator_thirdPass: Failed to create error for function name conflict with type.\n");
                    return;
                }
                LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                if (head == NULL) 
                {
                    DEBUG_PRINT("validator_thirdPass: Failed to create error linked list.\n");
                    return;
                }
                validator->errors = head;
            }
            else if(!hashTable_Symbol_tryInsert(validator->symbolStack->data, functionSymbol))
            {
                Error *error = error_create(validator->utilsArena, ERROR_ERROR, nameToken->location, "Function name already exists.");
                if (error == NULL) 
                {
                    DEBUG_PRINT("validator_thirdPass: Failed to create error for function name conflict.\n");
                    return;
                }
                LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                if (head == NULL) 
                {
                    DEBUG_PRINT("validator_thirdPass: Failed to create error linked list.\n");
                    return;
                }
                validator->errors = head;
            }
        }
        else if (node->type == AST_GLOBAL_VARIABLE_DECLARATION) 
        {
            LinkedList *fullTypeNodeLL = node->children;
            while (fullTypeNodeLL != NULL && ((AstNode *)fullTypeNodeLL->data)->type == AST_FULL_TYPE)
            {
                fullTypeNodeLL = fullTypeNodeLL->next;
            }

            CmcType *expressionType = NULL;
            if (fullTypeNodeLL != NULL)
            {
                AstNode *constExpressionNode = (AstNode *)fullTypeNodeLL->data;
                bool isConst = true;
                expressionType = validator_validateConstExpression(validator, constExpressionNode, &isConst);
            }
            
            fullTypeNodeLL = node->children;
            LinkedList *nameTokenNode = node->tokens;
            while (fullTypeNodeLL != NULL && ((AstNode *)fullTypeNodeLL->data)->type == AST_FULL_TYPE) 
            {
                if (nameToken->type == TOKEN_KEYWORD_EXPORT)
                {
                    // Skip export keyword
                    nameToken = (Token *)nameTokenNode->next->data;
                }

                AstNode *fullTypeNode = (AstNode *)node->children->data;
                nameToken = (Token *)nameTokenNode->data;

                CmcType *type = validator_cmcTypeFromAstFullTypeNode(validator, fullTypeNode);
                if (type == NULL) 
                {
                    DEBUG_PRINT("validator_thirdPass: Failed to create CmcType from AST full type node.\n");
                    return;
                }
    
                Symbol *variableSymbol = symbol_variable_create(validator->utilsArena, nameToken->text, type);
                if (variableSymbol == NULL) 
                {
                    DEBUG_PRINT("validator_thirdPass: Failed to create symbol for variable.\n");
                    return;
                }
    
                CmcType *typeWithSameName = hashTable_CmcType_find(validator->typeTable, variableSymbol->name);
                if (typeWithSameName != NULL)
                {
                    Error *error = error_create(validator->utilsArena, ERROR_ERROR, nameToken->location, "Variable name conflicts with a type.");
                    if (error == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error for variable name conflict with type.\n");
                        return;
                    }
                    LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                    if (head == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error linked list.\n");
                        return;
                    }
                    validator->errors = head;
                } 
                else if(!hashTable_Symbol_tryInsert(validator->symbolStack->data, variableSymbol))
                {
                    Error *error = error_create(validator->utilsArena, ERROR_ERROR, nameToken->location, "Variable name already exists.");
                    if (error == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error for variable name conflict.\n");
                        return;
                    }
                    LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                    if (head == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error linked list.\n");
                        return;
                    }
                    validator->errors = head;
                }

                if (expressionType != NULL)
                {
                    validator_matchType(validator, type, expressionType);
                }

                fullTypeNodeLL = fullTypeNodeLL->next;
                nameTokenNode = nameTokenNode->next;
            }
        }
        else if (node->type == AST_STRUCT_DECLARATION) 
        {
            AstNode *structMembersNode = node->children->data;
            CmcType *structType = hashTable_CmcType_find(validator->typeTable, nameToken->text);
            if (structType == NULL) 
            {
                DEBUG_PRINT("validator_thirdPass: Struct type not found in type table.\n");
                return;
            }

            size_t memberCount = 0;
            Symbol **structMembersArray = NULL;

            LinkedList *currentMemberNode = structMembersNode->children;
            while (currentMemberNode != NULL) 
            {
                memberCount++;
                currentMemberNode = currentMemberNode->next;
            }

            structMembersArray = arena_alloc(validator->utilsArena, sizeof(Symbol *) * memberCount, alignof(Symbol *));
            if (structMembersArray == NULL) 
            {
                DEBUG_PRINT("validator_thirdPass: Failed to allocate memory for struct members array.\n");
                return;
            }

            HashTable *structMemberSymbolTable = hashTable_create(validator->utilsArena);
            if (structMemberSymbolTable == NULL) 
            {
                DEBUG_PRINT("validator_thirdPass: Failed to create struct member symbol table.\n");
                return;
            }

            size_t index = 0;
            currentMemberNode = structMembersNode->children;
            LinkedList *currentMemeberNameNode = structMembersNode->tokens;
            while (currentMemberNode != NULL) 
            {
                AstNode *currentFullTypeNode = (AstNode *)currentMemberNode->data;
                CmcType *memberType = validator_cmcTypeFromAstFullTypeNode(validator, currentFullTypeNode);
                if (memberType == NULL) 
                {
                    DEBUG_PRINT("validator_thirdPass: Failed to create CmcType from AST full type node.\n");
                    return;
                }
                
                Token *memberNameToken = (Token *)currentMemeberNameNode->data;
                CmcType *typeWithSameName = hashTable_CmcType_find(validator->typeTable, memberNameToken->text);
                if (typeWithSameName != NULL)
                {
                    Error *error = error_create(validator->utilsArena, ERROR_ERROR, memberNameToken->location, "Struct member name conflicts with a type.");
                    if (error == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error for struct member name conflict with type.\n");
                        return;
                    }
                    LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                    if (head == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error linked list.\n");
                        return;
                    }
                    validator->errors = head;

                    currentMemberNode = currentMemberNode->next;
                    currentMemeberNameNode = currentMemeberNameNode->next;
                    continue;
                }

                Symbol *memberSymbol = symbol_variable_create(validator->utilsArena, memberNameToken->text, memberType);
                if (memberSymbol == NULL) 
                {
                    DEBUG_PRINT("validator_thirdPass: Failed to create symbol for struct member.\n");
                    return;
                }
                if (!hashTable_Symbol_tryInsert(structMemberSymbolTable, memberSymbol)) 
                {
                    Error *error = error_create(validator->utilsArena, ERROR_ERROR, memberNameToken->location, "Struct member name already exists.");
                    if (error == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error for struct member name conflict.\n");
                        return;
                    }
                    LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                    if (head == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error linked list.\n");
                        return;
                    }
                    validator->errors = head;
                }
                else
                {
                    structMembersArray[index++] = memberSymbol;
                }

                currentMemberNode = currentMemberNode->next;
                currentMemeberNameNode = currentMemeberNameNode->next;
            }

            structType->value.structUnion.memberCount = memberCount;
            structType->value.structUnion.structUnionMembers = structMembersArray;
        }
        else if (node->type == AST_UNION_DECLARATION) 
        {
            AstNode *unionMembersNode = node->children->data;
            CmcType *unionType = hashTable_CmcType_find(validator->typeTable, nameToken->text);
            if (unionType == NULL) 
            {
                DEBUG_PRINT("validator_thirdPass: Union type not found in type table.\n");
                return;
            }

            size_t memberCount = 0;
            Symbol **unionMembersArray = NULL;

            LinkedList *currentMemberNode = unionMembersNode->children;
            while (currentMemberNode != NULL) 
            {
                memberCount++;
                currentMemberNode = currentMemberNode->next;
            }

            unionMembersArray = arena_alloc(validator->utilsArena, sizeof(Symbol *) * memberCount, alignof(Symbol *));
            if (unionMembersArray == NULL) 
            {
                DEBUG_PRINT("validator_thirdPass: Failed to allocate memory for union members array.\n");
                return;
            }

            HashTable *unionMemberSymbolTable = hashTable_create(validator->utilsArena);
            if (unionMemberSymbolTable == NULL) 
            {
                DEBUG_PRINT("validator_thirdPass: Failed to create union member symbol table.\n");
                return;
            }

            size_t index = 0;
            currentMemberNode = unionMembersNode->children;
            LinkedList *currentMemeberNameNode = unionMembersNode->tokens;
            while (currentMemberNode != NULL) 
            {
                AstNode *currentFullTypeNode = (AstNode *)currentMemberNode->data;
                CmcType *memberType = validator_cmcTypeFromAstFullTypeNode(validator, currentFullTypeNode);
                if (memberType == NULL)
                {
                    DEBUG_PRINT("validator_thirdPass: Failed to create CmcType from AST full type node.\n");
                    return;
                }

                Token *memberNameToken = (Token *)currentMemeberNameNode->data;
                CmcType *typeWithSameName = hashTable_CmcType_find(validator->typeTable, memberNameToken->text);
                if (typeWithSameName != NULL)
                {
                    Error *error = error_create(validator->utilsArena, ERROR_ERROR, memberNameToken->location, "Union member name conflicts with a type.");
                    if (error == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error for union member name conflict with type.\n");
                        return;
                    }
                    LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                    if (head == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error linked list.\n");
                        return;
                    }
                    validator->errors = head;

                    currentMemberNode = currentMemberNode->next;
                    currentMemeberNameNode = currentMemeberNameNode->next;
                    continue;
                }

                Symbol *memberSymbol = symbol_variable_create(validator->utilsArena, memberNameToken->text, memberType);
                if (memberSymbol == NULL) 
                {
                    DEBUG_PRINT("validator_thirdPass: Failed to create symbol for union member.\n");
                    return;
                }
                if (!hashTable_Symbol_tryInsert(unionMemberSymbolTable, memberSymbol)) 
                {
                    Error *error = error_create(validator->utilsArena, ERROR_ERROR, memberNameToken->location, "Union member name already exists.");
                    if (error == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error for union member name conflict.\n");
                        return;
                    }
                    LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                    if (head == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error linked list.\n");
                        return;
                    }
                    validator->errors = head;
                }
                else
                {
                    unionMembersArray[index++] = memberSymbol;
                }

                currentMemberNode = currentMemberNode->next;
                currentMemeberNameNode = currentMemeberNameNode->next;
            }

            unionType->value.structUnion.memberCount = memberCount;
            unionType->value.structUnion.structUnionMembers = unionMembersArray;
        }
        else if (node->type == AST_ENUM_DECLARATION) 
        {
            // Validate enum values
            LinkedList *enumValues = ((AstNode *)node->children->data)->children;
            while(enumValues != NULL)
            {
                AstNode *enumValueNode = (AstNode *)enumValues->data;

                CmcType *expressionType = NULL;
                if (enumValueNode->children != NULL)
                {
                    AstNode *constExpressionNode = (AstNode *)enumValueNode->children->data;
                    bool isConst = true;
                    expressionType = validator_validateConstExpression(validator, constExpressionNode, &isConst);
                }
                
                Token *enumValueNameToken = (Token *)enumValueNode->tokens->data;
                CmcType *typeWithSameName = hashTable_CmcType_find(validator->typeTable, enumValueNameToken->text);
                if (typeWithSameName != NULL)
                {
                    Error *error = error_create(validator->utilsArena, ERROR_ERROR, enumValueNameToken->location, "Enum value name conflicts with a type.");
                    if (error == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error for enum value name conflict with type.\n");
                        return;
                    }
                    LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                    if (head == NULL) 
                    {
                        DEBUG_PRINT("validator_thirdPass: Failed to create error linked list.\n");
                        return;
                    }
                    validator->errors = head;

                    enumValues = enumValues->next;
                    continue;
                }

                Symbol *enumValueSymbol = symbol_enum_constant_create(validator->utilsArena, enumValueNameToken->text);
                if (enumValueSymbol == NULL) 
                {
                    DEBUG_PRINT("validator_secondPass: Failed to create symbol for enum value.\n");
                    return;
                }

                if (!hashTable_Symbol_tryInsert(validator->symbolStack->data, enumValueSymbol))
                {
                    Error *error = error_create(validator->utilsArena, ERROR_ERROR, enumValueNameToken->location, "Enum value already exists.");
                    if (error == NULL) 
                    {
                        DEBUG_PRINT("validator_secondPass: Failed to create error for enum value conflict.\n");
                        return;
                    }
                    LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                    if (head == NULL)
                    {
                        DEBUG_PRINT("validator_secondPass: Failed to create error linked list.\n");
                        return;
                    }
                    validator->errors = head;
                }

                if (expressionType != NULL)
                {
                    validator_matchTypeNumber(validator, expressionType);
                }

                enumValues = enumValues->next;
            }
        }
        
        current = current->next;
    }
}

void validator_fourthPass(Validator *validator)
{
    UNIMPLEMENTED();

    if (validator == NULL) 
    {
        DEBUG_PRINT("validator_fourthPass: Validator is NULL.\n");
        return;
    }

    if (validator->ast == NULL) 
    {
        DEBUG_PRINT("validator_fourthPass: AST is NULL.\n");
        return;
    }

    LinkedList *current = validator->ast->children;
    while (current != NULL) 
    {
        AstNode *node = (AstNode *)current->data;
        Token *nameToken = (Token *)node->tokens->data;
        if (nameToken->type == TOKEN_KEYWORD_EXPORT)
        {
            // Skip export keyword
            nameToken = (Token *)node->tokens->next->data;
        }

        if (node->type == AST_FUNCTION_DEFINITION) 
        {
            //TODO
        }

        current = current->next;
    }
}

CmcType *validator_cmcTypeFromAstFullTypeNode(Validator *validator, AstNode *node)
{
    if (node == NULL)
    {
        DEBUG_PRINT("validator_cmcTypeFromAstFullTypeNode: node is NULL.\n");
        return NULL;
    }

    if (node->type != AST_FULL_TYPE)
    {
        DEBUG_PRINT("validator_cmcTypeFromAstFullTypeNode: node is not of type AST_FULL_TYPE.\n");
        return NULL;
    }

    TypeSpec typeSpec = {0};
    LinkedList *currentNode = node->children;
    if (((AstNode *)currentNode->data)->type == AST_TYPE_SPECIFIERS)
    {
        AstNode *typeSpecNode = (AstNode *)currentNode->data;

        size_t specifierCount = 0;
        LinkedList *currentSpecifiers = typeSpecNode->tokens;
        while (currentSpecifiers != NULL)
        {
            specifierCount++;
            currentSpecifiers = currentSpecifiers->next;
        }
        typeSpec.count = specifierCount;

        TypeSpecEnum *specifiersArray = arena_alloc(validator->utilsArena, sizeof(TypeSpecEnum) * specifierCount, alignof(TypeSpecEnum));
        currentSpecifiers = typeSpecNode->tokens;
        size_t index = 0;
        while (currentSpecifiers != NULL)
        {
            specifiersArray[index++] = validator_typeSpecEnumFromTokenType(((Token *)currentSpecifiers->data)->type);
            currentSpecifiers = currentSpecifiers->next;
        }
        typeSpec.types = specifiersArray;

        currentNode = currentNode->next; // Move to the next node which should be AST_TYPE
    }

    Token *typeToken = ((AstNode *)currentNode->data)->tokens->data;

    CmcType *cmcType = hashTable_CmcType_find(validator->typeTable, typeToken->text);
    if (cmcType == NULL)
    {
        Error *error = error_create(validator->utilsArena, ERROR_ERROR, typeToken->location, "Type does not exist.");
        if (error == NULL)
        {
            DEBUG_PRINT("validator_cmcTypeFromAstFullTypeNode: Failed to create error for type not found.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("validator_cmcTypeFromAstFullTypeNode: Failed to create error linked list.\n");
            return NULL;
        }
        validator->errors = head;
        return NULL;
    }
    CmcType *resultType = cmcType_copy(validator->utilsArena, cmcType);
    if (resultType == NULL)
    {
        DEBUG_PRINT("validator_cmcTypeFromAstFullTypeNode: Failed to copy CmcType.\n");
        return NULL;
    }
    
    currentNode = currentNode->next;
    if (currentNode != NULL)
    {
        CmcType *arrayBaseType = resultType;
        resultType = cmcType_array_create(validator->utilsArena, arrayBaseType);
        if (resultType == NULL)
        {
            DEBUG_PRINT("validator_cmcTypeFromAstFullTypeNode: Failed to create array type.\n");
            return NULL;
        }
        
        currentNode = currentNode->next;
    }
    resultType->specifiers = typeSpec;

    return resultType;
}

TypeSpecEnum validator_typeSpecEnumFromTokenType(My_TokenType tokenType)
{
    switch (tokenType)
    {
        case TOKEN_KEYWORD_CONST:
            return TYPE_SPEC_CONST;
        case TOKEN_KEYWORD_PTR:
            return TYPE_SPEC_PTR;
        case TOKEN_KEYWORD_CONST_PTR:
            return TYPE_SPEC_CONST_PTR;
        default:
            DEBUG_PRINT("validator_typeSpecEnumFromTokenType: Unknown token type for TypeSpecEnum.\n");
            return -1; // Invalid TypeSpecEnum
    }

    UNREACHABLE();
}

CmcType *validator_validateConstExpression(Validator *validator, AstNode *constExpressionNode, bool *isConst)
{
    if (validator == NULL) 
    {
        DEBUG_PRINT("validator_validateConstExpression: Validator is NULL.\n");
        return NULL;
    }

    if (constExpressionNode == NULL) 
    {
        DEBUG_PRINT("validator_validateConstExpression: constExpressionNode is NULL.\n");
        return NULL;
    }

    if (!*isConst)
    {
        DEBUG_PRINT("validator_validateConstExpression: Expression is not constant.\n");
        return NULL;
    }

    switch (constExpressionNode->type)
    {
    case AST_EXPRESSION:;
        AstNode *expressionChild = constExpressionNode->children->data;
        return validator_validateConstExpression(validator, expressionChild, isConst);
    case AST_LOGICAL_OR_EXPRESSION:
    case AST_LOGICAL_AND_EXPRESSION:
    case AST_BITWISE_AND_EXPRESSION:
    case AST_BITWISE_OR_EXPRESSION:
    case AST_BITWISE_XOR_EXPRESSION:
    case AST_EQUALITY_EXPRESSION:
    case AST_RELATIONAL_EXPRESSION:
    case AST_SHIFT_EXPRESSION:
    case AST_ADDITIVE_EXPRESSION:
    case AST_MULTIPLICATIVE_EXPRESSION:;
        bool leftIsConst = true;
        AstNode *leftChild = constExpressionNode->children->data;
        CmcType *leftType = validator_validateConstExpression(validator, leftChild, &leftIsConst);
        AstNode *rightChild = constExpressionNode->children->next->data;
        bool rightIsConst = true;
        CmcType *rightType = validator_validateConstExpression(validator, rightChild, &rightIsConst);
        *isConst &= (leftIsConst && rightIsConst);
        if (!*isConst || leftType == NULL || rightType == NULL) return NULL;
        CmcType *binaryResultType = validator_matchConstBinaryType(validator, leftType, rightType, constExpressionNode->tokens->data);
        return binaryResultType;
    case AST_UNARY_EXPRESSION:;
        AstNode *unaryChild = constExpressionNode->children->data;
        CmcType *unaryType = validator_validateConstExpression(validator, unaryChild, isConst);
        if (!*isConst || unaryType == NULL) return NULL;
        CmcType *unaryResultType = validator_matchConstUnaryType(validator, unaryType, constExpressionNode->tokens->data);
        return unaryResultType;
    case AST_TYPE_CAST_EXPRESSION:;
        AstNode *typeToCastToNode = constExpressionNode->children->data;
        CmcType *typeToCastTo = validator_cmcTypeFromAstFullTypeNode(validator, typeToCastToNode);
        if (typeToCastTo == NULL) return NULL;
        AstNode *expressionToCastNode = constExpressionNode->children->next->data;
        CmcType *expressionToCastType = validator_validateConstExpression(validator, expressionToCastNode, isConst);
        if (!*isConst || expressionToCastType == NULL) return NULL;
        CmcType *typeCastResultType = validator_matchConstTypeCast(validator, typeToCastTo, expressionToCastType);
        return typeCastResultType;
    case AST_POSTFIX_EXPRESSION:;
        AstNode *primaryChild = constExpressionNode->children->data;
        CmcType *primaryType = validator_validateConstExpression(validator, primaryChild, isConst);

        LinkedList *postfixChildLL = constExpressionNode->children->next;
        CmcType *postfixResultType = primaryType;
        while (postfixChildLL != NULL)
        {
            bool postfixIsConst = true;
            AstNode *postfixChild = postfixChildLL->data;
            CmcType *postfixType = validator_validateConstExpression(validator, postfixChild, &postfixIsConst);
            *isConst &= postfixIsConst;
            if (*isConst && postfixResultType != NULL)
            {
                postfixResultType = validator_matchConstPostfixType(validator, postfixResultType, postfixType, postfixChild);
            }
            postfixChildLL = postfixChildLL->next;
        }
        return postfixResultType;
    case AST_STRUCT_UNION_DECLARATOR:;
        UNIMPLEMENTED(); // TODO: This should have its own function to validate if the fields match and the assigned values are constant
        return NULL;
    case AST_POSTFIX_PRIME_EXPRESSION:;
        return validator_getConstPostfixPrimeType(validator, constExpressionNode->tokens->data);
    case AST_ARRAY_INDEXING_EXPRESSION:;
        AstNode *arrayIndexingChild = constExpressionNode->children->data;
        CmcType *arrayIndexingType = validator_validateConstExpression(validator, arrayIndexingChild, isConst);
        if (!*isConst || arrayIndexingType == NULL) return NULL;
        CmcType *arrayIndexingResultType = validator_matchConstArrayIndexingType(validator, arrayIndexingType);
        return arrayIndexingResultType;
    case AST_PRIMARY_EXPRESSION:;
        Token *primaryToken = (Token *)constExpressionNode->tokens->data;
        Symbol *primarySymbol = hashTable_Symbol_find(validator->symbolStack->data, primaryToken->text);
        if (primarySymbol->type != SYMBOL_TYPE_VARIABLE && primarySymbol->type != SYMBOL_TYPE_ENUM_CONSTANT) 
        {
            Error *error = error_create(validator->utilsArena, ERROR_ERROR, primaryToken->location, "Constant expression must be a variable or enum constant.");
            if (error == NULL)
            {
                DEBUG_PRINT("validator_validateConstExpression: Failed to create error for non-constant primary expression.\n");
                return NULL;
            }
            LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
            if (head == NULL)
            {
                DEBUG_PRINT("validator_validateConstExpression: Failed to create error linked list.\n");
                return NULL;
            }
            validator->errors = head;
            *isConst = false;
            return NULL;
        }
        if (primarySymbol == NULL) return NULL;
        return validator_getConstPrimaryType(validator, primarySymbol);
    case AST_LITERAL:;
        return validator_getLiteralType(validator, constExpressionNode->tokens->data);
    case AST_ASSIGNMENT_EXPRESSION:
    case AST_FUNCTION_CALL_EXPRESSION:
        *isConst = false;
        return NULL;
    default:;
        DEBUG_PRINT("validator_validateConstExpression: Unsupported expression type: %d\n", constExpressionNode->type);
        UNREACHABLE();
    }

    UNREACHABLE();
}

CmcType *validator_matchType(Validator *validator, CmcType *expectedType, CmcType *actualType)
{
    return NULL;
    UNIMPLEMENTED();
}

CmcType *validator_matchTypeNumber(Validator *validator, CmcType *actualType)
{
    UNIMPLEMENTED();
}

CmcType *validator_matchConstBinaryType(Validator *validator, CmcType *leftType, CmcType *rightType, Token *operatorToken)
{
    UNIMPLEMENTED();
    if (validator == NULL) 
    {
        DEBUG_PRINT("validator_matchConstBinaryType: Validator is NULL.\n");
        return NULL;
    }

    if (leftType == NULL) 
    {
        DEBUG_PRINT("validator_matchConstBinaryType: Left or right type is NULL.\n");
        return NULL;
    }

    if (rightType == NULL) 
    {
        DEBUG_PRINT("validator_matchConstBinaryType: Left or right type is NULL.\n");
        return NULL;
    }

    if (operatorToken == NULL) 
    {
        DEBUG_PRINT("validator_matchConstBinaryType: Operator token is NULL.\n");
        return NULL;
    }

    if (leftType->type == CMC_TYPE_VOID || rightType->type == CMC_TYPE_VOID)
    {
        Error *error = error_create(validator->utilsArena, ERROR_ERROR, operatorToken->location, "Void types cannot be used in binary operations.");
        if (error == NULL)
        {
            DEBUG_PRINT("validator_matchConstBinaryType: Failed to create error for void type in binary operation.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("validator_matchConstBinaryType: Failed to create error linked list.\n");
            return NULL;
        }
        validator->errors = head;
        return NULL; // Void types cannot be used in binary operations
    }

    if (rightType->type == CMC_TYPE_STRUCT || rightType->type == CMC_TYPE_UNION || leftType->type == CMC_TYPE_STRUCT || leftType->type == CMC_TYPE_UNION)
    {
        Error *error = error_create(validator->utilsArena, ERROR_ERROR, operatorToken->location, "Structs and unions cannot be used in binary operations.");
        if (error == NULL)
        {
            DEBUG_PRINT("validator_matchConstBinaryType: Failed to create error for struct/union in binary operation.\n");
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
        if (head == NULL)
        {
            DEBUG_PRINT("validator_matchConstBinaryType: Failed to create error linked list.\n");
            return NULL;
        }
        validator->errors = head;
        return NULL; // Structs and unions cannot be used in binary operations
    }

    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};

    // ALL OPS: INT, UINT, FLOAT, CHAR, ENUM
    // ONLY ADD: STRING
    // ONLY BITWISE, LOGICAL, COMPARISON: BOOL
    // TODO:
    switch (operatorToken->type)
    {
    case TOKEN_DOUBLE_PIPE:
    case TOKEN_DOUBLE_AMPERSAND:
    case TOKEN_PIPE:
    case TOKEN_CARET:
    case TOKEN_AMPERSAND:
    case TOKEN_DOUBLE_EQUALS:
    case TOKEN_EXCLAMATION_EQUALS:
    case TOKEN_LESS_THAN:
    case TOKEN_GREATER_THAN:
    case TOKEN_LESS_THAN_EQUALS:
    case TOKEN_GREATER_THAN_EQUALS:
    case TOKEN_DOUBLE_LESS_THAN:
    case TOKEN_DOUBLE_GREATER_THAN:
    case TOKEN_PLUS:
    case TOKEN_MINUS:
    case TOKEN_STAR:
    case TOKEN_SLASH:
    case TOKEN_PERCENT:
        /* code */
        break;
    
    default:
        UNREACHABLE();
    }

    UNREACHABLE();
}

CmcType *validator_matchConstUnaryType(Validator *validator, CmcType *unaryType, Token *operatorToken)
{
    UNIMPLEMENTED();
}

CmcType *validator_matchConstTypeCast(Validator *validator, CmcType *typeToCastTo, CmcType *expressionToCastType)
{
    UNIMPLEMENTED();
}

CmcType *validator_matchConstPostfixType(Validator *validator, CmcType *primaryType, CmcType *postfixType, AstNode *postfixPrimeNode)
{
    UNIMPLEMENTED();
}

CmcType *validator_getConstPostfixPrimeType(Validator *validator, Token *postfixPrimeNode)
{
    UNIMPLEMENTED();
}

CmcType *validator_matchConstArrayIndexingType(Validator *validator, CmcType *arrayType)
{
    UNIMPLEMENTED();
}

CmcType *validator_getConstPrimaryType(Validator *validator, Symbol *primarySymbol)
{
    if (validator == NULL) 
    {
        DEBUG_PRINT("validator_getConstPrimaryType: Validator is NULL.\n");
        return NULL;
    }

    if (primarySymbol == NULL) 
    {
        DEBUG_PRINT("validator_getConstPrimaryType: primarySymbol is NULL.\n");
        return NULL;
    }

    if (primarySymbol->type != SYMBOL_TYPE_VARIABLE && primarySymbol->type != SYMBOL_TYPE_ENUM_CONSTANT) 
    {
        DEBUG_PRINT("validator_getConstPrimaryType: Symbol is not a variable or enum constant.\n");
        return NULL;
    }

    if (primarySymbol->type == SYMBOL_TYPE_VARIABLE)
    {
        return primarySymbol->value.variableType;
    }
    else
    {
        CmcType *enumType = hashTable_CmcType_find(validator->typeTable, "int32");
        if (enumType == NULL) 
        {
            DEBUG_PRINT("validator_getConstPrimaryType: Enum type not found in type table.\n");
            return NULL;
        }
        return enumType;
    }
}

CmcType *validator_getLiteralType(Validator *validator, Token *literalToken)
{
    if (validator == NULL)
    {
        DEBUG_PRINT("validator_getLiteralType: Validator is NULL.\n");
        return NULL;
    }

    if (literalToken == NULL)
    {
        DEBUG_PRINT("validator_getLiteralType: literalToken is NULL.\n");
        return NULL;
    }

    CmcType *type = NULL;
    switch (literalToken->type)
    {
    case TOKEN_LITERAL_INTEGER:
    case TOKEN_LITERAL_HEXADECIMAL:
    case TOKEN_LITERAL_OCTAL:
    case TOKEN_LITERAL_BINARY:
        type = hashTable_CmcType_find(validator->typeTable, "int32");
        if (type == NULL)
        {
            DEBUG_PRINT("validator_getLiteralType: Integer type not found in type table.\n");
            return NULL;
        }
        break;
    case TOKEN_LITERAL_FLOATINGPOINT:
        type = hashTable_CmcType_find(validator->typeTable, "float64");
        if (type == NULL)
        {
            DEBUG_PRINT("validator_getLiteralType: Floating point type not found in type table.\n");
            return NULL;
        }
        break;
    case TOKEN_LITERAL_CHARACTER:
        type = hashTable_CmcType_find(validator->typeTable, "char");
        if (type == NULL)
        {
            DEBUG_PRINT("validator_getLiteralType: Character type not found in type table.\n");
            return NULL;
        }
        break;
    case TOKEN_LITERAL_STRING:
        type = hashTable_CmcType_find(validator->typeTable, "string");
        if (type == NULL)
        {
            DEBUG_PRINT("validator_getLiteralType: String type not found in type table.\n");
            return NULL;
        }
        break;
    case TOKEN_LITERAL_BOOLEAN:
        type = hashTable_CmcType_find(validator->typeTable, "bool");
        if (type == NULL)
        {
            DEBUG_PRINT("validator_getLiteralType: Boolean type not found in type table.\n");
            return NULL;
        }
        break;
    case TOKEN_LITERAL_NULL:
        type = hashTable_CmcType_find(validator->typeTable, "void");
        if (type == NULL)
        {
            DEBUG_PRINT("validator_getLiteralType: Void type not found in type table.\n");
            return NULL;
        }
        break;
    default:
        DEBUG_PRINT("validator_getLiteralType: Unsupported literal token type: %d\n", literalToken->type);
        UNREACHABLE();
    }

    return type;
}

//------------------------------------------------------------

Validator* validator_create(Arena *utilsArena, AstNode *ast)
{
    if (utilsArena == NULL)
    {
        DEBUG_PRINT("validator_create: utilsArena is NULL.\n");
        return NULL;
    }

    if (ast == NULL)
    {
        DEBUG_PRINT("validator_create: ast is NULL.\n");
        return NULL;
    }

    Validator *validator = (Validator *)arena_alloc(utilsArena, sizeof(Validator), alignof(Validator));
    if (validator == NULL)
    {
        DEBUG_PRINT("validator_create: Failed to allocate memory for Validator.\n");
        return NULL;
    }

    validator->utilsArena = utilsArena;
    validator->ast = ast;
    validator->symbolStack = NULL;
    validator->typeTable = NULL;
    validator->errors = NULL;

    return validator;
}

void validator_validate(Validator *validator)
{
    if (validator == NULL) 
    {
        DEBUG_PRINT("validator_validate: Validator is NULL.\n");
        return;
    }

    if (validator->ast == NULL) 
    {
        DEBUG_PRINT("validator_validate: AST is NULL.\n");
        return;
    }

    // Initialize symbol stack and type table
    HashTable *globlaScoop = hashTable_create(validator->utilsArena);
    if (globlaScoop == NULL)
    {
        DEBUG_PRINT("validator_validate: Failed to create symbol stack.\n");
        return;
    }
    LinkedList *head = linkedList_HashTable_create(validator->utilsArena, validator->symbolStack, globlaScoop);
    if (head == NULL) 
    {
        DEBUG_PRINT("validator_validate: Failed to create symbol stack.\n");
        return;
    }
    validator->symbolStack = head;

    HashTable *typeTable = hashTable_create(validator->utilsArena);
    if (typeTable == NULL) 
    {
        DEBUG_PRINT("validator_validate: Failed to create type table.\n");
        return;
    }
    validator->typeTable = typeTable;

    // Initialize base types
    validator_initializeBaseTypes(validator);

    // Perform validation passes
    //validator_firstPass(validator); TODO
    if (validator->errors != NULL) return;
    validator_secondPass(validator);
    if (validator->errors != NULL) return;
    validator_thirdPass(validator);
    if (validator->errors != NULL) return;
    //validator_fourthPass(validator); TODO
    if (validator->errors != NULL) return;

    //hashTable_print(validator->typeTable, (PrintFunction)cmcType_print); TEST
    //hashTable_print(validator->symbolStack->data, (PrintFunction)symbol_print); TEST
}

void validator_print(const Validator *validator)
{
    if (validator == NULL) 
    {
        DEBUG_PRINT("validator_print: Validator is NULL.\n");
        return;
    }

    printf("Validator {\n");
    printf("\tutilsArena: ");
    arena_print(validator->utilsArena);
    printf("\tastRoot: \n");
    astNode_printTree(validator->ast, "", false);
    printf("}\n");
}