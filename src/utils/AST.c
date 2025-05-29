#include "utils/ast.h"

/**
 * Lookup table for ASTType
 */
static const char *astNode_typeAsStrings[] = {
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

AstNode *astNode_create(Arena *arena, AstType type, const Token *tokens, size_t tokenCount, const AstNode **children, size_t childCount)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("astNode_create: arena is NULL\n");
        return NULL;
    }

    if (type <= 0 || type >= AST_JUMP_STATEMENT)
    {
        DEBUG_PRINT("astNode_create: type is out of range\n");
        return NULL;
    }

    if (tokens == NULL)
    {
        DEBUG_PRINT("astNode_create: tokens is NULL\n");
        return NULL;
    }

    if (children == NULL)
    {
        DEBUG_PRINT("astNode_create: children is NULL\n");
        return NULL;
    }

    AstNode *node = (AstNode *)arena_alloc(arena, sizeof(AstNode), alignof(AstNode));
    if (node == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("astNode_create: arena_alloc failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("astNode_create: arena_alloc failed with unknown error\n");
        }

        return NULL;
    }

    node->type = type;
    node->tokens = tokens;
    node->tokenCount = tokenCount;
    node->children = children;
    node->childCount = childCount;

    return node;
}

void astNode_print(const AstNode *astNode)
{
    if (astNode == NULL)
    {
        DEBUG_PRINT("astNode_print: astNode is NULL\n");
        return;
    }

    printf("AST Node {\n");
    printf("    AST Node Type: %s\n", astNode_typeAsStrings[astNode->type]);
    printf("    Token Count: %zu\n", astNode->tokenCount);
    for (size_t i = 0; i < astNode->tokenCount; i++)
    {
        token_print(&(astNode->tokens[i]));
    }
    printf("    Child Count: %zu\n", astNode->childCount);
    printf("    For more details, use astNode_printTree function.\n");
    printf("}\n");
}

void astNode_printTree(const AstNode *astNode, char *indent, int isLast)
{
    if (astNode == NULL)
    {
        DEBUG_PRINT("astNode_printTree: astNode is NULL\n");
        return;
    }

    char *marker = isLast ? "└── " : "├── ";
    printf("%s%s%s\n", indent, marker, astNode_typeAsStrings[astNode->type]);

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
        if (astNode->childCount == 0)
        {
            printf("%s    ", newIndent);
        }
        else
        {
            printf("%s│   ", newIndent);
        }
        
        if (i + 1 >= astNode->tokenCount)
        {
            printf("└── ");
        }
        else
        {
            printf("├── ");
        }
        
        token_print(&(astNode->tokens[i]));
    }

    //Print children
    for (size_t i = 0; i < astNode->childCount; i++)
    {
        astNode_printTree(astNode->children[i], newIndent, i == astNode->childCount - 1);
    }
}

const char *astNode_getAstType(AstType type)
{
    if (type > 0 && type < AST_JUMP_STATEMENT)
    {
        DEBUG_PRINT("astNode_getAstType: type is within range\n");
        return "UNKNOWN";
    }

    return astNode_typeAsStrings[type];
}