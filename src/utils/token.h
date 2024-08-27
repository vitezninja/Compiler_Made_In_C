#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Enum representing the different types of tokens recognized by the lexer.
 * 
 * The `TokenType` enum defines various categories of tokens, including operators, literals,
 * punctuation, whitespace, comments, and special tokens such as end of file or unknown. 
 * Each value in this enum corresponds to a specific type of token that the lexer can identify.
 * 
 * The enum values are grouped by their functional categories:
 * 
 * - Arithmetic Operators: Operators for basic arithmetic operations.
 *   - `TOKEN_PLUS`         // Addition or Identity (+)
 *   - `TOKEN_DOUBLE_PLUS`  // Increment (++)
 *   - `TOKEN_MINUS`        // Subtraction or Negation (-)
 *   - `TOKEN_DOUBLE_MINUS` // Decrement (--)
 *   - `TOKEN_STAR`         // Multiplication (*)
 *   - `TOKEN_SLASH`        // Division (/)
 *   - `TOKEN_PERCENT`      // Modulus (remainder of division) (%)
 * 
 * - Compound Assignment Operators (Arithmetic): Operators for arithmetic operations with assignment.
 *   - `TOKEN_PLUS_EQUAL`   // Addition assignment (+=)
 *   - `TOKEN_MINUS_EQUAL`  // Subtraction assignment (-=)
 *   - `TOKEN_STAR_EQUAL`   // Multiplication assignment (*=)
 *   - `TOKEN_SLASH_EQUAL`  // Division assignment (/=)
 *   - `TOKEN_PERCENT_EQUAL`// Modulus assignment (%=)
 * 
 * - Compound Assignment Operators (Bitwise): Operators for bitwise operations with assignment.
 *   - `TOKEN_BITWISE_LEFT_SHIFT_EQUAL` // Bitwise left shift assignment (<<=)
 *   - `TOKEN_BITWISE_RIGHT_SHIFT_EQUAL`// Bitwise right shift assignment (>>=)
 *   - `TOKEN_BITWISE_AND_EQUAL`        // Bitwise AND assignment (&=)
 *   - `TOKEN_BITWISE_XOR_EQUAL`         // Bitwise XOR assignment (^=)
 *   - `TOKEN_BITWISE_OR_EQUAL`          // Bitwise OR assignment (|=)
 * 
 * - Comparison Operators: Operators for comparing values.
 *   - `TOKEN_EQUALS`                // Assignment (=)
 *   - `TOKEN_DOUBLE_EQUALS`         // Equality (==)
 *   - `TOKEN_NOT_EQUALS`            // Inequality (!=)
 *   - `TOKEN_LESS_THAN`             // Less than (<)
 *   - `TOKEN_GREATER_THAN`          // Greater than (>)
 *   - `TOKEN_LESS_THAN_OR_EQUAL`    // Less than or equal (<=)
 *   - `TOKEN_GREATER_THAN_OR_EQUAL` // Greater than or equal (>=)
 * 
 * - Logical Operators: Operators for logical operations.
 *   - `TOKEN_AND`  // Logical AND (&&)
 *   - `TOKEN_OR`   // Logical OR (||)
 *   - `TOKEN_NOT`  // Logical NOT (!)
 * 
 * - Bitwise Operators: Operators for bitwise operations.
 *   - `TOKEN_BITWISE_AND`         // Bitwise AND (&)
 *   - `TOKEN_BITWISE_OR`          // Bitwise OR (|)
 *   - `TOKEN_BITWISE_XOR`         // Bitwise XOR (^)
 *   - `TOKEN_BITWISE_NOT`         // Bitwise NOT (~)
 *   - `TOKEN_BITWISE_LEFT_SHIFT`  // Bitwise left shift (<<)
 *   - `TOKEN_BITWISE_RIGHT_SHIFT` // Bitwise right shift (>>)
 * 
 * - Parentheses and Brackets: Tokens representing various types of brackets.
 *   - `TOKEN_OPEN_PARENTHESIS`   // (
 *   - `TOKEN_CLOSE_PARENTHESIS`  // )
 *   - `TOKEN_OPEN_BRACKET`       // [
 *   - `TOKEN_CLOSE_BRACKET`      // ]
 *   - `TOKEN_OPEN_CURLY`         // {
 *   - `TOKEN_CLOSE_CURLY`        // }
 * 
 * - Literals: Tokens representing literal values.
 *   - `TOKEN_INTEGER`       // Integer literals
 *   - `TOKEN_FLOATINGPOINT` // Floating-point literals
 *   - `TOKEN_CHARACTER`     // Character literals
 *   - `TOKEN_STRING`        // String literals
 *   - `TOKEN_HEXADECIMAL`   // Hexadecimal literals
 *   - `TOKEN_OCTAL`         // Octal literals
 * 
 * - Identifier: Tokens representing variable or function names.
 *   - `TOKEN_IDENTIFIER` // Variable and function names
 * 
 * - Keywords: Tokens representing reserved keywords in the language.
 *   - `TOKEN_KEYWORD`   // Reserved keywords in the language
 * 
 * - Punctuation: Tokens representing punctuation marks.
 *   - `TOKEN_COMMA`      // ,
 *   - `TOKEN_SEMICOLON`  // ;
 *   - `TOKEN_COLON`      // :
 *   - `TOKEN_DOT`        // .
 *   - `TOKEN_ARROW`      // ->
 *   - `TOKEN_QUESTION_MARK` // ?
 * 
 * - Whitespace: Tokens representing whitespace characters.
 *   - `TOKEN_WHITESPACE` // Space, tab, newline
 * 
 * - Comments: Tokens representing comments in the source code.
 *   - `TOKEN_LINE_COMMENT`  // Single-line comment
 *   - `TOKEN_BLOCK_COMMENT` // Multi-line comment
 * 
 * - End of File: Token indicating the end of the input.
 *   - `TOKEN_EOF`     // End of File marker
 * 
 * - Unknown: Token for unrecognized or invalid input.
 *   - `TOKEN_UNKNOWN` // Unknown or invalid token
 * 
 * - Total Token Types: Total number of token types defined.
 *   - `TOKEN_TYPE_COUNT` // Keep this last in the list
 */
