#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * Returns a substring of the input string from start to end.
 * 
 * This function extracts a portion of the input string starting from the `start` index (inclusive)
 * and ending at the `end` index (exclusive). It returns a new dynamically allocated string containing
 * the requested substring.
 * 
 * @param from The input string.
 * 
 * @param start The start index (inclusive).
 * 
 * @param end The end index (exclusive).
 * 
 * @return A new string containing the substring, or NULL if an error occurs.
 * 
 * @note The caller is responsible for freeing the dynamically allocated string returned by this function.
 */
char *substring(const char *const string, const int start, const int end);

/**
 * Converts an escape sequence string to its corresponding character.
 *
 * @param input The escape sequence string in the format `"\\{char}"`.
 * 
 * @return The corresponding character, or `'\0'` if an error occurs.
 */
char convertEscapeString(const char *const input);

int covertStringToPreHash(const char *const input);

#endif // MY_STRING_H