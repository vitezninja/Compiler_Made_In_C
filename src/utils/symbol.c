#include "utils/symbol.h"

Symbol *symbol_create(Arena *arena, const char *name, SymbolType type, size_t hash)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("symbol_create: arena is NULL\n");
        return NULL;
    }

    if (name == NULL)
    {
        DEBUG_PRINT("symbol_create: name is NULL\n");
        return NULL;
    }

    if (type < 0)
    {
        DEBUG_PRINT("symbol_create: type is invalid\n");
        return NULL;
    }

    Symbol *symbol = (Symbol *)arena_alloc(arena, sizeof(Symbol), alignof(Symbol));
    if (symbol == NULL)
    {
        DEBUG_PRINT("symbol_create: arena_alloc failed with errno %d\n", errno);
        return NULL;
    }

    symbol->name = name;
    symbol->type = type;
    symbol->hash = hash;
    return symbol;
}

void symbol_print(const Symbol *symbol)
{
    if (symbol == NULL)
    {
        DEBUG_PRINT("symbol_print: symbol is NULL\n");
        return;
    }

    printf("Symbol {\n");
    printf("    name: \"%s\",\n", symbol->name);
    printf("    type: %d,\n", symbol->type);
    printf("    hash: %zu\n", symbol->hash);
    printf("}\n");
}