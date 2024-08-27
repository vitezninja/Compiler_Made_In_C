#include "token.h"

/*****************************************************************************************************
                            PRIVATE TOKEN FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

/**
 * Count of all the keywords in the lookup table
 */
#define KEYWORDS_COUNT (sizeof(keywords) / sizeof(keywords[0]))

static Token *createToken(const char *const text, const int start, const TokenType type, const TokenValue value);

static const char *escapeCharToString(const char escapeChar);

/*****************************************************************************************************
                                PRIVATE TOKEN FUNCTIONS START HERE
 *****************************************************************************************************/

/**
 * Creates a new `Token` with the given text, start position, type, and value.
 * The function allocates memory for the `Token` structure.
 *
 * This function assumes that `text` is dynamically allocated by the caller 
 * and takes ownership of it. The `Token` will be responsible for freeing 
 * the `text` when it is no longer needed.
 *
 * @param text The text to be associated with the token (assumed to be dynamically allocated).
 *             If `text` is `NULL`, the `length` field of the token will be set to `0`.
 *
 * @param start The starting position of the token in the source code.
 *
 * @param type The type of the token, indicating its category in the lexical analysis.
 *
 * @param value The value of the token, representing additional information like numeric values.
 *
 * @return A pointer to the created `Token`, or `NULL` if allocation fails.
 *
 * @note If memory allocation for the `Token` fails, the function will free the provided `text` to avoid memory leaks.
 *
 * @note The caller is responsible for cleaning up the memory allocated for the `Token` object. This
 *       should be done using `deleteToken` for a single token or `deleteTokens` for multiple tokens.
 */
static Token *createToken(const char *const text, const int start, const TokenType type, const TokenValue value)
{
    Token *token = (Token *)malloc(sizeof(Token));
    if (token == NULL)
    {
        fprintf(stderr, "Memory allocation for Token failed!\n");
        free((char *)text);
        return NULL;
    }

    token->text = text;
    token->start = start;
    if (text != NULL)
    {
        token->length = strlen(text);
    }
    else
    {
        token->text = 0;
    }
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
    "typedef",
    "extern",
    "static",
    "auto",
    "register",
    "void",
    "char",
    "string",
    "short",
    "int",
    "long",
    "float",
    "double",
    "signed",
    "unsigned",
    "struct",
    "union",
    "const",
    "restrict",
    "volatile",
    "sizeof",
    "enum",
    "inline",
    "case",
    "default",
    "if",
    "else",
    "switch",
    "while",
    "do",
    "for",
    "goto",
    "continue",
    "break",
    "return",
};

/**
 * Lookup table for TokenType
 */
