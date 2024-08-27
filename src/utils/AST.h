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

/**
 * Creates a new `ASTNode` with the specified type, tokens, and children.
 * 
 * Allocates memory for a new `ASTNode` and initializes its fields with the provided
 * type, tokens, and child nodes. The function does not take ownership of the tokens
 * arrays; it merely copies the pointers. But take ownership of the children array.
 * 
 * @param type The type of the AST node.
 * 
 * @param tokens An array of tokens associated with the node (must be dynamically allocated).
 * 
 * @param tokenCount The number of tokens in the `tokens` array.
 * 
 * @param children An array of child nodes (must be dynamically allocated).
 * 
 * @param childCount The number of child nodes in the `children` array.
 * 
 * @return A pointer to the newly created `ASTNode`, or NULL if memory allocation fails.
 * 
 * @note The caller is responsible for managing the memory of the `tokens` array. The
 *       `ASTNode` takes ownership of the `children` array and will free it when the
 *       `ASTNode` is deleted. To avoid memory leaks, it is advised to use the
 *       `deleteASTNode` function to clean up the `ASTNode` and its resources.
 */
ASTNode *createASTNode(const ASTType type, Token **const tokens, const size_t tokenCount, ASTNode **const children, const size_t childCount);

/**
 * Deletes an `ASTNode` and frees its memory.
 * 
 * Recursively deletes all child nodes, the array of child nodes, and the array of tokens
 * associated with the node. It also frees the memory allocated for the `ASTNode` itself.
 * 
 * @param astNode The `ASTNode` to be deleted.
 * 
 * @note The function assumes that the `tokens` array and `children` array are dynamically allocated.
 *       It is the caller's responsibility to manage the memory of individual tokens.
 */
void deleteASTNode(ASTNode *const astNode);

/**
 * Creates a duplicate of an `ASTNode`.
 * 
 * Allocates memory for a new `ASTNode` and copies the type, tokens, and child nodes
 * from the original node. It does not create deep copies of the tokens and children;
 * they are shared with the original node.
 * 
 * @param astNode The `ASTNode` to be duplicated.
 * 
 * @return A pointer to the duplicated `ASTNode`, or NULL if memory allocation fails.
 * 
 * @note The caller is responsible for managing the memory of the `tokens` array. The
 *       `ASTNode` takes ownership of the `children` array and will free it when the
 *       `ASTNode` is deleted. To avoid memory leaks, it is advised to use the
 *       `deleteASTNode` function to clean up the `ASTNode` and its resources.
 */
ASTNode *duplicateASTNode(ASTNode *const astNode);

/**
 * Recursively prints an Abstract Syntax Tree (AST) node with indentation.
 * 
 * This function prints the details of the AST node, including its type, tokens, and children.
 * It formats the output to visually represent the tree structure using ASCII characters for tree nodes.
 * 
 * @param astNode Pointer to the `ASTNode` to be printed. If NULL, the function returns immediately.
 * 
 * @param indent The current indentation string. This is used to format the tree structure.
 * 
 * @param isLast Indicates whether the current node is the last child of its parent. This affects the tree formatting.
 */
void printASTNode(const ASTNode *const astNode, char *indent, int isLast);

#endif