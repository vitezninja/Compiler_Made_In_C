#include "utils/ast.h"

/**
 * Lookup table for ASTType
 */
static const char *astNode_typeAsStrings[] = {
    [AST_PROGRAM] = "PROGRAM",
    [AST_IMPORT] = "IMPORT",
    [AST_IMPORT_FROM] = "IMPORT_FROM",

    [AST_FUNCTION_DEFINITION] = "FUNCTION_DEFINITION",
    [AST_GLOBAL_VARIABLE_DECLARATION] = "GLOBAL_VARIABLE_DECLARATION",

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

AstNode *astNode_create(Arena *arena, AstType type, LinkedList *tokens, LinkedList *children)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("astNode_create: arena is NULL\n");
        return NULL;
    }

    if (type < 0 || type >= AST_JUMP_STATEMENT)
    {
        DEBUG_PRINT("astNode_create: type is out of range\n");
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
    node->children = children;

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
    linkedList_printRecursive(astNode->tokens, (PrintFunction)token_print);
    astNode_printTree(astNode, "", false);
    printf("}\n");
}

void astNode_printTree(const AstNode *astNode, char *indent, bool isLast)
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
    if (astNode->children == NULL)
    {
        printf("%s└── Tokens:\n", newIndent);
    }
    else
    {
        printf("%s├── Tokens:\n", newIndent);
    }

    LinkedList *node = astNode->tokens;
    while (node != NULL)
    {
        if (astNode->children == NULL)
        {
            printf("%s    ", newIndent);
        }
        else
        {
            printf("%s│   ", newIndent);
        }
        
        if (node->next == NULL)
        {
            printf("└── ");
        }
        else
        {
            printf("├── ");
        }
        
        printf("Token: %s\n", token_typeToString(((Token *)node->data)->type));

        node = node->next;
    }

    //Print children
    node = astNode->children;
    while (node != NULL)
    {
        astNode_printTree((AstNode *)node->data, newIndent, node->next == NULL);
        node = node->next;
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