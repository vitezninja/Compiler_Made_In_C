#include "lexer.h"

/*****************************************************************************************************
                            PRIVATE LEXER FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

/**
 * Size of the text buffer
 */
#define TEXT_BUFFER_SIZE 100

/**
 * Size of the text buffer for a char in `"{char}\0"` format
 */
#define TEXT_BUFFER_FOR_CHAR 5

static int isOctalDigit(const char c);

static int getOctalValue(const char c);

static int isHexalDigit(const char c);

static int getHexalValue(const char c);

static char nextChar(const Lexer *const lexer);

static char peekChar(const Lexer *const lexer);

static void consumeChar(Lexer *const lexer, const int count);

static int addError(Lexer *lexer, Error *error);

static void updateStartingPos(Lexer *lexer);

static Token *handleComments(Lexer *const lexer);

static Token *handleWhitespace(Lexer *const lexer);

static Token *handleIdentifiersAndKeywords(Lexer *const lexer);

static Token *handleStrings(Lexer *const lexer);

static Token *handleNumbers(Lexer *const lexer);

/*****************************************************************************************************
                                PRIVATE LEXER FUNCTIONS START HERE
 *****************************************************************************************************/

/**
 * Checks if a character is a valid octal digit (0-7).
 *
 * This function determines if the provided character is within the range 
 * of valid octal digits. It returns 1 if the character is a valid octal digit,
 * otherwise it returns 0.
 *
 * @param c The character to check.
 * 
 * @return 1 if the character is an octal digit (0-7), 0 otherwise.
 */
static int isOctalDigit(const char c)
{
    return c >= '0' && c <= '7';
}

/**
 * Converts a character to its octal digit value.
 *
 * This function converts a character representing an octal digit (0-7) 
 * to its integer value. If the character is not a valid octal digit, 
 * it returns -1.
 *
 * @param c The character to convert.
 * 
 * @return The integer value of the octal digit, or -1 if the character is not a valid octal digit.
 */
static int getOctalValue(const char c)
{
    if (isOctalDigit(c))
    {
        return c - '0';
    }

    return -1;
}

/**
 * Checks if a character is a valid hexadecimal digit (0-9, A-F, a-f).
 *
 * This function determines if the provided character is within the range 
 * of valid hexadecimal digits. It returns 1 if the character is a valid 
 * hexadecimal digit, otherwise it returns 0.
 *
 * @param c The character to check.
 * 
 * @return 1 if the character is a hexadecimal digit (0-9, A-F, a-f), 0 otherwise.
 */
static int isHexalDigit(const char c)
{
    return (isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'));
}

/**
 * Converts a character to its hexadecimal digit value.
 *
 * This function converts a character representing a hexadecimal digit 
 * (0-9, A-F, a-f) to its integer value. If the character is not a valid 
 * hexadecimal digit, it returns -1.
 *
 * @param c The character to convert.
 * 
 * @return The integer value of the hexadecimal digit, or -1 if the character is not a valid hexadecimal digit.
 */
static int getHexalValue(const char c)
{
    if (isdigit(c))
    {
        return c - '0';
    }
    if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'f')
    {
        return c - 'a' + 10;
    }
    return -1;
}

/**
 * Retrieves the current character from the lexer input.
 * 
 * This function accesses the character at the current position of the lexer.
 * It does not modify the state of the lexer.
 * 
 * If the lexer is NULL or the position is out of bounds, an error message is
 * printed, and the function returns the null character ('\0') to indicate
 * an invalid state or error.
 * 
 * @param lexer Pointer to the `Lexer` object. This pointer is const and should not be modified by this function.
 * 
 * @return The character at the current position in the lexer input, or '\0' if the position is invalid.
 */
static char nextChar(const Lexer *const lexer)
{
    if(lexer == NULL || lexer->position > lexer->charCount)
    {
        fprintf(stderr, "Invalid Lexer state or position out of bounds!\n");
        return '\0';
    }

    return lexer->input[lexer->position];
}

/**
 * Retrieves the next character from the lexer input without advancing the position.
 * 
 * This function looks at the character immediately following the current position
 * in the lexer input. It does not modify the state of the lexer.
 * 
 * If the lexer is NULL or there are no more characters to peek at (i.e., the position
 * is at or near the end of the input), an error message is printed, and the function
 * returns the null character ('\0') to indicate no character available.
 * 
 * @param lexer Pointer to the `Lexer` object. This pointer is const and should not be modified by this function.
 * 
 * @return The character at the next position in the lexer input, or '\0' if there is no next character.
 */
static char peekChar(const Lexer *const lexer)
{
    if(lexer == NULL)
    {
        fprintf(stderr, "Lexer is NULL!\n");
        return '\0';
    }
    
    if (lexer->position + 1 > lexer->charCount)
    {
        return '\0';
    }
    return lexer->input[lexer->position + 1];
}

