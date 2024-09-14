#include "validator.h"

/*****************************************************************************************************
                            PRIVATE VALIDATOR FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

static int addError(Validator *validator, Error *error);

static int typeCheck(Validator *validator);

static int constantFold(Validator *validator);

/*****************************************************************************************************
                                PRIVATE VALIDATOR FUNCTIONS START HERE
 *****************************************************************************************************/

static int addError(Validator *validator, Error *error)
{
    if (validator == NULL)
    {
        fprintf(stderr, "Validator is not initialized.\n");
        return 0;
    }

    if (error == NULL)
    {
        fprintf(stderr, "Error is not initialized.\n");
        return 0;
    }

    if (validator->errorCount + 1 >= validator->errorsSize)
    {
        validator->errorsSize *= 2;
        Error **newErrors = realloc(validator->errors, validator->errorsSize * sizeof(Error *));
        if (newErrors == NULL)
        {
            fprintf(stderr, "Memory reallocation for Errors failed!\n");
            return 0;
        }
        validator->errors = newErrors;
    }

    validator->errors[validator->errorCount++] = error;
    return 1;
}

//TODO: Implement type checking
// This should first handle the global scope
// then call a recursive function to check each node in the AST
static int typeCheck(Validator *validator)
{
    if (validator == NULL)
    {
        fprintf(stderr, "Validator is not initialized.\n");
        return 0;
    }

    if (validator->globalScope == NULL)
    {
        fprintf(stderr, "Global scope is not initialized.\n");
        return 0;
    }

    if (validator->scopes == NULL)
    {
        fprintf(stderr, "Scopes stack is not initialized.\n");
        return 0;
    }

    if (validator->ASTroot == NULL)
    {
        fprintf(stderr, "ASTRoot is not initialized.\n");
        return 0;
    }

    if (validator->ASTroot->type != AST_PROGRAM)
    {
        fprintf(stderr, "ASTRoot is not a PROGRAM node.\n");
        return 0;
    }

    //Add function declarations to the global scope
    ASTNode *program = validator->ASTroot;
    //TODO: Implement adding function declarations to the global scope
    //This should something like a recusive decent parser but returning the retrived data found.

    return 1;
}

//TODO: Implement constant folding
// This should call a recursive function until it finds a constant expression then evaluate it
// The evaluation should be done similarly to how the parser parses
// This should alter the AST in place and free old nodes
static int constantFold(Validator *validator)
{
    if (validator == NULL)
    {
        fprintf(stderr, "Validator is not initialized.\n");
        return 0;
    }

    return 1;
}

/*****************************************************************************************************
                                PUBLIC VALIDATOR FUNCTIONS START HERE                                
 *****************************************************************************************************/

Validator *createValidator(ASTNode *ASTroot)
{
    if (ASTroot == NULL)
    {
        fprintf(stderr, "ASTRoot provided to the validator is NULL!\n");
        return NULL;
    }

    Validator *validator = (Validator *)malloc(sizeof(Validator));
    if (validator == NULL)
    {
        fprintf(stderr, "Memory allocation for Validator failed!\n");
        return NULL;
    }

    validator->globalScope = initHashTable();
    if (validator->globalScope == NULL)
    {
        free(validator);
        return NULL;
    }

    validator->scopes = initStack(sizeof(HashTable *));
    if (validator->scopes == NULL)
    {
        deleteHashTable(validator->globalScope);
        free(validator);
        return NULL;
    }

    validator->ASTroot = ASTroot;

    validator->errorsSize = 1;
    validator->errors = malloc(validator->errorsSize * sizeof(Error *));
    if (validator->errors == NULL)
    {
        fprintf(stderr, "Memory allocation for Validator->errors failed!\n");
        deleteHashTable(validator->globalScope);
        deleteStack(validator->scopes);
        free(validator);
        return NULL;
    }
    validator->errorCount = 0;

    return validator;
}

void deleteValidator(Validator *validator)
{
    deleteHashTable(validator->globalScope);
    deleteStack(validator->scopes);
    free(validator->ASTroot);

    deleteErrors(validator->errors, validator->errorCount);
    free(validator->errors);

    free(validator);
}

int validate(Validator *validator)
{
    if (validator == NULL)
    {
        fprintf(stderr, "Validator is not initialized.\n");
        return 0;
    }

    if (!typeCheck(validator))
    {
        fprintf(stderr, "Type checking failed!\n");
        return 0;
    }

    if (!constantFold(validator))
    {
        fprintf(stderr, "Constant folding failed!\n");
        return 0;
    }

    return 1;
}

ASTNode *copyASTNode(const Validator *const validator)
{
    if (validator == NULL)
    {
        fprintf(stderr, "Validator is not initialized.\n");
        return NULL;
    }

    return duplicateASTNode(validator->ASTroot);
}