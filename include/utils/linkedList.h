/**
 * @file linkedList.h
 * @brief Header file for linked list utilities.
 *
 * This file defines the structures and functions for creating and manipulating
 * linked lists in the compiler, including specialized lists for tokens, errors,
 * hash tables, symbols, and strings.
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdalign.h>
#include <stdio.h>
#include <errno.h>

// Forward declaration of the LinkedList structure
typedef struct LinkedList LinkedList;

#include "utils/logger.h"
#include "utils/arena.h"
#include "utils/token.h"
#include "utils/error.h"
#include "utils/hashTable.h"
#include "utils/symbol.h"
#include "utils/my_string.h"
#include "utils/ast.h"

/**
 * @struct LinkedList
 * @brief Structure representing a node in a linked list.
 *
 * This structure is used to create linked lists for various data types such as
 * tokens, errors, hash tables, symbols, and strings. Each node contains a pointer
 * to the next node and a pointer to the data it holds.
 */
struct LinkedList
{
    struct LinkedList *next;    /** Pointer to the next node in the linked list */
    void *data;                 /** Pointer to the data stored in this node */
};

/**
 * @brief Creates a new linked list node with the given data.
 *
 * This function allocates memory for a new LinkedList node and initializes it
 * with the provided data and chains it to the end of the linked list.
 * 
 *
 * @param arena Memory arena used for allocation.
 * @param head Pointer to the head of the linked list (can be NULL).
 * @param data Pointer to the data to be stored in the node.
 * @return Pointer to the head of the linked list. Set `errno` to indicate the error.
 */
LinkedList *linkedList_Token_create(Arena *arena, LinkedList *head, Token *data);

/**
 * @brief Creates a new linked list node with the given error data.
 *
 * This function allocates memory for a new LinkedList node and initializes it
 * with the provided error data and chains it to the end of the linked list.
 *
 * @param arena Memory arena used for allocation.
 * @param head Pointer to the head of the linked list (can be NULL).
 * @param data Pointer to the error data to be stored in the node.
 * @return Pointer to the head of the linked list. Set `errno` to indicate the error.
 */
LinkedList *linkedList_Error_create(Arena *arena, LinkedList *head, Error *data);

/**
 * @brief Creates a new linked list node with the given hash table data.
 *
 * This function allocates memory for a new LinkedList node and initializes it
 * with the provided hash table data and chains it to the start of the linked list.
 *
 * @param arena Memory arena used for allocation.
 * @param head Pointer to the head of the linked list (can be NULL).
 * @param data Pointer to the hash table data to be stored in the node.
 * @return Pointer to the newly created LinkedList node. Set `errno` to indicate the error.
 */
LinkedList *linkedList_HashTable_create(Arena *arena, LinkedList *head, HashTable *data);

/**
 * @brief Creates a new linked list node with the given symbol data.
 *
 * This function allocates memory for a new LinkedList node and initializes it
 * with the provided symbol data and chains it to the end of the linked list.
 *
 * @param arena Memory arena used for allocation.
 * @param head Pointer to the head of the linked list (can be NULL).
 * @param data Pointer to the symbol data to be stored in the node.
 * @return Pointer to the head of the linked list. Set `errno` to indicate the error.
 */
LinkedList *linkedList_Symbol_create(Arena *arena, LinkedList *head, Symbol *data);

/**
 * @brief Creates a new linked list node with the given string data.
 *
 * This function allocates memory for a new LinkedList node and initializes it
 * with the provided string data and chains it to the end of the linked list.
 *
 * @param arena Memory arena used for allocation.
 * @param head Pointer to the head of the linked list (can be NULL).
 * @param data Pointer to the string data to be stored in the node.
 * @return Pointer to the head of the linked list. Set `errno` to indicate the error.
 */
LinkedList *linkedList_String_create(Arena *arena, LinkedList *head, String *data);

/**
 * @brief Creates a new linked list node with the given AST node data.
 * 
 * This function allocates memory for a new LinkedList node and initializes it
 * with the provided AST node data and chains it to the end of the linked list.
 * 
 * @param arena Memory arena used for allocation.
 * @param head Pointer to the head of the linked list (can be NULL).
 * @param data Pointer to the AST node data to be stored in the node.
 * @return Pointer to the head of the linked list. Set `errno` to indicate the error.
 */
LinkedList *linkedList_Ast_create(Arena *arena, LinkedList *head, AstNode *data);

/**
 * @brief Prints the contents of a linked list node.
 *
 * This function prints the data contained in a linked list node using the
 * provided print function. It is useful for debugging and displaying the
 * contents of the linked list.
 *
 * @param node Pointer to the linked list node to be printed.
 * @param printFn Function pointer to the function that prints the data.
 */
void linkedList_print(const LinkedList *node, PrintFunction printFn);

/**
 * @brief Recursively prints the contents of a linked list.
 *
 * This function traverses the linked list starting from the head and prints
 * each node's data using the provided print function. It is useful for
 * displaying the entire linked list in a structured format.
 *
 * @param head Pointer to the head of the linked list.
 * @param printFn Function pointer to the function that prints the data.
 * 
 * @note This fucntion is not recursive in the traditional sense, but it iterates through the list.
 */
void linkedList_printRecursive(const LinkedList *head, PrintFunction printFn);

#endif // LINKED_LIST_H