/**
 * Advances the position in the lexer input by a specified number of characters.
 * 
 * This function moves the lexer’s current position forward by the given count. 
 * If the new position exceeds the end of the input, it is set to the end of the input.
 * 
 * If the lexer is NULL, an error message is printed, and the function returns 
 * without making any changes.
 * 
 * @param lexer Pointer to the `Lexer` object. This pointer is non-const and will be modified by this function.
 * 
 * @param count The number of characters to advance the position by.
 */
static void consumeChar(Lexer *const lexer, const int count)
{
    if(lexer == NULL)
    {
        fprintf(stderr, "Lexer is NULL!\n");
        return;
    }
    
    if (lexer->position + count >= lexer->charCount)
    {
        lexer->position = lexer->charCount;
        return;
    }
    lexer->position += count;
}

/**
 * Adds an `Error` object to the `Lexer`'s error list.
 * 
 * This function appends a new error to the list of errors maintained by the `Lexer`.
 * If necessary, it reallocates memory to expand the `errors` array to accommodate the new error.
 * 
 * @param lexer Pointer to the `Lexer` object to which the error should be added.
 * 
 * @param error Pointer to the `Error` object to be added to the `Lexer`'s error list.
 * 
 * @return `1` if the error was successfully added to the list; `0` otherwise.
 * 
 * @note The `Lexer` and `Error` pointers must be valid. The `Lexer`'s `errors` array will be expanded as needed, 
 *       and the function handles memory reallocation internally.
 */
static int addError(Lexer *lexer, Error *error)
{
    if (lexer == NULL)
    {
        fprintf(stderr, "Lexer is not initialized.\n");
        return 0;
    }

    if (error == NULL)
    {
        fprintf(stderr, "Error is not initialized.\n");
        return 0;
    }

    if (lexer->errorCount + 1 >= lexer->errorsSize)
    {
        lexer->errorsSize *= 2;
        Error **newErrors = realloc(lexer->errors, lexer->errorsSize * sizeof(Error *));
        if (newErrors == NULL)
        {
            fprintf(stderr, "Memory reallocation for Errors failed!\n");
            return 0;
        }
        lexer->errors = newErrors;
    }

    lexer->errors[lexer->errorCount++] = error;
    return 1;
}

/**
 * Updates the starting position for tokenization in the `Lexer`.
 * 
 * This function sets the `tokenStartingPos` field of the `Lexer` to the current position.
 * This is typically used to mark the beginning of a new token or to reset the starting position
 * for subsequent tokenization processes.
 * 
 * @param lexer Pointer to the `Lexer` object whose starting position is to be updated.
 * 
 * @note The `Lexer` pointer must be valid. If the `Lexer` is `NULL`, an error message is printed,
 *       and the function does nothing. Ensure that the `Lexer` is properly initialized before calling this function.
 */
static void updateStartingPos(Lexer *lexer)
{
    if (lexer == NULL)
    {
        fprintf(stderr, "Lexer is not initialized.\n");
        return;
    }

    lexer->tokenStartingPos = lexer->position;
}

/**
 * Processes and tokenizes comments in the lexer input.
 * 
 * This function handles two types of comments in the input stream:
 * - **Single-line comments** starting with `//`
 * - **Multi-line comments** enclosed in `/ * ... * /`
 * 
 * The function dynamically allocates and resizes memory as needed to store the entire comment text. 
 * If the comment extends beyond the initially allocated buffer size, the buffer is resized to accommodate the comment's length.
 * 
 * - **Single-line comments** are terminated by a newline character.
 * - **Multi-line comments** are terminated by `* /`. If the end of the input is reached without finding the closing `* /`, an error is generated.
 * 
 * If the `Lexer` is NULL, or if memory allocation or reallocation fails, an error message is printed, and the function returns `NULL`.
 * 
 * @param lexer Pointer to the `Lexer` object that manages the input text. The `Lexer` must be properly initialized before calling this function.
 * 
 * @return A pointer to a `Token` representing one of the following:
 * 
 *         - `TOKEN_BLOCK_COMMENT`: A multi-line comment (`/ * ... * /`).
 *         - `TOKEN_LINE_COMMENT`: A single-line comment (`//`).
 *         - `NULL`: If the `Lexer` is NULL, or if memory allocation or reallocation fails, or if no comment is found.
 * 
 * @note The `text` buffer is dynamically allocated and managed by this function. If memory reallocation fails,
 *       the allocated memory is freed, and `NULL` is returned.
 */
