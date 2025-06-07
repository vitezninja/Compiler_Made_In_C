/**
 * @file ast.h
 * @brief Header file for the Abstract Syntax Tree (AST) implementation.
 * 
 * This file defines the structures and functions for creating and manipulating
 * the Abstract Syntax Tree (AST) used in the compiler. The AST represents
 * the syntactic structure of the source code, with nodes corresponding to
 * various language constructs such as expressions, statements, and declarations.
 */

#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdalign.h>
#include <errno.h>
#include <stdbool.h>

// Forward declaration of the AstNode structure
struct AstNode;

#include "utils/logger.h"
#include "utils/token.h"
#include "utils/arena.h"
#include "utils/linkedList.h"

/**
 * @enum AstType
 * @brief Enumeration of all Abstract Syntax Tree (AST) node types.
 *
 * Represents the different syntactic constructs in the source code. Each enum value
 * corresponds to a distinct type of AST node used to model the structure of a program.
 */
typedef enum AstType
{
    AST_PROGRAM,
    AST_IMPORT,
    AST_IMPORT_FROM,

    AST_FUNCTION_DEFINITION,
    AST_GLOBAL_VARIABLE_DECLARATION,

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
} AstType;

/**
 * @struct AstNode
 * @brief Represents a single node in the Abstract Syntax Tree (AST).
 *
 * Each AST node describes a syntactic construct. Nodes can store one or more tokens
 * and have a list of child AST nodes forming a tree structure.
 */
typedef struct AstNode
{
    AstType type;               /** Type of the AST node. */
    struct LinkedList *tokens;         /** Array of tokens associated with this node. */
    struct LinkedList *children;       /** Array of child AST nodes. */
} AstNode;

/**
 * @brief Creates a new AST node and allocates memory from the provided arena.
 *
 * Initializes a new AST node with the given type, tokens, and children. All allocations
 * are performed using the provided memory arena.
 *
 * @param arena Pointer to the memory arena for allocation.
 * @param type Type of AST node to create.
 * @param tokens Pointer to the token array.
 * @param tokenCount Number of tokens.
 * @param children Pointer to array of child ASTNode pointers.
 * @param childCount Number of children.
 * @return Pointer to the newly created ASTNode. Set `errno` to indicate the error.
 */
AstNode *astNode_create(Arena *arena, AstType type, struct LinkedList *tokens, struct LinkedList *children);

/**
 * @brief Prints a brief summary of an AST node.
 *
 * Displays the node type and number of tokens/children. This is intended for simple debugging.
 *
 * @param astNode Pointer to the AST node to print.
 */
void astNode_print(const AstNode *astNode);

/**
 * @brief Recursively prints the AST as a tree.
 *
 * This function displays the full AST hierarchy with indentation to reflect nesting levels.
 *
 * @param astNode Pointer to the AST node.
 * @param indent Current indentation string (use "" for root).
 * @param isLast Flag indicating whether this node is the last child in its parent.
 */
void astNode_printTree(const AstNode *astNode, char *indent, bool isLast);

/**
 * @brief Returns the string name of an AST type.
 *
 * Converts an `AstType` enum value into a human-readable string.
 *
 * @param type AST type to convert.
 * @return String representing the name of the AST type.
 */
const char *astNode_getAstType(AstType type);

#endif // AST_H