typedef enum tokenType
{
    // Arithmetic Operators:
    TOKEN_PLUS,
    TOKEN_DOUBLE_PLUS,
    TOKEN_MINUS,
    TOKEN_DOUBLE_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,

    // Compound Assignment Operators (Arithmetic):
    TOKEN_PLUS_EQUAL,
    TOKEN_MINUS_EQUAL,
    TOKEN_STAR_EQUAL,
    TOKEN_SLASH_EQUAL,
    TOKEN_PERCENT_EQUAL,

    // Compound Assignment Operators (Bitwise):
    TOKEN_BITWISE_LEFT_SHIFT_EQUAL,
    TOKEN_BITWISE_RIGHT_SHIFT_EQUAL,
    TOKEN_BITWISE_AND_EQUAL,
    TOKEN_BITWISE_XOR_EQUAL,
    TOKEN_BITWISE_OR_EQUAL,

    // Comparison Operators:
    TOKEN_EQUALS,
    TOKEN_DOUBLE_EQUALS,
    TOKEN_NOT_EQUALS,
    TOKEN_LESS_THAN,
    TOKEN_GREATER_THAN,
    TOKEN_LESS_THAN_OR_EQUAL,
    TOKEN_GREATER_THAN_OR_EQUAL,

    // Logical Operators:
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,

    // Bitwise Operators:
    TOKEN_BITWISE_AND,
    TOKEN_BITWISE_OR,
    TOKEN_BITWISE_XOR,
    TOKEN_BITWISE_NOT,
    TOKEN_BITWISE_LEFT_SHIFT,
    TOKEN_BITWISE_RIGHT_SHIFT,

    // Parentheses and Brackets:
    TOKEN_OPEN_PARENTHESIS,
    TOKEN_CLOSE_PARENTHESIS,
    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
    TOKEN_OPEN_CURLY,
    TOKEN_CLOSE_CURLY,

    // Literals:
    TOKEN_INTEGER,
    TOKEN_FLOATINGPOINT,
    TOKEN_CHARACTER,
    TOKEN_STRING,
    TOKEN_HEXADECIMAL,
    TOKEN_OCTAL,

    // Identifier:
    TOKEN_IDENTIFIER,

    // Keywords:
    TOKEN_KEYWORD,

    // Punctuation:
    TOKEN_COMMA,
    TOKEN_SEMICOLON,
    TOKEN_COLON,
    TOKEN_DOT,
    TOKEN_ARROW,
    TOKEN_QUESTION_MARK,

    // Whitespace:
    TOKEN_WHITESPACE,

    // Comments:
    TOKEN_LINE_COMMENT,
    TOKEN_BLOCK_COMMENT,

    // End of File:
    TOKEN_EOF,

    // Unknown:
    TOKEN_UNKNOWN,

    // Total number of token types
    TOKEN_TYPE_COUNT // Keep this last
} TokenType;