static Token *handleComments(Lexer *const lexer)
{
    if (lexer == NULL)
    {
        fprintf(stderr, "Lexer is not initialized.\n");
        return NULL;
    }

    if (nextChar(lexer) != '/')
    {
        return NULL;
    }

    size_t size = TEXT_BUFFER_SIZE;
    char *text = (char *)malloc(size * sizeof(char));
    if (text == NULL)
    {
        fprintf(stderr, "Memory allocation for Token text failed!\n");
        return NULL;
    }
    size_t pos = 0;

    //Consume '/'
    text[pos++] = nextChar(lexer);
    consumeChar(lexer, 1);

    //Multi-line comment
    if (nextChar(lexer) == '*')
    {
        //Consume '*'
        text[pos++] = nextChar(lexer);
        consumeChar(lexer, 1);

        while (nextChar(lexer) != '\0' && (nextChar(lexer) != '*' || peekChar(lexer) != '/'))
        {
            text[pos++] = nextChar(lexer);
            consumeChar(lexer, 1);

            if (pos == size - 3)
            {
                size *= 2;
                char *extendedText = realloc(text, size * sizeof(char));
                if (extendedText == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Token text failed!\n");
                    free(text);
                    return NULL;
                }
                text = extendedText;
            }
        }

        //If we stopped because we found EOF
        if (nextChar(lexer) == '\0')
        {
            text[pos] = '\0';
            Token *token = createTokenNone(text, lexer->tokenStartingPos, TOKEN_UNKNOWN);
            addError(lexer, createError(ERROR_LEXING, "The multi-line comment was not closed!", duplicateToken(token)));
            return token;
        }

        //Consume '*'
        text[pos++] = nextChar(lexer);
        consumeChar(lexer, 1);
        //Consume '/'
        text[pos++] = nextChar(lexer);
        consumeChar(lexer, 1);

        text[pos] = '\0';
        return createTokenNone(text, lexer->tokenStartingPos, TOKEN_BLOCK_COMMENT);
    }

    //Single line comment
    if (nextChar(lexer) == '/')
    {
        //Consume '/'
        text[pos++] = nextChar(lexer);
        consumeChar(lexer, 1);

        while (nextChar(lexer) != '\0' && (nextChar(lexer) != '\r' || peekChar(lexer) != '\n'))
        {
            text[pos++] = nextChar(lexer);
            consumeChar(lexer, 1);

            if (pos == size - 3)
            {
                size *= 2;
                char *extendedText = realloc(text, size * sizeof(char));
                if (extendedText == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Token text failed!\n");
                    free(text);
                    return NULL;
                }
                text = extendedText;
            }
        }

        if (nextChar(lexer) != '\0')
        {
            //Consume '\r'
            text[pos++] = nextChar(lexer);
            consumeChar(lexer, 1);
            //Consume '\n'
            text[pos++] = nextChar(lexer);
            consumeChar(lexer, 1);
        }

        text[pos] = '\0';
        return createTokenNone(text, lexer->tokenStartingPos, TOKEN_LINE_COMMENT);
    }

    return NULL;
}

/**
 * Processes and tokenizes whitespace characters in the lexer input.
 * 
 * This function identifies and collects all consecutive whitespace characters from the lexer’s input 
 * stream. It dynamically allocates and resizes a buffer to store the whitespace characters encountered.
 * The function continues reading and storing characters until a non-whitespace character is found.
 * 
 * If the lexer is NULL or memory allocation fails, an error message is printed, and the function 
 * returns NULL. 
 * 
 * @param lexer Pointer to the `Lexer` object that provides access to the input source code stream. 
 *              The lexer must be initialized before being passed to this function.
 * 
 * @return Pointer to a `Token` object representing the collected whitespace characters. The token type 
 *         is set to `TOKEN_WHITESPACE`. Returns NULL if the lexer is NULL or if memory allocation fails.
 */
static Token *handleWhitespace(Lexer *const lexer)
{
    if (lexer == NULL)
    {
        fprintf(stderr, "Lexer is not initialized.\n");
        return NULL;
    }

    if (!isspace(nextChar(lexer)))
    {
        return NULL;
    }

    size_t size = TEXT_BUFFER_SIZE;
    char *text = (char *)malloc(size * sizeof(char));
    if (text == NULL)
    {
        fprintf(stderr, "Memory allocation for Token text failed!\n");
        return NULL;
    }
    size_t pos = 0;

    while (isspace(nextChar(lexer)))
    {
        text[pos++] = nextChar(lexer);
        consumeChar(lexer, 1);
        if (pos == size - 1)
        {
            size *= 2;
            char *extendedText = realloc(text, size * sizeof(char));
            if (extendedText == NULL)
            {
                fprintf(stderr, "Memory reallocation for Token text failed!\n");
                free(text);
                return NULL;
            }
            text = extendedText;
        }
    }

    text[pos] = '\0';
    return createTokenNone(text, lexer->tokenStartingPos, TOKEN_WHITESPACE);
}

