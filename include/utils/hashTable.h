/**
 * @file hashTable.h
 * @brief Header file for the hash table implementation.
 *
 * This file defines the structures and functions for creating and manipulating
 * hash tables in the compiler. It includes functions for inserting and finding
 * strings and symbols, as well as printing the contents of the hash table.
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// Forward declaration of the HashTable structure
struct HashTable;

#include "utils/logger.h"
#include "utils/arena.h"
#include "utils/linkedList.h"
#include "utils/symbol.h"
#include "utils/my_string.h"

/**
 * @def INITIAL_BUCKET_COUNT
 * @brief Initial number of buckets in the hash table.
 *
 * This constant defines the initial size of the hash table's bucket array.
 * It is used to allocate memory for the hash table when it is created.
 * It is also used when resizing the hash table to ensure that it has enough buckets
 * to handle the expected number of items.
 */
#define INITIAL_BUCKET_COUNT 16

/**
 * @struct HashTable
 * @brief Structure representing a hash table.
 *
 * This structure is used to create a hash table that can store strings and symbols.
 * It contains an array of linked lists (buckets) for handling collisions, the arena
 * for memory allocation, and metadata about the number of buckets and items.
 */
typedef struct HashTable
{
    Arena *arena;                   /** Memory arena used for allocation */
    struct LinkedList **buckets;    /** Array of linked lists (buckets) for collision resolution */
    size_t bucketCount;             /** Number of buckets in the hash table */
    size_t itemCount;               /** Total number of items in the hash table */
} HashTable;

/**
 * @brief Creates a new hash table in the given arena.
 *
 * This function initializes a hash table with a specified number of buckets
 * and allocates memory for it using the provided arena.
 *
 * @param arena The memory arena to use for allocation.
 * @return Pointer to the newly created HashTable, or NULL on failure. Set `errno` to indicate the error.
 */
HashTable *hashTable_create(Arena *arena);

/**
 * @brief Inserts a string into the hash table.
 *
 * This function attempts to insert a string with the given name and length into
 * the hash table. If a string with the same name already exists, it returns
 * the existing string; otherwise, it creates a new string and inserts it.
 *
 * @param hashTable Pointer to the HashTable to insert into.
 * @param name The name of the symbol (null-terminated).
 * @param length The length of the string (excluding null terminator).
 * @return Pointer to the inserted or existing String object. Set `errno` to indicate the error.
 */
String *hashTable_String_tryInsert(HashTable *hashTable, const char *name, size_t length);

/**
 * @brief Inserts a symbol into the hash table.
 *
 * This function attempts to insert a symbol with the given name and type into
 * the hash table. If a symbol with the same name already exists, it returns
 * the existing symbol; otherwise, it creates a new symbol and inserts it.
 *
 * @param hashTable Pointer to the HashTable to insert into.
 * @param name The name of the symbol (null-terminated).
 * @param type The type of the symbol.
 * @return Pointer to the inserted or existing Symbol object. Set `errno` to indicate the error.
 */
Symbol *hashTable_Symbol_tryInsert(HashTable *hashTable, const char *name, SymbolType type);

/**
 * @brief Finds a string in the hash table.
 *
 * This function searches for a string by its name in the hash table and returns
 * a pointer to the String object if found, or NULL if not found.
 *
 * @param hashTable Pointer to the HashTable to search in.
 * @param name The name of the string to find (null-terminated).
 * @return Pointer to the String object if found, or NULL if not found.
 */
String *hashTable_String_find(HashTable *hashTable, const char *name);

/**
 * @brief Finds a symbol in the hash table.
 *
 * This function searches for a symbol by its name in the hash table and returns
 * a pointer to the Symbol object if found, or NULL if not found.
 *
 * @param hashTable Pointer to the HashTable to search in.
 * @param name The name of the symbol to find (null-terminated).
 * @return Pointer to the Symbol object if found, or NULL if not found.
 */
Symbol *hashTable_Symbol_find(HashTable *hashTable, const char *name);

/**
 * @brief Prints the contents of the hash table.
 *
 * This function iterates through all buckets in the hash table and prints
 * the contents of each linked list.
 *
 * @param hashTable Pointer to the HashTable to print.
 * @param printFn Function pointer to a function that prints the data in each bucket.
 */
void hashTable_print(const HashTable *hashTable, PrintFunction printFn);

#endif // HASH_TABLE_H