static const char *const tokenTypeStrings[] = {
    // Arithmetic Operators:
    [TOKEN_PLUS] = "PLUS",
    [TOKEN_DOUBLE_PLUS] = "DOUBLE_PLUS",
    [TOKEN_MINUS] = "MINUS",
    [TOKEN_DOUBLE_MINUS] = "DOUBLE_MINUS",
    [TOKEN_STAR] = "STAR",
    [TOKEN_SLASH] = "SLASH",
    [TOKEN_PERCENT] = "PERCENT",

    // Compound Assignment Operators (Arithmetic):
    [TOKEN_PLUS_EQUAL] = "PLUS_EQUAL" ,
    [TOKEN_MINUS_EQUAL] = "MINUS_EQUAL",
    [TOKEN_STAR_EQUAL] = "STAR_EQUAL",
    [TOKEN_SLASH_EQUAL] = "SLASH_EQUAL",
    [TOKEN_PERCENT_EQUAL] = "PERCENT_EQUAL",

    // Compound Assignment Operators (Bitwise):
    [TOKEN_BITWISE_LEFT_SHIFT_EQUAL] = "BITWISE_LEFT_SHIFT_EQUAL",
    [TOKEN_BITWISE_RIGHT_SHIFT_EQUAL] = "BITWISE_RIGHT_SHIFT_EQUAL",
    [TOKEN_BITWISE_AND_EQUAL] = "BITWISE_AND_EQUAL",
    [TOKEN_BITWISE_XOR_EQUAL] = "BITWISE_XOR_EQUAL",
    [TOKEN_BITWISE_OR_EQUAL] = "BITWISE_OR_EQUAL",

    // Comparison Operators:
    [TOKEN_EQUALS] = "EQUALS",
    [TOKEN_DOUBLE_EQUALS] = "DOUBLE_EQUALS",
    [TOKEN_NOT_EQUALS] = "NOT_EQUALS",
    [TOKEN_LESS_THAN] = "LESS_THAN",
    [TOKEN_GREATER_THAN] = "GREATER_THAN",
    [TOKEN_LESS_THAN_OR_EQUAL] = "LESS_THAN_OR_EQUAL",
    [TOKEN_GREATER_THAN_OR_EQUAL] = "GREATER_THAN_OR_EQUAL",

    // Logical Operators:
    [TOKEN_AND] = "AND",
    [TOKEN_OR] = "OR",
    [TOKEN_NOT] = "NOT",

    // Bitwise Operators:
    [TOKEN_BITWISE_AND] = "BITWISE_AND",
    [TOKEN_BITWISE_OR] = "BITWISE_OR",
    [TOKEN_BITWISE_XOR] = "BITWISE_XOR",
    [TOKEN_BITWISE_NOT] = "BITWISE_NOT",
    [TOKEN_BITWISE_LEFT_SHIFT] = "BITWISE_LEFT_SHIFT",
    [TOKEN_BITWISE_RIGHT_SHIFT] = "BITWISE_RIGHT_SHIFT",

    // Parentheses and Brackets:
    [TOKEN_OPEN_PARENTHESIS] = "OPEN_PARENTHESIS",
    [TOKEN_CLOSE_PARENTHESIS] = "CLOSE_PARENTHESIS",
    [TOKEN_OPEN_BRACKET] = "OPEN_BRACKET",
    [TOKEN_CLOSE_BRACKET] = "CLOSE_BRACKET",
    [TOKEN_OPEN_CURLY] = "OPEN_CURLY",
    [TOKEN_CLOSE_CURLY] = "CLOSE_CURLY",

    // Literals:
    [TOKEN_INTEGER] = "INTEGER",
    [TOKEN_FLOATINGPOINT] = "FLOATINGPOINT",
    [TOKEN_CHARACTER] = "CHARACTER",
    [TOKEN_STRING] = "STRING",
    [TOKEN_HEXADECIMAL] = "HEXADECIMAL",
    [TOKEN_OCTAL] = "OCTAL",

    // Identifier:
    [TOKEN_IDENTIFIER] = "IDENTIFIER",

    // Keywords:
    [TOKEN_KEYWORD] = "KEYWORD",

    // Punctuation:
    [TOKEN_COMMA] = "COMMA",
    [TOKEN_SEMICOLON] = "SEMICOLON",
    [TOKEN_COLON] = "COLON",
    [TOKEN_DOT] = "DOT",
    [TOKEN_ARROW] = "ARROW",
    [TOKEN_QUESTION_MARK] = "QUESTION_MARK",

    // Whitespace:
    [TOKEN_WHITESPACE] = "WHITESPACE",

    // Comments:
    [TOKEN_LINE_COMMENT] = "LINE_COMMENT",
    [TOKEN_BLOCK_COMMENT] = "BLOCK_COMMENT",

    // End of File:
    [TOKEN_EOF] = "EOF",

    // Unknown:
    [TOKEN_UNKNOWN] = "UNKNOWN",
};

/*****************************************************************************************************
                                PUBLIC TOKEN FUNCTIONS START HERE                                
 *****************************************************************************************************/

Token *createTokenNone(const char *const text, const int start, const TokenType type)
{
    TokenValue value = {0};

    Token *token = createToken(text, start, type, value);
    if (token == NULL)
    {
        free((char *)text);
    }

    return token;
}

Token *createTokenNumber(const char *const text, const int start, const TokenType type, const int number)
{
    TokenValue value = {.number = number};

    Token *token = createToken(text, start, type, value);
    if (token == NULL)
    {
        free((char *)text);
    }

    return token;
}

Token *createTokenString(const char *const text, const int start, const TokenType type, const char *const string)
{
    TokenValue value = {.string = string};

    Token *token = createToken(text, start, type, value);
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

Token *createTokenChar(const char *const text, const int start, const TokenType type, const char character)
{
    TokenValue value = {.character = character};

    Token *token = createToken(text, start, type, value);
    if (token == NULL)
    {
        free((char *)text);
    }

    return token;
}

Token *createTokenFloat(const char *const text, const int start, const TokenType type, const double floatingPoint)
{
    TokenValue value = {.floatingPoint = floatingPoint};

    Token *token = createToken(text, start, type, value);
    if (token == NULL)
    {
        free((char *)text);
    }

    return token;
}

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

Token *duplicateToken(Token *const token)
{
    if (token == NULL)
    {
        fprintf(stderr, "Token is NULL!\n");
        return NULL;
    }

    Token *newToken = createToken(token->text, token->start, token->type, token->value);
    if (newToken == NULL)
    {
        fprintf(stderr, "Memory allocation for new Token failed!\n");
        return NULL;
    }
    
    return newToken;
}

void printToken(const Token *const token)
{
    if (token == NULL)
    {
        fprintf(stderr, "Token is NULL!\n");
        return;
    }

    if (token->type == TOKEN_EOF)
    {
        printf("%s token\n", getType(token->type));
        return;
    }

    printf("%s token, text: %s", getType(token->type), token->text);

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
    case TOKEN_HEXADECIMAL:
        printf(", value: %#x\n", token->value.number);
        break;
    case TOKEN_OCTAL:
        printf(", value: %#o\n", token->value.number);
        break;
    default:
        printf("\n");
        return;
    }
}

char *getType(TokenType type)
{
    if (type >= 0 && type < TOKEN_TYPE_COUNT)
    {
        return (char *)tokenTypeStrings[type];
    }
    else
    {
        return "UNKNOWN";
    }
}

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
