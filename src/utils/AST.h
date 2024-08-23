#ifndef AST_H
#define AST_H

#include "../utils/token.h"

/**
 * Enumeration of AST node types.
 * 
 * The `ASTType` enum defines various types of nodes in the Abstract Syntax Tree (AST).
 */
typedef enum astType
{
    AST_PROGRAM,
    AST_GLOBAL_VARIABLE_DECLARATION,
    AST_FUNCTION_DECLARATION,
    AST_FUNCTION_DEFINITION,
    AST_ENUM,
    AST_STRUCT,
    AST_UNION,
    AST_PARAMETER_LIST,
    AST_ENUM_LIST,
    AST_MEMBER_LIST,
    AST_LABELED_STATEMENT,
    AST_EXPRESSION_STATEMENT,
    AST_RETURN_STATEMENT,
    AST_BREAK_STATEMENT,
    AST_CONTINUE_STATEMENT,
    AST_GOTO_STATEMENT,
    AST_COMPOUND_STATEMENT,
    AST_LOCAL_VARIABLE_DECLARATION,
    AST_FOR_ITERATION_STATEMENT,
    AST_WHILE_ITERATION_STATEMENT,
    AST_DO_ITERATION_STATEMENT,
    AST_IF_STATEMENT,
    AST_SWITCH_STATEMENT,
    AST_SWITCH_BODY,
    AST_LITERAL,
    AST_BINARY_EXPRESSION,
    AST_UNARY_EXPRESSION,
    AST_IDENTIFIER_EXPRESSION,
    AST_PARENTHESES_EXPRESION,
    AST_TYPE_CAST_EXPRESION,
    AST_ASSIGNEMENT_EXPRESION,
    AST_FUNCTION_CALL,
    AST_FUNCTION_CALL_PARAMETER_LIST,
} ASTType;

/**
 * Represents a node in the Abstract Syntax Tree (AST).
 * 
 * The `ASTNode` structure encapsulates details about an AST node, including its type,
 * associated tokens, and child nodes.
 * 
 * - `type`: The type of the AST node.
 * - `tokens`: An array of tokens associated with this node. This array is managed by the caller.
 * - `tokenCount`: The number of tokens in the `tokens` array.
 * - `children`: An array of child AST nodes.
 * - `childCount`: The number of child nodes in the `children` array.
 */
typedef struct astNode
{
    ASTType type;               /** The type of the AST node. */
    Token **tokens;             /** Array of tokens associated with the node. */
    size_t tokenCount;          /** Number of tokens in the `tokens` array. */
    struct astNode **children;  /** Array of child nodes. */
    size_t childCount;          /** Number of child nodes in the `children` array. */
} ASTNode;

ASTNode *createASTNode(const ASTType type, Token **const tokens, const size_t tokenCount, ASTNode **const children, const size_t childCount);

void deleteASTNode(ASTNode *const astNode);

ASTNode *duplicateASTNode(ASTNode *const astNode);

void printASTNode(const ASTNode *const astNode, char *indent, int isLast);

#endif