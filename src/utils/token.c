#include "token.h"

/*****************************************************************************************************
                            PRIVATE TOKEN FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

/**
 * Count of all the keywords in the lookup table
 */
#define KEYWORDS_COUNT (sizeof(keywords) / sizeof(keywords[0]))

static Token *createToken(const char *const text, const TokenType type, const TokenValue value);

static const char *escapeCharToString(const char escapeChar);

/*****************************************************************************************************
                                PRIVATE TOKEN FUNCTIONS START HERE
 *****************************************************************************************************/

/**
 * Creates a new `Token` with the given text, type, and value.
 * The function allocates memory for the Token structure.
 * 
 * This function assumes that `text` is dynamically allocated 
 * by the caller and takes ownership of it. The `Token` will 
 * be responsible for freeing the `text` when it is no longer needed.
 * 
 * @param text The text to be associated with the token (assumed to be dynamically allocated).
 * 
 * @param type The type of the token.
 * 
 * @param value The value of the token.
 * 
 * @return A pointer to the created `Token`, or NULL if allocation fails.
 * 
 * @note The caller is responsible for cleaning up the memory allocated for the `Token` object. This
 *       should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
static Token *createToken(const char *const text, const TokenType type, const TokenValue value)
{
    Token *token = (Token *)malloc(sizeof(Token));
    if (token == NULL)
    {
        fprintf(stderr, "Memory allocation for Token failed!\n");
        free((char *)text);
        return NULL;
    }

    token->text = text;
    token->type = type;
    token->value = value;

    return token;
}

/**
 * Converts an escape character into its string representation.
 *
 * This function takes a character that represents an escape sequence
 * and returns a string that represents it in the format "\\{char}".
 * If the character is not a recognized escape sequence, it returns NULL.
 * 
 * @param escapeChar The escape character to be converted.
 * 
 * @return A string representing the escape character or NULL if not recognized.
 */
const char *escapeCharToString(const char escapeChar)
{
    switch (escapeChar)
    {
        case '\a':
            return "\\a";
        case '\b':
            return "\\b";
        case '\e':
            return "\\e";
        case '\f':
            return "\\f";
        case '\n':
            return "\\n";
        case '\r':
            return "\\r";
        case '\t':
            return "\\t";
        case '\v':
            return "\\v";
        case '\\':
            return "\\\\";
        case '\'':
            return "\\'";
        case '\"':
            return "\\\"";
        case '\?':
            return "\\?";
        default:
            return NULL;
    }
}

/**
 * Lookup table for keywords
 */
static const char *const keywords[] = 
{
    "break",
    "continue",
    "return",
    "void",
    "int",
    "float",
    "char",
    "string",
    "const",
    "do",
    "while",
    "for",
    "if",
    "else",
    "switch",
    "case",
    "default",
    "goto",
    "enum",
    "struct",
    "union",
};

/**
 * Lookup table for TokenType
 */
static const char *const tokenTypeStrings[] = {
    // Arithmetic Operators:
    "PLUS",
    "MINUS",
    "STAR",
    "SLASH",

    // Comparison Operators:
    "EQUALS",
    "DOUBLE_EQUALS",
    "NOT_EQUALS",
    "LESS_THAN",
    "GREATER_THAN",
    "LESS_THAN_OR_EQUAL",
    "GREATER_THAN_OR_EQUAL",

    // Logical Operators:
    "AND",
    "OR",
    "NOT",

    // Bitwise Operators:
    "BITWISE_AND",
    "BITWISE_OR",
    "BITWISE_XOR",
    "BITWISE_NOT",
    "BITWISE_LEFT_SHIFT",
    "BITWISE_RIGHT_SHIFT",

    // Parentheses and Brackets:
    "OPEN_PARENTHESIS",
    "CLOSE_PARENTHESIS",
    "OPEN_BRACKET",
    "CLOSE_BRACKET",
    "OPEN_CURLY",
    "CLOSE_CURLY",

    // Literals:
    "INTEGER",
    "FLOATINGPOINT",
    "CHARACTER",
    "STRING",
    "HEXAL",
    "OCTAL",

    // Identifier:
    "IDENTIFIER",

    // Keywords:
    "KEYWORD",

    // Punctuation:
    "COMMA",
    "SEMICOLON",
    "COLON",
    "DOT",
    "ARROW",

    // Whitespace:
    "WHITESPACE",

    // Comments:
    "LINE_COMMENT",
    "BLOCK_COMMENT",

    // End of File:
    "EOF",

    // Unknown:
    "UNKNOWN"
};

