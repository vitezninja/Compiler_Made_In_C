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

typedef struct AstNode AstNode;

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
    AST_TYPE,
    AST_TYPE_SPECIFIERS,
    AST_FULL_TYPE,
    AST_LITERAL,
    AST_PROGRAM,
    AST_IMPORT,
    AST_IMPORT_FROM,
    AST_IDENTIFIER_LIST,
    AST_FUNCTION_DEFINITION,
    AST_RETURN_PARAMETER_LIST,
    AST_FUNCTION_PARAMETER_LIST,
    AST_FUNCTION_PARAMETER,
    AST_GLOBAL_VARIABLE_DECLARATION,
    AST_STRUCT_DECLARATION,
    AST_UNION_DECLARATION,
    AST_STRUCT_UNION_MEMBER_DECLARATION,
    AST_STRUCT_UNION_DECLARATOR,
    AST_STRUCT_UNION_INDIRECT_DECLARATOR,
    AST_STRUCT_UNION_DIRECT_DECLARATOR,
    AST_ENUM_DECLARATION,
    AST_ENUM_VALUE_DECLARATION,
    AST_ENUM_VALUE,
    AST_TYPEDEF,
    AST_STATEMENT,
    AST_BRANCH_STATEMENT,
    AST_IF_STATEMENT,
    AST_SWITCH_STATEMENT,
    AST_SWITCH_CASE,
    AST_SWITCH_DEFAULT,
    AST_LOOP_STATEMENT,
    AST_FOR_STATEMENT,
    AST_FOR_INITIALIZER,
    AST_FOR_CONDITION,
    AST_FOR_INCREMENTATION,
    AST_FOREACH_STATEMENT,
    AST_WHILE_STATEMENT,
    AST_DO_WHILE_STATEMENT,
    AST_COMPOUND_STATEMENT,
    AST_LABEL,
    AST_EXPRESSION_STATEMENT,
    AST_VARIABLE_DECLARATION,
    AST_JUMP_STATEMENT,
    AST_GOTO_STATEMENT,
    AST_RETURN_STATEMENT,
    AST_CONTINUE_STATEMENT,
    AST_BREAK_STATEMENT,
    AST_EXPRESSION,
    AST_ASSIGNMENT_EXPRESSION,
    AST_LOGICAL_OR_EXPRESSION,
    AST_LOGICAL_AND_EXPRESSION,
    AST_BITWISE_OR_EXPRESSION,
    AST_BITWISE_XOR_EXPRESSION,
    AST_BITWISE_AND_EXPRESSION,
    AST_EQUALITY_EXPRESSION,
    AST_RELATIONAL_EXPRESSION,
    AST_SHIFT_EXPRESSION,    
    AST_ADDITIVE_EXPRESSION,
    AST_MULTIPLICATIVE_EXPRESSION,
    AST_TYPE_CAST_EXPRESSION,
    AST_UNARY_EXPRESSION,
    AST_POSTFIX_EXPRESSION,
    AST_POSTFIX_PRIME_EXPRESSION,
    AST_ARRAY_INDEXING_EXPRESSION,
    AST_FUNCTION_CALL_EXPRESSION,
    AST_PRIMARY_EXPRESSION,
} AstType;

/**
 * @struct AstNode
 * @brief Represents a single node in the Abstract Syntax Tree (AST).
 *
 * Each AST node describes a syntactic construct. Nodes can store one or more tokens
 * and have a list of child AST nodes forming a tree structure.
 */
struct AstNode
{
    AstType type;               /** Type of the AST node. */
    LinkedList *tokens;         /** Array of tokens associated with this node. */
    LinkedList *children;       /** Array of child AST nodes. */
};

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
AstNode *astNode_create(Arena *arena, AstType type, LinkedList *tokens, LinkedList *children);

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