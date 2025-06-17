#include "lexer.h"

/**
 * Checks if a character is a valid binary digit (0 or 1).
 * 
 * This function determines if the provided character is either '0' or '1'.
 * It returns true if the character is a valid binary digit, otherwise it returns false.
 * 
 * @param c The character to check.
 * 
 * @return true if the character is a binary digit (0 or 1), false otherwise.
 */
bool lexer_isBinaryDigit(char c);

/**
 * Checks if a character is a valid binary digit (0 or 1).
 *
 * This function determines if the provided character is either '0' or '1'.
 * It returns true if the character is a valid binary digit, otherwise it returns false.
 *
 * @param c The character to check.
 * 
 * @return true if the character is a binary digit (0 or 1), false otherwise.
 */
int lexer_getBinaryValue(char c);

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
bool lexer_isOctalDigit(char c);

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
int lexer_getOctalValue(char c);

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
bool lexer_isHexalDigit(char c);

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
int lexer_getHexalValue(char c);

/**
 * Converts an escaped character to its actual character value.
 *
 * This function takes a character that represents an escape sequence 
 * (e.g., '\n', '\t', etc.) and returns the corresponding character value.
 * If the escape sequence is invalid, it returns -1.
 *
 * @param text The character representing the escape sequence.
 * 
 * @return The actual character value of the escape sequence, or -1 if the escape sequence is invalid.
 */
char lexer_getEscapedChar(char text);

/**
 * Retrieves the current character from the lexer.
 *
 * This function returns the character at the current position in the lexer.
 * If the lexer is NULL or if the current position is beyond the source buffer size,
 * it returns '\0' to indicate the end of file.
 *
 * @param lexer The lexer instance.
 * 
 * @return The current character, or '\0' if the lexer is NULL or at end of file.
 */
char lexer_currentChar(const Lexer *lexer);

/**
 * Retrieves the next character from the lexer without consuming it.
 *
 * This function returns the character immediately following the current position in the lexer.
 * If the lexer is NULL or if the next position is beyond the source buffer size,
 * it returns '\0' to indicate the end of file.
 *
 * @param lexer The lexer instance.
 * 
 * @return The next character, or '\0' if the lexer is NULL or at end of file.
 */
char lexer_nextChar(const Lexer *lexer);

/**
 * Retrieves the character at a specified offset from the current position in the lexer.
 *
 * This function returns the character at the current position plus the specified offset.
 * If the lexer is NULL or if the position with the offset is beyond the source buffer size,
 * it returns '\0' to indicate the end of file.
 *
 * @param lexer The lexer instance.
 * @param offset The offset from the current position.
 * 
 * @return The character at the specified offset, or '\0' if out of bounds.
 */
char lexer_peekChar(const Lexer *lexer, size_t offset);

/**
 * Consumes a specified number of characters from the lexer.
 *
 * This function advances the current position in the lexer by the specified count.
 * It updates the line and column numbers accordingly, handling new lines correctly.
 * If the count exceeds the remaining characters in the source buffer, it moves to the end.
 *
 * @param lexer The lexer instance.
 * @param count The number of characters to consume.
 */
void lexer_consumeChar(Lexer *lexer, size_t count);

/**
 * Deletes whitespace characters from the lexer.
 *
 * This function consumes all whitespace characters (spaces, tabs, newlines) 
 * starting from the current position in the lexer. It updates the current position 
 * accordingly and returns true if any whitespace was deleted, false otherwise.
 *
 * @param lexer The lexer instance.
 * 
 * @return false if whitespace was deleted, true otherwise.
 */
bool lexer_deleteWhitespaces(Lexer *lexer);

/**
 * Deletes comments from the lexer.
 *
 * This function consumes single-line and multi-line comments starting from the 
 * current position in the lexer. It updates the current position accordingly and 
 * returns true if any comments were deleted, false otherwise.
 *
 * @param lexer The lexer instance.
 * 
 * @return false if comments were deleted, true otherwise.
 */
bool lexer_deleteComments(Lexer *lexer);

/**
 * Handles simple cases of tokens such as operators and delimiters.
 *
 * This function checks the current character in the lexer and creates a token 
 * for simple cases like operators (e.g., +, -, *, /) and delimiters (e.g., (, ), {, }, etc.).
 * It consumes the character and returns the created token.
 *
 * @param lexer The lexer instance.
 * 
 * @return A pointer to the created token, or NULL if no simple case was matched.
 */
Token *lexer_handleSimpleCase(Lexer *lexer);

/**
 * Handles numeric literals in the lexer.
 *
 * This function processes numeric literals, including binary, octal, hexadecimal,
 * and decimal numbers. It consumes the characters that form the number and returns
 * a token representing the numeric value.
 *
 * @param lexer The lexer instance.
 * 
 * @return A pointer to the created token for the numeric literal, or NULL if no number was matched.
 */
Token *lexer_handleNumbers(Lexer *lexer);

/**
 * Handles character literals in the lexer.
 *
 * This function processes character literals, including escaped characters, and
 * returns a token representing the character value. It consumes the characters that
 * form the character literal.
 *
 * @param lexer The lexer instance.
 * 
 * @return A pointer to the created token for the character literal, or NULL if no character was matched.
 */
Token *lexer_handleCharacters(Lexer *lexer);

/**
 * Handles string literals in the lexer.
 *
 * This function processes string literals, including escaped characters, and
 * returns a token representing the string value. It consumes the characters that
 * form the string literal.
 *
 * @param lexer The lexer instance.
 * 
 * @return A pointer to the created token for the string literal, or NULL if no string was matched.
 */
Token *lexer_handleStrings(Lexer *lexer);

/**
 * Handles boolean literals in the lexer.
 *
 * This function processes boolean literals (true and false) and returns a token
 * representing the boolean value. It consumes the characters that form the boolean literal.
 *
 * @param lexer The lexer instance.
 * 
 * @return A pointer to the created token for the boolean literal, or NULL if no boolean was matched.
 */
Token *lexer_handleBooleans(Lexer *lexer);

/**
 * Handles null literals in the lexer.
 *
 * This function processes the null literal and returns a token representing the null value.
 * It consumes the characters that form the null literal.
 *
 * @param lexer The lexer instance.
 * 
 * @return A pointer to the created token for the null literal, or NULL if no null was matched.
 */
Token *lexer_handleNull(Lexer *lexer);

/**
 * Handles identifiers and keywords in the lexer.
 *
 * This function processes identifiers and keywords, creating tokens for them.
 * It consumes the characters that form the identifier or keyword.
 *
 * @param lexer The lexer instance.
 * 
 * @return A pointer to the created token for the identifier or keyword, or NULL if no identifier or keyword was matched.
 */
Token *lexer_handleIdentifiersAndKeywords(Lexer *lexer);

// ---------------------------------------------------------------------------

bool lexer_isBinaryDigit(char c)
{
    return (c == '0' || c == '1');
}

int lexer_getBinaryValue(char c)
{
    if (lexer_isBinaryDigit(c))
    {
        return c - '0';
    }

    DEBUG_PRINT("lexer_getBinaryValue: Invalid binary digit '%c'\n", c);
    return -1;
}

bool lexer_isOctalDigit(char c)
{
    return c >= '0' && c <= '7';
}

int lexer_getOctalValue(char c)
{
    if (lexer_isOctalDigit(c))
    {
        return c - '0';
    }

    DEBUG_PRINT("lexer_getOctalValue: Invalid octal digit '%c'\n", c);
    return -1;
}

bool lexer_isHexalDigit(char c)
{
    return (isxdigit(c) != 0);
}

int lexer_getHexalValue(char c)
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

    DEBUG_PRINT("lexer_getHexalValue: Invalid hexadecimal digit '%c'\n", c);
    return -1;
}

