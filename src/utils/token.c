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
    [TOKEN_DOUBLE_LESS_THEN_EQUALS] = "TOKEN_DOUBLE_LESS_THEN_EQUALS",
    [TOKEN_DOUBLE_GREATER_THEN_EQUALS] = "TOKEN_DOUBLE_GREATER_THEN_EQUALS",
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
    [TOKEN_LITERAL_BOOLEAN] = "TOKEN_LITERAL_BOOLEAN",
    [TOKEN_LITERAL_INTEGER] = "TOKEN_LITERAL_INTEGER",
    [TOKEN_LITERAL_FLOATINGPOINT] = "TOKEN_LITERAL_FLOATINGPOINT",
    [TOKEN_LITERAL_CHARACTER] = "TOKEN_LITERAL_CHARACTER",
    [TOKEN_LITERAL_STRING] = "TOKEN_LITERAL_STRING",
    [TOKEN_LITERAL_HEXADECIMAL] = "TOKEN_LITERAL_HEXADECIMAL",
    [TOKEN_LITERAL_OCTAL] = "TOKEN_LITERAL_OCTAL",
    [TOKEN_LITERAL_NULL] = "TOKEN_LITERAL_NULL",
    [TOKEN_IDENTIFIER] = "TOKEN_IDENTIFIER",
    [TOKEN_KEYWORD_EXTERN] = "TOKEN_KEYWORD_EXTERN",
    [TOKEN_KEYWORD_AUTO] = "TOKEN_KEYWORD_AUTO",
    [TOKEN_KEYWORD_REGISTER] = "TOKEN_KEYWORD_REGISTER",
    [TOKEN_KEYWORD_RESTRICT] = "TOKEN_KEYWORD_RESTRICT",
    [TOKEN_KEYWORD_VOLATILE] = "TOKEN_KEYWORD_VOLATILE",
    [TOKEN_KEYWORD_STATIC] = "TOKEN_KEYWORD_STATIC",
    [TOKEN_KEYWORD_INLINE] = "TOKEN_KEYWORD_INLINE",
    [TOKEN_KEYWORD_TYPEDEF] = "TOKEN_KEYWORD_TYPEDEF",
    [TOKEN_KEYWORD_VOID] = "TOKEN_KEYWORD_VOID",
    [TOKEN_KEYWORD_CHAR] = "TOKEN_KEYWORD_CHAR",
    [TOKEN_KEYWORD_STRING] = "TOKEN_KEYWORD_STRING",
    [TOKEN_KEYWORD_BOOL] = "TOKEN_KEYWORD_BOOL",
    [TOKEN_KEYWORD_SHORT] = "TOKEN_KEYWORD_SHORT",
    [TOKEN_KEYWORD_INT] = "TOKEN_KEYWORD_INT",
    [TOKEN_KEYWORD_HEX] = "TOKEN_KEYWORD_HEX",
    [TOKEN_KEYWORD_OCT] = "TOKEN_KEYWORD_OCT",
    [TOKEN_KEYWORD_LONG] = "TOKEN_KEYWORD_LONG",
    [TOKEN_KEYWORD_FLOAT] = "TOKEN_KEYWORD_FLOAT",
    [TOKEN_KEYWORD_DOUBLE] = "TOKEN_KEYWORD_DOUBLE",
    [TOKEN_KEYWORD_SIGNED] = "TOKEN_KEYWORD_SIGNED",
    [TOKEN_KEYWORD_UNSIGNED] = "TOKEN_KEYWORD_UNSIGNED",
    [TOKEN_KEYWORD_STRUCT] = "TOKEN_KEYWORD_STRUCT",
    [TOKEN_KEYWORD_UNION] = "TOKEN_KEYWORD_UNION",
    [TOKEN_KEYWORD_CONST] = "TOKEN_KEYWORD_CONST",
    [TOKEN_KEYWORD_SIZEOF] = "TOKEN_KEYWORD_SIZEOF",
    [TOKEN_KEYWORD_ENUM] = "TOKEN_KEYWORD_ENUM",
    [TOKEN_KEYWORD_CASE] = "TOKEN_KEYWORD_CASE",
    [TOKEN_KEYWORD_DEFAULT] = "TOKEN_KEYWORD_DEFAULT",
    [TOKEN_KEYWORD_IF] = "TOKEN_KEYWORD_IF",
    [TOKEN_KEYWORD_ELSE] = "TOKEN_KEYWORD_ELSE",
    [TOKEN_KEYWORD_SWITCH] = "TOKEN_KEYWORD_SWITCH",
    [TOKEN_KEYWORD_WHILE] = "TOKEN_KEYWORD_WHILE",
    [TOKEN_KEYWORD_DO] = "TOKEN_KEYWORD_DO",
    [TOKEN_KEYWORD_FOR] = "TOKEN_KEYWORD_FOR",
    [TOKEN_KEYWORD_GOTO] = "TOKEN_KEYWORD_GOTO",
    [TOKEN_KEYWORD_CONTINUE] = "TOKEN_KEYWORD_CONTINUE",
    [TOKEN_KEYWORD_BREAK] = "TOKEN_KEYWORD_BREAK",
    [TOKEN_KEYWORD_RETURN] = "TOKEN_KEYWORD_RETURN",
    [TOKEN_COMMA] = "TOKEN_COMMA",
    [TOKEN_SEMICOLON] = "TOKEN_SEMICOLON",
    [TOKEN_COLON] = "TOKEN_COLON",
    [TOKEN_DOT] = "TOKEN_DOT",
    [TOKEN_ARROW] = "TOKEN_ARROW",
    [TOKEN_QUESTION_MARK] = "TOKEN_QUESTION_MARK",
    [TOKEN_EOF] = "TOKEN_EOF",
    [TOKEN_UNKNOWN] = "TOKEN_UNKNOWN",
};

