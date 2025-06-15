#include "utils/token.h"

/**
 * Lookup table for My_TokenType
 */
static const char *token_typeAsStrings[] = {
    [TOKEN_PLUS] = "TOKEN_PLUS",
    [TOKEN_DOUBLE_PLUS] = "TOKEN_DOUBLE_PLUS",
    [TOKEN_MINUS] = "TOKEN_MINUS",
    [TOKEN_DOUBLE_MINUS] = "TOKEN_DOUBLE_MINUS",
    [TOKEN_STAR] = "TOKEN_STAR",
    [TOKEN_SLASH] = "TOKEN_SLASH",
    [TOKEN_PERCENT] = "TOKEN_PERCENT",
    [TOKEN_PLUS_EQUALS] = "TOKEN_PLUS_EQUALS",
    [TOKEN_MINUS_EQUALS] = "TOKEN_MINUS_EQUALS",
    [TOKEN_STAR_EQUALS] = "TOKEN_STAR_EQUALS",
    [TOKEN_SLASH_EQUALS] = "TOKEN_SLASH_EQUALS",
    [TOKEN_PERCENT_EQUALS] = "TOKEN_PERCENT_EQUALS",
    [TOKEN_DOUBLE_LESS_THAN_EQUALS] = "TOKEN_DOUBLE_LESS_THAN_EQUALS",
    [TOKEN_DOUBLE_GREATER_THAN_EQUALS] = "TOKEN_DOUBLE_GREATER_THAN_EQUALS",
    [TOKEN_AMPERSAND_EQUALS] = "TOKEN_AMPERSAND_EQUALS",
    [TOKEN_CARET_EQUALS] = "TOKEN_CARET_EQUALS",
    [TOKEN_PIPE_EQUALS] = "TOKEN_PIPE_EQUALS",
    [TOKEN_EQUALS] = "TOKEN_EQUALS",
    [TOKEN_DOUBLE_EQUALS] = "TOKEN_DOUBLE_EQUALS",
    [TOKEN_EXCLAMATION_EQUALS] = "TOKEN_EXCLAMATION_EQUALS",
    [TOKEN_LESS_THAN] = "TOKEN_LESS_THAN",
    [TOKEN_GREATER_THAN] = "TOKEN_GREATER_THAN",
    [TOKEN_LESS_THAN_EQUALS] = "TOKEN_LESS_THAN_EQUALS",
    [TOKEN_GREATER_THAN_EQUALS] = "TOKEN_GREATER_THAN_EQUALS",
    [TOKEN_DOUBLE_AMPERSAND] = "TOKEN_DOUBLE_AMPERSAND",
    [TOKEN_DOUBLE_PIPE] = "TOKEN_DOUBLE_PIPE",
    [TOKEN_EXCLAMATION] = "TOKEN_EXCLAMATION",
    [TOKEN_AMPERSAND] = "TOKEN_AMPERSAND",
    [TOKEN_PIPE] = "TOKEN_PIPE",
    [TOKEN_CARET] = "TOKEN_CARET",
    [TOKEN_TILDE] = "TOKEN_TILDE",
    [TOKEN_DOUBLE_LESS_THAN] = "TOKEN_DOUBLE_LESS_THAN",
    [TOKEN_DOUBLE_GREATER_THAN] = "TOKEN_DOUBLE_GREATER_THAN",
    [TOKEN_OPEN_PARENTHESIS] = "TOKEN_OPEN_PARENTHESIS",
    [TOKEN_CLOSE_PARENTHESIS] = "TOKEN_CLOSE_PARENTHESIS",
    [TOKEN_OPEN_BRACKET] = "TOKEN_OPEN_BRACKET",
    [TOKEN_CLOSE_BRACKET] = "TOKEN_CLOSE_BRACKET",
    [TOKEN_OPEN_CURLY] = "TOKEN_OPEN_CURLY",
    [TOKEN_CLOSE_CURLY] = "TOKEN_CLOSE_CURLY",
    [TOKEN_LITERAL_INTEGER] = "TOKEN_LITERAL_INTEGER",
    [TOKEN_LITERAL_BINARY] = "TOKEN_LITERAL_BINARY",
    [TOKEN_LITERAL_OCTAL] = "TOKEN_LITERAL_OCTAL",
    [TOKEN_LITERAL_HEXADECIMAL] = "TOKEN_LITERAL_HEXADECIMAL",
    [TOKEN_LITERAL_FLOATINGPOINT] = "TOKEN_LITERAL_FLOATINGPOINT",
    [TOKEN_LITERAL_CHARACTER] = "TOKEN_LITERAL_CHARACTER",
    [TOKEN_LITERAL_STRING] = "TOKEN_LITERAL_STRING",
    [TOKEN_LITERAL_BOOLEAN] = "TOKEN_LITERAL_BOOLEAN",
    [TOKEN_LITERAL_NULL] = "TOKEN_LITERAL_NULL",
    [TOKEN_IDENTIFIER] = "TOKEN_IDENTIFIER",
    [TOKEN_KEYWORD_INT_64] = "TOKEN_KEYWORD_INT_64",
    [TOKEN_KEYWORD_INT_32] = "TOKEN_KEYWORD_INT_32",
    [TOKEN_KEYWORD_INT_16] = "TOKEN_KEYWORD_INT_16",
    [TOKEN_KEYWORD_INT_8] = "TOKEN_KEYWORD_INT_8",
    [TOKEN_KEYWORD_UINT_64] = "TOKEN_KEYWORD_UINT_64",
    [TOKEN_KEYWORD_UINT_32] = "TOKEN_KEYWORD_UINT_32",
    [TOKEN_KEYWORD_UINT_16] = "TOKEN_KEYWORD_UINT_16",
    [TOKEN_KEYWORD_UINT_8] = "TOKEN_KEYWORD_UINT_8",
    [TOKEN_KEYWORD_FLOAT_64] = "TOKEN_KEYWORD_FLOAT_64",
    [TOKEN_KEYWORD_FLOAT_32] = "TOKEN_KEYWORD_FLOAT_32",
    [TOKEN_KEYWORD_CHAR] = "TOKEN_KEYWORD_CHAR",
    [TOKEN_KEYWORD_STRING] = "TOKEN_KEYWORD_STRING",
    [TOKEN_KEYWORD_BOOL] = "TOKEN_KEYWORD_BOOL",
    [TOKEN_KEYWORD_VOID] = "TOKEN_KEYWORD_VOID",
    [TOKEN_KEYWORD_TYPEDEF] = "TOKEN_KEYWORD_TYPEDEF",
    [TOKEN_KEYWORD_CONST] = "TOKEN_KEYWORD_CONST",
    [TOKEN_KEYWORD_CONST_PTR] = "TOKEN_KEYWORD_CONST_PTR",
    [TOKEN_KEYWORD_PTR] = "TOKEN_KEYWORD_PTR",
    [TOKEN_KEYWORD_IF] = "TOKEN_KEYWORD_IF",
    [TOKEN_KEYWORD_ELSE] = "TOKEN_KEYWORD_ELSE",
    [TOKEN_KEYWORD_ENDIF] = "TOKEN_KEYWORD_ENDIF",
    [TOKEN_KEYWORD_SWITCH] = "TOKEN_KEYWORD_SWITCH",
    [TOKEN_KEYWORD_CASE] = "TOKEN_KEYWORD_CASE",
    [TOKEN_KEYWORD_DEFAULT] = "TOKEN_KEYWORD_DEFAULT",
    [TOKEN_KEYWORD_FOR] = "TOKEN_KEYWORD_FOR",
    [TOKEN_KEYWORD_FOREACH] = "TOKEN_KEYWORD_FOREACH",
    [TOKEN_KEYWORD_WHILE] = "TOKEN_KEYWORD_WHILE",
    [TOKEN_KEYWORD_DO] = "TOKEN_KEYWORD_DO",
    [TOKEN_KEYWORD_RETURN] = "TOKEN_KEYWORD_RETURN",
    [TOKEN_KEYWORD_CONTINUE] = "TOKEN_KEYWORD_CONTINUE",
    [TOKEN_KEYWORD_BREAK] = "TOKEN_KEYWORD_BREAK",
    [TOKEN_KEYWORD_GOTO] = "TOKEN_KEYWORD_GOTO",
    [TOKEN_KEYWORD_WHEN] = "TOKEN_KEYWORD_WHEN",
    [TOKEN_KEYWORD_STRUCT] = "TOKEN_KEYWORD_STRUCT",
    [TOKEN_KEYWORD_UNION] = "TOKEN_KEYWORD_UNION",
    [TOKEN_KEYWORD_ENUM] = "TOKEN_KEYWORD_ENUM",
    [TOKEN_KEYWORD_IMPORT] = "TOKEN_KEYWORD_IMPORT",
    [TOKEN_KEYWORD_FROM] = "TOKEN_KEYWORD_FROM",
    [TOKEN_KEYWORD_EXPORT] = "TOKEN_KEYWORD_EXPORT",
    [TOKEN_COMMA] = "TOKEN_COMMA",
    [TOKEN_SEMICOLON] = "TOKEN_SEMICOLON",
    [TOKEN_COLON] = "TOKEN_COLON",
    [TOKEN_DOT] = "TOKEN_DOT",
    [TOKEN_EOF] = "TOKEN_EOF",
    [TOKEN_UNKNOWN] = "TOKEN_UNKNOWN",
};