/**
 * Processes and tokenizes identifiers and keywords from the lexer input.
 * 
 * This function collects characters that form identifiers or keywords, including letters, digits,
 * and underscores. It dynamically allocates and resizes a buffer to store these characters as long
 * as they meet the criteria for identifiers or keywords. The function then classifies the collected
 * text as either a keyword or an identifier.
 * 
 * If the lexer is NULL or memory allocation fails, an error message is printed, and the function 
 * returns NULL.
 * 
 * @param lexer Pointer to the `Lexer` object that provides access to the input source code stream. 
 *              The lexer must be initialized before being passed to this function.
 * 
 * @return Pointer to a `Token` object representing the collected identifier or keyword. The token 
 *         type is set to `TOKEN_KEYWORD` if the text matches a keyword, otherwise it is set to 
 *         `TOKEN_IDENTIFIER`. Returns NULL if the lexer is NULL or if memory allocation fails.
 */
static Token *handleIdentifiersAndKeywords(Lexer *const lexer)
{
    if (lexer == NULL)
    {
        fprintf(stderr, "Lexer is not initialized.\n");
        return NULL;
    }

    if (!isalpha(nextChar(lexer)) && nextChar(lexer) != '_')
    {
        return NULL;
    }

    size_t size = TEXT_BUFFER_SIZE;
    char *text = (char *)malloc(size * sizeof(char));
    if (text == NULL)
    {
        fprintf(stderr, "Memory allocation for Token text failed!\n");
        return NULL;
    }
    size_t pos = 0;

    while (isalnum(nextChar(lexer)) || nextChar(lexer) == '_'|| isdigit(nextChar(lexer)))
    {
        text[pos++] = nextChar(lexer);
        consumeChar(lexer , 1);

        if (pos == size - 1)
        {
            size *= 2;
            char *extendedText = realloc(text, size * sizeof(char));
            if (extendedText == NULL)
            {
                fprintf(stderr, "Memory reallocation for Token text failed!\n");
                free(text);
                return NULL;
            }
            text = extendedText;
        }
    }

    text[pos] = '\0';
    if (isKeyword(text))
    {
        return createTokenNone(text, lexer->tokenStartingPos, TOKEN_KEYWORD);
    }
    else
    {
        return createTokenNone(text, lexer->tokenStartingPos, TOKEN_IDENTIFIER);
    }
}

/**
 * Processes and tokenizes string literals from the lexer input.
 * 
 * This function collects characters enclosed in double quotes (`""`). It dynamically
 * allocates and resizes a buffer to store these characters as long as they are part
 * of the string literal. The function stops collecting characters when it encounters
 * the closing double quote or the end-of-file (EOF). If the string literal is valid,
 * it returns a token representing the string literal; otherwise, it returns an error token.
 * 
 * If the lexer is NULL or memory allocation fails, an error message is printed, and the function 
 * returns NULL.
 * 
 * @param lexer Pointer to the `Lexer` object that provides access to the input source code stream. 
 *              The lexer must be initialized before being passed to this function.
 * 
 * @return Pointer to a `Token` object representing the collected string literal. If the end-of-file
 *         is encountered before finding a closing quote, the token type is set to `TOKEN_UNKNOWN`. 
 *         Returns NULL if the lexer is NULL or if memory allocation fails.
 */
static Token *handleStrings(Lexer *const lexer)
{
    if (lexer == NULL)
    {
        fprintf(stderr, "Lexer is not initialized.\n");
        return NULL;
    }

    if (nextChar(lexer) != '\"')
    {
        return NULL;
    }

    size_t size = TEXT_BUFFER_SIZE;
    char *text = (char *)malloc(size * sizeof(char));
    if (text == NULL)
    {
        fprintf(stderr, "Memory allocation for Token text failed!\n");
        return NULL;
    }
    size_t pos = 0;

    //Consume opening '\"'
    text[pos++] = nextChar(lexer);
    consumeChar(lexer, 1);

    while (nextChar(lexer) != '\"' && nextChar(lexer) != '\0')
    {
        text[pos++] = nextChar(lexer);
        consumeChar(lexer, 1);

        if (pos == size - 2)
        {
            size *= 2;
            char *extendedText = realloc(text, size * sizeof(char));
            if (extendedText == NULL)
            {
                fprintf(stderr, "Memory reallocation for Token text failed!\n");
                free(text);
                return NULL;
            }
            text = extendedText;
        }
    }

    //If we stopped because we found EOF
    if (nextChar(lexer) == '\0')
    {
        text[pos] = '\0';
        Token *token = createTokenNone(text, lexer->tokenStartingPos, TOKEN_UNKNOWN);
        addError(lexer, createError(ERROR_LEXING, "The string wasn't closed!", duplicateToken(token)));
        return token;
    }

    //Consume closing '\"'
    text[pos++] = nextChar(lexer);
    consumeChar(lexer, 1);

    text[pos] = '\0';
    return createTokenString(text, lexer->tokenStartingPos, TOKEN_STRING, substring(text, 1, pos - 1));
}

