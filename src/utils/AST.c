#include "utils/ast.h"

/**
 * Lookup table for ASTType
 */
static const char *astNode_typeAsStrings[] = {
    [AST_TYPE] = "AST_TYPE",
    [AST_TYPE_SPECIFIERS] = "AST_TYPE_SPECIFIERS",
    [AST_LITERAL] = "AST_LITERAL",
    [AST_PROGRAM] = "AST_PROGRAM",
    [AST_IMPORT] = "AST_IMPORT",
    [AST_IMPORT_FROM] = "AST_IMPORT_FROM",
    [AST_IDENTIFIER_LIST] = "AST_IDENTIFIER_LIST",
    [AST_FUNCTION_DEFINITION] = "AST_FUNCTION_DEFINITION",
    [AST_RETURN_PARAMETER_LIST] = "AST_RETURN_PARAMETER_LIST",
    [AST_RETURN_PARAMETER] = "AST_RETURN_PARAMETER",
    [AST_FUNCTION_PARAMETER_LIST] = "AST_FUNCTION_PARAMETER_LIST",
    [AST_FUNCTION_PARAMETER] = "AST_FUNCTION_PARAMETER",
    [AST_GLOBAL_VARIABLE_DECLARATION] = "AST_GLOBAL_VARIABLE_DECLARATION",
    [AST_STRUCT_DECLARATION] = "AST_STRUCT_DECLARATION",
    [AST_UNION_DECLARATION] = "AST_UNION_DECLARATION",
    [AST_STRUCT_UNION_MEMBER_DECLARATION] = "AST_STRUCT_UNION_MEMBER_DECLARATION",
    [AST_STRUCT_UNION_DECLARATOR] = "AST_STRUCT_UNION_DECLARATOR",
    [AST_STRUCT_UNION_INDIRECT_DECLARATOR] = "AST_STRUCT_UNION_INDIRECT_DECLARATOR",
    [AST_STRUCT_UNION_DIRECT_DECLARATOR] = "AST_STRUCT_UNION_DIRECT_DECLARATOR",
    [AST_ENUM_DECLARATION] = "AST_ENUM_DECLARATION",
    [AST_ENUM_VALUE_DECLARATION] = "AST_ENUM_VALUE_DECLARATION",
    [AST_TYPEDEF] = "AST_TYPEDEF",
    [AST_STATEMENT] = "AST_STATEMENT",
    [AST_BRANCH_STATEMENT] = "AST_BRANCH_STATEMENT",
    [AST_IF_STATEMENT] = "AST_IF_STATEMENT",
    [AST_SWITCH_STATEMENT] = "AST_SWITCH_STATEMENT",
    [AST_LOOP_STATEMENT] = "AST_LOOP_STATEMENT",
    [AST_FOR_STATEMENT] = "AST_FOR_STATEMENT",
    [AST_FOREACH_STATEMENT] = "AST_FOREACH_STATEMENT",
    [AST_WHILE_STATEMENT] = "AST_WHILE_STATEMENT",
    [AST_DO_WHILE_STATEMENT] = "AST_DO_WHILE_STATEMENT",
    [AST_COMPOUND_STATEMENT] = "AST_COMPOUND_STATEMENT",
    [AST_LABEL] = "AST_LABEL",
    [AST_EXPRESSION_STATEMENT] = "AST_EXPRESSION_STATEMENT",
    [AST_VARIABLE_DECLARATION] = "AST_VARIABLE_DECLARATION",
    [AST_JUMP_STATEMENT] = "AST_JUMP_STATEMENT",
    [AST_EXPRESSION] = "AST_EXPRESSION",
    [AST_FUNCTION_CALL] = "AST_FUNCTION_CALL",
    [AST_ASSIGNMENT_EXPRESSION] = "AST_ASSIGNMENT_EXPRESSION",
    [AST_LOGICAL_OR_EXPRESSION] = "AST_LOGICAL_OR_EXPRESSION",
    [AST_LOGICAL_AND_EXPRESSION] = "AST_LOGICAL_AND_EXPRESSION",
    [AST_BITWISE_OR_EXPRESSION] = "AST_BITWISE_OR_EXPRESSION",
    [AST_BITWISE_XOR_EXPRESSION] = "AST_BITWISE_XOR_EXPRESSION",
    [AST_BITWISE_AND_EXPRESSION] = "AST_BITWISE_AND_EXPRESSION",
    [AST_EQUALITY_EXPRESSION] = "AST_EQUALITY_EXPRESSION",
    [AST_RELATIONAL_EXPRESSION] = "AST_RELATIONAL_EXPRESSION",
    [AST_SHIFT_EXPRESSION] = "AST_SHIFT_EXPRESSION",
    [AST_ADDITIVE_EXPRESSION] = "AST_ADDITIVE_EXPRESSION",
    [AST_MULTIPLICATIVE_EXPRESSION] = "AST_MULTIPLICATIVE_EXPRESSION",
    [AST_TYPE_CAST_EXPRESSION] = "AST_TYPE_CAST_EXPRESSION",
    [AST_UNARY_EXPRESSION] = "AST_UNARY_EXPRESSION",
    [AST_POSTFIX_EXPRESSION] = "AST_POSTFIX_EXPRESSION",
    [AST_ARRAY_INDEXING] = "AST_ARRAY_INDEXING",
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