#include "utils/error.h"

Error *error_create(Arena *arena, ErrorType type, size_t length, SourceLocation location, const char *message)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("error_create: arena is NULL\n");
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
        DEBUG_PRINT("error_create: arena_alloc failed with errno %d\n", errno);
        return NULL;
    }

    error->type = type;
    error->length = length;
    error->location = location;
    error->message = message;
    return error;
}

void error_print(const Error *error, const char *sourceBuffer)
{
    if (error == NULL)
    {
        DEBUG_PRINT("error_print: error is NULL\n");
        return;
    }

    if (sourceBuffer == NULL)
    {
        DEBUG_PRINT("error_print: sourceBuffer is NULL\n");
        return;
    }

    const char *type_str = (error->type == ERROR_WARNING) ? "Warning" : (error->type == ERROR_ERROR) ? "Error" : "Fatal Error";
    fprintf(stderr, "[%s] %s:%" PRId32 ":%" PRId32 ": %s\n", type_str, error->location.fileName, error->location.line, error->location.column, error->message);
    size_t pos = error->location.lineStart;
    fprintf(stderr, "\t");
    while (true)
    {
        if (sourceBuffer[pos] == '\n' || sourceBuffer[pos] == '\0')
        {
            break;
        }
        fprintf(stderr, "%c", sourceBuffer[pos++]);
    }
    fprintf(stderr, "\n");
    fprintf(stderr, "\t");
    for (size_t i = 0; i < error->location.column - 1; i++)
    {
        fprintf(stderr, " ");
    }
    fprintf(stderr, "^");
    for (size_t i = 0; i < error->length - 1; i++)
    {
        fprintf(stderr, "~");
    }
    fprintf(stderr, "\n");
}