/**
 * Lookup table for keywords
 */
static const char *token_keywordsAsStrings[] = {
    [TOKEN_KEYWORD_EXTERN] = "extern",
    [TOKEN_KEYWORD_AUTO] = "auto",
    [TOKEN_KEYWORD_REGISTER] = "register",
    [TOKEN_KEYWORD_RESTRICT] = "restrict",
    [TOKEN_KEYWORD_VOLATILE] = "volatile",
    [TOKEN_KEYWORD_STATIC] = "static",
    [TOKEN_KEYWORD_INLINE] = "inline",
    [TOKEN_KEYWORD_TYPEDEF] = "typedef",
    [TOKEN_KEYWORD_VOID] = "void",
    [TOKEN_KEYWORD_CHAR] = "char",
    [TOKEN_KEYWORD_STRING] = "string",
    [TOKEN_KEYWORD_BOOL] = "bool",
    [TOKEN_KEYWORD_SHORT] = "short",
    [TOKEN_KEYWORD_INT] = "int",
    [TOKEN_KEYWORD_HEX] = "hex",
    [TOKEN_KEYWORD_OCT] = "oct",
    [TOKEN_KEYWORD_LONG] = "long",
    [TOKEN_KEYWORD_FLOAT] = "float",
    [TOKEN_KEYWORD_DOUBLE] = "double",
    [TOKEN_KEYWORD_SIGNED] = "signed",
    [TOKEN_KEYWORD_UNSIGNED] = "unsigned",
    [TOKEN_KEYWORD_STRUCT] = "struct",
    [TOKEN_KEYWORD_UNION] = "union",
    [TOKEN_KEYWORD_CONST] = "const",
    [TOKEN_KEYWORD_SIZEOF] = "sizeof",
    [TOKEN_KEYWORD_ENUM] = "enum",
    [TOKEN_KEYWORD_CASE] = "case",
    [TOKEN_KEYWORD_DEFAULT] = "default",
    [TOKEN_KEYWORD_IF] = "if",
    [TOKEN_KEYWORD_ELSE] = "else",
    [TOKEN_KEYWORD_SWITCH] = "switch",
    [TOKEN_KEYWORD_WHILE] = "while",
    [TOKEN_KEYWORD_DO] = "do",
    [TOKEN_KEYWORD_FOR] = "for",
    [TOKEN_KEYWORD_GOTO] = "goto",
    [TOKEN_KEYWORD_CONTINUE] = "continue",
    [TOKEN_KEYWORD_BREAK] = "break",
    [TOKEN_KEYWORD_RETURN] = "return",
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
        case TOKEN_LITERAL_FLOATINGPOINT:
            printf("%lf\n", token->value.float_value);
            break;
        case TOKEN_LITERAL_BOOLEAN:
            printf("%s\n", token->value.boolean_value ? "true" : "false");
            break;
        case TOKEN_LITERAL_CHARACTER:
            printf("'%d'\n", token->value.char_value);
            break;
        case TOKEN_LITERAL_STRING:
            printf("\"%s\"\n", token->value.string_value);
            break;
        case TOKEN_LITERAL_HEXADECIMAL:
            printf("0x%" PRIx64 "\n", token->value.int_value);
            break;
        case TOKEN_LITERAL_OCTAL:
            printf("0%" PRIo64" \n", token->value.int_value);
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