char lexer_getEscapedChar(char text)
{
    if (text == '\0')
    {
        DEBUG_PRINT("lexer_getEscapedChar: Invalid escape sequence '\\0'\n");
        return -1;
    }

    switch (text)
    {
        case 'a': return '\a';  // Alert (bell)
        case 'b': return '\b';  // Backspace
        case 'f': return '\f';  // Form feed
        case 'n': return '\n';  // New line
        case 'r': return '\r';  // Carriage return
        case 't': return '\t';  // Horizontal tab
        case 'v': return '\v';  // Vertical tab
        case '\\': return '\\'; // Backslash
        case '\'': return '\''; // Single quote
        case '"': return '"';   // Double quote
        default:
            return -1; // Invalid escape sequence
    }
}

char lexer_currentChar(const Lexer *lexer)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_currentChar: Lexer is NULL.\n");
        return '\0';
    }

    if (lexer->currentPosition >= lexer->sourceBufferSize)
    {
        return '\0'; // End of file
    }

    return lexer->sourceBuffer[lexer->currentPosition];
}

char lexer_nextChar(const Lexer *lexer)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_nextChar: Lexer is NULL.\n");
        return '\0';
    }

    if (lexer->currentPosition + 1 >= lexer->sourceBufferSize)
    {
        return '\0'; // End of file
    }

    return lexer->sourceBuffer[lexer->currentPosition + 1];
}

char lexer_peekChar(const Lexer *lexer, size_t offset)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_peekChar: Lexer is NULL.\n");
        return '\0';
    }

    if (lexer->currentPosition + offset >= lexer->sourceBufferSize)
    {
        return '\0'; // End of file
    }

    return lexer->sourceBuffer[lexer->currentPosition + offset];
}

void lexer_consumeChar(Lexer *lexer, size_t count)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_consumeChar: Lexer is NULL.\n");
        return;
    }

    if (lexer->currentPosition + count >= lexer->sourceBufferSize)
    {
        lexer->currentPosition = lexer->sourceBufferSize; // Move to end of file
        lexer->column += (lexer->sourceBufferSize - lexer->currentPosition + 1);
        return;
    }

    size_t startingPos = lexer->currentPosition;
    size_t endPos = lexer->currentPosition + count;
    
    // Update line and column based on new position
    for (size_t i = startingPos; i < endPos; i++)
    {
        if (lexer->sourceBuffer[i] == '\n')
        {
            lexer->line++;
            lexer->column = 1; // Reset column to 1 for the new line
            lexer->currentLineStart = i + 1; // Update the start of the current line
        }
        else
        {
            lexer->column++;
        }
    }

    lexer->currentPosition = endPos;
}

bool lexer_deleteWhitespaces(Lexer *lexer)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_deleteWhitespaces: Lexer is NULL.\n");
        return true;
    }

    if (!isspace(lexer_currentChar(lexer)))
    {
        return true;
    }    

    while (isspace(lexer_currentChar(lexer)))
    {
        lexer_consumeChar(lexer, 1);
    }

    return false;
}

bool lexer_deleteComments(Lexer *lexer)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_deleteComments: Lexer is NULL.\n");
        return true;
    }

    if (lexer_currentChar(lexer) != '/')
    {
        return true;
    }

    //Consume '/'
    lexer_consumeChar(lexer, 1);

    //Multi-line comment
    if (lexer_currentChar(lexer) == '*')
    {
        //Consume '*'
        lexer_consumeChar(lexer, 1);

        size_t commnetLenght = 2;
        // Break if the current character is '\0' or if the curent character is '*' and next character is '/'
        while (lexer_currentChar(lexer) != '\0' && (lexer_currentChar(lexer) != '*' || lexer_nextChar(lexer) != '/'))
        {
            lexer_consumeChar(lexer, 1);
            commnetLenght++;
        }

        //If we stopped because we found EOF
        if (lexer_currentChar(lexer) == '\0')
        {
            SourceLocation posLoc = {
                .fileName = lexer->fileName,
                .lineStart = lexer->currentLineStart,
                .line = lexer->line,
                .column = lexer->column,
                .length = commnetLenght,
            };
            Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "The multi-line comment was not closed!");
            if (error == NULL)
            {
                DEBUG_PRINT("lexer_deleteComments: Memory allocation for Error failed with errno %d\n", errno);
                return true;
            }
            LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
            if (head == NULL)
            {
                DEBUG_PRINT("lexer_deleteComments: Memory allocation for LinkedList failed with errno %d\n", errno);
                return true;
            }
            lexer->error = head;
            return true;
        }

        //Consume '*'
        lexer_consumeChar(lexer, 1);
        //Consume '/'
        lexer_consumeChar(lexer, 1);

        return false;
    }

    //Single line comment
    if (lexer_currentChar(lexer) == '/')
    {
        //Consume '/'
        lexer_consumeChar(lexer, 1);

        // Break if the current character is '\0' or if the current character is '\n'
        while (lexer_currentChar(lexer) != '\0' && lexer_currentChar(lexer) != '\n') 
        {
            lexer_consumeChar(lexer, 1);
        }

        if (lexer_currentChar(lexer) == '\n')
        {
            lexer_consumeChar(lexer, 1);
        }
    }

    return false;
}

Token *lexer_handleSimpleCase(Lexer *lexer)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_handleSimpleCase: Lexer is NULL.\n");
        return NULL;
    }

    char text[4] = {0};
    size_t pos = 0;
    char c = lexer_currentChar(lexer);
    text[pos++] = c;
    My_TokenType type;
    switch (c)
    {
    case '\0':
        type = TOKEN_EOF;
        break;
    case '~':
        type = TOKEN_TILDE;
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
        if (lexer_nextChar(lexer) == '+')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_DOUBLE_PLUS;
            break;
        }
        else if (lexer_nextChar(lexer) == '=')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_PLUS_EQUALS;
            break;
        }
        type = TOKEN_PLUS;
        break;
    case '-':
        if (lexer_nextChar(lexer) == '-')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_DOUBLE_MINUS;
            break;
        }
        else if (lexer_nextChar(lexer) == '=')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_MINUS_EQUALS;
            break;
        }
        type = TOKEN_MINUS;
        break;
    case '*':
        if (lexer_nextChar(lexer) == '=')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_STAR_EQUALS;
            break;
        }
        type = TOKEN_STAR;
        break;
    case '/':
        if (lexer_nextChar(lexer) == '=')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_SLASH_EQUALS;
            break;
        }
        else if (lexer_nextChar(lexer) == '/' || lexer_nextChar(lexer) == '*')
        {
            return NULL;
        }
        type = TOKEN_SLASH;
        break;
    case '%':
        if (lexer_nextChar(lexer) == '=')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_PERCENT_EQUALS;
            break;
        }
        type = TOKEN_PERCENT;
        break;
    case '=':
        if (lexer_nextChar(lexer) == '=')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_DOUBLE_EQUALS;
            break;
        }
        type = TOKEN_EQUALS;
        break;
    case '!':
        if (lexer_nextChar(lexer) == '=')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_EXCLAMATION_EQUALS;
            break;
        }
        type = TOKEN_EXCLAMATION;
        break;
    case '<':
        if (lexer_nextChar(lexer) == '=')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_LESS_THAN_EQUALS;
            break;
        }
        else if (lexer_nextChar(lexer) == '<')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            if (lexer_nextChar(lexer) == '=')
            {
                lexer_consumeChar(lexer, 1);
                text[pos++] = lexer_currentChar(lexer);
                type = TOKEN_DOUBLE_LESS_THAN_EQUALS;
                break;
            }
            type = TOKEN_DOUBLE_LESS_THAN;
            break;
        }
        type = TOKEN_LESS_THAN;
        break;
    case '>':
        if (lexer_nextChar(lexer) == '=')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_GREATER_THAN_EQUALS;
            break;
        }
        else if (lexer_nextChar(lexer) == '>')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            if (lexer_nextChar(lexer) == '=')
            {
                lexer_consumeChar(lexer, 1);
                text[pos++] = lexer_currentChar(lexer);
                type = TOKEN_DOUBLE_GREATER_THAN_EQUALS;
                break;
            }
            type = TOKEN_DOUBLE_GREATER_THAN;
            break;
        }
        type = TOKEN_GREATER_THAN;
        break;
    case '&':
        if (lexer_nextChar(lexer) == '&')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_DOUBLE_AMPERSAND;
            break;
        }
        else if (lexer_nextChar(lexer) == '=')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_AMPERSAND_EQUALS;
            break;
        }
        type = TOKEN_AMPERSAND;
        break;
    case '|':
        if (lexer_nextChar(lexer) == '|')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_DOUBLE_PIPE;
            break;
        }
        else if (lexer_nextChar(lexer) == '=')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_PIPE_EQUALS;
            break;
        }
        type = TOKEN_PIPE;
        break;
    case '^':
        if (lexer_nextChar(lexer) == '=')
        {
            lexer_consumeChar(lexer, 1);
            text[pos++] = lexer_currentChar(lexer);
            type = TOKEN_CARET_EQUALS;
            break;
        }
        type = TOKEN_CARET;
        break;
    default:
        return NULL;
    }

    lexer_consumeChar(lexer, 1);
    text[pos] = '\0';
    String *str = hashTable_String_tryInsert(lexer->stringInterningTable, text, pos);
    if (str == NULL)
    {
        DEBUG_PRINT("lexer_handleSimpleCase: hashTable_String_tryInsert failed with errno %d\n", errno);
        return NULL;
    }

    SourceLocation posLoc = {
        .fileName = lexer->fileName,
        .lineStart = lexer->currentLineStart,
        .line = lexer->line,
        .column = lexer->column,
        .length = pos
    };
    Token *token = token_create(lexer->tokenArena, type, str->name, posLoc, (TokenValue){0});
    if (token == NULL)
    {
        DEBUG_PRINT("lexer_handleSimpleCase: token_create failed with errno %d\n", errno);
        return NULL;
    }
    return token;
}