/**
 * Lookup table for keywords
 */
static const char *token_keywordsAsStrings[] = {
    [TOKEN_KEYWORD_INT_64] = "int64",
    [TOKEN_KEYWORD_INT_32] = "int32",
    [TOKEN_KEYWORD_INT_16] = "int16",
    [TOKEN_KEYWORD_INT_8] = "int8",
    [TOKEN_KEYWORD_UINT_64] = "uint64",
    [TOKEN_KEYWORD_UINT_32] = "uint32",
    [TOKEN_KEYWORD_UINT_16] = "uint16",
    [TOKEN_KEYWORD_UINT_8] = "uint8",
    [TOKEN_KEYWORD_FLOAT_64] = "float64",
    [TOKEN_KEYWORD_FLOAT_32] = "float32",
    [TOKEN_KEYWORD_CHAR] = "char",
    [TOKEN_KEYWORD_STRING] = "string",
    [TOKEN_KEYWORD_BOOL] = "bool",
    [TOKEN_KEYWORD_VOID] = "void",
    [TOKEN_KEYWORD_TYPEDEF] = "typedef",
    [TOKEN_KEYWORD_CONST] = "const",
    [TOKEN_KEYWORD_CONST_PTR] = "const_ptr",
    [TOKEN_KEYWORD_PTR] = "ptr",
    [TOKEN_KEYWORD_IF] = "if",
    [TOKEN_KEYWORD_ENDIF] = "endif",
    [TOKEN_KEYWORD_ELSE] = "else",
    [TOKEN_KEYWORD_SWITCH] = "switch",
    [TOKEN_KEYWORD_CASE] = "case",
    [TOKEN_KEYWORD_DEFAULT] = "default",
    [TOKEN_KEYWORD_FOR] = "for",
    [TOKEN_KEYWORD_FOREACH] = "foreach",
    [TOKEN_KEYWORD_WHILE] = "while",
    [TOKEN_KEYWORD_DO] = "do",
    [TOKEN_KEYWORD_RETURN] = "return",
    [TOKEN_KEYWORD_CONTINUE] = "continue",
    [TOKEN_KEYWORD_BREAK] = "break",
    [TOKEN_KEYWORD_GOTO] = "goto",
    [TOKEN_KEYWORD_WHEN] = "when",
    [TOKEN_KEYWORD_STRUCT] = "struct",
    [TOKEN_KEYWORD_UNION] = "union",
    [TOKEN_KEYWORD_ENUM] = "enum",
    [TOKEN_KEYWORD_IMPORT] = "import",
    [TOKEN_KEYWORD_FROM] = "from",
    [TOKEN_KEYWORD_EXPORT] = "export",
};

