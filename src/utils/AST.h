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
    AST_GLOBAL_DECLARATION,
    AST_FUNCTION_DEFINITION,
    AST_DECLARATION_SPECIFIERS,
    AST_STORAGE_CLASS_SPECIFIER,
    AST_TYPE_SPECIFIER,
    AST_STRUCT_OR_UNION_SPECIFIER,
    AST_STRUCT_DECLARATION,
    AST_SPECIFIER_QUALIFIER,
    AST_TYPE_QUALIFIER,
    AST_STRUCT_DECLARATOR_LIST,
    AST_STRUCT_DECLARATOR,
    AST_DECLARATOR,
    AST_POINTER,
    AST_DIRECT_DECLARATOR,
    AST_DIRECT_DECLARATOR_PRIME,
    AST_ASSIGNMENT_EXPRESSION,
    AST_ASSIGNMENT_OPERATOR,
    AST_CONDITIONAL_EXPRESSION,
    AST_LOGICAL_OR_EXPRESSION,
    AST_LOGICAL_AND_EXPRESSION,
    AST_BITWISE_OR_EXPRESSION,
    AST_BITWISE_XOR_EXPRESSION,
    AST_BITWISE_AND_EXPRESSION,
    AST_EQUALITY_EXPRESSION,
    AST_EQUALITY_OPERATOR,
    AST_RELATIONAL_EXPRESSION,
    AST_RELATIONAL_OPERATOR,
    AST_SHIFT_EXPRESSION,
    AST_SHIFT_OPERATOR,
    AST_ADDITIVE_EXPRESSION,
    AST_ADDITIVE_OPERATOR,
    AST_MULTIPLICATIVE_EXPRESSION,
    AST_MULTIPLICATIVE_OPERATOR,
    AST_CAST_EXPRESSION,
    AST_UNARY_EXPRESSION,
    AST_UNARY_OPERATOR,
    AST_PREFIX_UNARY_TOKEN,
    AST_POSTFIX_EXPRESSION,
    AST_POSTFIX_EXPRESSION_PRIME,
    AST_POSTFIX_OPERATOR,
    AST_PRIMARY_EXPRESSION,
    AST_LITERAL,
    AST_TOKEN,
    AST_EXPRESSION,
    AST_ARGUMENT_EXPRESSION,
    AST_TYPE_NAME,
    AST_ABSTRACT_DECLARATOR,
    AST_DIRECT_ABSTRACT_DECLARATOR,
    AST_DIRECT_ABSTRACT_DECLARATOR_PRIME,
    AST_PARAMETER_LIST,
    AST_PARAMETER_DECLARATION,
    AST_INITIALIZER_LIST,
    AST_DESIGNATION,
    AST_DESIGNATOR,
    AST_CONSTANT_EXPRESSION,
    AST_INITIALIZER,
    AST_IDENTIFIER_LIST,
    AST_ENUM_SPECIFIER,
    AST_ENUMERATOR_LIST,
    AST_ENUMERATOR,
    AST_DECLARATION,
    AST_INIT_DECLARATOR_LIST,
    AST_INIT_DECLARATOR,
    AST_STATEMENT,
    AST_LABELED_STATEMENT,
    AST_COMPOUND_STATEMENT,
    AST_EXPRESSION_STATEMENT,
    AST_SELECTION_STATEMENT,
    AST_ITERATION_STATEMENT,
    AST_FOR_CONTROL,
    AST_JUMP_STATEMENT,
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