Token *lexer_handleNumbers(Lexer *lexer)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_handleNumbers: Lexer is NULL.\n");
        return NULL;
    }

    if (!isdigit(lexer_currentChar(lexer)))
    {
        return NULL;
    }

    size_t size = TEXT_BUFFER_SIZE;
    char *text = (char *)malloc(size * sizeof(char));
    if (text == NULL)
    {
        DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Token text failed with errno %d\n", errno);
        return NULL;
    }
    size_t pos = 0;


    int64_t value = 0;
    bool isOctal = false;
    bool isHexal = false;
    bool isBinary = false;
    double doubleValue = 0.0;
    size_t mantissaCount = 0;

    //Check if the number is either hexadecimal or octal
    if (lexer_currentChar(lexer) == '0')
    {
        //Consume '0'
        text[pos++] = lexer_currentChar(lexer);
        lexer_consumeChar(lexer, 1);

        //Check if the next character is the start of a hexadecimal number
        //Exemple Hexdecimal: 0x1A3F
        if (lexer_currentChar(lexer) == 'x' || lexer_currentChar(lexer) == 'X')
        {
            isHexal = true;
            //Consume 'x' or 'X'
            text[pos++] = lexer_currentChar(lexer);
            lexer_consumeChar(lexer, 1);
        }
        //Check if the next character is the start of an octal number
        //Exemple Octal: 0o123
        else if (lexer_currentChar(lexer) == 'o' || lexer_currentChar(lexer) == 'O')
        {
            isOctal = 1;
            //Consume 'o' or 'O'
            text[pos++] = lexer_currentChar(lexer);
            lexer_consumeChar(lexer, 1);
        }
        //Check if the next character is the start of a binary number
        //Exemple Binary: 0b1010
        else if (lexer_currentChar(lexer) == 'b' || lexer_currentChar(lexer) == 'B')
        {
            isBinary = true;
            //Consume 'b' or 'B'
            text[pos++] = lexer_currentChar(lexer);
            lexer_consumeChar(lexer, 1);
        }
        //Normal 0
        else if (!isalnum(lexer_currentChar(lexer)));
        //Invalid integer
        else
        {
            while (isalnum(lexer_currentChar(lexer)))
            {
                text[pos++] = lexer_currentChar(lexer);
                lexer_consumeChar(lexer, 1);
                if (pos >= size - 1)
                {
                    size *= 2;
                    char *extendedText = realloc(text, size * sizeof(char));
                    if (extendedText == NULL)
                    {
                        DEBUG_PRINT("lexer_handleNumbers: Memory reallocation for Token text failed with errno %d\n", errno);
                        free(text);
                        return NULL;
                    }
                    text = extendedText;
                }
            }

            text[pos] = '\0';
            String *str = string_create(lexer->utilsArena, text, pos, 0);
            if (str == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for String failed with errno %d\n", errno);
                free(text);
                return NULL;
            }
            free(text);

            SourceLocation posLoc = {
                .fileName = lexer->fileName,
                .lineStart = lexer->currentLineStart,
                .line = lexer->line,
                .column = lexer->column,
                .length = pos
            };
            Token *token = token_create(lexer->tokenArena, TOKEN_UNKNOWN, str->name, posLoc, (TokenValue){0});
            if (token == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Token failed with errno %d\n", errno);
                return NULL;
            }

            Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "Invalid integer constant starting with 0");
            if (error == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error failed with errno %d\n", errno);
                return NULL;

            }
            LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
            if (head == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error linked list failed with errno %d\n", errno);
                return NULL;
            }
            lexer->error = head;

            return token;
        }
    }

    //Check if the numbers second character is a 0
    if (lexer_currentChar(lexer) == '0')
    {
        text[pos] = '\0';
        String *str = string_create(lexer->utilsArena, text, pos, 0);
        if (str == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for String failed with errno %d\n", errno);
            free(text);
            return NULL;
        }
        free(text);

        SourceLocation posLoc = {
            .fileName = lexer->fileName,
            .lineStart = lexer->currentLineStart,
            .line = lexer->line,
            .column = lexer->column,
            .length = pos
        };
        Token *token = token_create(lexer->tokenArena, TOKEN_UNKNOWN, str->name, posLoc, (TokenValue){0});
        if (token == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Token failed with errno %d\n", errno);
            return NULL;
        }

        Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "Invalid integer constant starting with 0");
        if (error == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
        if (head == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error linked list failed with errno %d\n", errno);
            return NULL;
        }
        lexer->error = head;
        return token;
    }

    //Binary numbers
    if (isBinary)
    {
        while (lexer_isBinaryDigit(lexer_currentChar(lexer)))
        {
            text[pos++] = lexer_currentChar(lexer);
            int64_t shiftedValue = value << 1; // Multiply by 2 to shift the binary value by 1 so 0b101 becomes 0b1010
            value = shiftedValue + lexer_getBinaryValue(lexer_currentChar(lexer)); // Add the current binary digit value
            lexer_consumeChar(lexer, 1);

            if (pos >= size - 1)
            {
                size *= 2;
                char *extendedText = realloc(text, size * sizeof(char));
                if (extendedText == NULL)
                {
                    DEBUG_PRINT("lexer_handleNumbers: Memory reallocation for Token text failed with errno %d\n", errno);
                    free(text);
                    return NULL;
                }
                text = extendedText;
            }
        }
        
        bool hasInvalidSuffix = false;
        size_t invalidSuffixLength = 0;
        //Handle invalid digits or characters following a binary number
        while (isalnum(lexer_currentChar(lexer)))
        {
            hasInvalidSuffix = true;
            text[pos++] = lexer_currentChar(lexer);
            invalidSuffixLength++;
            lexer_consumeChar(lexer, 1);
            if (pos >= size - 1)
            {
                size *= 2;
                char *extendedText = realloc(text, size * sizeof(char));
                if (extendedText == NULL)
                {
                    DEBUG_PRINT("lexer_handleNumbers: Memory reallocation for Token text failed with errno %d\n", errno);
                    free(text);
                    return NULL;
                }
                text = extendedText;
            }
        }
    
        if (hasInvalidSuffix)
        {
            text[pos] = '\0';
            String *str = string_create(lexer->utilsArena, text, pos, 0);
            if (str == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for String failed with errno %d\n", errno);
                free(text);
                return NULL;
            }
            free(text);

            SourceLocation posLoc = {
                .fileName = lexer->fileName,
                .lineStart = lexer->currentLineStart,
                .line = lexer->line,
                .column = lexer->column,
                .length = pos
            };
            Token *token = token_create(lexer->tokenArena, TOKEN_UNKNOWN, str->name, posLoc, (TokenValue){0});
            if (token == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Token failed with errno %d\n", errno);
                return NULL;
            }

            posLoc.length = invalidSuffixLength;
            Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "Invalid suffix in binary number");
            if (error == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error failed with errno %d\n", errno);
                return NULL;
            }
            LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
            if (head == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error linked list failed with errno %d\n", errno);
                return NULL;
            }
            lexer->error = head;
            return token;
        }
    
        text[pos] = '\0';
        String *string = hashTable_String_tryInsert(lexer->stringInterningTable, text, pos);
        if (string == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for String in hash table failed with errno %d\n", errno);
            free(text);
            return NULL;
        }    
        free(text);

        SourceLocation posLoc = {
            .fileName = lexer->fileName,
            .lineStart = lexer->currentLineStart,
            .line = lexer->line,
            .column = lexer->column,
            .length = pos
        };
        Token *token = token_create(lexer->tokenArena, TOKEN_LITERAL_BINARY, string->name, posLoc, (TokenValue){.int_value = value});
        if (token == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Token failed with errno %d\n", errno);
            return NULL;
        }
        return token;
    }

    //Octal numbers
    if (isOctal)
    {
        while (lexer_isOctalDigit(lexer_currentChar(lexer)))
        {
            text[pos++] = lexer_currentChar(lexer);
            int64_t shiftedValue = value << 3; // Multiply by 8 to shift the octal value by 1 so 0123 becomes 01230
            value = shiftedValue + lexer_getOctalValue(lexer_currentChar(lexer)); // Add the current octal digit value
            lexer_consumeChar(lexer, 1);

            if (pos >= size - 1)
            {
                size *= 2;
                char *extendedText = realloc(text, size * sizeof(char));
                if (extendedText == NULL)
                {
                    DEBUG_PRINT("lexer_handleNumbers: Memory reallocation for Token text failed with errno %d\n", errno);
                    free(text);
                    return NULL;
                }
                text = extendedText;
            }
        }

        bool hasInvalidSuffix = false;
        size_t invalidSuffixLength = 0;
        //Handle invalid digits or characters following an octal number
        while (isalnum(lexer_currentChar(lexer)))
        {
            hasInvalidSuffix = true;
            text[pos++] = lexer_currentChar(lexer);
            invalidSuffixLength++;
            lexer_consumeChar(lexer, 1);

            if (pos >= size - 1)
            {
                size *= 2;
                char *extendedText = realloc(text, size * sizeof(char));
                if (extendedText == NULL)
                {
                    DEBUG_PRINT("lexer_handleNumbers: Memory reallocation for Token text failed with errno %d\n", errno);
                    free(text);
                    return NULL;
                }
                text = extendedText;
            }
            
        }

        if (hasInvalidSuffix)
        {
            text[pos] = '\0';
            String *str = string_create(lexer->utilsArena, text, pos, 0);
            if (str == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for String failed with errno %d\n", errno);
                free(text);
                return NULL;
            }
            free(text);

            SourceLocation posLoc = {
                .fileName = lexer->fileName,
                .lineStart = lexer->currentLineStart,
                .line = lexer->line,
                .column = lexer->column,
                .length = pos
            };
            Token *token = token_create(lexer->tokenArena, TOKEN_UNKNOWN, str->name, posLoc, (TokenValue){0});
            if (token == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Token failed with errno %d\n", errno);
                return NULL;
            }

            posLoc.length = invalidSuffixLength;
            Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "Invalid suffix in octal number");
            if (error == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error failed with errno %d\n", errno);
                return NULL;
            }
            LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
            if (head == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error linked list failed with errno %d\n", errno);
                return NULL;
            }
            lexer->error = head;
            return token;
        }

        text[pos] = '\0';
        String *string = hashTable_String_tryInsert(lexer->stringInterningTable, text, pos);
        if (string == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for String in hash table failed with errno %d\n", errno);
            free(text);
            return NULL;
        }
        free(text);

        SourceLocation posLoc = {
            .fileName = lexer->fileName,
            .lineStart = lexer->currentLineStart,
            .line = lexer->line,
            .column = lexer->column,
            .length = pos
        };
        Token *token = token_create(lexer->tokenArena, TOKEN_LITERAL_OCTAL, string->name, posLoc, (TokenValue){.int_value = value});
        if (token == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Token failed with errno %d\n", errno);
            return NULL;
        }
        return token;
    }

    //Hexadecimal numbers
    if (isHexal)
    {
        while (lexer_isHexalDigit(lexer_currentChar(lexer)))
        {
            text[pos++] = lexer_currentChar(lexer);
            int64_t shiftedValue = value << 4; // Multiply by 16 to shift the hexadecimal value by 1 so 0x1A3 becomes 0x1A30
            value = shiftedValue + lexer_getHexalValue(lexer_currentChar(lexer));
            lexer_consumeChar(lexer, 1);

            if (pos >= size - 1)
            {
                size *= 2;
                char *extendedText = realloc(text, size * sizeof(char));
                if (extendedText == NULL)
                {
                    DEBUG_PRINT("lexer_handleNumbers: Memory reallocation for Token text failed with errno %d\n", errno);
                    free(text);
                    return NULL;
                }
                text = extendedText;
            }
        }

        bool hasInvalidSuffix = false;
        size_t invalidSuffixLength = 0;
        //Handle invalid characters following a hexadecimal number
        while (isalpha(lexer_currentChar(lexer)))
        {
            hasInvalidSuffix = true;
            text[pos++] = lexer_currentChar(lexer);
            lexer_consumeChar(lexer, 1);

            if (pos >= size - 1)
            {
                size *= 2;
                char *extendedText = realloc(text, size * sizeof(char));
                if (extendedText == NULL)
                {
                    DEBUG_PRINT("lexer_handleNumbers: Memory reallocation for Token text failed with errno %d\n", errno);
                    free(text);
                    return NULL;
                }
                text = extendedText;
            }
        }

        if (hasInvalidSuffix)
        {
            text[pos] = '\0';
            String *str = string_create(lexer->utilsArena, text, pos, 0);
            if (str == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for String failed with errno %d\n", errno);
                free(text);
                return NULL;
            }
            free(text);

            SourceLocation posLoc = {
                .fileName = lexer->fileName,
                .lineStart = lexer->currentLineStart,
                .line = lexer->line,
                .column = lexer->column,
                .length = pos
            };
            Token *token = token_create(lexer->tokenArena, TOKEN_UNKNOWN, str->name, posLoc, (TokenValue){0});
            if (token == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Token failed with errno %d\n", errno);
                return NULL;
            }

            posLoc.length = invalidSuffixLength;
            Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "Invalid suffix in hexadecimal number");
            if (error == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error failed with errno %d\n", errno);
                return NULL;
            }
            LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
            if (head == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error linked list failed with errno %d\n", errno);
                return NULL;
            }
            lexer->error = head;
            return token;
        }

        text[pos] = '\0';
        String *string = hashTable_String_tryInsert(lexer->stringInterningTable, text, pos);
        if (string == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for String in hash table failed with errno %d\n", errno);
            free(text);
            return NULL;
        }
        free(text);

        SourceLocation posLoc = {
            .fileName = lexer->fileName,
            .lineStart = lexer->currentLineStart,
            .line = lexer->line,
            .column = lexer->column,
            .length = pos
        };
        Token *token = token_create(lexer->tokenArena, TOKEN_LITERAL_HEXADECIMAL, string->name, posLoc, (TokenValue){.int_value = value});
        if (token == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Token failed with errno %d\n", errno);
            return NULL;
        }
        return token;
    }

    //Integer number part
    while (isdigit(lexer_currentChar(lexer)))
    {
        text[pos++] = lexer_currentChar(lexer);
        int64_t shiftedValue = value * 10; // Multiply by 10 to shift the integer value by 1 so 123 becomes 1230
        value = shiftedValue + (lexer_currentChar(lexer) - '0');
        lexer_consumeChar(lexer, 1);

        if (pos >= size - 4)
        {
            size *= 2;
            char *extendedText = realloc(text, size * sizeof(char));
            if (extendedText == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory reallocation for Token text failed with errno %d\n", errno);
                free(text);
                return NULL;
            }
            text = extendedText;
        }
    }

    //If there is a dot after the integer number part its a floating-point number
    if (lexer_currentChar(lexer) == '.')
    {
        //Consume '.'
        text[pos++] = lexer_currentChar(lexer);
        lexer_consumeChar(lexer, 1);

        while (isdigit(lexer_currentChar(lexer)))
        {
            text[pos++] = lexer_currentChar(lexer);
            int64_t shiftedValue = value * 10; // Multiply by 10 to shift the integer value by 1 so 123.0 becomes 1230.0
            value = shiftedValue + (lexer_currentChar(lexer) - '0');
            mantissaCount++;
            lexer_consumeChar(lexer, 1);
    
            if (pos >= size - 2)
            {
                size *= 2;
                char *extendedText = realloc(text, size * sizeof(char));
                if (extendedText == NULL)
                {
                    DEBUG_PRINT("lexer_handleNumbers: Memory reallocation for Token text failed with errno %d\n", errno);
                    free(text);
                    return NULL;
                }
                text = extendedText;
            }
        }

        bool hasInvalidSuffix = false;
        size_t invalidSuffixLength = 0;
        while (isalnum(lexer_currentChar(lexer)))
        {
            hasInvalidSuffix = true;
            text[pos++] = lexer_currentChar(lexer);
            invalidSuffixLength++;
            lexer_consumeChar(lexer, 1);

            if (pos >= size - 1)
            {
                size *= 2;
                char *extendedText = realloc(text, size * sizeof(char));
                if (extendedText == NULL)
                {
                    DEBUG_PRINT("lexer_handleNumbers: Memory reallocation for Token text failed with errno %d\n", errno);
                    free(text);
                    return NULL;
                }
                text = extendedText;
            }
        }
        
        if (hasInvalidSuffix)
        {
            text[pos] = '\0';
            String *str = string_create(lexer->utilsArena, text, pos, 0);
            if (str == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for String failed with errno %d\n", errno);
                free(text);
                return NULL;
            }
            free(text);

            SourceLocation posLoc = {
                .fileName = lexer->fileName,
                .lineStart = lexer->currentLineStart,
                .line = lexer->line,
                .column = lexer->column,
                .length = pos
            };
            Token *token = token_create(lexer->tokenArena, TOKEN_UNKNOWN, str->name, posLoc, (TokenValue){0});
            if (token == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Token failed with errno %d\n", errno);
                return NULL;
            }

            posLoc.length = invalidSuffixLength;
            Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "Invalid suffix in floating-point number");
            if (error == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error failed with errno %d\n", errno);
                return NULL;
            }
            LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
            if (head == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error linked list failed with errno %d\n", errno);
                return NULL;
            }
            lexer->error = head;
            return token;
        }

        text[pos] = '\0';
        doubleValue = (double) value / (10.0 * mantissaCount); // Convert to double by dividing by 10 raised to the mantissa count

        String *string = hashTable_String_tryInsert(lexer->stringInterningTable, text, pos);
        if (string == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for String in hash table failed with errno %d\n", errno);
            free(text);
            return NULL;
        }
        free(text);

        SourceLocation posLoc = {
            .fileName = lexer->fileName,
            .lineStart = lexer->currentLineStart,
            .line = lexer->line,
            .column = lexer->column,
            .length = pos
        };
        Token *token = token_create(lexer->tokenArena, TOKEN_LITERAL_FLOATINGPOINT, string->name, posLoc, (TokenValue){.float_value = doubleValue});
        if (token == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Token failed with errno %d\n", errno);
            return NULL;
        }
        return token;
    }

    bool hasInvalidSuffix = false;
    size_t invalidSuffixLength = 0;
    while (isalnum(lexer_currentChar(lexer)))
    {
        hasInvalidSuffix = true;
        text[pos++] = lexer_currentChar(lexer);
        invalidSuffixLength++;
        lexer_consumeChar(lexer, 1);

        if (pos >= size - 1)
        {
            size *= 2;
            char *extendedText = realloc(text, size * sizeof(char));
            if (extendedText == NULL)
            {
                DEBUG_PRINT("lexer_handleNumbers: Memory reallocation for Token text failed with errno %d\n", errno);
                free(text);
                return NULL;
            }
            text = extendedText;
        }
    }

    if (hasInvalidSuffix)
    {
        text[pos] = '\0';
        String *str = string_create(lexer->utilsArena, text, pos, 0);
        if (str == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for String failed with errno %d\n", errno);
            free(text);
            return NULL;
        }
        free(text);

        SourceLocation posLoc = {
            .fileName = lexer->fileName,
            .lineStart = lexer->currentLineStart,
            .line = lexer->line,
            .column = lexer->column,
            .length = pos
        };
        Token *token = token_create(lexer->tokenArena, TOKEN_UNKNOWN, str->name, posLoc, (TokenValue){0});
        if (token == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Token failed with errno %d\n", errno);
            return NULL;
        }

        posLoc.length = invalidSuffixLength;
        Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "Invalid suffix in integer number");
        if (error == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
        if (head == NULL)
        {
            DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Error linked list failed with errno %d\n", errno);
            return NULL;
        }
        lexer->error = head;
        return token;
    }

    // Handle invalid digits or characters following an integer number
    text[pos] = '\0';
    String *str = hashTable_String_tryInsert(lexer->stringInterningTable, text, pos);
    if (str == NULL)
    {
        DEBUG_PRINT("lexer_handleNumbers: Memory allocation for String in hash table failed with errno %d\n", errno);
        free(text);
        return NULL;
    }
    free(text);

    SourceLocation posLoc = {
        .fileName = lexer->fileName,
        .lineStart = lexer->currentLineStart,
        .line = lexer->line,
        .column = lexer->column,
        .length = pos
    };
    Token *token = token_create(lexer->tokenArena, TOKEN_LITERAL_INTEGER, str->name, posLoc, (TokenValue){.int_value = value});
    if (token == NULL)
    {
        DEBUG_PRINT("lexer_handleNumbers: Memory allocation for Token failed with errno %d\n", errno);
        return NULL;
    }
    return token;
}

