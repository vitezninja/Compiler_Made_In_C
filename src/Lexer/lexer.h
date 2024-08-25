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
 * - `input`: A pointer to a constant string that contains the text to be lexically analyzed. 
 *            The input string is not modified by the lexer.
 * 
 * - `charCount`: The total number of characters in the input string.
 * 
 * - `position`: The current position (index) in the input string from which the lexer is reading.
 * 
 * The `Lexer` struct is used by various functions to perform lexical analysis, including tokenizing and character consumption.
 * 
 * @note The caller is responsible for managing the lifecycle of the `Lexer` object. After use, the memory allocated for the
 *       `Lexer` should be released using the `deleteLexer` function.
 */
typedef struct lexer
{
    int tokenStartingPos;
    const char *input; /** Pointer to the constant input string to be analyzed. */
    size_t charCount;  /** Total number of characters in the input string. */
    size_t position;   /** Current position (index) in the input string. */
    Error **errors;
    size_t errorCount;
    size_t errorsSize;
} Lexer;

Lexer *createLexer(const char *const input);

void deleteLexer(Lexer *const lexer);

Token *lex(Lexer *const lexer);

#endif