/**
 * Processes and tokenizes character literals from the lexer input.
 * 
 * This function handles character literals enclosed in single quotes (`''`). It collects
 * the character between the quotes, accounting for potential escape sequences. The function 
 * dynamically allocates and resizes a buffer to store the character and its escape sequence 
 * if present. If the character literal is valid, it returns a token representing the character literal;
 * otherwise, it returns an error token.
 * 
 * If the lexer is NULL or memory allocation fails, an error message is printed, and the function
 * returns NULL.
 * 
 * @param lexer Pointer to the `Lexer` object that provides access to the input source code stream.
 *              The lexer must be initialized before being passed to this function.
 * 
 * @return Pointer to a `Token` object representing the collected character literal. If the 
 *         character literal is invalid or the end-of-file is encountered prematurely, the token 
 *         type is set to `TOKEN_UNKNOWN`. Returns NULL if the lexer is NULL or if memory 
 *         allocation fails.
 */
static Token *handleCharacters(Lexer *const lexer)
{
    if (lexer == NULL)
    {
        fprintf(stderr, "Lexer is not initialized.\n");
        return NULL;
    }

    if (nextChar(lexer) != '\'')
    {
        return NULL;
    }

    size_t size = TEXT_BUFFER_FOR_CHAR;
    char *text = (char *)malloc(size * sizeof(char));
    if (text == NULL)
    {
        fprintf(stderr, "Memory allocation for Token text failed!\n");
        return NULL;
    }
    size_t pos = 0;

    //Consume opening '\''
    text[pos++] = nextChar(lexer);
    consumeChar(lexer, 1);

    int isEscaped = 0;
    //Check for escape sequence
    if (nextChar(lexer) == '\\')
    {
        isEscaped = 1;
        text[pos++] = nextChar(lexer);
        consumeChar(lexer, 1);
    }

    //Handle EOF scenario
    if (nextChar(lexer) == '\0')
    {
        text[pos] = '\0';
        Token *token = createTokenNone(text, lexer->tokenStartingPos, TOKEN_UNKNOWN);
        addError(lexer, createError(ERROR_LEXING, "The character wasn't closed!", duplicateToken(token)));
        return token;
    }

    //Consume character
    text[pos++] = nextChar(lexer);
    consumeChar(lexer, 1);  

    if (nextChar(lexer) != '\'')
    {
        text[pos++] = nextChar(lexer);
        consumeChar(lexer, 1);
        text[pos] = '\0';
        Token *token = createTokenNone(text, lexer->tokenStartingPos, TOKEN_UNKNOWN);
        addError(lexer, createError(ERROR_LEXING, "The character wasn't closed!", duplicateToken(token)));
        return token;
    }

    //Consume closing '\''
    text[pos++] = nextChar(lexer);
    consumeChar(lexer, 1);

    text[pos] = '\0';
    char retChar = text[1];
    if (isEscaped)
    {
        const char *ss = substring(text, 1, 3);
        retChar = convertEscapeString(ss);
        if (retChar == '\0')
        {
            addError(lexer, createError(ERROR_LEXING, "Invalid escape string format.", NULL));
        }
        free((char *)ss);
    }
    return createTokenChar(text, lexer->tokenStartingPos, TOKEN_CHARACTER, retChar);
}

/**
 * Processes and tokenizes numeric literals from the lexer input.
 * 
 * This function handles integer literals, octal literals, hexadecimal literals, and floating-point literals.
 * It supports the following formats:
 * 
 * - Decimal integers (e.g., 123)
 * 
 * - Octal integers (e.g., 0754, prefixed with '0')
 * 
 * - Hexadecimal integers (e.g., 0x1F, prefixed with '0x' or '0X')
 * 
 * - Floating-point numbers (e.g., 123.456)
 * 
 * The function handles memory allocation dynamically to accommodate numbers of varying lengths.
 * It returns tokens for recognized numeric literals or an error token if the input is invalid.
 * 
 * @param lexer Pointer to the `Lexer` object that provides access to the input source code stream.
 *              The lexer must be initialized before being passed to this function.
 * 
 * @return Pointer to a `Token` object representing the recognized numeric literal. If the numeric literal
 *         is invalid, the token type is set to `TOKEN_UNKNOWN`. Returns NULL if the lexer is NULL or if
 *         memory allocation fails.
 */
