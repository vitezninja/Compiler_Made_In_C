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

typedef struct Symbol Symbol;
typedef union SymbolValue SymbolValue;
typedef struct FunctionValue FunctionValue;

#include "utils/logger.h"
#include "utils/arena.h"
#include "utils/type.h"

/**
 * @enum SymbolType
 * @brief Enumerates possible kinds of symbols in the compiler.
 */
typedef enum SymbolType
{
    SYMBOL_TYPE_VARIABLE,       /** Represents a variable symbol. */
    SYMBOL_TYPE_FUNCTION,       /** Represents a function symbol. */
    SYMBOL_TYPE_ENUM_CONSTANT,  /** Represents an enum constant symbol. */
    SYMBOL_TYPE_LABEL,          /** Represents a label symbol. */
} SymbolType;

/**
 * @union SymbolValue
 * @brief Union to hold different types of values associated with a symbol.
 *
 * This union allows a Symbol to hold various types of data depending on its kind,
 * such as function parameters, variable types, or struct members.
 */
union SymbolValue
{
    FunctionValue *function;       /** Function-specific information (if applicable) */
    CmcType *variableType;         /** Type of the variable (if applicable) */
};

/**
 * @struct Symbol
 * @brief Represents a named entity in the program with associated metadata.
 *
 * The Symbol struct is used to store entries in the symbol table, containing
 * the name of the symbol, its kind/type, and a precomputed hash for efficient lookup.
 */
struct Symbol
{
    SymbolType type;     /** Type of the symbol (e.g., function, variable, type) */
    const char *name;    /** Pointer to the name of the symbol (null-terminated string) */
    size_t hash;         /** Precomputed hash of the symbol's name for quick comparisons */
    SymbolValue value;   /** Union of different symbol value types */
};

/**
 * @struct FunctionValue
 * @brief Represents function-specific information for a symbol.
 * 
 * This structure holds the arity (number of parameters) and arrays of return
 * and parameter types for a function symbol.
 */
struct FunctionValue
{
    CmcType **returnTypes; /** Array of return types of the function */
    size_t returnCount;    /** Number of return types (if applicable) */
    CmcType **paramTypes;  /** Array of parameter types (if applicable) */
    size_t arity;          /** Number of parameters the function takes */
};

/**
 * @brief Creates a new symbol for a variable.
 *
 * Allocates memory for a Symbol and initializes its fields.
 *
 * @param arena Memory arena used for allocation.
 * @param name Name of the variable (null-terminated string).
 * @param type Type of the variable.
 * @param hash Precomputed hash of the variable name.
 * @return Pointer to the newly created Symbol, or NULL if allocation fails.
 */
Symbol *symbol_variable_create(Arena *arena, const char *name, CmcType *type);

/**
 * @brief Creates a new symbol for a function.
 * 
 * Allocates memory for a Symbol and initializes its fields.
 * 
 * @param arena Memory arena used for allocation.
 * @param name Name of the function (null-terminated string).
 * @param functionValue Pointer to FunctionValue containing function-specific information.
 * @return Pointer to the newly created Symbol, or NULL if allocation fails.
 */
Symbol *symbol_function_create(Arena *arena, const char *name, FunctionValue *functionValue);

/**
 * @brief Creates a new symbol for an enum constant.
 * 
 * Allocates memory for a Symbol and initializes its fields.
 * 
 * @param arena Memory arena used for allocation.
 * @param name Name of the enum constant (null-terminated string).
 * @return Pointer to the newly created Symbol, or NULL if allocation fails.
 */
Symbol *symbol_enum_constant_create(Arena *arena, const char *name);

/**
 * @brief Creates a new symbol for a label.
 * 
 * Allocates memory for a Symbol and initializes its fields.
 * 
 * @param arena Memory arena used for allocation.
 * @param name Name of the label (null-terminated string).
 * @return Pointer to the newly created Symbol, or NULL if allocation fails.
 */
Symbol *symbol_label_create(Arena *arena, const char *name);

/**
 * @brief Prints a symbol's details to stdout (for debugging).
 *
 * Displays the symbol's name, type, and hash value.
 *
 * @param symbol Pointer to the Symbol to print.
 */
void symbol_print(const Symbol *symbol);

#endif // SYMBOL_H