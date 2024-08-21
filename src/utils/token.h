#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Enum representing the different types of tokens recognized by the lexer.
 * 
 * The `TokenType` enum defines various categories of tokens, including operators, literals,
 * punctuation, whitespace, comments, and special tokens like end of file or unknown. Each
 * value in this enum corresponds to a specific type of token that the lexer can identify.
 * 
 * The enum values are grouped by their functional categories:
 * 
 * - **Arithmetic Operators**: Operators for basic arithmetic operations.
 *   - `TOKEN_PLUS`         // Addition or Identity (+)
 *   - `TOKEN_DOUBLE_PLUS`  // Increment (++)
 *   - `TOKEN_MINUS`        // Subtraction or Negation (-)
 *   - `TOKEN_DOUBLE_MINUS` // Decrement (--)
 *   - `TOKEN_STAR`         // Multiplication (*)
 *   - `TOKEN_SLASH`        // Division (/)
 *   - `TOKEN_PERCENT`      // Modulus (remainder of division) (%)
 * 
 * - **Comparison Operators**: Operators for comparing values.
 *   - `TOKEN_EQUALS`                // Assignment (=)
 *   - `TOKEN_DOUBLE_EQUALS`         // Equality (==)
 *   - `TOKEN_NOT_EQUALS`            // Inequality (!=)
 *   - `TOKEN_LESS_THAN`             // Less than (<)
 *   - `TOKEN_GREATER_THAN`          // Greater than (>)
 *   - `TOKEN_LESS_THAN_OR_EQUAL`    // Less than or equal (<=)
 *   - `TOKEN_GREATER_THAN_OR_EQUAL` // Greater than or equal (>=)
 * 
 * - **Logical Operators**: Operators for logical operations.
 *   - `TOKEN_AND`  // Logical AND (&&)
 *   - `TOKEN_OR`   // Logical OR (||)
 *   - `TOKEN_NOT`  // Logical NOT (!)
 * 
 * - **Bitwise Operators**: Operators for bitwise operations.
 *   - `TOKEN_BITWISE_AND`         // Bitwise AND (&)
 *   - `TOKEN_BITWISE_OR`          // Bitwise OR (|)
 *   - `TOKEN_BITWISE_XOR`         // Bitwise XOR (^)
 *   - `TOKEN_BITWISE_NOT`         // Bitwise NOT (~)
 *   - `TOKEN_BITWISE_LEFT_SHIFT`  // Bitwise left shift (<<)
 *   - `TOKEN_BITWISE_RIGHT_SHIFT` // Bitwise right shift (>>)
 * 
 * - **Parentheses and Brackets**: Tokens representing various types of brackets.
 *   - `TOKEN_OPEN_PARENTHESIS`   // (
 *   - `TOKEN_CLOSE_PARENTHESIS`  // )
 *   - `TOKEN_OPEN_BRACKET`       // [
 *   - `TOKEN_CLOSE_BRACKET`      // ]
 *   - `TOKEN_OPEN_CURLY`         // {
 *   - `TOKEN_CLOSE_CURLY`        // }
 * 
 * - **Literals**: Tokens representing literal values.
 *   - `TOKEN_INTEGER`       // Integer literals
 *   - `TOKEN_FLOATINGPOINT` // Floating-point literals
 *   - `TOKEN_CHARACTER`     // Character literals
 *   - `TOKEN_STRING`        // String literals
 *   - `TOKEN_HEXADECIMAL`   // Hexadecimal literals
 *   - `TOKEN_OCTAL`         // Octal literals
 * 
 * - **Identifier**: Tokens representing variable or function names.
 *   - `TOKEN_IDENTIFIER` // Variable and function names
 * 
 * - **Keywords**: Tokens representing reserved keywords in the language.
 *   - `TOKEN_KEYWORD`   // Reserved keywords in the language
 * 
 * - **Punctuation**: Tokens representing punctuation marks.
 *   - `TOKEN_COMMA`      // ,
 *   - `TOKEN_SEMICOLON`  // ;
 *   - `TOKEN_COLON`      // :
 *   - `TOKEN_DOT`        // .
 *   - `TOKEN_ARROW`      // ->
 * 
 * - **Whitespace**: Tokens representing whitespace characters.
 *   - `TOKEN_WHITESPACE` // Space, tab, newline
 * 
 * - **Comments**: Tokens representing comments in the source code.
 *   - `TOKEN_LINE_COMMENT`  // Single-line comment
 *   - `TOKEN_BLOCK_COMMENT` // Multi-line comment
 * 
 * - **End of File**: Token indicating the end of the input.
 *   - `TOKEN_EOF`     // End of File marker
 * 
 * - **Unknown**: Token for unrecognized or invalid input.
 *   - `TOKEN_UNKNOWN` // Unknown or invalid token
 * 
 * - **Total Token Types**: Total number of token types defined.
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
    int number; /**Constant integer value for numeric tokens. */
    const char *string; /**Pointer to a constant string for text-based tokens. */
    char character; /**Constant single character for character tokens. */
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
    TokenType type; /**The type of the token. */
    TokenValue value; /**The value associated with the token. */
} Token;

Token *createTokenNone(const char *const text, const TokenType type);

Token *createTokenNumber(const char *const text, const TokenType type, const int number);

Token *createTokenString(const char *const text, const TokenType type, const char *const string);

Token *createTokenChar(const char *const text, const TokenType type, const char character);

Token *createTokenFloat(const char *const text, const TokenType type, const double floatingPoint);

void deleteToken(Token *const token);

void deleteTokens(Token **const tokens, const size_t count);

void printToken(const Token *const token);

int isKeyword(const char *const input);

#endif