static Token *handleNumbers(Lexer *const lexer)
{
    if (lexer == NULL)
    {
        fprintf(stderr, "Lexer is not initialized.\n");
        return NULL;
    }

    if (!isdigit(nextChar(lexer)))
    {
        return NULL;
    }

    size_t size = TEXT_BUFFER_SIZE;
    char *text = (char *)malloc(size * sizeof(char));
    if (text == NULL)
    {
        fprintf(stderr, "Memory allocation for Token text failed!\n");
        return NULL;
    }
    size_t pos = 0;

    int value = 0;
    int isOctal = 0;
    int isHexal = 0;
    double doubleValue = 0.0;
    size_t mantissaCount = 0;

    if (nextChar(lexer) == '0')
    {
        //Consume '0'
        text[pos++] = nextChar(lexer);
        consumeChar(lexer, 1);

        if (nextChar(lexer) == 'x' || nextChar(lexer) == 'X')
        {
            isHexal = 1;
            //Consume 'x' or 'X'
            text[pos++] = nextChar(lexer);
            consumeChar(lexer, 1);
        }
        else
        {
            isOctal = 1;
        }
    }

    //Octal numbers
    if (isOctal)
    {
        while (isOctalDigit(nextChar(lexer)))
        {
            text[pos++] = nextChar(lexer);
            value = value * 8 + getOctalValue(nextChar(lexer));
            consumeChar(lexer, 1);

            if (pos == size - 1)
            {
                size *= 2;
                char *extendedText = realloc(text, size * sizeof(char));
                if (extendedText == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Token text failed!\n");
                    free(text);
                    return NULL;
                }
                text = extendedText;
            }
        }

        //Handle invalid digits following an octal number
        if (isdigit(nextChar(lexer)))
        {
            text[pos++] = nextChar(lexer);
            consumeChar(lexer, 1);
            text[pos] = '\0';
            Token *token = createTokenNone(text, lexer->tokenStartingPos, TOKEN_UNKNOWN);
            addError(lexer, createError(ERROR_LEXING, "Invalid digit in an octal number", duplicateToken(token)));
            return token;
        }

        text[pos] = '\0';
        return createTokenNumber(text, lexer->tokenStartingPos, TOKEN_OCTAL, value);
    }

    //Hexadecimal numbers
    if (isHexal)
    {
        while (isHexalDigit(nextChar(lexer)))
        {
            text[pos++] = nextChar(lexer);
            value = value * 16 + getHexalValue(nextChar(lexer));
            consumeChar(lexer, 1);

            if (pos == size - 1)
            {
                size *= 2;
                char *extendedText = realloc(text, size * sizeof(char));
                if (extendedText == NULL)
                {
                    fprintf(stderr, "Memory reallocation for Token text failed!\n");
                    free(text);
                    return NULL;
                }
                text = extendedText;
            }
        }

        //Handle invalid characters following a hexadecimal number
        if (isalpha(nextChar(lexer)))
        {
            text[pos++] = nextChar(lexer);
            consumeChar(lexer, 1);
            text[pos] = '\0';
            Token *token = createTokenNone(text, lexer->tokenStartingPos, TOKEN_UNKNOWN);
            addError(lexer, createError(ERROR_LEXING, "Invalid character in a hexadecimal number", duplicateToken(token)));
            return token;
        }

        text[pos] = '\0';
        return createTokenNumber(text, lexer->tokenStartingPos, TOKEN_HEXADECIMAL, value);
    }

    //Integer number part
    while (isdigit(nextChar(lexer)))
    {
        text[pos++] = nextChar(lexer);
        value = value * 10 + (nextChar(lexer) - '0');
        consumeChar(lexer, 1);

        if (pos == size - 3)
        {
            size *= 2;
            char *extendedText = realloc(text, size * sizeof(char));
            if (extendedText == NULL)
            {
                fprintf(stderr, "Memory reallocation for Token text failed!\n");
                free(text);
                return NULL;
            }
            text = extendedText;
        }
    }

    //If there is not dot after the numbers its an integer number
    if (nextChar(lexer) != '.')
    {
        text[pos] = '\0';
        return createTokenNumber(text, lexer->tokenStartingPos, TOKEN_INTEGER, value);
    }

    //Floating-Point number part
    //Consume '.'
    text[pos++] = nextChar(lexer);
    consumeChar(lexer, 1);  

    while (isdigit(nextChar(lexer)))
    {
        text[pos++] = nextChar(lexer);
        doubleValue = doubleValue * 10 + (nextChar(lexer) - '0');
        mantissaCount++;
        consumeChar(lexer, 1);

        if (pos == size - 1)
        {
            size *= 2;
            char *extendedText = realloc(text, size * sizeof(char));
            if (extendedText == NULL)
            {
                fprintf(stderr, "Memory reallocation for Token text failed!\n");
                free(text);
                return NULL;
            }
            text = extendedText;
        }
    }

    text[pos] = '\0';
    for (size_t i = 0; i < mantissaCount; i++)
    {
        doubleValue /= 10.0;
    }
    doubleValue += value;
    
    return createTokenFloat(text, lexer->tokenStartingPos, TOKEN_FLOATINGPOINT, doubleValue);
}