/*****************************************************************************************************
                                PUBLIC TOKEN FUNCTIONS START HERE                                
 *****************************************************************************************************/

/**
 * Creates a new `Token` with the given text and type. 
 * The token's value is initialized to a default state.
 * 
 * This function assumes that `text` is dynamically allocated 
 * by the caller and takes ownership of it. The `Token` will 
 * be responsible for freeing the `text` when it is no longer needed.
 * 
 * @param text The text to be associated with the token (assumed to be dynamically allocated).
 * 
 * @param type The type of the token.
 * 
 * @return A pointer to the created `Token`, or NULL if allocation fails.
 * 
 * @note The caller is responsible for cleaning up the memory allocated for the `Token` object. This
 *       should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
Token *createTokenNone(const char *const text, const TokenType type)
{
    TokenValue value = {0};

    Token *token = createToken(text, type, value);
    if (token == NULL)
    {
        free((char *)text);
    }

    return token;
}

/**
 * Creates a new `Token` with the given text, type, and integer value.
 * 
 * This function assumes that `text` is dynamically allocated 
 * by the caller and takes ownership of it. The `Token` will 
 * be responsible for freeing the `text` when it is no longer needed.
 * 
 * @param text The text to be associated with the token (assumed to be dynamically allocated).
 * 
 * @param type The type of the token.
 * 
 * @param number The integer value to be associated with the token.
 * 
 * @return A pointer to the created `Token`, or NULL if allocation fails.
 * 
 * @note The caller is responsible for cleaning up the memory allocated for the `Token` object. This
 *       should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
Token *createTokenNumber(const char *const text, const TokenType type, const int number)
{
    TokenValue value = {.number = number};

    Token *token = createToken(text, type, value);
    if (token == NULL)
    {
        free((char *)text);
    }

    return token;
}

/**
 * Creates a new `Token` with the given text, type, and string value.
 * 
 * This function assumes that `text` is dynamically allocated 
 * by the caller and takes ownership of it. The `Token` will 
 * be responsible for freeing the `text` when it is no longer needed.
 * The function also allocates memory for a copy of the `string` value.
 * 
 * If the allocation for the `string` fails, the function will 
 * free the `text` and return NULL.
 * 
 * @param text The text to be associated with the token (assumed to be dynamically allocated).
 * 
 * @param type The type of the token.
 * 
 * @param string The string value to be associated with the token (assumed to be dynamically allocated).
 * 
 * @return A pointer to the created `Token`, or NULL if allocation fails.
 * 
 * @note The caller is responsible for cleaning up the memory allocated for the `Token` object. This
 *       should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
Token *createTokenString(const char *const text, const TokenType type, const char *const string)
{
    TokenValue value = {.string = string};

    Token *token = createToken(text, type, value);
    if (token == NULL)
    {
        if (value.string != NULL)
        {
            free((char *)value.string);
        }
        free((char *)text);
    }

    return token;
}

/**
 * Creates a new `Token` with the given text, type, and character value.
 * 
 * This function assumes that `text` is dynamically allocated 
 * by the caller and takes ownership of it. The `Token` will 
 * be responsible for freeing the `text` when it is no longer needed.
 * 
 * @param text The text to be associated with the token (assumed to be dynamically allocated).
 * 
 * @param type The type of the token.
 * 
 * @param character The character value to be associated with the token.
 * 
 * @return A pointer to the created `Token`, or NULL if allocation fails.
 * 
 * @note The caller is responsible for cleaning up the memory allocated for the `Token` object. This
 *       should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
Token *createTokenChar(const char *const text, const TokenType type, const char character)
{
    TokenValue value = {.character = character};

    Token *token = createToken(text, type, value);
    if (token == NULL)
    {
        free((char *)text);
    }

    return token;
}

/**
 * Creates a new `Token` with the given text, type, and floating-point value.
 * 
 * This function assumes that `text` is dynamically allocated 
 * by the caller and takes ownership of it. The `Token` will 
 * be responsible for freeing the `text` when it is no longer needed.
 * 
 * @param text The text to be associated with the token (assumed to be dynamically allocated).
 * 
 * @param type The type of the token.
 * 
 * @param floatingPoint The floating-point value to be associated with the token.
 * 
 * @return A pointer to the created `Token`, or NULL if allocation fails.
 * 
 * @note The caller is responsible for cleaning up the memory allocated for the `Token` object. This
 *       should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
Token *createTokenFloat(const char *const text, const TokenType type, const double floatingPoint)
{
    TokenValue value = {.floatingPoint = floatingPoint};

    Token *token = createToken(text, type, value);
    if (token == NULL)
    {
        free((char *)text);
    }

    return token;
}

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
void deleteToken(Token *const token)
{
    if (token == NULL)
    {
        fprintf(stderr, "Token is NULL!\n");
        return;
    }

    free((char *)token->text);
    if (token->type == TOKEN_STRING)
    {
        free((char *)token->value.string);
    }
    free(token);
}

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
void deleteTokens(Token **const tokens, const size_t count)
{
    if (tokens == NULL)
    {
        fprintf(stderr, "Tokens is NULL!\n");
        return;
    }

    for (size_t i = 0; i < count; i++)
    {
        if (tokens[i] != NULL)
        {
            deleteToken(tokens[i]);
        }
    }

    free(tokens);
}

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
void printToken(const Token *const token)
{
    if (token == NULL)
    {
        fprintf(stderr, "Token is NULL!\n");
        return;
    }

    if (token->type >= 0 && token->type < TOKEN_TYPE_COUNT)
    {
        printf("%s token", tokenTypeStrings[token->type]);
    }
    else
    {
        printf("UNKNOWN token type");
    }

    const char *escape = escapeCharToString(token->value.character);
    switch (token->type)
    {
    case TOKEN_INTEGER:
        printf(", value: %d\n", token->value.number);
        break;
    case TOKEN_FLOATINGPOINT:
        printf(", value: %f\n", token->value.floatingPoint);
        break;
    case TOKEN_CHARACTER:
        if (escape == NULL)
        {
            printf(", value: %c\n", token->value.character);
        }
        else
        {
            printf(", value: %s\n", escape);
        }
        break;
    case TOKEN_STRING:
        printf(", value: %s\n", token->value.string);
        break;
    case TOKEN_HEXAL:
        printf(", value: %#x\n", token->value.number);
        break;
    case TOKEN_OCTAL:
        printf(", value: %#o\n", token->value.number);
        break;
    case TOKEN_IDENTIFIER:
    case TOKEN_KEYWORD:
        printf(", name: %s\n", token->text);
        break;
    case TOKEN_LINE_COMMENT:
    case TOKEN_BLOCK_COMMENT:
        printf(", comment text: %s\n", token->text);
        break;
    case TOKEN_UNKNOWN:
        printf(", text found: %s\n", token->text);
        break;
    default:
        printf("\n");
        return;
    }
}

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
int isKeyword(const char *const input)
{
    if (input == NULL)
    {
        return 0;
    }

    for (size_t i = 0; i < KEYWORDS_COUNT; i++)
    {
        if (strcmp(input, keywords[i]) == 0)
        {
            return 1;
        }
    }
    
    return 0;
}