Token *lexer_handleCharacters(Lexer *lexer)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_handleCharacters: Lexer is not initialized.\n");
        return NULL;
    }

    if (lexer_currentChar(lexer) != '\'')
    {
        return NULL;
    }

    char text[5] = {0};
    size_t pos = 0;

    //Consume opening '\''
    text[pos++] = lexer_currentChar(lexer);
    lexer_consumeChar(lexer, 1);

    bool isEscaped = 0;
    //Check for escape sequence
    if (lexer_currentChar(lexer) == '\\')
    {
        isEscaped = true;
        text[pos++] = lexer_currentChar(lexer);
        lexer_consumeChar(lexer, 1);
    }

    //Handle EOF scenario
    if (lexer_currentChar(lexer) == '\0' || lexer_currentChar(lexer) == '\n')
    {
        text[pos] = '\0';
        String *str = string_create(lexer->utilsArena, text, pos, 0);
        if (str == NULL)
        {
            DEBUG_PRINT("lexer_handleCharacters: Memory allocation for String failed with errno %d\n", errno);
            return NULL;
        }

        SourceLocation posLoc = {
            .fileName = lexer->fileName,
            .lineStart = lexer->currentLineStart,
            .line = lexer->line,
            .column = lexer->column,
            .length = pos
        };
        Token *token = token_create(lexer->tokenArena, TOKEN_UNKNOWN, str->name, posLoc, (TokenValue){0});
        if (token == NULL)
        {
            DEBUG_PRINT("lexer_handleCharacters: Memory allocation for Token failed with errno %d\n", errno);
            return NULL;
        }

        Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "The character wasn't closed!");
        if (error == NULL)
        {
            DEBUG_PRINT("lexer_handleCharacters: Memory allocation for Error failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
        if (head == NULL)
        {
            DEBUG_PRINT("lexer_handleCharacters: Memory allocation for Error linked list failed with errno %d\n", errno);
            return NULL;
        }
        lexer->error = head;
        return token;
    }

    if (lexer_currentChar(lexer) != '\'' || isEscaped)
    {
        //Consume character
        text[pos++] = lexer_currentChar(lexer);
        lexer_consumeChar(lexer, 1);
    }
    else
    {
        text[pos++] = lexer_currentChar(lexer);
        lexer_consumeChar(lexer, 1);

        text[pos] = '\0';
        String *str = string_create(lexer->utilsArena, text, pos, 0);
        if (str == NULL)
        {
            DEBUG_PRINT("lexer_handleCharacters: Memory allocation for String failed with errno %d\n", errno);
            return NULL;
        }

        SourceLocation posLoc = {
            .fileName = lexer->fileName,
            .lineStart = lexer->currentLineStart,
            .line = lexer->line,
            .column = lexer->column,
            .length = pos
        };
        Token *token = token_create(lexer->tokenArena, TOKEN_UNKNOWN, str->name, posLoc, (TokenValue){0});
        if (token == NULL)
        {
            DEBUG_PRINT("lexer_handleCharacters: Memory allocation for Token failed with errno %d\n", errno);
            return NULL;
        }

        Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "Empty character constant is not allowed!");
        if (error == NULL)
        {
            DEBUG_PRINT("lexer_handleCharacters: Memory allocation for Error failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
        if (head == NULL)
        {
            DEBUG_PRINT("lexer_handleCharacters: Memory allocation for Error linked list failed with errno %d\n", errno);
            return NULL;
        }
        lexer->error = head;
        return token;
    }

    if (lexer_currentChar(lexer) != '\'' && !isEscaped)
    {
        text[pos++] = lexer_currentChar(lexer);
        lexer_consumeChar(lexer, 1);
        text[pos] = '\0';

        String *str = string_create(lexer->utilsArena, text, pos, 0);
        if (str == NULL)
        {
            DEBUG_PRINT("lexer_handleCharacters: Memory allocation for String failed with errno %d\n", errno);
            return NULL;
        }

        SourceLocation posLoc = {
            .fileName = lexer->fileName,
            .lineStart = lexer->currentLineStart,
            .line = lexer->line,
            .column = lexer->column,
            .length = pos
        };
        Token *token = token_create(lexer->tokenArena, TOKEN_UNKNOWN, str->name, posLoc, (TokenValue){0});
        if (token == NULL)
        {
            DEBUG_PRINT("lexer_handleCharacters: Memory allocation for Token failed with errno %d\n", errno);
            return NULL;
        }

        Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "Multi-character character constant is not allowed!");
        if (error == NULL)
        {
            DEBUG_PRINT("lexer_handleCharacters: Memory allocation for Error failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
        if (head == NULL)
        {
            DEBUG_PRINT("lexer_handleCharacters: Memory allocation for Error linked list failed with errno %d\n", errno);
            return NULL;
        }
        lexer->error = head;
        return token;
    }

    //Consume closing '\''
    text[pos++] = lexer_currentChar(lexer);
    lexer_consumeChar(lexer, 1);

    text[pos] = '\0';

    char retChar = 0; 
    if (!isEscaped)
    {
        retChar = text[1]; // The character is the second character in the text array
    }
    else
    {
        retChar = lexer_getEscapedChar(text[2]);
        if (retChar == -1)
        {
            printf("lexer_handleCharacters: Invalid escape sequence in character constant!\n");
            String *str = string_create(lexer->utilsArena, text, pos, 0);
            if (str == NULL)
            {
                DEBUG_PRINT("lexer_handleCharacters: Memory allocation for String failed with errno %d\n", errno);
                return NULL;
            }

            SourceLocation posLoc = {
                .fileName = lexer->fileName,
                .lineStart = lexer->currentLineStart,
                .line = lexer->line,
                .column = lexer->column,
                .length = pos
            };
            Token *token = token_create(lexer->tokenArena, TOKEN_UNKNOWN, str->name, posLoc, (TokenValue){0});
            if (token == NULL)
            {
                DEBUG_PRINT("lexer_handleCharacters: Memory allocation for Token failed with errno %d\n", errno);
                return NULL;
            }

            Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "Invalid escape sequence in character constant!");
            if (error == NULL)
            {
                DEBUG_PRINT("lexer_handleCharacters: Memory allocation for Error failed with errno %d\n", errno);
                return NULL;
            }
            LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
            if (head == NULL)
            {
                DEBUG_PRINT("lexer_handleCharacters: Memory allocation for Error linked list failed with errno %d\n", errno);
                return NULL;
            }
            lexer->error = head;
            return token;
        }
    }

    String *str = hashTable_String_tryInsert(lexer->stringInterningTable, text, pos);
    if (str == NULL)
    {
        DEBUG_PRINT("lexer_handleCharacters: Memory allocation for String in hash table failed with errno %d\n", errno);
        return NULL;
    }

    SourceLocation posLoc = {
        .fileName = lexer->fileName,
        .lineStart = lexer->currentLineStart,
        .line = lexer->line,
        .column = lexer->column,
        .length = pos
    };
    Token *token = token_create(lexer->tokenArena, TOKEN_LITERAL_CHARACTER, str->name, posLoc, (TokenValue){.char_value = retChar});
    if (token == NULL)
    {
        DEBUG_PRINT("lexer_handleCharacters: Memory allocation for Token failed with errno %d\n", errno);
        return NULL;
    }
    return token;
}

Token *lexer_handleStrings(Lexer *lexer)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_handleStrings: Lexer is not initialized.\n");
        return NULL;
    }

    if (lexer_currentChar(lexer) != '\"')
    {
        return NULL;
    }

    size_t size = TEXT_BUFFER_SIZE;
    char *text = (char *)malloc(size * sizeof(char));
    if (text == NULL)
    {
        DEBUG_PRINT("lexer_handleStrings: Memory allocation for Token text failed.\n");
        return NULL;
    }
    size_t pos = 0;

    //Consume opening '\"'
    text[pos++] = lexer_currentChar(lexer);
    lexer_consumeChar(lexer, 1);

    bool isEscaped = false;
    while ((lexer_currentChar(lexer) != '\"' || isEscaped) && lexer_currentChar(lexer) != '\0' && lexer_currentChar(lexer) != '\n')
    {
        if (lexer_currentChar(lexer) == '\\')
        {
            isEscaped = true;
        }
        else
        {
            isEscaped = false;
        }
        text[pos++] = lexer_currentChar(lexer);
        lexer_consumeChar(lexer, 1);

        if (pos >= size - 2)
        {
            size *= 2;
            char *extendedText = realloc(text, size * sizeof(char));
            if (extendedText == NULL)
            {
                DEBUG_PRINT("lexer_handleStrings: Memory reallocation for Token text failed.\n");
                free(text);
                return NULL;
            }
            text = extendedText;
        }
    }

    //If we stopped because we found EOF or newline, we need to handle the error
    if (lexer_currentChar(lexer) == '\0' || lexer_currentChar(lexer) == '\n')
    {
        text[pos] = '\0';
        String *str = string_create(lexer->utilsArena, text, pos, 0);
        if (str == NULL)
        {
            DEBUG_PRINT("lexer_handleStrings: Memory allocation for String failed with errno %d\n", errno);
            free(text);
            return NULL;
        }
        free(text);

        SourceLocation posLoc = {
            .fileName = lexer->fileName,
            .lineStart = lexer->currentLineStart,
            .line = lexer->line,
            .column = lexer->column,
            .length = pos
        };
        Token *token = token_create(lexer->tokenArena, TOKEN_UNKNOWN, str->name, posLoc, (TokenValue){0});
        if (token == NULL)
        {
            DEBUG_PRINT("lexer_handleStrings: Memory allocation for Token failed with errno %d\n", errno);
            return NULL;
        }

        Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "The string wasn't closed!");
        if (error == NULL)
        {
            DEBUG_PRINT("lexer_handleStrings: Memory allocation for Error failed with errno %d\n", errno);
            return NULL;
        }
        LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
        if (head == NULL)
        {
            DEBUG_PRINT("lexer_handleStrings: Memory allocation for Error linked list failed with errno %d\n", errno);
            return NULL;
        }
        lexer->error = head;
        return token;
    }

    //Consume closing '\"'
    text[pos++] = lexer_currentChar(lexer);
    lexer_consumeChar(lexer, 1);

    text[pos] = '\0';

    String *str = hashTable_String_tryInsert(lexer->stringInterningTable, text, pos);
    if (str == NULL)
    {
        DEBUG_PRINT("lexer_handleStrings: Memory allocation for String in hash table failed with errno %d\n", errno);
        free(text);
        return NULL;
    }
    free(text);

    SourceLocation posLoc = {
        .fileName = lexer->fileName,
        .lineStart = lexer->currentLineStart,
        .line = lexer->line,
        .column = lexer->column,
        .length = pos
    };
    // TODO: Remove the starting and ending " for the value
    Token *token = token_create(lexer->tokenArena, TOKEN_LITERAL_STRING, str->name, posLoc, (TokenValue){.string_value = str->name});
    if (token == NULL)
    {
        DEBUG_PRINT("lexer_handleStrings: Memory allocation for Token failed with errno %d\n", errno);
        return NULL;
    }
    return token;
}

