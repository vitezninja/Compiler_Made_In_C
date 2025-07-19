/**
 * @file token.h
 * @brief Header file for the Token structure and related functions.
 * 
 * This file defines the Token structure used to represent tokens in the compiler's lexer.
 * It includes enumerations for token types, a union for token values, and functions for creating and managing tokens.
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdalign.h>
#include <string.h>
#include <errno.h>

typedef union TokenValue TokenValue;
typedef struct Token Token;

#include "utils/logger.h"
#include "utils/arena.h"
#include "utils/location.h"

/**
 * @enum My_TokenType
 * @brief Enumerates all token types recognized by the lexer.
 *
 * Includes operators, literals, keywords, punctuation, and special markers like EOF and UNKNOWN.
 * Keyword range is delimited by TOKEN_KEYWORD_FIRST and TOKEN_KEYWORD_LAST for classification.
 */
typedef enum My_TokenType
{
    // Arithmetic Operators:
    TOKEN_PLUS,                         /** + */
    TOKEN_DOUBLE_PLUS,                  /** ++ */
    TOKEN_MINUS,                        /** - */
    TOKEN_DOUBLE_MINUS,                 /** -- */
    TOKEN_STAR,                         /** * */
    TOKEN_SLASH,                        /** / */
    TOKEN_PERCENT,                      /** % */

    // Compound Assignment Operators (Arithmetic):
    TOKEN_PLUS_EQUALS,                  /** += */
    TOKEN_MINUS_EQUALS,                 /** -= */
    TOKEN_STAR_EQUALS,                  /** *= */
    TOKEN_SLASH_EQUALS,                 /** /= */
    TOKEN_PERCENT_EQUALS,               /** %= */

    // Compound Assignment Operators (Bitwise):
    TOKEN_DOUBLE_LESS_THAN_EQUALS,      /** <<= */
    TOKEN_DOUBLE_GREATER_THAN_EQUALS,   /** >>= */
    TOKEN_AMPERSAND_EQUALS,             /** &= */
    TOKEN_CARET_EQUALS,                 /** ^= */
    TOKEN_PIPE_EQUALS,                  /** |= */

    // Comparison Operators:
    TOKEN_EQUALS,                       /** = */
    TOKEN_DOUBLE_EQUALS,                /** == */
    TOKEN_EXCLAMATION_EQUALS,           /** != */
    TOKEN_LESS_THAN,                    /** < */
    TOKEN_GREATER_THAN,                 /** > */
    TOKEN_LESS_THAN_EQUALS,             /** <= */
    TOKEN_GREATER_THAN_EQUALS,          /** >= */

    // Logical Operators:
    TOKEN_DOUBLE_AMPERSAND,             /** && */
    TOKEN_DOUBLE_PIPE,                  /** || */
    TOKEN_EXCLAMATION,                  /** ! */

    // Bitwise Operators:
    TOKEN_AMPERSAND,                    /** & */
    TOKEN_PIPE,                         /** | */
    TOKEN_CARET,                        /** ^ */
    TOKEN_TILDE,                        /** ~ */
    TOKEN_DOUBLE_LESS_THAN,             /** << */
    TOKEN_DOUBLE_GREATER_THAN,          /** >> */

    // Parentheses and Brackets:
    TOKEN_OPEN_PARENTHESIS,             /** ( */
    TOKEN_CLOSE_PARENTHESIS,            /** ) */
    TOKEN_OPEN_BRACKET,                 /** [ */
    TOKEN_CLOSE_BRACKET,                /** ] */
    TOKEN_OPEN_CURLY,                   /** { */  
    TOKEN_CLOSE_CURLY,                  /** } */

    // Literals:
    TOKEN_LITERAL_INTEGER,              /** Integer literal */
    TOKEN_LITERAL_BINARY,               /** Binary literal */
    TOKEN_LITERAL_OCTAL,                /** Octal literal */
    TOKEN_LITERAL_HEXADECIMAL,          /** Hexadecimal literal */
    TOKEN_LITERAL_FLOATINGPOINT,        /** Floating-point literal */
    TOKEN_LITERAL_CHARACTER,            /** Character literal */
    TOKEN_LITERAL_STRING,               /** String literal */
    TOKEN_LITERAL_BOOLEAN,              /** Boolean literal */
    TOKEN_LITERAL_NULL,                 /** Null literal */

    // Identifier:
    TOKEN_IDENTIFIER,                   /** Identifier */

    // Keywords: (range between TOKEN_KEYWORD_FIRST and TOKEN_KEYWORD_LAST)
    TOKEN_KEYWORD_FIRST, // Keep this the first keyword
    TOKEN_KEYWORD_INT_64,               /** int64 */
    TOKEN_KEYWORD_INT_32,               /** int32 */
    TOKEN_KEYWORD_INT_16,               /** int16 */
    TOKEN_KEYWORD_INT_8,                /** int8 */
    TOKEN_KEYWORD_UINT_64,              /** uint64 */
    TOKEN_KEYWORD_UINT_32,              /** uint32 */
    TOKEN_KEYWORD_UINT_16,              /** uint16 */
    TOKEN_KEYWORD_UINT_8,               /** uint8 */
    TOKEN_KEYWORD_FLOAT_64,             /** float64 */
    TOKEN_KEYWORD_FLOAT_32,             /** float32 */
    TOKEN_KEYWORD_CHAR,                 /** char */
    TOKEN_KEYWORD_STRING,               /** string */
    TOKEN_KEYWORD_BOOL,                 /** bool */
    TOKEN_KEYWORD_VOID,                 /** void */
    
    TOKEN_KEYWORD_CONST,                /** const */
    TOKEN_KEYWORD_CONST_PTR,            /** const_ptr */
    TOKEN_KEYWORD_PTR,                  /** ptr */

    TOKEN_KEYWORD_IF,                   /** if */
    TOKEN_KEYWORD_ELSE,                 /** else */
    TOKEN_KEYWORD_ENDIF,                /** endif */
    TOKEN_KEYWORD_SWITCH,               /** switch */
    TOKEN_KEYWORD_CASE,                 /** case */
    TOKEN_KEYWORD_DEFAULT,              /** default */
    
    TOKEN_KEYWORD_FOR,                  /** for */
    TOKEN_KEYWORD_FOREACH,              /** foreach */
    TOKEN_KEYWORD_WHILE,                /** while */
    TOKEN_KEYWORD_DO,                   /** do */
    
    TOKEN_KEYWORD_RETURN,               /** return */
    TOKEN_KEYWORD_CONTINUE,             /** continue */
    TOKEN_KEYWORD_BREAK,                /** break */
    TOKEN_KEYWORD_GOTO,                 /** goto */
    TOKEN_KEYWORD_WHEN,                 /** when */

    TOKEN_KEYWORD_STRUCT,               /** struct */
    TOKEN_KEYWORD_UNION,                /** union */
    TOKEN_KEYWORD_ENUM,                 /** enum */

    TOKEN_KEYWORD_IMPORT,               /** import */
    TOKEN_KEYWORD_FROM,                 /** from */
    TOKEN_KEYWORD_EXPORT,               /** export */
    TOKEN_KEYWORD_LAST, // Keep this the last keyword

    // Punctuation:
    TOKEN_COMMA,                        /** , */
    TOKEN_SEMICOLON,                    /** ; */
    TOKEN_COLON,                        /** : */ 
    TOKEN_DOT,                          /** . */

    // End of File:
    TOKEN_EOF,                          /** End of File */

    // Unknown:
    TOKEN_UNKNOWN,                      /** Unknown token */

    // Total number of token types
    TOKEN_TYPE_COUNT // Keep this last
} My_TokenType;

