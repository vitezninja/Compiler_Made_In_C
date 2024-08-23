#include "my_string.h"

/*****************************************************************************************************
                            PRIVATE MY_STRING FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/


/*****************************************************************************************************
                                PRIVATE MY_STRING FUNCTIONS START HERE
 *****************************************************************************************************/

/*****************************************************************************************************
                                PUBLIC MY_STRING FUNCTIONS START HERE                                
 *****************************************************************************************************/

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
char *substring(const char *const from, const int start, const int end)
{
    int length = strlen(from);
    if (from == NULL || start < 0 || start >= length || end > length || end < start)
    {
        fprintf(stderr, "Invalid substring range or NULL input.\n");
        return NULL;
    }
    
    char *text = (char *)malloc((end - start + 1) * sizeof(char));
    if (text == NULL)
    {
        fprintf(stderr, "Memory allocation for substring failed.\n");
        return NULL;
    }

    strncpy(text, from + start, end - start);
    text[end - start] = '\0';
    return text;
}

/**
 * Converts an escape sequence string to its corresponding character.
 *
 * @param input The escape sequence string in the format `"\\{char}"`.
 * 
 * @return The corresponding character, or `'\0'` if an error occurs.
 */
char convertEscapeString(const char *const input)
{
    if (input == NULL || strlen(input) != 2 || input[0] != '\\')
    {
        fprintf(stderr, "Invalid escape string format.\n");
        return '\0';
    }

    switch (input[1])
    {
    case 'a':
        return '\a';
    case 'b':
        return '\b';
    case 'e':
        return '\e';
    case 'f':
        return '\f';
    case 'n':
        return '\n';
    case 'r':
        return '\r';
    case 't':
        return '\t';
    case 'v':
        return '\v';
    case '\\':
        return '\\';
    case '\'':
        return '\'';
    case '\"':
        return '\"';
    case '?':
        return '\?';
    default:
        fprintf(stderr, "Unknown escape character: %c\n", input[1]);
        return '\0';
    }
}