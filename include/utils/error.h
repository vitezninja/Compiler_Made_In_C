/**
 * @file error.h
 * @brief Header file for error handling in the compiler.
 * 
 * This file defines the Error structure and functions for creating, printing,
 * and managing errors and warnings encountered during the compilation process.
 */

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdalign.h>
#include <errno.h>

// Forward declaration of the Error structure
struct Error;

#include "utils/logger.h"
#include "utils/arena.h"

/**
 * @enum ErrorType
 * @brief Enumeration of error severity types.
 *
 * Represents the severity level of an error encountered during compilation.
 */
typedef enum ErrorType
{
    ERROR_WARNING, /** Non-critical warning that doesn't stop compilation. */
    ERROR_ERROR,   /** Compilation error that prevents further processing. */
    ERROR_FATAL,   /** Serious error that should terminate the compiler. */
} ErrorType;

/**
 * @struct Error
 * @brief Structure representing a single compilation error or warning.
 *
 * The Error structure is used to describe a specific issue encountered during
 * lexing, parsing, or other stages of compilation.
 */
typedef struct Error
{
    ErrorType type;             /** Severity/type of the error. */
    size_t length;              /** Length of the error span in bytes. */
    size_t line;                /** Line number in the source code where the error occurred. */
    size_t column;              /** Column number in the source code where the error occurred. */
    const char *message;        /** Human-readable error message. */
} Error;

/**
 * @brief Creates a new error.
 *
 * Allocates a new error using the provided arena.
 *
 * @param arena Memory arena used for allocation.
 * @param type Type/severity of the error.
 * @param length Length of the error span in bytes.
 * @param line Line number in the source code where the error occurred.
 * @param column Column number in the source code where the error occurred.
 * @param message Null-terminated string containing the error message.
 * @return Pointer to the error.
 */
Error *error_create(Arena *arena, ErrorType type, size_t length, size_t line, size_t column, const char *message);

/**
 * @brief Prints a formatted representation of an error to standard output.
 *
 * Prints the details of the error, including its type, length, line, column,
 *
 * @param error Pointer to the error to be printed.
 */
void error_print(const Error *error);

#endif // ERROR_H