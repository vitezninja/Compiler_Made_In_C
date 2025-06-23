/**
 * @file symbol.h
 * @brief Header file for the Symbol structure and related functions.
 * 
 * This file defines the Symbol structure used to represent named entities in the
 * compiler, such as functions, variables, and types. It includes functions for
 * creating symbols, printing their details, and managing symbol metadata.
 */

#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include <stdalign.h>
#include <errno.h>

// Forward declaration of the Symbol structure
typedef struct Symbol Symbol;

#include "utils/logger.h"
#include "utils/arena.h"

/**
 * @enum SymbolType
 * @brief Enumerates possible kinds of symbols in the compiler.
 */
typedef enum SymbolType
{
    SYMBOL_TYPE_UNKNOWN = 0,    /** Represents an unknown symbol type. */
    SYMBOL_TYPE_FUNCTION,       /** Represents a function symbol. */
    SYMBOL_TYPE_VARIABLE,       /** Represents a variable symbol. */
    SYMBOL_TYPE_TYPE,           /** Represents a type symbol. */
} SymbolType;

/**
 * @struct Symbol
 * @brief Represents a named entity in the program with associated metadata.
 *
 * The Symbol struct is used to store entries in the symbol table, containing
 * the name of the symbol, its kind/type, and a precomputed hash for efficient lookup.
 */
struct Symbol
{
    const char *name;   /** Pointer to the name of the symbol (null-terminated string) */
    SymbolType type;    /** Type of the symbol (e.g., function, variable, type) */
    size_t hash;        /** Precomputed hash of the symbol's name for quick comparisons */
};

/**
 * @brief Creates a new Symbol in the given arena.
 *
 * Allocates and initializes a Symbol using the provided name, type, and hash.
 * This is intended to be used when inserting a new entry into a symbol table.
 *
 * @param arena The memory arena to allocate the Symbol from.
 * @param name The name of the symbol (must be a valid null-terminated string).
 * @param type The type/category of the symbol.
 * @param hash The hash value for the symbol's name (should be precomputed).
 * @return Pointer to the newly allocated Symbol, or NULL on failure. Set `errno` to indicate the error.
 */
Symbol *symbol_create(Arena *arena, const char *name, SymbolType type, size_t hash);

/**
 * @brief Prints a symbol's details to stdout (for debugging).
 *
 * Displays the symbol's name, type, and hash value.
 *
 * @param symbol Pointer to the Symbol to print.
 */
void symbol_print(const Symbol *symbol);

#endif // SYMBOL_H