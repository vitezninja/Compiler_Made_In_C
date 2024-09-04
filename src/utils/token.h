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
 *   - `TOKEN_PLUS_EQUALS`   // Addition assignment (+=)
 *   - `TOKEN_MINUS_EQUALS`  // Subtraction assignment (-=)
 *   - `TOKEN_STAR_EQUALS`   // Multiplication assignment (*=)
 *   - `TOKEN_SLASH_EQUALS`  // Division assignment (/=)
 *   - `TOKEN_PERCENT_EQUALS`// Modulus assignment (%=)
 * 
 * - Compound Assignment Operators (Bitwise): Operators for bitwise operations with assignment.
 *   - `TOKEN_BITWISE_LEFT_SHIFT_EQUALS` // Bitwise left shift assignment (<<=)
 *   - `TOKEN_BITWISE_RIGHT_SHIFT_EQUALS`// Bitwise right shift assignment (>>=)
 *   - `TOKEN_BITWISE_AND_EQUALS`        // Bitwise AND assignment (&=)
 *   - `TOKEN_BITWISE_XOR_EQUALS`         // Bitwise XOR assignment (^=)
 *   - `TOKEN_BITWISE_OR_EQUALS`          // Bitwise OR assignment (|=)
 * 
 * - Comparison Operators: Operators for comparing values.
 *   - `TOKEN_EQUALS`                // Assignment (=)
 *   - `TOKEN_DOUBLE_EQUALS`         // Equality (==)
 *   - `TOKEN_NOT_EQUALS`            // Inequality (!=)
 *   - `TOKEN_LESS_THAN`             // Less than (<)
 *   - `TOKEN_GREATER_THAN`          // Greater than (>)
 *   - `TOKEN_LESS_THAN_OR_EQUALS`    // Less than or equal (<=)
 *   - `TOKEN_GREATER_THAN_OR_EQUALS` // Greater than or equal (>=)
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
    TOKEN_PLUS_EQUALS,
    TOKEN_MINUS_EQUALS,
    TOKEN_STAR_EQUALS,
    TOKEN_SLASH_EQUALS,
    TOKEN_PERCENT_EQUALS,

    // Compound Assignment Operators (Bitwise):
    TOKEN_BITWISE_LEFT_SHIFT_EQUALS,
    TOKEN_BITWISE_RIGHT_SHIFT_EQUALS,
    TOKEN_BITWISE_AND_EQUALS,
    TOKEN_BITWISE_XOR_EQUALS,
    TOKEN_BITWISE_OR_EQUALS,

    // Comparison Operators:
    TOKEN_EQUALS,
    TOKEN_DOUBLE_EQUALS,
    TOKEN_NOT_EQUALS,
    TOKEN_LESS_THAN,
    TOKEN_GREATER_THAN,
    TOKEN_LESS_THAN_OR_EQUALS,
    TOKEN_GREATER_THAN_OR_EQUALS,

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
 * Enum representing various reserved keywords in the language.
 * 
 * The `Keywords` enum defines a set of reserved keywords that are used in the language's syntax. 
 * Each value in this enum corresponds to a specific keyword that has a predefined meaning in the language. 
 * Keywords are fundamental components of the language and cannot be used as identifiers or variable names.
 * 
 * The enum values are categorized into different groups based on their usage:
 * 
 * - **Storage Class Specifiers**: Keywords that specify the storage duration and visibility of variables.
 *   - `TOKEN_KEYWORD_TYPEDEF`   // Defines a new type name.
 *   - `TOKEN_KEYWORD_EXTERN`    // Declares variables or functions that are defined in other translation units.
 *   - `TOKEN_KEYWORD_STATIC`    // Defines variables with static storage duration.
 *   - `TOKEN_KEYWORD_AUTO`      // Declares automatic variables (default storage class).
 *   - `TOKEN_KEYWORD_REGISTER`  // Requests that a variable be stored in a CPU register.
 * 
 * - **Type Specifiers**: Keywords that define various data types.
 *   - `TOKEN_KEYWORD_VOID`      // Represents an absence of type.
 *   - `TOKEN_KEYWORD_CHAR`      // Represents character type.
 *   - `TOKEN_KEYWORD_STRING`    // Represents string type.
 *   - `TOKEN_KEYWORD_SHORT`     // Represents short integer type.
 *   - `TOKEN_KEYWORD_INT`       // Represents integer type.
 *   - `TOKEN_KEYWORD_LONG`      // Represents long integer type.
 *   - `TOKEN_KEYWORD_FLOAT`     // Represents floating-point type.
 *   - `TOKEN_KEYWORD_DOUBLE`    // Represents double-precision floating-point type.
 *   - `TOKEN_KEYWORD_SIGNED`    // Specifies signed integers.
 *   - `TOKEN_KEYWORD_UNSIGNED`  // Specifies unsigned integers.
 *   - `TOKEN_KEYWORD_STRUCT`    // Defines a structure.
 *   - `TOKEN_KEYWORD_UNION`     // Defines a union.
 *   - `TOKEN_KEYWORD_CONST`     // Indicates that a variable's value cannot be changed.
 *   - `TOKEN_KEYWORD_RESTRICT`  // Indicates that a pointer is the only reference to an object.
 *   - `TOKEN_KEYWORD_VOLATILE`  // Indicates that a variable may be changed by external factors.
 *   - `TOKEN_KEYWORD_SIZEOF`    // Returns the size of a data type or object.
 *   - `TOKEN_KEYWORD_ENUM`      // Defines an enumeration.
 *   - `TOKEN_KEYWORD_INLINE`    // Suggests that a function should be inlined.
 * 
 * - **Control Flow Keywords**: Keywords used for controlling the flow of execution.
 *   - `TOKEN_KEYWORD_CASE`      // Marks a branch in a switch statement.
 *   - `TOKEN_KEYWORD_DEFAULT`   // Specifies the default branch in a switch statement.
 *   - `TOKEN_KEYWORD_IF`        // Starts a conditional statement.
 *   - `TOKEN_KEYWORD_ELSE`      // Specifies an alternative branch in an if statement.
 *   - `TOKEN_KEYWORD_SWITCH`    // Starts a switch statement.
 *   - `TOKEN_KEYWORD_WHILE`     // Starts a while loop.
 *   - `TOKEN_KEYWORD_DO`        // Starts a do-while loop.
 *   - `TOKEN_KEYWORD_FOR`       // Starts a for loop.
 *   - `TOKEN_KEYWORD_GOTO`      // Transfers control to a labeled statement.
 *   - `TOKEN_KEYWORD_CONTINUE`  // Skips the remaining statements in a loop iteration.
 *   - `TOKEN_KEYWORD_BREAK`     // Exits from a loop or switch statement.
 *   - `TOKEN_KEYWORD_RETURN`    // Exits from a function and optionally returns a value.
 */