/**
 * Represents the value associated with a token.
 * 
 * The `TokenValue` union is used to store different types of data that a token can hold,
 * depending on its type. The union provides a flexible way to handle various token values
 * without using multiple distinct structures. It includes the following members:
 * 
 * - `number`: A constant integer value representing numeric tokens. This can be used for tokens
 *              that represent whole numbers.
 * 
 * - `string`: A pointer to a constant string representing text-based tokens. This can be
 *             used for tokens that contain string literals.
 * 
 * - `character`: A constant single character value for tokens that represent individual characters.
 * 
 * - `floatingPoint`: A constant double precision floating-point value for tokens that represent
 *                     floating-point numbers.
 * 
 * The exact member to be used depends on the `TokenType` and the specific needs of the
 * token being represented.
 * 
 * @note Ensure that the correct member of the union is accessed based on the token type.
 *       Misusing the union members can lead to undefined behavior or incorrect data interpretation.
 */
typedef union tokenValue
{
    int number;           /**Constant integer value for numeric tokens. */
    const char *string;   /**Pointer to a constant string for text-based tokens. */
    char character;       /**Constant single character for character tokens. */
    double floatingPoint; /**Constant floating-point value for floating-point tokens. */
} TokenValue;

/**
 * Represents a token in the lexer output.
 * 
 * The `Token` structure encapsulates the details of a single token identified
 * during lexical analysis. It includes the following fields:
 * 
 * - `text`: A pointer to a string that contains the textual representation
 *            of the token. This string is typically dynamically allocated and represents
 *            the content of the token.
 * 
 * - `type`: An enumeration of type `TokenType` that specifies the category or type
 *           of the token (e.g., keyword, operator, identifier).
 * 
 * - `value`: A `TokenValue` union that holds additional data associated with the token.
 *            The type of data in this union depends on the `TokenType` and may include
 *            numeric values, string literals, or other relevant information.
 * 
 * The `Token` struct is used by the lexer and other components to represent and process
 * individual elements of the input text.
 * 
 * @note The caller is responsible for managing the lifecycle of the `Token` object. After use,
 *       the memory allocated for the `Token` and its associated `text` should be released using
 *       the `deleteToken` function (for a single token) or `deleteTokens` function (for multiple tokens).
 */
typedef struct token
{
    const char *text; /**The text of the token. */
    int start;
    size_t length;
    TokenType type;   /**The type of the token. */
    TokenValue value; /**The value associated with the token. */
} Token;