Token *lexer_handleBooleans(Lexer *lexer)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_handleBooleans: Lexer is not initialized.\n");
        return NULL;
    }

    if (lexer_currentChar(lexer) != 't' && lexer_currentChar(lexer) != 'f')
    {
        return NULL;
    }

    size_t size = TEXT_BUFFER_SIZE;
    char *text = (char *)malloc(size * sizeof(char));
    if (text == NULL)
    {
        DEBUG_PRINT("lexer_handleBooleans: Memory allocation for Token text failed with errno %d\n", errno);
        return NULL;
    }

    size_t pos = 0;

    while (isalpha(lexer_peekChar(lexer, pos)))
    {
        text[pos] = lexer_peekChar(lexer, pos);
        pos++;

        if (pos >= size - 1)
        {
            size *= 2;
            char *extendedText = realloc(text, size * sizeof(char));
            if (extendedText == NULL)
            {
                DEBUG_PRINT("lexer_handleBooleans: Memory reallocation for Token text failed with errno %d\n", errno);
                free(text);
                return NULL;
            }
            text = extendedText;
        }
    }

    text[pos] = '\0';
    bool isBoolean = false;
    bool boolValue = false;
    if (strcmp(text, "true") == 0)
    {
        isBoolean = true;
        boolValue = true;
    }
    else if (strcmp(text, "false") == 0)
    {
        isBoolean = true;
        boolValue = false;
    }

    if (!isBoolean)
    {
        free(text);
        return NULL;
    }

    lexer_consumeChar(lexer, pos); // Consume the boolean text
    String *str = hashTable_String_tryInsert(lexer->stringInterningTable, text, pos);
    if (str == NULL)
    {
        DEBUG_PRINT("lexer_handleBooleans: Memory allocation for String in hash table failed with errno %d\n", errno);
        free(text);
        return NULL;
    }
    free(text);

    SourceLocation posLoc = {
        .fileName = lexer->fileName,
        .lineStart = lexer->currentLineStart,
        .line = lexer->line,
        .column = lexer->column,
        .length = pos
    };
    Token *token = token_create(lexer->tokenArena, TOKEN_LITERAL_BOOLEAN, str->name, posLoc, (TokenValue){.boolean_value = boolValue});
    if (token == NULL)
    {
        DEBUG_PRINT("lexer_handleBooleans: Memory allocation for Token failed with errno %d\n", errno);
        return NULL;
    }
    return token;
}