/**
 * Processes and tokenizes single-character and multi-character operators from the lexer input.
 * 
 * This function identifies and creates tokens for various operators and delimiters in the input stream:
 * 
 * - **Single-character operators**: `+`, `-`, `*`, `/`, `%`, `(`, `)`, `[`, `]`, `{`, `}`, `,`, `;`, `:`, `.`, '!', '=', '?', '~', '<', '>', '&', '|', '^'
 * 
 * - **Multi-character operators**: `->`, `==`, `!=`, `<=`, `>=`, `<<`, `>>`, `&&`, `||`, `++`, `--`, `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `|=`, `^=`, `<<=`, `>>=`
 * 
 * The function dynamically allocates memory to store the text of the token and determines the token type
 * based on the current and next characters in the lexer buffer. For multi-character operators, both characters
 * are included in the token.
 * 
 * If the `Lexer` is NULL or memory allocation fails, an error message is printed, and the function returns `NULL`.
 * 
 * @param lexer Pointer to the `Lexer` object that provides access to the input source code stream.
 *              The `Lexer` must be properly initialized before being passed to this function.
 * 
 * @return A pointer to a `Token` object representing the recognized operator or delimiter, or `NULL` if:
 * 
 *         - The `Lexer` is NULL.
 * 
 *         - Memory allocation fails.
 * 
 *         - An unrecognized character is encountered.
 * 
 *         - The current character does not match any known operator or delimiter.
 * 
 * @note The `text` buffer is dynamically allocated and managed by this function. If resizing the buffer fails,
 *       the allocated memory is freed, and `NULL` is returned. Ensure to handle the returned `Token` appropriately,
 *       and be cautious of any unrecognized characters.
 */
static Token *handleSimpleCase(Lexer *const lexer)
{
    if (lexer == NULL)
    {
        fprintf(stderr, "Lexer is not initialized.\n");
        return NULL;
    }

    size_t size = 3;
    char *text = (char *)malloc(size * sizeof(char));
    if (text == NULL)
    {
        fprintf(stderr, "Memory allocation for Token text failed!\n");
        return NULL;
    }

    size_t pos = 0;
    char currentChar = nextChar(lexer);
    text[pos++] = currentChar;
    TokenType type;
    switch (currentChar)
    {
    case '\0':
        type = TOKEN_EOF;
        break;
    case '?':
        type = TOKEN_QUESTION_MARK;
        break;
    case '~':
        type = TOKEN_BITWISE_NOT;
        break;
    case '(':
        type = TOKEN_OPEN_PARENTHESIS;
        break;
    case ')':
        type = TOKEN_CLOSE_PARENTHESIS;
        break;
    case '[':
        type = TOKEN_OPEN_BRACKET;
        break;
    case ']':
        type = TOKEN_CLOSE_BRACKET;
        break;
    case '{':
        type = TOKEN_OPEN_CURLY;
        break;
    case '}':
        type = TOKEN_CLOSE_CURLY;
        break;
    case ',':
        type = TOKEN_COMMA;
        break;
    case ';':
        type = TOKEN_SEMICOLON;
        break;
    case ':':
        type = TOKEN_COLON;
        break;
    case '.':
        type = TOKEN_DOT;
        break;
    case '+':
        if (peekChar(lexer) == '+')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_DOUBLE_PLUS;
            break;
        }
        else if (peekChar(lexer) == '=')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_PLUS_EQUAL;
            break;
        }
        type = TOKEN_PLUS;
        break;
    case '-':
        if (peekChar(lexer) == '-')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_DOUBLE_MINUS;
            break;
        }
        else if (peekChar(lexer) == '>')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_ARROW;
            break;
        }
        else if (peekChar(lexer) == '=')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_MINUS_EQUAL;
            break;
        }
        type = TOKEN_MINUS;
        break;
    case '*':
        if (peekChar(lexer) == '=')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_STAR_EQUAL;
            break;
        }
        type = TOKEN_STAR;
        break;
    case '/':
        if (peekChar(lexer) == '=')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_SLASH_EQUAL;
            break;
        }
        else if (peekChar(lexer) == '/' || peekChar(lexer) == '*')
        {
            free(text);
            return NULL;
        }
        type = TOKEN_SLASH;
        break;
    case '%':
        if (peekChar(lexer) == '=')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_PERCENT_EQUAL;
            break;
        }
        type = TOKEN_PERCENT;
        break;
    case '=':
        if (peekChar(lexer) == '=')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_DOUBLE_EQUALS;
            break;
        }
        type = TOKEN_EQUALS;
        break;
    case '!':
        if (peekChar(lexer) == '=')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_NOT_EQUALS;
            break;
        }
        type = TOKEN_NOT;
        break;
    case '<':
        if (peekChar(lexer) == '=')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_LESS_THAN_OR_EQUAL;
            break;
        }
        else if (peekChar(lexer) == '<')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            if (peekChar(lexer) == '=')
            {
                consumeChar(lexer, 1);
                text[pos++] = nextChar(lexer);
                type = TOKEN_BITWISE_LEFT_SHIFT_EQUAL;
                break;
            }
            type = TOKEN_BITWISE_LEFT_SHIFT;
            break;
        }
        type = TOKEN_LESS_THAN;
        break;
    case '>':
        if (peekChar(lexer) == '=')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_GREATER_THAN_OR_EQUAL;
            break;
        }
        else if (peekChar(lexer) == '>')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            if (peekChar(lexer) == '=')
            {
                consumeChar(lexer, 1);
                text[pos++] = nextChar(lexer);
                type = TOKEN_BITWISE_RIGHT_SHIFT_EQUAL;
                break;
            }
            type = TOKEN_BITWISE_RIGHT_SHIFT;
            break;
        }
        type = TOKEN_GREATER_THAN;
        break;
    case '&':
        if (peekChar(lexer) == '&')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_AND;
            break;
        }
        else if (peekChar(lexer) == '=')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_BITWISE_AND_EQUAL;
            break;
        }
        type = TOKEN_BITWISE_AND;
        break;
    case '|':
        if (peekChar(lexer) == '|')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_OR;
            break;
        }
        else if (peekChar(lexer) == '=')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_BITWISE_OR_EQUAL;
            break;
        }
        type = TOKEN_BITWISE_OR;
        break;
    case '^':
        if (peekChar(lexer) == '=')
        {
            consumeChar(lexer, 1);
            text[pos++] = nextChar(lexer);
            type = TOKEN_BITWISE_XOR_EQUAL;
            break;
        }
        type = TOKEN_BITWISE_XOR;
        break;
    default:
        free(text);
        return NULL;
    }

    consumeChar(lexer, 1);
    text[pos] = '\0';
    return createTokenNone(text, lexer->tokenStartingPos, type);
}