/**
 * Creates a new `Token` with the given text, start position, and type.
 * The token's value is initialized to a default state (zero-initialized).
 *
 * This function assumes that `text` is dynamically allocated by the caller 
 * and takes ownership of it. The `Token` will be responsible for freeing 
 * the `text` when it is no longer needed.
 *
 * @param text The text to be associated with the token (assumed to be dynamically allocated).
 *             If `text` is `NULL`, the function may return a token with a `length` of `0`.
 *
 * @param start The starting position of the token in the source code.
 *
 * @param type The type of the token, indicating its category in the lexical analysis.
 *
 * @return A pointer to the created `Token`, or `NULL` if allocation fails.
 *
 * @note If the `createToken` function fails to allocate the `Token` structure,
 *       this function will free the provided `text` to prevent memory leaks.
 *
 * @note The caller is responsible for cleaning up the memory allocated for the `Token` object. This
 *       should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
Token *createTokenNone(const char *const text, const int start, const TokenType type);

/**
 * Creates a new `Token` with the given text, start position, type, and integer value.
 * 
 * This function assumes that `text` is dynamically allocated by the caller 
 * and takes ownership of it. The `Token` will be responsible for freeing 
 * the `text` when it is no longer needed.
 * 
 * @param text The text to be associated with the token (assumed to be dynamically allocated).
 *             If `text` is `NULL`, the function may still return a token with a `length` of `0`.
 * 
 * @param start The starting position of the token in the source code.
 * 
 * @param type The type of the token, indicating its category in the lexical analysis.
 * 
 * @param number The integer value to be associated with the token.
 * 
 * @return A pointer to the created `Token`, or `NULL` if allocation fails.
 * 
 * @note If the `createToken` function fails to allocate the `Token` structure,
 *       this function will free the provided `text` to prevent memory leaks.
 * 
 * @note The caller is responsible for cleaning up the memory allocated for the `Token` object. This
 *       should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
Token *createTokenNumber(const char *const text, const int start, const TokenType type, const int number);

/**
 * Creates a new `Token` with the given text, start position, type, and string value.
 * 
 * This function assumes that `text` and `string` are dynamically allocated 
 * by the caller and takes ownership of them. The `Token` will be responsible 
 * for freeing the `text` and `string` when they are no longer needed.
 * 
 * The function also allocates memory for a copy of the `string` value.
 * 
 * If the allocation for the `Token` or the `string` fails, the function will 
 * free the `text` and `string` (if applicable) and return `NULL`.
 * 
 * @param text The text to be associated with the token (assumed to be dynamically allocated).
 * 
 * @param start The starting position of the token in the source code.
 * 
 * @param type The type of the token, indicating its category in lexical analysis.
 * 
 * @param string The string value to be associated with the token (assumed to be dynamically allocated).
 * 
 * @return A pointer to the created `Token`, or `NULL` if allocation fails.
 * 
 * @note If the `createToken` function fails to allocate the `Token` structure, 
 *       this function will free both the `text` and `string` to avoid memory leaks.
 * 
 * @note The caller is responsible for cleaning up the memory allocated for the `Token` object. 
 *       This should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
Token *createTokenString(const char *const text, const int start, const TokenType type, const char *const string);

/**
 * Creates a new `Token` with the given text, start position, type, and character value.
 * 
 * This function assumes that `text` is dynamically allocated by the caller and takes
 * ownership of it. The `Token` will be responsible for freeing the `text` when it is
 * no longer needed.
 * 
 * The `character` value is directly assigned to the `Token` structure.
 * 
 * If the allocation for the `Token` fails, the function will free the `text` and return `NULL`.
 * 
 * @param text The text to be associated with the token (assumed to be dynamically allocated).
 * 
 * @param start The starting position of the token in the source code.
 * 
 * @param type The type of the token, indicating its category in lexical analysis.
 * 
 * @param character The character value to be associated with the token.
 * 
 * @return A pointer to the created `Token`, or `NULL` if allocation fails.
 * 
 * @note If the allocation for the `Token` structure fails, this function will free the 
 *       dynamically allocated `text` to avoid memory leaks.
 * 
 * @note The caller is responsible for cleaning up the memory allocated for the `Token` object. 
 *       This should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
Token *createTokenChar(const char *const text, const int start, const TokenType type, const char character);

/**
 * Creates a new `Token` with the given text, start position, type, and floating-point value.
 * 
 * This function assumes that `text` is dynamically allocated by the caller and takes
 * ownership of it. The `Token` will be responsible for freeing the `text` when it is
 * no longer needed.
 * 
 * The `floatingPoint` value is directly assigned to the `Token` structure.
 * 
 * If the allocation for the `Token` fails, the function will free the `text` and return `NULL`.
 * 
 * @param text The text to be associated with the token (assumed to be dynamically allocated).
 * 
 * @param start The starting position of the token in the source code.
 * 
 * @param type The type of the token, indicating its category in lexical analysis.
 * 
 * @param floatingPoint The floating-point value to be associated with the token.
 * 
 * @return A pointer to the created `Token`, or `NULL` if allocation fails.
 * 
 * @note If the allocation for the `Token` structure fails, this function will free the 
 *       dynamically allocated `text` to avoid memory leaks.
 * 
 * @note The caller is responsible for cleaning up the memory allocated for the `Token` object. 
 *       This should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
Token *createTokenFloat(const char *const text, const int start, const TokenType type, const double floatingPoint);

/**
 * Frees the memory associated with a `Token`.
 * 
 * This function assumes that `token` is a valid pointer to a dynamically allocated `Token` structure.
 * It frees the memory allocated for the `text` field and, if the token type is `TOKEN_STRING`,
 * it also frees the memory allocated for the `value.string` field. Finally, it frees the memory
 * allocated for the `Token` structure itself.
 * 
 * @param token A pointer to the `Token` to be freed. If the pointer is NULL, no action is taken.
 */