Token *lexer_handleNull(Lexer *lexer)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_handleNull: Lexer is not initialized.\n");
        return NULL;
    }

    if (lexer_currentChar(lexer) != 'n' && lexer_currentChar(lexer) != 'N')
    {
        return NULL;
    }

    size_t size = TEXT_BUFFER_SIZE;
    char *text = (char *)malloc(size * sizeof(char));
    if (text == NULL)
    {
        DEBUG_PRINT("lexer_handleNull: Memory allocation for Token text failed.\n");
        return NULL;
    }

    size_t pos = 0;
    while (isalpha(lexer_peekChar(lexer, pos)))
    {
        text[pos] = lexer_peekChar(lexer, pos);
        pos++;

        if (pos >= size - 1)
        {
            size *= 2;
            char *extendedText = realloc(text, size * sizeof(char));
            if (extendedText == NULL)
            {
                DEBUG_PRINT("lexer_handleNull: Memory reallocation for Token text failed.\n");
                free(text);
                return NULL;
            }
            text = extendedText;
        }
    }

    text[pos] = '\0';
    if (strcmp(text, "null") != 0 && strcmp(text, "NULL") != 0)
    {
        free(text);
        return NULL;
    }

    lexer_consumeChar(lexer, pos); // Consume the null text
    String *str = hashTable_String_tryInsert(lexer->stringInterningTable, text, pos);
    if (str == NULL)
    {
        DEBUG_PRINT("lexer_handleNull: Memory allocation for String in hash table failed with errno %d\n", errno);
        free(text);
        return NULL;
    }
    free(text);

    SourceLocation posLoc = {
        .fileName = lexer->fileName,
        .lineStart = lexer->currentLineStart,
        .line = lexer->line,
        .column = lexer->column,
        .length = pos
    };
    Token *token = token_create(lexer->tokenArena, TOKEN_LITERAL_NULL, str->name, posLoc, (TokenValue){0});
    if (token == NULL)
    {
        DEBUG_PRINT("lexer_handleNull: Memory allocation for Token failed with errno %d\n", errno);
        return NULL;
    }
    return token;
}

