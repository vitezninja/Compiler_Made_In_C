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
    [AST_GLOBAL_DECLARATION] = "GLOBAL_DECLARATION",
    [AST_FUNCTION_DEFINITION] = "FUNCTION_DEFINITION",
    [AST_DECLARATION_SPECIFIERS] = "DECLARATION_SPECIFIERS",
    [AST_STORAGE_CLASS_SPECIFIER] = "STORAGE_CLASS_SPECIFIER",
    [AST_TYPE_SPECIFIER] = "TYPE_SPECIFIER",
    [AST_STRUCT_OR_UNION_SPECIFIER] = "STRUCT_OR_UNION_SPECIFIER",
    [AST_STRUCT_DECLARATION] = "STRUCT_DECLARATION",
    [AST_SPECIFIER_QUALIFIER] = "SPECIFIER_QUALIFIER",
    [AST_TYPE_QUALIFIER] = "TYPE_QUALIFIER",
    [AST_STRUCT_DECLARATOR_LIST] = "STRUCT_DECLARATOR_LIST",
    [AST_STRUCT_DECLARATOR] = "STRUCT_DECLARATOR",
    [AST_DECLARATOR] = "DECLARATOR",
    [AST_POINTER] = "POINTER",
    [AST_DIRECT_DECLARATOR] = "DIRECT_DECLARATOR",
    [AST_DIRECT_DECLARATOR_PRIME] = "DIRECT_DECLARATOR_PRIME",
    [AST_ASSIGNMENT_EXPRESSION] = "ASSIGNMENT_EXPRESSION",
    [AST_ASSIGNMENT_OPERATOR] = "ASSIGNMENT_OPERATOR",
    [AST_CONDITIONAL_EXPRESSION] = "CONDITIONAL_EXPRESSION",
    [AST_LOGICAL_OR_EXPRESSION] = "LOGICAL_OR_EXPRESSION",
    [AST_LOGICAL_AND_EXPRESSION] = "LOGICAL_AND_EXPRESSION",
    [AST_BITWISE_OR_EXPRESSION] = "BITWISE_OR_EXPRESSION",
    [AST_BITWISE_XOR_EXPRESSION] = "BITWISE_XOR_EXPRESSION",
    [AST_BITWISE_AND_EXPRESSION] = "BITWISE_AND_EXPRESSION",
    [AST_EQUALITY_EXPRESSION] = "EQUALITY_EXPRESSION",
    [AST_EQUALITY_OPERATOR] = "EQUALITY_OPERATOR",
    [AST_RELATIONAL_EXPRESSION] = "RELATIONAL_EXPRESSION",
    [AST_RELATIONAL_OPERATOR] = "RELATIONAL_OPERATOR",
    [AST_SHIFT_EXPRESSION] = "SHIFT_EXPRESSION",
    [AST_SHIFT_OPERATOR] = "SHIFT_OPERATOR",
    [AST_ADDITIVE_EXPRESSION] = "ADDITIVE_EXPRESSION",
    [AST_ADDITIVE_OPERATOR] = "ADDITIVE_OPERATOR",
    [AST_MULTIPLICATIVE_EXPRESSION] = "MULTIPLICATIVE_EXPRESSION",
    [AST_MULTIPLICATIVE_OPERATOR] = "MULTIPLICATIVE_OPERATOR",
    [AST_CAST_EXPRESSION] = "CAST_EXPRESSION",
    [AST_UNARY_EXPRESSION] = "UNARY_EXPRESSION",
    [AST_UNARY_OPERATOR] = "UNARY_OPERATOR",
    [AST_PREFIX_UNARY_TOKEN] = "PREFIX_UNARY_TOKEN",
    [AST_POSTFIX_EXPRESSION] = "POSTFIX_EXPRESSION",
    [AST_POSTFIX_EXPRESSION_PRIME] = "POSTFIX_EXPRESSION_PRIME",
    [AST_POSTFIX_OPERATOR] = "POSTFIX_OPERATOR",
    [AST_PRIMARY_EXPRESSION] = "PRIMARY_EXPRESSION",
    [AST_LITERAL] = "LITERAL",
    [AST_TOKEN] = "TOKEN", 
    [AST_EXPRESSION] = "EXPRESSION",
    [AST_ARGUMENT_EXPRESSION] = "ARGUMENT_EXPRESSION",
    [AST_TYPE_NAME] = "TYPE_NAME",
    [AST_ABSTRACT_DECLARATOR] = "ABSTRACT_DECLARATOR",
    [AST_DIRECT_ABSTRACT_DECLARATOR] = "DIRECT_ABSTRACT_DECLARATOR",
    [AST_DIRECT_ABSTRACT_DECLARATOR_PRIME] = "DIRECT_ABSTRACT_DECLARATOR_PRIME",
    [AST_PARAMETER_LIST] = "PARAMETER_LIST",
    [AST_PARAMETER_DECLARATION] = "PARAMETER_DECLARATION",
    [AST_INITIALIZER_LIST] = "INITIALIZER_LIST",
    [AST_DESIGNATION] = "DESIGNATION",
    [AST_DESIGNATOR] = "DESIGNATOR",
    [AST_CONSTANT_EXPRESSION] = "CONSTANT_EXPRESSION",
    [AST_INITIALIZER] = "INITIALIZER",
    [AST_IDENTIFIER_LIST] = "IDENTIFIER_LIST",
    [AST_ENUM_SPECIFIER] = "ENUM_SPECIFIER",
    [AST_ENUMERATOR_LIST] = "ENUMERATOR_LIST",
    [AST_ENUMERATOR] = "ENUMERATOR",
    [AST_DECLARATION] = "DECLARATION",
    [AST_INIT_DECLARATOR_LIST] = "INIT_DECLARATOR_LIST",
    [AST_INIT_DECLARATOR] = "INIT_DECLARATOR",
    [AST_STATEMENT] = "STATEMENT",
    [AST_LABELED_STATEMENT] = "LABELED_STATEMENT",
    [AST_COMPOUND_STATEMENT] = "COMPOUND_STATEMENT",
    [AST_EXPRESSION_STATEMENT] = "EXPRESSION_STATEMENT",
    [AST_SELECTION_STATEMENT] = "SELECTION_STATEMENT",
    [AST_ITERATION_STATEMENT] = "ITERATION_STATEMENT",
    [AST_FOR_CONTROL] = "FOR_CONTROL",
    [AST_JUMP_STATEMENT] = "JUMP_STATEMENT",
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