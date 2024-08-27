#include "AST.h"

/*****************************************************************************************************
                            PRIVATE AST FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

/*****************************************************************************************************
                                PRIVATE AST FUNCTIONS START HERE
 *****************************************************************************************************/

/**
 * Lookup table for ASTType
 */
static const char *const ASTTypes[] = {
    [AST_PROGRAM] = "PROGRAM",
    [AST_GLOBAL_VARIABLE_DECLARATION] = "GLOBAL_VARIABLE_DECLARATION",
    [AST_FUNCTION_DECLARATION] = "FUNCTION_DECLARATION",
    [AST_FUNCTION_DEFINITION] = "FUNCTION_DEFINITION",
    [AST_ENUM] = "ENUM",
    [AST_STRUCT] = "STRUCT",
    [AST_UNION] = "UNION",
    [AST_PARAMETER_LIST] = "PARAMETER_LIST",
    [AST_ENUM_LIST] = "ENUM_LIST",
    [AST_MEMBER_LIST] = "MEMBER_LIST",
    [AST_LABELED_STATEMENT] = "LABELED_STATEMENT",
    [AST_EXPRESSION_STATEMENT] = "EXPRESSION_STATEMENT",
    [AST_RETURN_STATEMENT] = "RETURN_STATEMENT",
    [AST_BREAK_STATEMENT] = "BREAK_STATEMENT",
    [AST_CONTINUE_STATEMENT] = "CONTINUE_STATEMENT",
    [AST_GOTO_STATEMENT] = "GOTO_STATEMENT",
    [AST_COMPOUND_STATEMENT] = "COMPOUND_STATEMENT",
    [AST_LOCAL_VARIABLE_DECLARATION] = "LOCAL_VARIABLE_DECLARATION",
    [AST_FOR_ITERATION_STATEMENT] = "FOR_ITERATION_STATEMENT",
    [AST_WHILE_ITERATION_STATEMENT] = "WHILE_ITERATION_STATEMENT",
    [AST_DO_ITERATION_STATEMENT] = "DO_ITERATION_STATEMENT",
    [AST_IF_STATEMENT] = "IF_STATEMENT",
    [AST_SWITCH_STATEMENT] = "SWITCH_STATEMENT",
    [AST_SWITCH_BODY] = "SWITCH_BODY",
    [AST_LITERAL] = "LITERAL",
    [AST_BINARY_EXPRESSION] = "BINARY_EXPRESSION",
    [AST_UNARY_EXPRESSION] = "UNARY_EXPRESSION",
    [AST_IDENTIFIER_EXPRESSION] = "IDENTIFIER_EXPRESSION",
    [AST_PARENTHESES_EXPRESION] = "PARENTHESES_EXPRESION",
    [AST_TYPE_CAST_EXPRESION] = "TYPE_CAST_EXPRESION",
    [AST_ASSIGNEMENT_EXPRESION] = "ASSIGNEMENT_EXPRESION",
    [AST_FUNCTION_CALL] = "FUNCTION_CALL",
    [AST_FUNCTION_CALL_PARAMETER_LIST] = "FUNCTION_CALL_PARAMETER_LIST",
};


/*****************************************************************************************************
                                PUBLIC AST FUNCTIONS START HERE                                
 *****************************************************************************************************/

ASTNode *createASTNode(const ASTType type, Token **const tokens, const size_t tokenCount, ASTNode **const children, const size_t childCount)
{
    ASTNode *astNode = (ASTNode *)malloc(sizeof(ASTNode)); 
    if (astNode == NULL)
    {
        fprintf(stderr, "Memory allocation for AST Node failed!\n");
        return NULL;
    }

    astNode->type = type;
    astNode->tokens = tokens;
    astNode->tokenCount = tokenCount;
    astNode->children = children;
    astNode->childCount = childCount;

    return astNode;
}

void deleteASTNode(ASTNode *const astNode)
{
    if (astNode == NULL)
    {
        return;
    }

    for (size_t i = 0; i < astNode->childCount; ++i) 
    {
        deleteASTNode(astNode->children[i]);
    }

    free(astNode->children);
    free(astNode->tokens);
    free(astNode);
}

ASTNode *duplicateASTNode(ASTNode *const astNode)
{
    if (astNode == NULL)
    {
        fprintf(stderr, "ASTNode is NULL!\n");
        return NULL;
    }

    ASTNode *newNode = createASTNode(astNode->type, astNode->tokens, astNode->tokenCount, astNode->children, astNode->childCount);
    if (newNode == NULL)
    {
        fprintf(stderr, "Memory allocation for new AST Node failed!\n");
        return NULL;
    }
    
    return newNode;
}

void printASTNode(const ASTNode *const astNode, char *indent, int isLast)
{
    if (astNode == NULL)
    {
        return;
    }

    char *marker = isLast ? "└── " : "├── ";
    printf("%s%s%s\n", indent, marker, ASTTypes[astNode->type]);

    char newIndent[256];
    snprintf(newIndent, sizeof(newIndent), "%s%s", indent, isLast ? "    " : "│   ");

    //Print tokens
    if (astNode->childCount == 0)
    {
        printf("%s└── Tokens:\n", newIndent);
    }
    else
    {
        printf("%s├── Tokens:\n", newIndent);
    }

    for (size_t i = 0; i < astNode->tokenCount; i++)
    {
        if (i + 1 >= astNode->tokenCount)
        {
            if (astNode->childCount == 0)
            {
                printf("%s    └── ", newIndent);
            }
            else
            {
                printf("%s│   └── ", newIndent);
            }
        }
        else
        {
            printf("%s│   ├── ", newIndent);
        }
        
        printToken(astNode->tokens[i]);
    }

    //Print children
    for (size_t i = 0; i < astNode->childCount; i++)
    {
        printASTNode(astNode->children[i], newIndent, i == astNode->childCount - 1);
    }
}