/**
 * @union TokenValue
 * @brief Holds the value of a literal token.
 *
 * Used only when token type is a literal (e.g., integer, float, char, etc.).
 */
union TokenValue
{
    int64_t int_value;          /** Integer value */
    double float_value;         /** Floating-point value */
    bool boolean_value;         /** Boolean value */
    const char *string_value;   /** String value */
    char char_value;            /** Character value */
};

/**
 * @struct Token
 * @brief Represents a token produced by the lexer.
 *
 * Each token includes its type, the raw source text it represents,
 * its location in the source code, and a union for holding literal values
 * (such as integers, floats, strings, etc.) if applicable.
 */
struct Token
{
    My_TokenType type;          /** Type of the token */
    const char *text;           /** Pointer to the raw text of the token */
    SourceLocation location;    /** Location in the source code */
    TokenValue value;           /** Union value for literals */
};

/**
 * @brief Creates and returns a new Token in the provided arena.
 *
 * This function allocates memory for a Token object and initializes its fields.
 * The `text` pointer should refer to a substring in the source buffer; it is not copied.
 *
 * @param arena   Memory arena used for allocation.
 * @param type    Type of the token (from My_TokenType enum).
 * @param text    Pointer to the beginning of the token in the source buffer.
 * @param location Source location of the token in the source code.
 * @param value   Value union (used only if the token is a literal).
 * @return        Pointer to the newly created Token, or NULL on failure. Set `errno` to indicate the error.
 */
Token *token_create(Arena *arena, My_TokenType type, const char *text, SourceLocation location, TokenValue value);

/**
 * @brief Creates a deep copy of a Token into the provided arena.
 *
 * This function duplicates the token and stores it in the given arena.
 * It is useful when tokens need to be preserved beyond the lifetime of the original buffer.
 *
 * @param arena  Memory arena used for allocation.
 * @param token  Pointer to the token to copy.
 * @return       Pointer to the copied Token, or NULL on failure. Set `errno` to indicate the error.
 */
Token *token_copy(Arena *arena, const Token *token);

/**
 * @brief Prints the token to stdout in a human-readable format (for debugging).
 *
 * Uses the token's `text`, `type`, and position information. This function is
 * typically used during lexical analysis to inspect token streams.
 *
 * @param token Pointer to the Token to print.
 */
void token_print(const Token *token);

/**
 * @brief Returns the keyword token type corresponding to the string.
 *
 * @param str   Null-terminated input string.
 * @return      My_TokenType of keyword, or TOKEN_UNKNOWN if not a keyword.
 */
My_TokenType token_keywordTypeFromString(const char *str);

/**
 * @brief Returns a string representation of a token type.
 *
 * @param type  The My_TokenType enum.
 * @return      Null-terminated string name.
 * 
 * @note The string is statically allocated and should not be freed.
 */
const char *token_typeToString(My_TokenType type);

#endif // TOKEN_H