Token *token_create(Arena *arena, My_TokenType type, const char *text, size_t length, size_t line, size_t column, TokenValue value)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("token_create: arena is NULL\n");
        return NULL;
    }

    if (type >= TOKEN_TYPE_COUNT || type == TOKEN_KEYWORD_FIRST || type == TOKEN_KEYWORD_LAST)
    {
        DEBUG_PRINT("token_create: invalid token type %d\n", type);
        return NULL;
    }

    if (text == NULL)
    {
        DEBUG_PRINT("token_create: text is NULL\n");
        return NULL;
    }

    Token *token = (Token *)arena_alloc(arena, sizeof(Token), alignof(Token));
    if (token == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("token_create: arena_alloc failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("token_create: arena_alloc failed with unknown error\n");
        }

        return NULL;
    }

    token->type = type;
    token->text = text;
    token->length = length;
    token->line = line;
    token->column = column;
    token->value = value;

    return token;
}

Token *token_copy(Arena *arena, const Token *token)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("token_copy: arena is NULL\n");
        return NULL;
    }

    if (token == NULL)
    {
        DEBUG_PRINT("token_copy: token is NULL\n");
        return NULL;
    }

    TokenValue value = token->value; // Copy the value union

    Token *new_token = token_create(arena, token->type, token->text, token->length, token->line, token->column, value);
    if (new_token == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("token_copy: token_create failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("token_copy: token_create failed with unknown error\n");
        }

        return NULL;
    }

    return new_token;
}

