#include "utils/my_string.h"

String *string_create(Arena *arena, const char *name, size_t length, size_t hash)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("string_create: arena is NULL\n");
        return NULL;
    }

    if (name == NULL)
    {
        DEBUG_PRINT("string_create: name is NULL\n");
        return NULL;
    }

    String *string = (String *)arena_alloc(arena, sizeof(String), alignof(String));
    if (string == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("string_create: arena_alloc failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("string_create: arena_alloc failed with unknown error\n");
        }

        return NULL;
    }

    string->name = (char *)arena_alloc(arena, length + 1, alignof(char));
    if (string->name == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("string_create: arena_alloc failed for name with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("string_create: arena_alloc failed for name with unknown error\n");
        }

        return NULL;
    }

    strncpy(string->name, name, length);
    string->name[length] = '\0'; // Ensure null-termination
    string->length = length;
    string->hash = hash;

    return string;
}

void string_print(const String *string)
{
    if (string == NULL)
    {
        DEBUG_PRINT("string_print: string is NULL\n");
        return;
    }

    printf("String {\n");
    printf("    name: \"%s\",\n", string->name);
    printf("    length: %zu,\n", string->length);
    printf("    hash: %zu\n", string->hash);
    printf("}\n");
}