Token *lexer_handleIdentifiersAndKeywords(Lexer *lexer)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_handleIdentifiersAndKeywords: Lexer is not initialized.\n");
        return NULL;
    }

    if (!isalpha(lexer_currentChar(lexer)) && lexer_currentChar(lexer) != '_')
    {
        return NULL;
    }

    size_t size = TEXT_BUFFER_SIZE;
    char *text = (char *)malloc(size * sizeof(char));
    if (text == NULL)
    {
        DEBUG_PRINT("lexer_handleIdentifiersAndKeywords: Memory allocation for Token text failed.\n");
        return NULL;
    }
    size_t pos = 0;

    while (isalnum(lexer_currentChar(lexer)) || lexer_currentChar(lexer) == '_'|| isdigit(lexer_currentChar(lexer)))
    {
        text[pos++] = lexer_currentChar(lexer);
        lexer_consumeChar(lexer , 1);

        if (pos >= size - 1)
        {
            size *= 2;
            char *extendedText = realloc(text, size * sizeof(char));
            if (extendedText == NULL)
            {
                DEBUG_PRINT("lexer_handleIdentifiersAndKeywords: Memory reallocation for Token text failed.\n");
                free(text);
                return NULL;
            }
            text = extendedText;
        }
    }

    text[pos] = '\0';
    String *str = hashTable_String_tryInsert(lexer->stringInterningTable, text, pos);
    if (str == NULL)
    {
        DEBUG_PRINT("lexer_handleIdentifiersAndKeywords: Memory allocation for String in hash table failed with errno %d\n", errno);
        free(text);
        return NULL;
    }
    free(text);

    SourceLocation posLoc = {
        .fileName = lexer->fileName,
        .lineStart = lexer->currentLineStart,
        .line = lexer->line,
        .column = lexer->column,
        .length = pos

    };
    My_TokenType keywordType = token_keywordTypeFromString(str->name);
    Token *token = NULL;
    if (keywordType != TOKEN_UNKNOWN)
    {
        token = token_create(lexer->tokenArena, keywordType, str->name, posLoc, (TokenValue){0});
    }
    else
    {
        token = token_create(lexer->tokenArena, TOKEN_IDENTIFIER, str->name, posLoc, (TokenValue){0});
    }

    if (token == NULL)
    {
        DEBUG_PRINT("lexer_handleIdentifiersAndKeywords: Memory allocation for Token failed with errno %d\n", errno);
        return NULL;
    }
    return token;
}