void deleteToken(Token *const token);

/**
 * Frees an array of dynamically allocated Tokens.
 * 
 * This function assumes that `tokens` is a valid pointer to an array of dynamically allocated `Token`
 * pointers. It iterates over each element of the array and calls `deleteToken` to free each individual
 * Token. After all Tokens have been freed, it frees the memory allocated for the array itself.
 * 
 * @param tokens A pointer to an array of `Token` pointers. If the pointer is NULL, no action is taken.
 * 
 * @param count The number of Tokens in the array.
 */
void deleteTokens(Token **const tokens, const size_t count);

/**
 * Creates a duplicate of an existing `Token`.
 * 
 * This function creates a new `Token` that is a copy of the provided token. 
 * The new `Token` will have the same `text`, `start` position, `type`, and `value`
 * as the original token. The `text` of the new token is not reallocated but 
 * merely referenced, assuming the `text` is dynamically allocated and managed 
 * elsewhere.
 * 
 * If the provided token is `NULL`, the function will return `NULL` and print an error message.
 * If memory allocation for the new token fails, the function will also return `NULL` and print an error message.
 * 
 * @param token A pointer to the `Token` to be duplicated. It must not be `NULL`.
 * 
 * @return A pointer to the newly created duplicate `Token`, or `NULL` if the allocation fails or the input token is `NULL`.
 * 
 * @note The caller is responsible for cleaning up the memory allocated for both the original and duplicate `Token` objects.
 *       This should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
Token *duplicateToken(Token *const token);

/**
 * Prints the representation of a `Token` based on its type.
 * 
 * This function handles various token types and prints their
 * associated values. If the token type is not recognized or if 
 * there is a NULL pointer where it shouldn't be, it prints an 
 * error message.
 * 
 * @param token The `Token` to be printed. This should be a valid pointer to a `Token` structure.
 */
void printToken(const Token *const token);

/**
 * Retrieves the string representation of a given `TokenType`.
 * 
 * This function maps a `TokenType` enumeration value to its corresponding
 * string representation. It returns a string that describes the type of the token.
 * If the provided `TokenType` is invalid (i.e., not within the defined range), 
 * the function returns the string `"UNKNOWN"`.
 * 
 * @param type The `TokenType` value for which the string representation is requested.
 *              It should be a valid `TokenType` within the range of defined types.
 * 
 * @return A string representing the `TokenType`. If the type is valid, the corresponding
 *         string from the `tokenTypeStrings` array is returned. If the type is invalid,
 *         the string `"UNKNOWN"` is returned.
 */
char *getType(TokenType type);

/**
 * Checks if the given input string is a keyword.
 *
 * This function compares the input string against a pre-defined list of keywords.
 * It returns 1 if the input matches any of the keywords, and 0 otherwise.
 *
 * @param input The string to be checked. It should be non-NULL.
 * 
 * @return 1 if the input is a keyword, 0 otherwise.
 */
int isKeyword(const char *const input);

#endif