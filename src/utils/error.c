#include "utils/error.h"

Error *error_create(Arena *arena, ErrorType type, size_t length, size_t line, size_t column, const char *message)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("error_create: arena is NULL\n");
        return NULL;
    }

    if (type < 0 || type >= ERROR_FATAL)
    {
        DEBUG_PRINT("error_create: invalid error type\n");
        return NULL;
    }

    if (message == NULL)
    {
        DEBUG_PRINT("error_create: message is NULL\n");
        return NULL;
    }

    Error *error = (Error *)arena_alloc(arena, sizeof(Error), alignof(Error));
    if (error == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("error_create: arena_alloc failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("error_create: arena_alloc failed with unknown error\n");
        }
        
        return NULL;
    }

    error->type = type;
    error->length = length;
    error->line = line;
    error->column = column;
    error->message = message;

    return error;
}

void error_print(const Error *error)
{
    if (error == NULL)
    {
        DEBUG_PRINT("error_print: error is NULL\n");
        return;
    }

    printf("Error {\n");
    const char *type_str = (error->type == ERROR_WARNING) ? "Warning" : (error->type == ERROR_ERROR) ? "Error" : "Fatal Error";
    printf("    Type: %s\n", type_str);
    printf("    Length: %zu\n", error->length);
    printf("    Line: %zu\n", error->line);
    printf("    Column: %zu\n", error->column);
    printf("    Message: %s\n", error->message);
    printf("}\n");
}