void token_print(const Token *token)
{
    if (token == NULL)
    {
        DEBUG_PRINT("token_print: token is NULL\n");
        return;
    }

    printf("Token {\n");
    printf("    Type   : %s\n", token_typeToString(token->type));
    printf("    Text   : \"%s\"\n", token->text);
    printf("    Length : %zu\n", token->length);
    printf("    Line   : %zu\n", token->line);
    printf("    Column : %zu\n", token->column);
    printf("    Value  : ");
    switch (token->type)
    {
        case TOKEN_LITERAL_INTEGER:
            printf("%" PRId64 "\n", token->value.int_value);
            break;
        case TOKEN_LITERAL_BINARY:
            printf("0b%" PRIx64 "\n", token->value.int_value); // TODO handle binary format
            break;
        case TOKEN_LITERAL_OCTAL:
            printf("0%" PRIo64" \n", token->value.int_value);
            break;
        case TOKEN_LITERAL_HEXADECIMAL:
            printf("0x%" PRIx64 "\n", token->value.int_value);
            break;
        case TOKEN_LITERAL_FLOATINGPOINT:
            printf("%lf\n", token->value.float_value);
            break;
        case TOKEN_LITERAL_CHARACTER:
            printf("'%d'\n", token->value.char_value);
            break;
        case TOKEN_LITERAL_STRING:
            printf("\"%s\"\n", token->value.string_value);
            break;
        case TOKEN_LITERAL_BOOLEAN:
            printf("%s\n", token->value.boolean_value ? "true" : "false");
            break;
        case TOKEN_LITERAL_NULL:
            printf("NULL\n");
            break;
        default:
            printf("N/A\n");
            break;
    }
    printf("}\n");
}

My_TokenType token_keywordTypeFromString(const char *str)
{
    if (str == NULL)
    {
        DEBUG_PRINT("token_keywordTypeFromString: string is NULL\n");
        return TOKEN_UNKNOWN;
    }

    const int firstKeyword = TOKEN_KEYWORD_FIRST + 1;
    for (int i = firstKeyword; i < TOKEN_KEYWORD_LAST; i++)
    {
        if (strcmp(str, token_keywordsAsStrings[i]) == 0)
        {
            return (My_TokenType)i;
        }
    }

    return TOKEN_UNKNOWN;
}

const char *token_typeToString(My_TokenType type)
{
    if (type < 0 || type >= TOKEN_TYPE_COUNT || type == TOKEN_KEYWORD_FIRST || type == TOKEN_KEYWORD_LAST)
    {
        DEBUG_PRINT("token_typeToString: invalid token type %d\n", type);
        return NULL;
    }

    return token_typeAsStrings[type];
}