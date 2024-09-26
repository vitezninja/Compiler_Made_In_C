#include "validator.h"

/*****************************************************************************************************
                            PRIVATE VALIDATOR FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

static int addError(Validator *validator, Error *error);

static void addCreatedToken(Validator *validator, Token *token);

static int typeCheck(Validator *validator);

static int constantFold(Validator *validator, int optimize);

static void findConstant(Validator *validator, ASTNode *node);

static ASTNode *tryFold(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldConditionalExpression(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldLogicalOrExpression(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldLogicalAndExpression(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldBitwiseOrExpression(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldBitwiseXorExpression(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldBitwiseAndExpression(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldEqualityExpression(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldRelationalExpression(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldShiftExpression(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldAdditiveExpression(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldMultiplicativeExpression(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldCastExpression(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldUnaryExpression(Validator *validator, ASTNode *node, int *isConstant);

static ASTNode *foldPrimaryExpression(Validator *validator, ASTNode *node, int *isConstant);

static Symbol *findTypeSymbol(Validator *validator, ASTNode *node);

static int getSymbolSize(Symbol *symbol);

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

static void addCreatedToken(Validator *validator, Token *token)
{
    if (validator == NULL)
    {
        fprintf(stderr, "Validator is not initialized.\n");
        return;
    }

    if (token == NULL)
    {
        fprintf(stderr, "Token is not initialized.\n");
        return;
    }

    if (validator->createdTokenCount + 1 >= validator->createdTokensSize)
    {
        validator->createdTokensSize *= 2;
        Token **newTokens = realloc(validator->createdTokens, validator->createdTokensSize * sizeof(Token *));
        if (newTokens == NULL)
        {
            fprintf(stderr, "Memory reallocation for Tokens failed!\n");
            return;
        }
        validator->createdTokens = newTokens;
    }

    validator->createdTokens[validator->createdTokenCount++] = token;
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

    //Add function declarations to the global scope
    //TODO: Implement adding function declarations to the global scope
    //This should something like a recusive decent parser but returning the retrived data found.

    return 1;
}

static int constantFold(Validator *validator, int optimize)
{
    if (validator == NULL)
    {
        fprintf(stderr, "Validator is not initialized.\n");
        return 0;
    }

    if (optimize)
    {
        #if defined(_POSIX_VERSION)
        for (size_t i = 0; i < validator->ASTroot->childCount; i++)
        {
            pid_t parent = fork();

            if (!parent)
            {
                findConstant(validator, validator->ASTroot->children[i]);   
                exit(0);
            }
        }
        while (wait(NULL) > 0);
        #else
        //TODO: Implement threading for Windows
        findConstant(validator, validator->ASTroot);
        #endif
    }
    else
    {
        findConstant(validator, validator->ASTroot);
    }

    return 1;
}

static void findConstant(Validator *validator, ASTNode *node)
{
    if (node == NULL)
    {
        return;
    }

    for (size_t i = 0; i < node->childCount; i++)
    {
        if (node->children[i]->type == AST_CONSTANT_EXPRESSION)
        {
            int isConstant = 1;
            tryFold(validator, node->children[i], &isConstant);
        }
        else
        {
            findConstant(validator, node->children[i]);
        }
    }
}

static ASTNode *tryFold(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (*isConstant == 0)
    {
        return NULL;
    }

    ASTNode *result = NULL;
    if (node->type == AST_CONSTANT_EXPRESSION)
    {
        int isConstant = 1;
        ASTNode *child = tryFold(validator, node->children[0], &isConstant);
        freeASTNode(node->children[0]);
        node->children[0] = child;
        result = node;
    }    
    else if (node->type == AST_CONDITIONAL_EXPRESSION)
    {
        result = foldConditionalExpression(validator, node, isConstant); //Done
    }
    else if (node->type == AST_LOGICAL_OR_EXPRESSION) 
    {
        result = foldLogicalOrExpression(validator, node, isConstant); //Done
    }
    else if (node->type == AST_LOGICAL_AND_EXPRESSION)
    {
        result = foldLogicalAndExpression(validator, node, isConstant); //Done
    }
    else if (node->type == AST_BITWISE_OR_EXPRESSION)
    {
        result = foldBitwiseOrExpression(validator, node, isConstant); //Done
    }
    else if (node->type == AST_BITWISE_XOR_EXPRESSION)
    {
        result = foldBitwiseXorExpression(validator, node, isConstant); //Done
    }
    else if (node->type == AST_BITWISE_AND_EXPRESSION)
    {
        result = foldBitwiseAndExpression(validator, node, isConstant); //Done
    }
    else if (node->type == AST_EQUALITY_EXPRESSION)
    {
        result = foldEqualityExpression(validator, node, isConstant); //Done
    }
    else if (node->type == AST_RELATIONAL_EXPRESSION)
    {
        result = foldRelationalExpression(validator, node, isConstant); //Done
    }
    else if (node->type == AST_SHIFT_EXPRESSION)
    {
        result = foldShiftExpression(validator, node, isConstant); //Done
    }
    else if (node->type == AST_ADDITIVE_EXPRESSION)
    {
        result = foldAdditiveExpression(validator, node, isConstant); //Done
    }
    else if (node->type == AST_MULTIPLICATIVE_EXPRESSION)
    {
        result = foldMultiplicativeExpression(validator, node, isConstant); //Done
    }
    else if (node->type == AST_CAST_EXPRESSION)
    {
        //TODO: Implement cast expression folding
        result = foldCastExpression(validator, node, isConstant);
    }
    else if (node->type == AST_UNARY_EXPRESSION)
    {
        //TODO: Implement sizeof calculation
        result = foldUnaryExpression(validator, node, isConstant); //Mostly done
    }
    else if (node->type == AST_POSTFIX_EXPRESSION)
    {
        *isConstant = 0;
        result = deepCopyASTNode(node); //Done
    }
    else if (node->type == AST_PRIMARY_EXPRESSION)
    {
        result = foldPrimaryExpression(validator, node, isConstant); //Done
    }
    else if (node->type == AST_LITERAL)
    {
        return deepCopyASTNode(node); //Done
    }
    else 
    {
        fprintf(stderr, "Unknown node type: %d\n", node->type);
        *isConstant = 0;
        return NULL;
    }

    return result;
}

static ASTNode *foldConditionalExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    int isConstantChild = 1;
    ASTNode *trueExpression = tryFold(validator, node->children[1], &isConstantChild);
    freeASTNode(node->children[1]);
    node->children[1] = trueExpression;
    if (!isConstantChild)
    {
        *isConstant = 0;
    }

    isConstantChild = 1;
    ASTNode *falseExpression = tryFold(validator, node->children[2], &isConstantChild);
    freeASTNode(node->children[2]);
    node->children[2] = falseExpression;
    if (!isConstantChild)
    {
        *isConstant = 0;
    }

    isConstantChild = 1;
    ASTNode *condition = tryFold(validator, node->children[0], &isConstantChild);
    freeASTNode(node->children[0]);
    node->children[0] = condition;
    if (isConstantChild)
    {
        ASTNode *returnExpression = NULL;

        if ((condition->tokens[0]->type == TOKEN_INTEGER && condition->tokens[0]->value.number != 0) ||
            (condition->tokens[0]->type == TOKEN_FLOATINGPOINT && condition->tokens[0]->value.floatingPoint != 0.0) ||
            (condition->tokens[0]->type == TOKEN_CHARACTER && condition->tokens[0]->value.character != '\0') ||
            (condition->tokens[0]->type == TOKEN_STRING && condition->tokens[0]->value.string != NULL) ||
            (condition->tokens[0]->type == TOKEN_HEXADECIMAL && condition->tokens[0]->value.number != 0) ||
            (condition->tokens[0]->type == TOKEN_OCTAL && condition->tokens[0]->value.number != 0))
        {
            returnExpression = deepCopyASTNode(node->children[1]);
            deleteASTNode(node->children[2]);
        }
        else
        {
            deleteASTNode(node->children[1]);
            returnExpression = deepCopyASTNode(node->children[2]);
        }
        freeASTNode(node);

        return returnExpression;
    }
    else
    {
        *isConstant = 0;
        return deepCopyASTNode(node);
    }
}

static ASTNode *foldLogicalOrExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    int *isConstantChild = malloc(node->childCount * sizeof(int));
    memset(isConstantChild, 1, node->childCount * sizeof(int));
    //Iterating over the children and fold them
    int foldCount = 0;
    for (size_t i = 0; i < node->childCount; i++)
    {
        ASTNode *child = tryFold(validator, node->children[i], &(isConstantChild[i]));
        freeASTNode(node->children[i]);
        node->children[i] = child;
        if (isConstantChild[i])
        {
            foldCount++;
        }
        else
        {
            *isConstant = 0;
        }
    }
    if (foldCount == 0)
    {
        free(isConstantChild);
        return deepCopyASTNode(node);
    }

    //Allocating memory
    size_t tokensSize = node->tokenCount;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        free(isConstantChild);
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = node->childCount;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(isConstantChild);
        free(tokens);
        *isConstant = 0;
        return NULL;
    }
    size_t childCount = 0;
    
    ASTNode *left = node->children[0];
    size_t i;
    size_t currentOperator = 0;
    for (i = 1; i < node->childCount; i++)
    {
        Token **newTokens = malloc(1 * sizeof(Token *));
        if (newTokens == NULL)
        {
            fprintf(stderr, "Memory allocation for newTokens failed.\n");
            free(isConstantChild);
            free(tokens);
            free(children);
            *isConstant = 0;
            return NULL;
        }

        if (isConstantChild[i - 1] && isConstantChild[i])
        {
            ASTNode *right = node->children[i];
            currentOperator++;

            int value_i = 0;
            double value_f = 0.0;
            
            int isFloat = 0;
            switch (left->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value_i = left->tokens[0]->value.number;
                break;
            case TOKEN_FLOATINGPOINT:
                value_f = left->tokens[0]->value.floatingPoint;
                isFloat = 1;
                break;
            case TOKEN_CHARACTER:
                value_i = left->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                value_i = (left->tokens[0]->value.string != NULL);
                break;
            default:
                break;
            }

            switch (right->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value_i = isFloat ? value_f || right->tokens[0]->value.number : value_i || right->tokens[0]->value.number;
                break;
            case TOKEN_FLOATINGPOINT:
                value_i = isFloat ? value_f || right->tokens[0]->value.floatingPoint : value_i || right->tokens[0]->value.floatingPoint;
                break;
            case TOKEN_CHARACTER:
                value_i = isFloat ? value_f || right->tokens[0]->value.character : value_i || right->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                value_i = isFloat ? value_f || (right->tokens[0]->value.string != NULL) : value_i || (right->tokens[0]->value.string != NULL);
                break;
            default:
                break;
            }

            newTokens[0] = createTokenNumber(NULL, left->tokens[0]->start, TOKEN_INTEGER, value_i);
            addCreatedToken(validator, newTokens[0]);
            freeASTNode(left);
            left = createASTNode(AST_LITERAL, newTokens, 1, NULL, 0);
        }
        else
        {
            children[childCount++] = left;
            tokens[tokenCount++] = node->tokens[currentOperator++];
            left = node->children[i];
        }
    }
    free(isConstantChild);

    children[childCount++] = left;
    
    if (childCount == 1)
    {
        free(tokens);
        free(children);
        return left;
    }

    ASTNode *newExpression = createASTNode(AST_LOGICAL_OR_EXPRESSION, tokens, tokenCount, children, childCount);
    freeASTNode(node);

    return newExpression;
}

static ASTNode *foldLogicalAndExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    int *isConstantChild = malloc(node->childCount * sizeof(int));
    memset(isConstantChild, 1, node->childCount * sizeof(int));
    //Iterating over the children and fold them
    int foldCount = 0;
    for (size_t i = 0; i < node->childCount; i++)
    {
        ASTNode *child = tryFold(validator, node->children[i], &(isConstantChild[i]));
        freeASTNode(node->children[i]);
        node->children[i] = child;
        if (isConstantChild[i])
        {
            foldCount++;
        }
        else
        {
            *isConstant = 0;
        }
    }
    if (foldCount == 0)
    {
        free(isConstantChild);
        return deepCopyASTNode(node);
    }

    //Allocating memory
    size_t tokensSize = node->tokenCount;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        free(isConstantChild);
        *isConstant = 0;
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = node->childCount;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(isConstantChild);
        free(tokens);
        *isConstant = 0;
        return NULL;
    }
    size_t childCount = 0;
    
    ASTNode *left = node->children[0];
    size_t i;
    size_t currentOperator = 0;
    for (i = 1; i < node->childCount; i++)
    {
        Token **newTokens = malloc(1 * sizeof(Token *));
        if (newTokens == NULL)
        {
            fprintf(stderr, "Memory allocation for newTokens failed.\n");
            free(isConstantChild);
            free(tokens);
            free(children);
            *isConstant = 0;
            return NULL;
        }

        if (isConstantChild[i - 1] && isConstantChild[i])
        {
            ASTNode *right = node->children[i];
            currentOperator++;

            int value_i = 0;
            double value_f = 0.0;

            int isFloat = 0;
            switch (left->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value_i = left->tokens[0]->value.number;
                break;
            case TOKEN_FLOATINGPOINT:
                value_f = left->tokens[0]->value.floatingPoint;
                isFloat = 1;
                break;
            case TOKEN_CHARACTER:
                value_i = left->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                value_i = (left->tokens[0]->value.string != NULL);
                break;
            default:
                break;
            }

            switch (right->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value_i = isFloat ? value_f && right->tokens[0]->value.number : value_i && right->tokens[0]->value.number;
                break;
            case TOKEN_FLOATINGPOINT:
                value_i = isFloat ? value_f && right->tokens[0]->value.floatingPoint : value_i && right->tokens[0]->value.floatingPoint;
                break;
            case TOKEN_CHARACTER:
                value_i = isFloat ? value_f && right->tokens[0]->value.character : value_i && right->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                value_i = isFloat ? value_f && (right->tokens[0]->value.string != NULL) : value_i && (right->tokens[0]->value.string != NULL);
                break;
            default:
                break;
            }

            newTokens[0] = createTokenNumber(NULL, left->tokens[0]->start, TOKEN_INTEGER, value_i);
            addCreatedToken(validator, newTokens[0]);
            freeASTNode(left);
            left = createASTNode(AST_LITERAL, newTokens, 1, NULL, 0);
        }
        else
        {
            children[childCount++] = left;
            tokens[tokenCount++] = node->tokens[currentOperator++];
            left = node->children[i];
        }
    }
    free(isConstantChild);

    children[childCount++] = left;
    
    if (childCount == 1)
    {
        free(tokens);
        free(children);
        return left;
    }

    ASTNode *newExpression = createASTNode(AST_LOGICAL_AND_EXPRESSION, tokens, tokenCount, children, childCount);
    freeASTNode(node);
    
    return newExpression;
}

static ASTNode *foldBitwiseOrExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    int *isConstantChild = malloc(node->childCount * sizeof(int));
    memset(isConstantChild, 1, node->childCount * sizeof(int));
    //Iterating over the children and fold them
    int foldCount = 0;
    for (size_t i = 0; i < node->childCount; i++)
    {
        ASTNode *child = tryFold(validator, node->children[i], &(isConstantChild[i]));
        freeASTNode(node->children[i]);
        node->children[i] = child;
        if (isConstantChild[i])
        {
            foldCount++;
        }
        else
        {
            *isConstant = 0;
        }
    }
    if (foldCount == 0)
    {
        free(isConstantChild);
        return deepCopyASTNode(node);
    }

    //Allocating memory
    size_t tokensSize = node->tokenCount;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        free(isConstantChild);
        *isConstant = 0;
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = node->childCount;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(isConstantChild);
        free(tokens);
        *isConstant = 0;
        return NULL;
    }
    size_t childCount = 0;
    
    ASTNode *left = node->children[0];
    size_t i;
    size_t currentOperator = 0;
    for (i = 1; i < node->childCount; i++)
    {
        Token **newTokens = malloc(1 * sizeof(Token *));
        if (newTokens == NULL)
        {
            fprintf(stderr, "Memory allocation for newTokens failed.\n");
            free(isConstantChild);
            free(tokens);
            free(children);
            *isConstant = 0;
            return NULL;
        }

        if (isConstantChild[i - 1] && isConstantChild[i])
        {
            ASTNode *right = node->children[i];
            currentOperator++;

            int value = 0;

            switch (left->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value = left->tokens[0]->value.number;
                break;
            case TOKEN_CHARACTER:
                value = left->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary | ('string')", left->tokens[0]));
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            case TOKEN_FLOATINGPOINT:
                addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary | ('float')", left->tokens[0]));
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            default:
                break;
            }


            switch (right->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value |= right->tokens[0]->value.number;
                break;
            case TOKEN_CHARACTER:
                value |= right->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary | ('string')", right->tokens[0]));
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            case TOKEN_FLOATINGPOINT:
                addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary | ('float')", right->tokens[0]));
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            default:
                break;
            }

            newTokens[0] = createTokenNumber(NULL, left->tokens[0]->start, TOKEN_INTEGER, value);
            addCreatedToken(validator, newTokens[0]);
            freeASTNode(left);
            left = createASTNode(AST_LITERAL, newTokens, 1, NULL, 0);
        }
        else
        {
            children[childCount++] = left;
            tokens[tokenCount++] = node->tokens[currentOperator++];
            left = node->children[i];
        }
    }
    free(isConstantChild);

    children[childCount++] = left;
    
    if (childCount == 1)
    {
        free(tokens);
        free(children);
        return left;
    }
    
    ASTNode *newExpression = createASTNode(AST_BITWISE_OR_EXPRESSION, tokens, tokenCount, children, childCount);
    freeASTNode(node);
    
    return newExpression;
}

static ASTNode *foldBitwiseXorExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    int *isConstantChild = malloc(node->childCount * sizeof(int));
    memset(isConstantChild, 1, node->childCount * sizeof(int));
    //Iterating over the children and fold them
    int foldCount = 0;
    for (size_t i = 0; i < node->childCount; i++)
    {
        ASTNode *child = tryFold(validator, node->children[i], &(isConstantChild[i]));
        freeASTNode(node->children[i]);
        node->children[i] = child;
        if (isConstantChild[i])
        {
            foldCount++;
        }
        else
        {
            *isConstant = 0;
        }
    }
    if (foldCount == 0)
    {
        free(isConstantChild);
        return deepCopyASTNode(node);
    }

    //Allocating memory
    size_t tokensSize = node->tokenCount;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        free(isConstantChild);
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = node->childCount;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(isConstantChild);
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;
    
    ASTNode *left = node->children[0];
    size_t i;
    size_t currentOperator = 0;
    for (i = 1; i < node->childCount; i++)
    {
        Token **newTokens = malloc(1 * sizeof(Token *));
        if (newTokens == NULL)
        {
            fprintf(stderr, "Memory allocation for newTokens failed.\n");
            free(isConstantChild);
            free(tokens);
            free(children);
            return NULL;
        }

        if (isConstantChild[i - 1] && isConstantChild[i])
        {
            ASTNode *right = node->children[i];
            currentOperator++;

            int value = 0;

            switch (left->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value = left->tokens[0]->value.number;
                break;
            case TOKEN_CHARACTER:
                value = left->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary ^ ('string')", left->tokens[0]));
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            case TOKEN_FLOATINGPOINT:
                addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary ^ ('float')", left->tokens[0]));
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            default:
                break;
            }

            switch (right->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value ^= right->tokens[0]->value.number;
                break;
            case TOKEN_CHARACTER:
                value ^= right->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary ^ ('string')", right->tokens[0]));
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            case TOKEN_FLOATINGPOINT:
                addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary ^ ('float')", right->tokens[0]));
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            default:
                break;
            }

            newTokens[0] = createTokenNumber(NULL, left->tokens[0]->start, TOKEN_INTEGER, value);
            addCreatedToken(validator, newTokens[0]);
            freeASTNode(left);
            left = createASTNode(AST_LITERAL, newTokens, 1, NULL, 0);
        }
        else
        {
            children[childCount++] = left;
            tokens[tokenCount++] = node->tokens[currentOperator++];
            left = node->children[i];
        }
    }
    free(isConstantChild);

    children[childCount++] = left;
    
    if (childCount == 1)
    {
        free(tokens);
        free(children);
        return left;
    }
    
    ASTNode *newExpression = createASTNode(AST_BITWISE_XOR_EXPRESSION, tokens, tokenCount, children, childCount);
    freeASTNode(node);
    
    return newExpression;
}

static ASTNode *foldBitwiseAndExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    int *isConstantChild = malloc(node->childCount * sizeof(int));
    memset(isConstantChild, 1, node->childCount * sizeof(int));
    //Iterating over the children and fold them
    int foldCount = 0;
    for (size_t i = 0; i < node->childCount; i++)
    {
        ASTNode *child = tryFold(validator, node->children[i], &(isConstantChild[i]));
        freeASTNode(node->children[i]);
        node->children[i] = child;
        if (isConstantChild[i])
        {
            foldCount++;
        }
        else
        {
            *isConstant = 0;
        }
    }
    if (foldCount == 0)
    {
        free(isConstantChild);
        return deepCopyASTNode(node);
    }

    //Allocating memory
    size_t tokensSize = node->tokenCount;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        free(isConstantChild);
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = node->childCount;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(isConstantChild);
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;
    
    ASTNode *left = node->children[0];
    size_t i;
    size_t currentOperator = 0;
    for (i = 1; i < node->childCount; i++)
    {
        Token **newTokens = malloc(1 * sizeof(Token *));
        if (newTokens == NULL)
        {
            fprintf(stderr, "Memory allocation for newTokens failed.\n");
            free(isConstantChild);
            free(tokens);
            free(children);
            return NULL;
        }

        if (isConstantChild[i - 1] && isConstantChild[i])
        {
            ASTNode *right = node->children[i];
            currentOperator++;

            int value = 0;

            switch (left->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value = left->tokens[0]->value.number;
                break;
            case TOKEN_CHARACTER:
                value = left->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary & ('string')", left->tokens[0]));
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            case TOKEN_FLOATINGPOINT:
                addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary & ('float')", left->tokens[0]));
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            default:
                break;
            }

            switch (right->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value &= right->tokens[0]->value.number;
                break;
            case TOKEN_CHARACTER:
                value &= right->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary & ('string')", right->tokens[0]));
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            case TOKEN_FLOATINGPOINT:
                addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary & ('float')", right->tokens[0]));
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            default:
                break;
            }

            newTokens[0] = createTokenNumber(NULL, left->tokens[0]->start, TOKEN_INTEGER, value);
            addCreatedToken(validator, newTokens[0]);
            freeASTNode(left);
            left = createASTNode(AST_LITERAL, newTokens, 1, NULL, 0);
        }
        else
        {
            children[childCount++] = left;
            tokens[tokenCount++] = node->tokens[currentOperator++];
            left = node->children[i];
        }
    }
    free(isConstantChild);

    children[childCount++] = left;
    
    if (childCount == 1)
    {
        free(tokens);
        free(children);
        return left;
    }
    
    ASTNode *newExpression = createASTNode(AST_BITWISE_AND_EXPRESSION, tokens, tokenCount, children, childCount);
    freeASTNode(node);
    
    return newExpression;
}

static ASTNode *foldEqualityExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    int *isConstantChild = malloc(node->childCount * sizeof(int));
    memset(isConstantChild, 1, node->childCount * sizeof(int));
    //Iterating over the children and fold them
    int foldCount = 0;
    for (size_t i = 0; i < node->childCount; i++)
    {
        ASTNode *child = tryFold(validator, node->children[i], &(isConstantChild[i]));
        freeASTNode(node->children[i]);
        node->children[i] = child;
        if (isConstantChild[i])
        {
            foldCount++;
        }
        else
        {
            *isConstant = 0;
        }
    }
    if (foldCount == 0)
    {
        free(isConstantChild);
        return deepCopyASTNode(node);
    }

    //Allocating memory
    size_t tokensSize = node->tokenCount;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        free(isConstantChild);
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = node->childCount;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(isConstantChild);
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;
    
    ASTNode *left = node->children[0];
    size_t i;
    size_t currentOperator = 0;
    for (i = 1; i < node->childCount; i++)
    {
        Token **newTokens = malloc(1 * sizeof(Token *));
        if (newTokens == NULL)
        {
            fprintf(stderr, "Memory allocation for newTokens failed.\n");
            free(isConstantChild);
            free(tokens);
            free(children);
            return NULL;
        }

        if (isConstantChild[i - 1] && isConstantChild[i])
        {
            ASTNode *right = node->children[i];
            currentOperator++;

            int value_i = 0;
            double value_f = 0.0;
            
            int isFloat = 0;
            switch (left->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value_i = left->tokens[0]->value.number;
                break;
            case TOKEN_FLOATINGPOINT:
                value_f = left->tokens[0]->value.floatingPoint;
                isFloat = 1;
                break;
            case TOKEN_CHARACTER:
                value_i = left->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                value_i = (left->tokens[0]->value.string != NULL);
                break;
            default:
                break;
            }

            switch (right->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                if (node->tokens[currentOperator - 1]->type == TOKEN_DOUBLE_EQUALS)
                {
                    value_i = isFloat ? value_f == right->tokens[0]->value.number : value_i == right->tokens[0]->value.number;
                }
                else
                {
                    value_i = isFloat ? value_f != right->tokens[0]->value.number : value_i != right->tokens[0]->value.number;
                }
                break;
            case TOKEN_FLOATINGPOINT:
                if (node->tokens[currentOperator - 1]->type == TOKEN_DOUBLE_EQUALS)
                {
                    value_i = isFloat ? value_f == right->tokens[0]->value.floatingPoint : value_i == right->tokens[0]->value.floatingPoint;
                }
                else
                {
                    value_i = isFloat ? value_f != right->tokens[0]->value.floatingPoint : value_i != right->tokens[0]->value.floatingPoint;
                }
                break;
            case TOKEN_CHARACTER:
                if (node->tokens[currentOperator - 1]->type == TOKEN_DOUBLE_EQUALS)
                {
                    value_i = isFloat ? value_f == right->tokens[0]->value.character : value_i == right->tokens[0]->value.character;
                }
                else
                {
                    value_i = isFloat ? value_f != right->tokens[0]->value.character : value_i != right->tokens[0]->value.character;
                }
                break;
            case TOKEN_STRING:
                if (node->tokens[currentOperator - 1]->type == TOKEN_DOUBLE_EQUALS)
                {
                    value_i = isFloat ? value_f == (right->tokens[0]->value.string != NULL) : value_i == (right->tokens[0]->value.string != NULL);
                }
                else
                {
                    value_i = isFloat ? value_f != (right->tokens[0]->value.string != NULL) : value_i != (right->tokens[0]->value.string != NULL);
                }
                break;
            default:
                break;
            }

            newTokens[0] = createTokenNumber(NULL, left->tokens[0]->start, TOKEN_INTEGER, value_i);
            addCreatedToken(validator, newTokens[0]);
            freeASTNode(left);
            left = createASTNode(AST_LITERAL, newTokens, 1, NULL, 0);
        }
        else
        {
            break;
        }
    }
    free(isConstantChild);

    children[childCount++] = left;
    for (; i < node->childCount; i++)
    {
        tokens[tokenCount++] = node->tokens[currentOperator++];
        children[childCount++] = node->children[i];
    }
    
    if (childCount == 1)
    {
        free(tokens);
        free(children);
        return left;
    }
    
    ASTNode *newExpression = createASTNode(AST_EQUALITY_EXPRESSION, tokens, tokenCount, children, childCount);
    freeASTNode(node);
    
    return newExpression;
}

static ASTNode *foldRelationalExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    int *isConstantChild = malloc(node->childCount * sizeof(int));
    memset(isConstantChild, 1, node->childCount * sizeof(int));
    //Iterating over the children and fold them
    int foldCount = 0;
    for (size_t i = 0; i < node->childCount; i++)
    {
        ASTNode *child = tryFold(validator, node->children[i], &(isConstantChild[i]));
        freeASTNode(node->children[i]);
        node->children[i] = child;
        if (isConstantChild[i])
        {
            foldCount++;
        }
        else
        {
            *isConstant = 0;
        }
    }
    if (foldCount == 0)
    {
        free(isConstantChild);
        return deepCopyASTNode(node);
    }

    //Allocating memory
    size_t tokensSize = node->tokenCount;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        free(isConstantChild);
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = node->childCount;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(isConstantChild);
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;
    
    ASTNode *left = node->children[0];
    size_t i;
    size_t currentOperator = 0;
    for (i = 1; i < node->childCount; i++)
    {
        Token **newTokens = malloc(1 * sizeof(Token *));
        if (newTokens == NULL)
        {
            fprintf(stderr, "Memory allocation for newTokens failed.\n");
            free(isConstantChild);
            free(tokens);
            free(children);
            return NULL;
        }

        if (isConstantChild[i - 1] && isConstantChild[i])
        {
            ASTNode *right = node->children[i];
            currentOperator++;

            int value_i = 0;
            double value_f = 0.0;

            int isFloat = 0;
            switch (left->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value_i = left->tokens[0]->value.number;
                break;
            case TOKEN_FLOATINGPOINT:
                value_f = left->tokens[0]->value.floatingPoint;
                isFloat = 1;
                break;
            case TOKEN_CHARACTER:
                value_i = left->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                value_i = (left->tokens[0]->value.string != NULL);
                break;
            default:
                break;
            }

            switch (right->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                if (node->tokens[currentOperator - 1]->type == TOKEN_LESS_THAN)
                {
                    value_i = isFloat ? value_f < right->tokens[0]->value.number : value_i < right->tokens[0]->value.number;
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_LESS_THAN_OR_EQUALS)
                {
                    value_i = isFloat ? value_f <= right->tokens[0]->value.number : value_i <= right->tokens[0]->value.number;
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_GREATER_THAN)
                {
                    value_i = isFloat ? value_f > right->tokens[0]->value.number : value_i > right->tokens[0]->value.number;
                }
                else
                {
                    value_i = isFloat ? value_f >= right->tokens[0]->value.number : value_i >= right->tokens[0]->value.number;
                }
                break;
            case TOKEN_FLOATINGPOINT:
                if (node->tokens[currentOperator - 1]->type == TOKEN_LESS_THAN)
                {
                    value_i = isFloat ? value_f < right->tokens[0]->value.floatingPoint : value_i < right->tokens[0]->value.floatingPoint;
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_LESS_THAN_OR_EQUALS)
                {
                    value_i = isFloat ? value_f <= right->tokens[0]->value.floatingPoint : value_i <= right->tokens[0]->value.floatingPoint;
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_GREATER_THAN)
                {
                    value_i = isFloat ? value_f > right->tokens[0]->value.floatingPoint : value_i > right->tokens[0]->value.floatingPoint;
                }
                else
                {
                    value_i = isFloat ? value_f >= right->tokens[0]->value.floatingPoint : value_i >= right->tokens[0]->value.floatingPoint;
                }
                break;
            case TOKEN_CHARACTER:
                if (node->tokens[currentOperator - 1]->type == TOKEN_LESS_THAN)
                {
                    value_i = isFloat ? value_f < right->tokens[0]->value.character : value_i < right->tokens[0]->value.character;
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_LESS_THAN_OR_EQUALS)
                {
                    value_i = isFloat ? value_f <= right->tokens[0]->value.character : value_i <= right->tokens[0]->value.character;
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_GREATER_THAN)
                {
                    value_i = isFloat ? value_f > right->tokens[0]->value.character : value_i > right->tokens[0]->value.character;
                }
                else
                {
                    value_i = isFloat ? value_f >= right->tokens[0]->value.character : value_i >= right->tokens[0]->value.character;
                }
                break;
            case TOKEN_STRING:
                if (node->tokens[currentOperator - 1]->type == TOKEN_LESS_THAN)
                {
                    value_i = isFloat ? value_f < (right->tokens[0]->value.string != NULL) : value_i < (right->tokens[0]->value.string != NULL);
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_LESS_THAN_OR_EQUALS)
                {
                    value_i = isFloat ? value_f <= (right->tokens[0]->value.string != NULL) : value_i <= (right->tokens[0]->value.string != NULL);
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_GREATER_THAN)
                {
                    value_i = isFloat ? value_f > (right->tokens[0]->value.string != NULL) : value_i > (right->tokens[0]->value.string != NULL);
                }
                else
                {
                    value_i = isFloat ? value_f >= (right->tokens[0]->value.string != NULL) : value_i >= (right->tokens[0]->value.string != NULL);
                }
                break;
            default:
                break;
            }

            newTokens[0] = createTokenNumber(NULL, left->tokens[0]->start, TOKEN_INTEGER, value_i);
            addCreatedToken(validator, newTokens[0]);
            freeASTNode(left);
            left = createASTNode(AST_LITERAL, newTokens, 1, NULL, 0);
        }
        else
        {
            break;
        }
    }
    free(isConstantChild);

    children[childCount++] = left;
    for (; i < node->childCount; i++)
    {
        tokens[tokenCount++] = node->tokens[currentOperator++];
        children[childCount++] = node->children[i];
    }
    
    if (childCount == 1)
    {
        free(tokens);
        free(children);
        return left;
    }
    
    ASTNode *newExpression = createASTNode(AST_RELATIONAL_EXPRESSION, tokens, tokenCount, children, childCount);
    freeASTNode(node);
    
    return newExpression;
}

static ASTNode *foldShiftExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    int *isConstantChild = malloc(node->childCount * sizeof(int));
    memset(isConstantChild, 1, node->childCount * sizeof(int));
    //Iterating over the children and fold them
    int foldCount = 0;
    for (size_t i = 0; i < node->childCount; i++)
    {
        ASTNode *child = tryFold(validator, node->children[i], &(isConstantChild[i]));
        freeASTNode(node->children[i]);
        node->children[i] = child;
        if (isConstantChild[i])
        {
            foldCount++;
        }
        else
        {
            *isConstant = 0;
        }
    }
    if (foldCount == 0)
    {
        free(isConstantChild);
        return deepCopyASTNode(node);
    }

    //Allocating memory
    size_t tokensSize = node->tokenCount;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        free(isConstantChild);
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = node->childCount;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(isConstantChild);
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;
    
    ASTNode *left = node->children[0];
    size_t i;
    size_t currentOperator = 0;
    for (i = 1; i < node->childCount; i++)
    {
        Token **newTokens = malloc(1 * sizeof(Token *));
        if (newTokens == NULL)
        {
            fprintf(stderr, "Memory allocation for newTokens failed.\n");
            free(isConstantChild);
            free(tokens);
            free(children);
            return NULL;
        }

        if (isConstantChild[i - 1] && isConstantChild[i])
        {
            ASTNode *right = node->children[i];
            currentOperator++;
            
            int value = 0;

            switch (left->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value = left->tokens[0]->value.number;
                break;
            case TOKEN_CHARACTER:
                value = left->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                if (node->tokens[currentOperator - 1]->type == TOKEN_BITWISE_LEFT_SHIFT)
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary << ('string')", left->tokens[0]));
                }
                else
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary >> ('string')", left->tokens[0]));
                }
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            case TOKEN_FLOATINGPOINT:
                if (node->tokens[currentOperator - 1]->type == TOKEN_BITWISE_LEFT_SHIFT)
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary << ('float')", left->tokens[0]));
                }
                else
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary >> ('float')", left->tokens[0]));
                }
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            default:
                break;
            }

            switch (right->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                if (node->tokens[currentOperator - 1]->type == TOKEN_BITWISE_LEFT_SHIFT)
                {
                    value <<= right->tokens[0]->value.number;
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_BITWISE_RIGHT_SHIFT)
                {
                    value >>= right->tokens[0]->value.number;
                }
                break;
            case TOKEN_CHARACTER:
                if (node->tokens[currentOperator - 1]->type == TOKEN_BITWISE_LEFT_SHIFT)
                {
                    value <<= right->tokens[0]->value.character;
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_BITWISE_RIGHT_SHIFT)
                {
                    value >>= right->tokens[0]->value.character;
                }
                break;
            case TOKEN_STRING:
                if (node->tokens[currentOperator - 1]->type == TOKEN_BITWISE_LEFT_SHIFT)
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary << ('string')", right->tokens[0]));
                }
                else
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary >> ('string')", right->tokens[0]));
                }
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            case TOKEN_FLOATINGPOINT:
                if (node->tokens[currentOperator - 1]->type == TOKEN_BITWISE_LEFT_SHIFT)
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary << ('float')", right->tokens[0]));
                }
                else
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary >> ('float')", right->tokens[0]));
                }
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            default:
                break;
            }

            newTokens[0] = createTokenNumber(NULL, left->tokens[0]->start, TOKEN_INTEGER, value);
            addCreatedToken(validator, newTokens[0]);
            freeASTNode(left);
            left = createASTNode(AST_LITERAL, newTokens, 1, NULL, 0);
        }
        else
        {
            break;
        }
    }
    free(isConstantChild);

    children[childCount++] = left;
    for (; i < node->childCount; i++)
    {
        tokens[tokenCount++] = node->tokens[currentOperator++];
        children[childCount++] = node->children[i];
    }
    
    if (childCount == 1)
    {
        free(tokens);
        free(children);
        return left;
    }
    
    ASTNode *newExpression = createASTNode(AST_SHIFT_EXPRESSION, tokens, tokenCount, children, childCount);
    freeASTNode(node);
    
    return newExpression;
}

static ASTNode *foldAdditiveExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    int *isConstantChild = malloc(node->childCount * sizeof(int));
    memset(isConstantChild, 1, node->childCount * sizeof(int));
    //Iterating over the children and fold them
    int foldCount = 0;
    for (size_t i = 0; i < node->childCount; i++)
    {
        ASTNode *child = tryFold(validator, node->children[i], &(isConstantChild[i]));
        freeASTNode(node->children[i]);
        node->children[i] = child;
        if (isConstantChild[i])
        {
            foldCount++;
        }
        else
        {
            *isConstant = 0;
        }
    }
    if (foldCount == 0)
    {
        free(isConstantChild);
        return deepCopyASTNode(node);
    }

    //Allocating memory
    size_t tokensSize = node->tokenCount;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        free(isConstantChild);
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = node->childCount;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(isConstantChild);
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;
    
    ASTNode *left = node->children[0];
    size_t i;
    size_t currentOperator = 0;
    for (i = 1; i < node->childCount; i++)
    {
        Token **newTokens = malloc(1 * sizeof(Token *));
        if (newTokens == NULL)
        {
            fprintf(stderr, "Memory allocation for newTokens failed.\n");
            free(isConstantChild);
            free(tokens);
            free(children);
            return NULL;
        }

        if (isConstantChild[i - 1] && isConstantChild[i])
        {
            ASTNode *right = node->children[i];
            currentOperator++;

            int value_i = 0;
            double value_f = 0.0;

            int isFloat = 0;
            switch (left->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value_i = left->tokens[0]->value.number;
                break;
            case TOKEN_FLOATINGPOINT:
                value_f = left->tokens[0]->value.floatingPoint;
                isFloat = 1;
                break;
            case TOKEN_CHARACTER:
                value_i = left->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                value_i = (left->tokens[0]->value.string != NULL);
                break;
            default:
                break;
            }

            switch (right->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                if (node->tokens[currentOperator - 1]->type == TOKEN_PLUS)
                {
                    if (isFloat)
                    {
                        value_f += right->tokens[0]->value.number;
                    }
                    else
                    {
                        value_i += right->tokens[0]->value.number;
                    }
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_MINUS)
                {
                    if (isFloat)
                    {
                        value_f -= right->tokens[0]->value.number;
                    }
                    else
                    {
                        value_i -= right->tokens[0]->value.number;
                    }
                }
                break;
            case TOKEN_FLOATINGPOINT:
                if (node->tokens[currentOperator - 1]->type == TOKEN_PLUS)
                {
                    if (isFloat)
                    {
                        value_f += right->tokens[0]->value.floatingPoint;
                    }
                    else
                    {
                        value_f = value_i + right->tokens[0]->value.floatingPoint;
                        isFloat = 1;
                    }
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_MINUS)
                {
                    if (isFloat)
                    {
                        value_f -= right->tokens[0]->value.floatingPoint;
                    }
                    else
                    {
                        value_f = value_i - right->tokens[0]->value.floatingPoint;
                        isFloat = 1;
                    }
                }
                break;
            case TOKEN_CHARACTER:
                if (node->tokens[currentOperator - 1]->type == TOKEN_PLUS)
                {
                    if (isFloat)
                    {
                        value_f += right->tokens[0]->value.character;
                    }
                    else
                    {
                        value_i += right->tokens[0]->value.character;
                    }
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_MINUS)
                {
                    if (isFloat)
                    {
                        value_f -= right->tokens[0]->value.character;
                    }
                    else
                    {
                        value_i -= right->tokens[0]->value.character;
                    }
                }
                break;
            case TOKEN_STRING:
                if (node->tokens[currentOperator - 1]->type == TOKEN_PLUS)
                {
                    value_i += (right->tokens[0]->value.string != NULL);
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_MINUS)
                {
                    value_i -= (right->tokens[0]->value.string != NULL);
                }
                break;
            default:
                break;
            }

            if (isFloat)
            {
                newTokens[0] = createTokenFloat(NULL, left->tokens[0]->start, TOKEN_FLOATINGPOINT, value_f);
            }
            else
            {
                newTokens[0] = createTokenNumber(NULL, left->tokens[0]->start, TOKEN_INTEGER, value_i);
            }
            addCreatedToken(validator, newTokens[0]);
            freeASTNode(left);
            left = createASTNode(AST_LITERAL, newTokens, 1, NULL, 0);
        }
        else
        {
            children[childCount++] = left;
            tokens[tokenCount++] = node->tokens[currentOperator++];
            left = node->children[i];
        }
    }
    free(isConstantChild);

    children[childCount++] = left;
    
    if (childCount == 1)
    {
        free(tokens);
        free(children);
        return left;
    }
    
    ASTNode *newExpression = createASTNode(AST_ADDITIVE_EXPRESSION, tokens, tokenCount, children, childCount);
    freeASTNode(node);
    
    return newExpression;
}

static ASTNode *foldMultiplicativeExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    int *isConstantChild = malloc(node->childCount * sizeof(int));
    memset(isConstantChild, 1, node->childCount * sizeof(int));
    //Iterating over the children and fold them
    int foldCount = 0;
    for (size_t i = 0; i < node->childCount; i++)
    {
        ASTNode *child = tryFold(validator, node->children[i], &(isConstantChild[i]));
        freeASTNode(node->children[i]);
        node->children[i] = child;
        if (isConstantChild[i])
        {
            foldCount++;
        }
        else
        {
            *isConstant = 0;
        }
    }
    if (foldCount == 0)
    {
        free(isConstantChild);
        return deepCopyASTNode(node);
    }

    //Allocating memory
    size_t tokensSize = node->tokenCount;
    Token **tokens = malloc(tokensSize * sizeof(Token *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for tokens failed.\n");
        free(isConstantChild);
        return NULL;
    }
    size_t tokenCount = 0;
    size_t childrenSize = node->childCount;
    ASTNode **children = malloc(childrenSize * sizeof(ASTNode *));
    if (children == NULL)
    {
        fprintf(stderr, "Memory allocation for children failed.\n");
        free(isConstantChild);
        free(tokens);
        return NULL;
    }
    size_t childCount = 0;
    
    ASTNode *left = node->children[0];
    size_t i;
    size_t currentOperator = 0;
    for (i = 1; i < node->childCount; i++)
    {
        Token **newTokens = malloc(1 * sizeof(Token *));
        if (newTokens == NULL)
        {
            fprintf(stderr, "Memory allocation for newTokens failed.\n");
            free(isConstantChild);
            free(tokens);
            free(children);
            return NULL;
        }

        if (isConstantChild[i - 1] && isConstantChild[i])
        {
            ASTNode *right = node->children[i];
            currentOperator++;

            int value_i = 0;
            double value_f = 0.0;

            int isFloat = 0;
            switch (left->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                value_i = left->tokens[0]->value.number;
                break;
            case TOKEN_FLOATINGPOINT:
                value_f = left->tokens[0]->value.floatingPoint;
                isFloat = 1;
                break;
            case TOKEN_CHARACTER:
                value_i = left->tokens[0]->value.character;
                break;
            case TOKEN_STRING:
                if (node->tokens[currentOperator - 1]->type == TOKEN_STAR)
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary * ('string')", left->tokens[0]));
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_SLASH)
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary / ('string')", left->tokens[0]));
                }
                else
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary % ('string')", left->tokens[0]));
                }
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            default:
                break;
            }

            switch (right->tokens[0]->type)
            {
            case TOKEN_INTEGER:
            case TOKEN_HEXADECIMAL:
            case TOKEN_OCTAL:
                if (node->tokens[currentOperator - 1]->type == TOKEN_STAR)
                {
                    if (isFloat)
                    {
                        value_f *= right->tokens[0]->value.number;
                    }
                    else
                    {
                        value_i *= right->tokens[0]->value.number;
                    }
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_SLASH)
                {
                    if (right->tokens[0]->value.number == 0)
                    {
                        addError(validator, createError(ERROR_VALIDATION, "Division by zero.", right->tokens[0]));
                        free(isConstantChild);
                        free(tokens);
                        free(children);
                        *isConstant = 0;
                        return NULL;
                    }

                    if (isFloat)
                    {
                        value_f /= right->tokens[0]->value.number;
                    }
                    else
                    {
                        value_i /= right->tokens[0]->value.number;
                    }
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_PERCENT)
                {
                    if (right->tokens[0]->value.number == 0)
                    {
                        addError(validator, createError(ERROR_VALIDATION, "Division by zero.", right->tokens[0]));
                        free(isConstantChild);
                        free(tokens);
                        free(children);
                        *isConstant = 0;
                        return NULL;
                    }

                    if (isFloat)
                    {
                        addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary % ('float')", left->tokens[0]));
                        free(isConstantChild);
                        free(tokens);
                        free(children);
                        *isConstant = 0;
                        return NULL;
                    }

                    value_i %= right->tokens[0]->value.number;
                }
                break;
            case TOKEN_FLOATINGPOINT:
                if (node->tokens[currentOperator - 1]->type == TOKEN_STAR)
                {
                    if (isFloat)
                    {
                        value_f *= right->tokens[0]->value.floatingPoint;
                    }
                    else
                    {
                        value_f = value_i * right->tokens[0]->value.floatingPoint;
                        isFloat = 1;
                    }
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_SLASH)
                {
                    if (right->tokens[0]->value.number == 0)
                    {
                        addError(validator, createError(ERROR_VALIDATION, "Division by zero.", right->tokens[0]));
                        free(isConstantChild);
                        free(tokens);
                        free(children);
                        *isConstant = 0;
                        return NULL;
                    }

                    if (isFloat)
                    {
                        value_f /= right->tokens[0]->value.floatingPoint;
                    }
                    else
                    {
                        value_f = value_i / right->tokens[0]->value.floatingPoint;
                        isFloat = 1;
                    }
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_PERCENT)
                {
                    if (isFloat)
                    {
                        addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary % ('float')", left->tokens[0]));    
                    }
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary % ('float')", right->tokens[0]));
                    free(isConstantChild);
                    free(tokens);
                    free(children);
                    *isConstant = 0;
                    return NULL;
                }
                break;
            case TOKEN_CHARACTER:
                if (node->tokens[currentOperator - 1]->type == TOKEN_STAR)
                {
                    if (isFloat)
                    {
                        value_f *= right->tokens[0]->value.character;
                    }
                    else
                    {
                        value_i *= right->tokens[0]->value.character;
                    }
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_SLASH)
                {
                    if (right->tokens[0]->value.character == 0)
                    {
                        addError(validator, createError(ERROR_VALIDATION, "Division by zero.", right->tokens[0]));
                        free(isConstantChild);
                        free(tokens);
                        free(children);
                        *isConstant = 0;
                        return NULL;
                    }

                    if (isFloat)
                    {
                        value_f /= right->tokens[0]->value.character;
                    }
                    else
                    {
                        value_i /= right->tokens[0]->value.character;
                    }
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_PERCENT)
                {
                    if (right->tokens[0]->value.character == 0)
                    {
                        addError(validator, createError(ERROR_VALIDATION, "Division by zero.", right->tokens[0]));
                        free(isConstantChild);
                        free(tokens);
                        free(children);
                        *isConstant = 0;
                        return NULL;
                    }

                    if (isFloat)
                    {
                        addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary % ('float')", left->tokens[0]));
                        free(isConstantChild);
                        free(tokens);
                        free(children);
                        *isConstant = 0;
                        return NULL;
                    }

                    value_i %= right->tokens[0]->value.character;
                }
                break;
            case TOKEN_STRING:
                if (node->tokens[currentOperator - 1]->type == TOKEN_STAR)
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary * ('string')", right->tokens[0]));
                }
                else if (node->tokens[currentOperator - 1]->type == TOKEN_SLASH)
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary / ('string')", right->tokens[0]));
                }
                else
                {
                    if (isFloat)
                    {
                        addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary % ('float')", left->tokens[0]));
                    }
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to binary % ('string')", right->tokens[0]));
                }
                free(isConstantChild);
                free(tokens);
                free(children);
                *isConstant = 0;
                return NULL;
            default:
                break;
            }

            if (isFloat)
            {
                newTokens[0] = createTokenFloat(NULL, left->tokens[0]->start, TOKEN_FLOATINGPOINT, value_f);
            }
            else
            {
                newTokens[0] = createTokenNumber(NULL, left->tokens[0]->start, TOKEN_INTEGER, value_i);
            }
            addCreatedToken(validator, newTokens[0]);
            freeASTNode(left);
            left = createASTNode(AST_LITERAL, newTokens, 1, NULL, 0);
        }
        else
        {
            break;
        }
    }
    free(isConstantChild);

    children[childCount++] = left;
    for (; i < node->childCount; i++)
    {
        tokens[tokenCount++] = node->tokens[currentOperator++];
        children[childCount++] = node->children[i];
    }
    
    if (childCount == 1)
    {
        free(tokens);
        free(children);
        return left;
    }
    
    ASTNode *newExpression = createASTNode(AST_MULTIPLICATIVE_EXPRESSION, tokens, tokenCount, children, childCount);
    freeASTNode(node);
    
    return newExpression;
}

static ASTNode *foldCastExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    return deepCopyASTNode(node);
}

static ASTNode *foldUnaryExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (node->tokenCount > 0 && node->tokens[0]->type == TOKEN_KEYWORD)
    {
        int result = 0;
        if (node->tokenCount ==  1)
        {
            int isConstantChild = 1;
            ASTNode *size = tryFold(validator, node->children[0], &isConstantChild);
            freeASTNode(node->children[0]);
            node->children[0] = size;
            if (isConstantChild)
            {
                if (size->tokens[0]->type == TOKEN_INTEGER ||
                    size->tokens[0]->type == TOKEN_OCTAL ||
                    size->tokens[0]->type == TOKEN_HEXADECIMAL)
                {
                    result = sizeof(int);
                }
                else if (size->tokens[0]->type == TOKEN_FLOATINGPOINT)
                {
                    result = sizeof(double);
                }
                else if (size->tokens[0]->type == TOKEN_CHARACTER)
                {
                    result = sizeof(char);
                }
                else if (size->tokens[0]->type == TOKEN_STRING)
                {
                    result = sizeof(char *);
                }

                Token **newTokens = malloc(1 * sizeof(Token *));
                if (newTokens == NULL)
                {
                    fprintf(stderr, "Memory allocation for newTokens failed.\n");
                    return NULL;
                }
                newTokens[0] = createTokenNumber(NULL, size->tokens[0]->start, TOKEN_INTEGER, result);
                addCreatedToken(validator, newTokens[0]);
                freeASTNode(size);
                return createASTNode(AST_LITERAL, newTokens, 1, NULL, 0);
            }
            else
            {
                *isConstant = 0;
                return deepCopyASTNode(node);
            }
        }
        else
        {
            Symbol *typeSymobol = findTypeSymbol(validator, node->children[0]);
            result = getSymbolSize(typeSymobol);
            Token **newTokens = malloc(1 * sizeof(Token *));
            if (newTokens == NULL)
            {
                fprintf(stderr, "Memory allocation for newTokens failed.\n");
                return NULL;
            }
            newTokens[0] = createTokenNumber(NULL, node->children[0]->tokens[0]->start, TOKEN_INTEGER, result);
            addCreatedToken(validator, newTokens[0]);
            freeASTNode(node->children[0]);
            return createASTNode(AST_LITERAL, newTokens, 1, NULL, 0);
        }
    }
    else if (node->tokenCount == 1)
    {
        int isConstantChild = 1;
        ASTNode *expression = tryFold(validator, node->children[0], &isConstantChild);
        freeASTNode(node->children[0]);
        node->children[0] = expression;

        if (node->tokens[0]->type == TOKEN_BITWISE_AND ||
            node->tokens[0]->type == TOKEN_STAR ||
            node->tokens[0]->type == TOKEN_DOUBLE_PLUS ||
            node->tokens[0]->type == TOKEN_DOUBLE_MINUS)
        {
            if (isConstantChild)
            {
                addError(validator, createError(ERROR_VALIDATION, "Invalid operand to unary operator", node->tokens[0]));
            }
            *isConstant = 0;
            return deepCopyASTNode(node);
        }


        if (isConstantChild)
        {
            int value_i = 0;
            double value_f = 0.0;

            int isFloat = 0;
            if (expression->tokens[0]->type == TOKEN_INTEGER || expression->tokens[0]->type == TOKEN_OCTAL || expression->tokens[0]->type == TOKEN_HEXADECIMAL)
            {
                if (node->tokens[0]->type == TOKEN_PLUS)
                {
                    value_i = expression->tokens[0]->value.number;
                }
                else if (node->tokens[0]->type == TOKEN_MINUS)
                {
                    value_i = -expression->tokens[0]->value.number;
                }
                else if (node->tokens[0]->type == TOKEN_BITWISE_NOT)
                {
                    value_i = ~expression->tokens[0]->value.number;
                }
                else if (node->tokens[0]->type == TOKEN_NOT)
                {
                    value_i = !expression->tokens[0]->value.number;
                }
            }
            else if (expression->tokens[0]->type == TOKEN_FLOATINGPOINT)
            {
                isFloat = 1;
                if (node->tokens[0]->type == TOKEN_PLUS)
                {
                    value_f = expression->tokens[0]->value.floatingPoint;
                }
                else if (node->tokens[0]->type == TOKEN_MINUS)
                {
                    value_f = -expression->tokens[0]->value.floatingPoint;
                }
                else if (node->tokens[0]->type == TOKEN_BITWISE_NOT)
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to unary ~ ('float')", expression->tokens[0]));
                    *isConstant = 0;
                    return NULL;
                } 
                else if (node->tokens[0]->type == TOKEN_NOT)
                {
                    value_f = !expression->tokens[0]->value.floatingPoint;
                }
            }
            else if (expression->tokens[0]->type == TOKEN_CHARACTER)
            {
                if (node->tokens[0]->type == TOKEN_PLUS)
                {
                    value_i = expression->tokens[0]->value.character;
                }
                else if (node->tokens[0]->type == TOKEN_MINUS)
                {
                    value_i = -expression->tokens[0]->value.character;
                }
                else if (node->tokens[0]->type == TOKEN_BITWISE_NOT)
                {
                    value_i = ~expression->tokens[0]->value.character;
                }
                else if (node->tokens[0]->type == TOKEN_NOT)
                {
                    value_i = !expression->tokens[0]->value.character;
                }
            }
            else if (expression->tokens[0]->type == TOKEN_STRING)
            {
                if (node->tokens[0]->type == TOKEN_PLUS)
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to unary + ('string')", expression->tokens[0]));
                    *isConstant = 0;
                    return NULL;
                }
                else if (node->tokens[0]->type == TOKEN_MINUS)
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to unary - ('string')", expression->tokens[0]));
                    *isConstant = 0;
                    return NULL;
                }
                else if (node->tokens[0]->type == TOKEN_BITWISE_NOT)
                {
                    addError(validator, createError(ERROR_VALIDATION, "Invalid operand to unary ~ ('string')", expression->tokens[0]));
                    *isConstant = 0;
                    return NULL;
                }
                else if (node->tokens[0]->type == TOKEN_NOT)
                {
                    value_i = !(expression->tokens[0]->value.string != NULL);
                }
            }

            Token **newTokens = malloc(1 * sizeof(Token *));
            if (newTokens == NULL)
            {
                fprintf(stderr, "Memory allocation for newTokens failed.\n");
                return NULL;
            }
            if (isFloat)
            {
                newTokens[0] = createTokenFloat(NULL, expression->tokens[0]->start, TOKEN_FLOATINGPOINT, value_f);
            }
            else 
            {
                newTokens[0] = createTokenNumber(NULL, expression->tokens[0]->start, TOKEN_INTEGER, value_i);
            }
            addCreatedToken(validator, newTokens[0]);
            freeASTNode(expression);
            return createASTNode(AST_LITERAL, newTokens, 1, NULL, 0);
        }
        else
        {
            *isConstant = 0;
        }
    }

    return deepCopyASTNode(node);
}

static ASTNode *foldPrimaryExpression(Validator *validator, ASTNode *node, int *isConstant)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (node->tokenCount == 1 && node->tokens[0]->type == TOKEN_IDENTIFIER)
    {
        *isConstant = 0;
        return deepCopyASTNode(node);
    }
    else 
    {
        int isConstantChild = 1;
        ASTNode *expression = tryFold(validator, node->children[0], &isConstantChild);
        freeASTNode(node->children[0]);
        freeASTNode(node);
        if (!isConstantChild)
        {
            *isConstant = 0;
        }
        return expression;
    }
}

static Symbol *findTypeSymbol(Validator *validator, ASTNode *node)
{
    if (validator == NULL)
    {
        fprintf(stderr, "Validator is not initialized.\n");
        return NULL;
    }

    if (node == NULL)
    {
        fprintf(stderr, "ASTNode is NULL.\n");
        return NULL;
    }

    return NULL;
}

static int getSymbolSize(Symbol *symbol)
{
    if (symbol == NULL)
    {
        return 0;
    }

    switch (symbol->type)
    {
    case SYMBOL_VARIABLE:
        return symbol->data.variableSymbol->size;
        break;
    case SYMBOL_STRUCT:
        return symbol->data.structureSymbol->size;
    case SYMBOL_UNION:
        return symbol->data.unionSymbol->size;
        break;
    case SYMBOL_ENUM:
        return symbol->data.enumerationSymbol->size;
        break;
    case SYMBOL_TYPEDEF:
        return getSymbolSize(symbol->data.typedefSymbol->type);
        break;
    default:
        return 0;
    }
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

    validator->createdTokensSize = 5;
    validator->createdTokens = malloc(validator->createdTokensSize * sizeof(Token *));
    if (validator->createdTokens == NULL)
    {
        fprintf(stderr, "Memory allocation for Validator->createdTokens failed!\n");
        deleteHashTable(validator->globalScope);
        deleteStack(validator->scopes);
        deleteErrors(validator->errors, validator->errorCount);
        free(validator);
        return NULL;
    }
    validator->createdTokenCount = 0;

    return validator;
}

void deleteValidator(Validator *validator)
{
    deleteHashTable(validator->globalScope);
    deleteStack(validator->scopes);
    free(validator->ASTroot);

    deleteErrors(validator->errors, validator->errorCount);
    free(validator->errors);

    //TODO:
    //Created tokens will leak memory but we can't free them here because they are used in the AST
    /*
    for (size_t i = 0; i < validator->createdTokenCount; i++)
    {
        deleteTokens(validator->createdTokens, validator->createdTokenCount);
    }
    */

    free(validator);
}

int validate(Validator *validator, int optimize)
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

    if (!constantFold(validator, optimize))
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

    return deepCopyASTNode(validator->ASTroot);
}