/*****************************************************************************************************
                                PUBLIC LEXER FUNCTIONS START HERE                                
 *****************************************************************************************************/

Lexer *createLexer(const char *const input)
{
    if (input == NULL) {
        fprintf(stderr, "Invalid input.\n");
        return NULL;
    }

    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
    if (lexer == NULL)
    {
        fprintf(stderr, "Memory allocation for Lexer failed!\n");
        return NULL;
    }

    lexer->tokenStartingPos = 0;
    lexer->input = strdup(input);
    if (lexer->input == NULL)
    {
        fprintf(stderr, "Memory allocation for input string failed!\n");
        free(lexer);
        return NULL;
    }

    lexer->charCount = strlen(lexer->input);
    lexer->position = 0;
    
    lexer->errorsSize = 10;
    lexer->errors = malloc(lexer->errorsSize * sizeof(Error *));
    lexer->errorCount = 0;

    return lexer;
}

void deleteLexer(Lexer *const lexer)
{
    if (lexer == NULL)
    {
        return;
    }

    deleteErrors(lexer->errors, lexer->errorCount);
    free(lexer->errors);
    
    free((char *)lexer->input);
    free(lexer);
}

Token *lex(Lexer *const lexer)
{
    if (lexer == NULL)
    {
        fprintf(stderr, "Lexer is not initialized.\n");
        return NULL;
    }

    Token *token = NULL;

    if (token == NULL) token = handleSimpleCase(lexer);
    if (token == NULL) token = handleNumbers(lexer);
    if (token == NULL) token = handleCharacters(lexer);
    if (token == NULL) token = handleStrings(lexer);
    if (token == NULL) token = handleIdentifiersAndKeywords(lexer);
    if (token == NULL) token = handleWhitespace(lexer);
    if (token == NULL) token = handleComments(lexer);

    //Unknown
    if(token == NULL)
    {
        char *text = (char *)malloc(2 * sizeof(char));
        if (text == NULL)
        {
            fprintf(stderr, "Memory allocation for Token text failed!\n");
            return NULL;
        }
        text[0] = nextChar(lexer);
        consumeChar(lexer, 1);
        text[1] = '\0';
        token = createTokenNone(text, lexer->tokenStartingPos, TOKEN_UNKNOWN);
        addError(lexer, createError(ERROR_LEXING, "Unknown character found while lexing!", duplicateToken(token)));
    }

    updateStartingPos(lexer);

    return token;
}