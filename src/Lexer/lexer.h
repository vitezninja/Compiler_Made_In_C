#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../utils/token.h"
#include "../utils/my_string.h"
#include "../utils/error.h"

/**
 * Represents a lexical analyzer (lexer) for processing input text.
 * 
 * The `Lexer` structure holds the state and input necessary for tokenizing text.
 * It includes the following fields:
 * 
 * - `tokenStartingPos`: The starting position (index) of the current token being processed in the input string.
 * 
 * - `input`: A pointer to a constant string that contains the text to be lexically analyzed. 
 *            The input string is not modified by the lexer.
 * 
 * - `charCount`: The total number of characters in the input string.
 * 
 * - `position`: The current position (index) in the input string from which the lexer is reading.
 * 
 * - `errors`: An array of pointers to `Error` objects representing any lexical errors encountered during analysis.
 * 
 * - `errorCount`: The number of errors currently stored in the `errors` array.
 * 
 * - `errorsSize`: The allocated size of the `errors` array. This may be larger than `errorCount` to accommodate additional errors.
 * 
 * The `Lexer` struct is used by various functions to perform lexical analysis, including tokenizing and character consumption.
 * 
 * @note The caller is responsible for managing the lifecycle of the `Lexer` object. After use, the memory allocated for the
 *       `Lexer`, including any errors stored, should be released using the `deleteLexer` function.
 */
typedef struct lexer
{
    int tokenStartingPos;
    const char *input;      /** Pointer to the constant input string to be analyzed. */
    size_t charCount;       /** Total number of characters in the input string. */
    size_t position;        /** Current position (index) in the input string. */
    Error **errors;         /** Array of pointers to `Error` objects representing lexical errors. */
    size_t errorCount;      /** Number of errors currently stored in the `errors` array. */
    size_t errorsSize;      /** Allocated size of the `errors` array. */
} Lexer;

/**
 * Creates a new `Lexer` object.
 * 
 * Allocates memory for a `Lexer` structure and initializes it with a copy of the provided input string.
 * The function duplicates the input string and calculates its length to set up the lexer.
 * 
 * @param input A pointer to the input string to be used by the lexer. This string is copied and managed by
 *              the newly created `Lexer` object. The input string must not be NULL.
 * 
 * @return A pointer to the newly created `Lexer` object, or `NULL` if memory allocation fails or the input
 *         string is NULL. The returned `Lexer` object is initialized with:
 * 
 *         - `tokenStartingPos`: Set to `0`.
 * 
 *         - `input`: A copy of the provided input string.
 * 
 *         - `charCount`: The length of the input string.
 * 
 *         - `position`: Initialized to `0`, indicating the starting position in the input string.
 * 
 *         - `errorsSize`: Initialized to `10`, the initial capacity for storing errors.
 * 
 *         - `errors`: Pointer to an array of `Error` pointers, allocated to hold `errorsSize` errors.
 * 
 *         - `errorCount`: Initialized to `0`, indicating no errors have been recorded yet.
 * 
 * @note The caller is responsible for managing the lifecycle of the `Lexer` object. When the `Lexer` is
 *       no longer needed, it should be cleaned up using the `deleteLexer` function to free all allocated memory.
 * 
 * @note If the `input` parameter is `NULL`, the function prints an error message and returns `NULL`.
 *       If memory allocation for the `Lexer` or its input fails, appropriate error messages are printed, and
 *       `NULL` is returned.
 */
Lexer *createLexer(const char *const input);

/**
 * Deletes a `Lexer` object and frees its associated memory.
 * 
 * This function deallocates memory used by the `Lexer` structure, including:
 * 
 * - The input string (`input`).
 * 
 * - The array of error pointers (`errors`).
 * 
 * It also calls `deleteErrors` to clean up the individual `Error` objects stored in the `errors` array.
 * 
 * @param lexer A pointer to the `Lexer` object to be deleted. If `lexer` is `NULL`, the function does nothing.
 */
void deleteLexer(Lexer *const lexer);

/**
 * Tokenizes the next input segment from the lexer.
 * 
 * This function attempts to create a token for various types of input encountered in the source code, including:
 * 
 * - Simple cases: Operators and delimiters (e.g., `+`, `-`, `*`, `/`, `;`, `(`, etc.).
 * 
 * - Numeric literals: Integer and floating-point numbers.
 * 
 * - Characters: Single characters enclosed in quotes.
 * 
 * - Strings: Sequences of characters enclosed in double quotes.
 * 
 * - Identifiers and keywords: Variable names and reserved words.
 * 
 * - Whitespace: Spaces, tabs, and newlines (which are generally ignored for tokenization purposes).
 * 
 * - Comments: Single-line (`//`) and multi-line (`/ * ... * /`) comments which are removed from the token stream.
 * 
 * If none of these cases apply, the function defaults to returning an unknown token.
 * 
 * @param lexer Pointer to the `Lexer` object that provides access to the input source code stream.
 *              The `Lexer` must be initialized and properly set up before being passed to this function.
 * 
 * @return A pointer to a `Token` object representing the next token in the input. If the lexer is `NULL`,
 *         if memory allocation fails, or if no valid token is identified, the function returns `NULL`.
 * 
 * @note The caller is responsible for managing the memory allocated for the `Token` object. This should be
 *       done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 * 
 * @note The function updates the starting position of the next token using `updateStartingPos` after token creation.
 */
Token *lex(Lexer *const lexer);

#endif // LEXER_H