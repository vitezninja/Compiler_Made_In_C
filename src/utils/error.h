#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include "token.h"

/**
 * Represents the type of an error.
 * 
 * The `ErrorType` enumeration defines the possible types of errors that can occur during parsing or processing.
 * 
 * - `ERROR_LEXING`: An error occurred during lexing.
 * - `ERROR_PARSING`: An error occurred during parsing.
 * - `ERROR_VALIDATION`: An error occurred during validation.
 */
typedef enum errorType
{
    ERROR_LEXING,   /** An error occurred during lexing. */
    ERROR_PARSING,  /** An error occurred during parsing. */
    ERROR_VALIDATION, /** An error occurred during validation. */
} ErrorType;

/**
 * Represents an error encountered during parsing or processing.
 * 
 * The `Error` structure encapsulates information about an error, including its type,
 * a descriptive message, and an optional token associated with the error.
 * 
 * - `type`: The type of the error, defined by the `ErrorType` enumeration.
 * - `message`: A string containing a descriptive message about the error. This is a constant string.
 * - `errorToken`: A pointer to the `Token` associated with the error, if applicable. This can be NULL if no specific token is related to the error.
 */
typedef struct error
{
    ErrorType type;             /** The type of the error */
    const char *message;        /** Descriptive message about the error. */
    const Token *errorToken;    /** The token associated with the error, if any. */
} Error;

/**
 * Creates a new Error object.
 *
 * This function creates a new Error object with the specified type, message, and token.
 *
 * @param type The type of the error.
 * 
 * @param message The error message.
 * 
 * @param token The token associated with the error (optional).
 * 
 * @return A pointer to the newly created Error object, or NULL if memory allocation fails or the message is NULL.
 * 
 * @note It is the caller's responsibility to free the returned Error object by calling `deleteError` or `deleteErrors`.
 */
Error *createError(const ErrorType type, const char *const message, const Token *const token);

/**
 * Deletes an Error object.
 *
 * This function deletes the specified Error object.
 *
 * @param error The Error object to delete.
 */
void deleteError(Error *error);

/**
 * Deletes an array of Error objects.
 *
 * This function deletes the specified array of Error objects.
 *
 * @param errors The array of Error objects to delete.
 * 
 * @param count The number of Error objects in the array.
 */
void deleteErrors(Error **errors, const size_t count);

/**
 * Prints an Error object.
 *
 * This function prints the specified Error object.
 *
 * @param error The Error object to print.
 */
void printError(const Error *const error);

#endif // ERROR_H