typedef enum keywords
{
    KEYWORD_TYPEDEF,
    KEYWORD_EXTERN,
    KEYWORD_STATIC,
    KEYWORD_AUTO,
    KEYWORD_REGISTER,
    KEYWORD_VOID,
    KEYWORD_CHAR,
    KEYWORD_STRING,
    KEYWORD_SHORT,
    KEYWORD_INT,
    KEYWORD_LONG,
    KEYWORD_FLOAT,
    KEYWORD_DOUBLE,
    KEYWORD_SIGNED,
    KEYWORD_UNSIGNED,
    KEYWORD_STRUCT,
    KEYWORD_UNION,
    KEYWORD_CONST,
    KEYWORD_RESTRICT,
    KEYWORD_VOLATILE,
    KEYWORD_SIZEOF,
    KEYWORD_ENUM,
    KEYWORD_INLINE,
    KEYWORD_CASE,
    KEYWORD_DEFAULT,
    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_SWITCH,
    KEYWORD_WHILE,
    KEYWORD_DO,
    KEYWORD_FOR,
    KEYWORD_GOTO,
    KEYWORD_CONTINUE,
    KEYWORD_BREAK,
    KEYWORD_RETURN,
    KEYWORD_NOT_KEYWORD = -1,
} Keywords;

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
 * - `keyword`: A constant value from the `Keywords` enumeration representing keyword tokens.
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
    Keywords keyword;     /**Constant keyword value for keyword tokens. */
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
 * Creates a new `Token` with the given text, start position, type, and keyword value.
 * 
 * This function creates a `Token` specifically for keywords. It assumes that `text` is dynamically
 * allocated by the caller and takes ownership of it. The `Token` will be responsible for freeing 
 * the `text` when it is no longer needed.
 * 
 * The `keyword` value is directly assigned to the `Token` structure as part of its `TokenValue`.
 * 
 * If the allocation for the `Token` fails, the function will free the `text` and return `NULL`.
 * 
 * @param text     The text to be associated with the token (assumed to be dynamically allocated).
 * 
 * @param start    The starting position of the token in the source code.
 * 
 * @param type     The type of the token, which should be `TOKEN_KEYWORD` for keyword tokens.
 * 
 * @param keyword  The `Keywords` enum value representing the specific keyword for the token.
 * 
 * @return A pointer to the created `Token`, or `NULL` if allocation fails.
 * 
 * @note If the allocation for the `Token` structure fails, this function will free the dynamically 
 *       allocated `text` to avoid memory leaks.
 * 
 * @note The caller is responsible for cleaning up the memory allocated for the `Token` object. 
 *       This should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
Token *createTokenKeyword(const char *const text, const int start, const TokenType type, const Keywords keyword);

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
 * Checks if the given input string is a reserved keyword.
 * 
 * This function compares the input string against a pre-defined list of reserved keywords. 
 * It determines if the input string matches any of the keywords and returns the corresponding 
 * `Keywords` enum value if a match is found. If the input does not match any keyword, it returns 
 * `TOKEN_KEYWORD_NOT_KEYWORD` to indicate that the string is not a recognized keyword.
 * 
 * @param input The string to be checked. It should not be NULL.
 * 
 * @return A `Keywords` enum value representing the matched keyword if the input is a keyword; 
 *         `TOKEN_KEYWORD_NOT_KEYWORD` if the input does not match any keyword.
 * 
 * @note If the input string is NULL, the function returns `TOKEN_KEYWORD_NOT_KEYWORD`.
 */
Keywords isKeyword(const char *const input);

#endif // TOKEN_H