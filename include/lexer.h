/**
 * @file lexer.h
 * @brief Header file for the lexer module.
 * 
 * This file defines the Lexer structure and functions for lexing source code.
 * It includes functions for creating a lexer, lexing source code, handling tokens,
 * and managing errors. The lexer processes the source code character by character,
 */

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <errno.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

typedef struct Lexer Lexer;

#include "utils/logger.h"
#include "utils/token.h"
#include "utils/arena.h"
#include "utils/linkedList.h"
#include "utils/error.h"
#include "utils/location.h"

/**
 * @brief The size of the text buffer used by the lexer.
 */
#define TEXT_BUFFER_SIZE 256

/**
 * @brief The lexer structure.
 * 
 * This structure holds the state of the lexer, including the source code being lexed,
 * the current position in the source code, and the arenas used for memory allocation.
 * It also contains linked lists for errors and tokens, and a hash table for string interning
 * to optimize memory usage for strings.
 * 
 * The lexer processes the source code character by character, identifying tokens such as keywords,
 * identifiers, literals (strings, characters, numbers), and operators. It also handles whitespace
 * and comments, ensuring that they do not interfere with token recognition.
 * * The lexer is designed to be efficient and to minimize memory allocations by using arenas for
 * token storage and string interning.
 * 
 * @note The lexer assumes that the source code is provided as a null-terminated string.
 * @note The lexer does not handle Unicode characters; it operates on ASCII characters.
 */
struct Lexer
{
    Arena *utilsArena;                  /** Arena for utility allocations, such as errors and tokens */
    Arena *tokenArena;                  /** Arena for token allocations, used to store tokens created during lexing */
    LinkedList *error;                  /** Linked list of errors encountered during lexing */
    LinkedList *tokens;                 /** Linked list of tokens generated during lexing */
    HashTable *stringInterningTable;    /** Hash table for string interning to optimize memory usage */
    const char *fileName;               /** The name of the source file being lexed */
    const char *sourceBuffer;           /** Pointer to the source code buffer being lexed */
    size_t sourceBufferSize;            /** Size of the source code buffer in bytes */
    size_t currentPosition;             /** Current position in the source code buffer */
    size_t currentLineStart;            /** Start position of the current line in the source code buffer */
    size_t line;                        /** Current line number in the source code (1-based index) */
    size_t column;                      /** Current column number in the source code (1-based index) */
};

/**
 * @brief Creates a new lexer instance.
 * 
 * This function initializes a new Lexer structure with the provided parameters.
 * It allocates memory for the lexer using the specified arenas and initializes
 * its fields to prepare it for lexing the source code.
 * 
 * @param utilsArena The arena used for utility allocations, such as errors and tokens.
 * @param tokenArena The arena used for token allocations.
 * @param stringInterningTable The hash table used for string interning.
 * @param fileName The name of the source file being lexed.
 * @param sourceBuffer Pointer to the source code buffer being lexed.
 * @param sourceBufferSize Size of the source code buffer in bytes.
 * @return A pointer to the newly created Lexer instance, or NULL if an error occurred.
 */
Lexer *lexer_create(Arena *utilsArena, Arena *tokenArena, HashTable *stringInterningTable, const char *fileName, const char *sourceBuffer, size_t sourceBufferSize);

/**
 * @brief Lexes the source code and generates tokens.
 * 
 * This function processes the source code character by character, identifying
 * tokens such as keywords, identifiers, literals (strings, characters, numbers),
 * and operators. It also handles whitespace and comments, ensuring that they do
 * not interfere with token recognition.
 * 
 * The function updates the lexer state, including the current position, line,
 * and column numbers, as it processes the source code.
 * 
 * @param lexer The lexer instance to be used for lexing.
 */
void lexer_lex(Lexer* lexer);

/**
 * @brief Prints the current state of the lexer.
 * 
 * This function outputs the internal state of the lexer, including the arenas used,
 * the list of tokens generated, the string interning table, and the current position
 * in the source code. It is useful for debugging purposes to understand how the lexer
 * is processing the source code.
 * 
 * @param lexer The lexer instance to be printed.
 */
void lexer_print(const Lexer* lexer);

#endif // LEXER_H