// ---------------------------------------------------------------------------

Lexer *lexer_create(Arena *utilsArena, Arena *tokenArena, HashTable *stringInterningTable, const char *fileName, const char *sourceBuffer, size_t sourceBufferSize)
{
    if (utilsArena == NULL)
    {
        DEBUG_PRINT("lexer_create: utilsArena is NULL.\n");
        return NULL;
    }

    if (tokenArena == NULL)
    {
        DEBUG_PRINT("lexer_create: tokenArena is NULL.\n");
        return NULL;
    }

    if (stringInterningTable == NULL)
    {
        DEBUG_PRINT("lexer_create: stringInterningTable is NULL.\n");
        return NULL;
    }

    if (fileName == NULL)
    {
        DEBUG_PRINT("lexer_create: fileName is NULL.\n");
        return NULL;
    }

    if (sourceBuffer == NULL)
    {
        DEBUG_PRINT("lexer_create: sourceBuffer is NULL.\n");
        return NULL;
    }

    if (sourceBufferSize == 0)
    {
        DEBUG_PRINT("lexer_create: sourceBufferSize is 0.\n");
        return NULL;
    }

    Lexer *lexer = (Lexer *)arena_alloc(utilsArena, sizeof(Lexer), alignof(Lexer));
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_create: arena_alloc failed with errno %d\n", errno);
        return NULL;
    }

    lexer->utilsArena = utilsArena;
    lexer->tokenArena = tokenArena;
    lexer->error = NULL; // Initialize error list as NULL
    lexer->tokens = NULL; // Initialize tokens list as NULL
    lexer->stringInterningTable = stringInterningTable;
    lexer->fileName = fileName;
    lexer->sourceBuffer = sourceBuffer;
    lexer->sourceBufferSize = sourceBufferSize;
    lexer->currentPosition = 0;
    lexer->currentLineStart = 0;
    lexer->line = 1; // Start at line 1
    lexer->column = 1; // Start at column 1
    return lexer;
}

void lexer_lex(Lexer* lexer)
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_lex: Lexer is NULL.\n");
        return;
    }

    Token *currentToken = NULL;
    do 
    {
        currentToken = NULL;

        bool noWhiteSpace = false;
        bool noComment = false;
        do {
            noWhiteSpace = lexer_deleteWhitespaces(lexer);
            noComment =  lexer_deleteComments(lexer);
        } while (!(noWhiteSpace && noComment));

        if (currentToken == NULL) currentToken = lexer_handleSimpleCase(lexer);
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("lexer_lex: lexer_handleSimpleCase failed with errno %d\n", errno);
            return;
        }
        
        if (currentToken == NULL) currentToken = lexer_handleNumbers(lexer);
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("lexer_lex: lexer_handleNumbers failed with errno %d\n", errno);
            return;
        }
        
        if (currentToken == NULL) currentToken = lexer_handleCharacters(lexer);
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("lexer_lex: lexer_handleCharacters failed with errno %d\n", errno);
            return;
        }

        if (currentToken == NULL) currentToken = lexer_handleStrings(lexer);
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("lexer_lex: lexer_handleStrings failed with errno %d\n", errno);
            return;
        }

        if (currentToken == NULL) currentToken = lexer_handleBooleans(lexer);
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("lexer_lex: lexer_handleBooleans failed with errno %d\n", errno);
            return;
        }

        if (currentToken == NULL) currentToken = lexer_handleNull(lexer);
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("lexer_lex: lexer_handleNull failed with errno %d\n", errno);
            return;
        }

        if (currentToken == NULL) currentToken = lexer_handleIdentifiersAndKeywords(lexer);
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("lexer_lex: lexer_handleIdentifiersAndKeywords failed with errno %d\n", errno);
            return;
        }

        //Unknown
        if(currentToken == NULL)
        {
            printf("before pos: %zu", lexer->column);
            char unknownChar[2] = {0};
            unknownChar[0] = lexer_currentChar(lexer);
            lexer_consumeChar(lexer, 1);
            unknownChar[1] = '\0';
            printf("after pos: %zu\n", lexer->column);

            String *str = string_create(lexer->utilsArena, unknownChar, 1, 0);
            if (str == NULL)
            {
                DEBUG_PRINT("lexer_lex: Memory allocation for String failed with errno %d\n", errno);
                return;
            }

            SourceLocation posLoc = {
                .fileName = lexer->fileName,
                .lineStart = lexer->currentLineStart,
                .line = lexer->line,
                .column = lexer->column - 1,
                .length = 1
            };
            currentToken = token_create(lexer->tokenArena, TOKEN_UNKNOWN, str->name, posLoc, (TokenValue){0});
            if (currentToken == NULL)
            {
                DEBUG_PRINT("lexer_lex: Memory allocation for Token failed with errno %d\n", errno);
                return;
            }

            Error *error = error_create(lexer->utilsArena, ERROR_ERROR, posLoc, "Unknown character");
            if (error == NULL)
            {
                DEBUG_PRINT("lexer_lex: Memory allocation for Error failed with errno %d\n", errno);
                return;
            }
            LinkedList *head = linkedList_Error_create(lexer->utilsArena, lexer->error, error);
            if (head == NULL)
            {
                DEBUG_PRINT("lexer_lex: Memory allocation for Error linked list failed with errno %d\n", errno);
                return;
            }
            lexer->error = head;
        }

        LinkedList *head = linkedList_Token_create(lexer->tokenArena, lexer->tokens, currentToken);
        if (head == NULL)
        { 
            DEBUG_PRINT("lexer_lex: linkedList_Token_create failed with errno %d\n", errno);
            return;
        }
        lexer->tokens = head;
    } while (currentToken->type != TOKEN_EOF);
}

void lexer_print(const Lexer* lexer)    
{
    if (lexer == NULL)
    {
        DEBUG_PRINT("lexer_print: Lexer is NULL.\n");
        return;
    }

    printf("Lexer: {\n");
    printf("    utilsArena:\n");
    arena_print(lexer->utilsArena);
    printf("    tokenArena:\n");
    arena_print(lexer->tokenArena);
    printf("    tokens:\n");
    if (lexer->tokens != NULL)
    {
        linkedList_print(lexer->tokens, (PrintFunction)token_print);
    }
    else
    {
        printf("NULL\n");
    }
    printf("    stringInterningTable:\n");
    hashTable_print(lexer->stringInterningTable, (PrintFunction)string_print);
    printf("    sourceBuffer: \"%.*s\"\n", (int)lexer->sourceBufferSize, lexer->sourceBuffer);
    printf("    sourceBufferSize: %zu\n", lexer->sourceBufferSize);
    printf("    currentPosition: %zu\n", lexer->currentPosition);
    printf("    line: %zu\n", lexer->line);
    printf("    column: %zu\n", lexer->column);
    printf("}\n");
}