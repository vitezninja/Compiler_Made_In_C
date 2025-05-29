/**
 * @file my_string.h
 * @brief Header file for the String structure and related functions.
 * 
 * This file defines the String structure used to represent strings in the compiler,
 * along with functions for creating, printing, and managing strings.
 */

#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdalign.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

// Forward declaration of the String structure
struct String;

#include "utils/logger.h"
#include "utils/arena.h"

/**
 * @struct String
 * @brief Represents a string with associated metadata.
 *
 * This structure is designed for efficient string handling within
 * the compiler.
 */
typedef struct String
{
    char *name;     /** Pointer to the character data of the string */
    size_t length;  /** Length of the string in bytes (excluding null terminator) */
    size_t hash;    /** Precomputed hash value of the string for quick comparisons */
} String;

/**
 * @brief Creates and initializes a new String in the given arena.
 *
 * This function copies the provided string data into the arena,
 * sets the length and stores the precomputed hash value.
 *
 * @param arena Arena allocator to use for memory allocation.
 * @param name Pointer to the character data to copy.
 * @param length Length of the character data.
 * @param hash Precomputed hash of the string.
 * @return A pointer to the newly created String, or NULL on failure. Set `errno` to indicate the error.
 */
String *string_create(Arena *arena, const char *name, size_t length, size_t hash);

/**
 * @brief Prints the string to standard output (for debugging).
 *
 * This function prints the raw string data as well as its length and hash.
 *
 * @param string Pointer to the String to print.
 */
void string_print(const String *string);

#endif // MY_STRING_H