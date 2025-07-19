#include "validator.h"

void validator_initializeBaseTypes(Validator *validator);

void validator_firstPass(Validator *validator);

void validator_secondPass(Validator *validator);

void validator_thirdPass(Validator *validator);

void validator_fourthPass(Validator *validator);

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
        CmcType *baseType = cmcType_base_create(validator->utilsArena, baseTypes[i]);
        if (baseType == NULL) 
        {
            DEBUG_PRINT("validator_initializeBaseTypes: Failed to create base type.\n");
            return;
        }
        hashTable_CmcType_tryInsert(validator->typeTable, baseType);
    }
}

// First pass: Import symbols
void validator_firstPass(Validator *validator)
{
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

    //LinkedList *current = validator->ast->children;
    // TODO
}

// Second pass: Validate Struct names, Union names, Enum names and Enum values
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
        if (node->type == AST_STRUCT_DECLARATION)
        {
            Token *nameToken = (Token *)node->tokens->data;
            if (nameToken->type == TOKEN_KEYWORD_EXPORT)
            {
                // Skip export keyword
                nameToken = (Token *)node->tokens->next->data;
            }
            
            CmcType *structType = cmcType_structOrUnion_create(validator->utilsArena, CMC_TYPE_STRUCT, nameToken->text, NULL, 0);
            if (structType == NULL) 
            {
                DEBUG_PRINT("validator_validate: Failed to create struct type for struct declaration.\n");
                return;
            }

            if(!hashTable_CmcType_tryInsert(validator->typeTable, structType))
            {
                Error *error = error_create(validator->utilsArena, ERROR_ERROR, nameToken->location, "Struct name already exists.");
                if (error == NULL) 
                {
                    DEBUG_PRINT("validator_validate: Failed to create error for struct name conflict.\n");
                    return;
                }
                LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                if (head == NULL) 
                {
                    DEBUG_PRINT("validator_validate: Failed to create error linked list.\n");
                    return;
                }
                validator->errors = head;
            }
        }
        else if (node->type == AST_UNION_DECLARATION)
        {
            Token *nameToken = (Token *)node->tokens->data;
            if (nameToken->type == TOKEN_KEYWORD_EXPORT)
            {
                // Skip export keyword
                nameToken = (Token *)node->tokens->next->data;
            }

            CmcType *unionType = cmcType_structOrUnion_create(validator->utilsArena, CMC_TYPE_UNION, nameToken->text, NULL, 0);
            if (unionType == NULL) 
            {
                DEBUG_PRINT("validator_validate: Failed to create union type for union declaration.\n");
                return;
            }

            if(!hashTable_CmcType_tryInsert(validator->typeTable, unionType))
            {
                Error *error = error_create(validator->utilsArena, ERROR_ERROR, nameToken->location, "Union name already exists.");
                if (error == NULL) 
                {
                    DEBUG_PRINT("validator_validate: Failed to create error for union name conflict.\n");
                    return;
                }
                LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                if (head == NULL) 
                {
                    DEBUG_PRINT("validator_validate: Failed to create error linked list.\n");
                    return;
                }
                validator->errors = head;
            }
        }
        else if (node->type == AST_ENUM_DECLARATION)
        {
            Token *nameToken = (Token *)node->tokens->data;
            if (nameToken->type == TOKEN_KEYWORD_EXPORT)
            {
                // Skip export keyword
                nameToken = (Token *)node->tokens->next->data;
            }

            CmcType *enumType = cmcType_enum_create(validator->utilsArena, nameToken->text);
            if (enumType == NULL) 
            {
                DEBUG_PRINT("validator_validate: Failed to create enum type for enum declaration.\n");
                return;
            }

            if(!hashTable_CmcType_tryInsert(validator->typeTable, enumType))
            {
                Error *error = error_create(validator->utilsArena, ERROR_ERROR, nameToken->location, "Enum name already exists.");
                if (error == NULL) 
                {
                    DEBUG_PRINT("validator_validate: Failed to create error for enum name conflict.\n");
                    return;
                }
                LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                if (head == NULL) 
                {
                    DEBUG_PRINT("validator_validate: Failed to create error linked list.\n");
                    return;
                }
                validator->errors = head;
            }

            // Validate enum values
            LinkedList *enumValues = ((AstNode *)node->children->data)->children;
            while(enumValues != NULL)
            {
                AstNode *enumValueNode = (AstNode *)enumValues->data;
                
                Symbol *enumValueSymbol = symbol_enum_constant_create(validator->utilsArena, ((Token *)enumValueNode->tokens->data)->text);
                if (enumValueSymbol == NULL) 
                {
                    DEBUG_PRINT("validator_validate: Failed to create symbol for enum value.\n");
                    return;
                }

                if (!hashTable_Symbol_tryInsert(validator->symbolStack->data, enumValueSymbol))
                {
                    Error *error = error_create(validator->utilsArena, ERROR_ERROR, ((Token *)enumValueNode->tokens->data)->location, "Enum value already exists.");
                    if (error == NULL) 
                    {
                        DEBUG_PRINT("validator_validate: Failed to create error for enum value conflict.\n");
                        return;
                    }
                    LinkedList *head = linkedList_Error_create(validator->utilsArena, validator->errors, error);
                    if (head == NULL)
                    {
                        DEBUG_PRINT("validator_validate: Failed to create error linked list.\n");
                        return;
                    }
                    validator->errors = head;
                }

                enumValues = enumValues->next;
            }
        }

        current = current->next;
    }
}

// Third pass: Validate Function names, Variables, Struct and Union members
void validator_thirdPass(Validator *validator)
{
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

    //LinkedList *current = validator->ast->children;
    // TODO
}

// Fourth pass: Validate Functions
void validator_fourthPass(Validator *validator)
{
    if (validator == NULL) 
    {
        DEBUG_PRINT("validator_fifthPass: Validator is NULL.\n");
        return;
    }

    if (validator->ast == NULL) 
    {
        DEBUG_PRINT("validator_fifthPass: AST is NULL.\n");
        return;
    }

    //LinkedList *current = validator->ast->children;
    // TODO
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
    validator_firstPass(validator);
    validator_secondPass(validator);
    validator_thirdPass(validator);
    validator_fourthPass(validator);
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