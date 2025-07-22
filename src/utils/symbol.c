#include "utils/symbol.h"

/**
 * @brief Converts a SymbolType enum to a string representation.
 */
static const char *symbol_symbolTypeAsString[] = {
    [SYMBOL_TYPE_VARIABLE] = "VARIABLE",
    [SYMBOL_TYPE_FUNCTION] = "FUNCTION",
    [SYMBOL_TYPE_ENUM_CONSTANT] = "ENUM_CONSTANT",
    [SYMBOL_TYPE_LABEL] = "LABEL"
};

/**
 * @brief Creates a new symbol for a variable.
 * 
 * Allocates a new symbol using the provided arena, initializes it with the given name,
 * type, hash, and value.
 * 
 * @param arena Memory arena used for allocation.
 * @param name Name of the variable (null-terminated string).
 * @param type Type of the variable.
 * @param hash Precomputed hash of the variable name.
 * @return Pointer to the newly created Symbol, or NULL if allocation fails.
 */
Symbol *symbol_create(Arena *arena, const char *name, SymbolType type, SymbolValue value);

/**
 * @brief Converts a SymbolType enum to a string representation.
 * 
 * This function returns a string representation of the given SymbolType.
 * 
 * @param type The SymbolType to convert.
 * @return A string representation of the SymbolType, or "UNKNOWN" if the type is invalid.
 */
const char *symbol_typeAsString(SymbolType type);

//----------------------------------------------------------

Symbol *symbol_create(Arena *arena, const char *name, SymbolType type, SymbolValue value)
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
    symbol->type = type;\
    symbol->hash = 0; // Hash can be computed later if needed
    symbol->value = value;
    return symbol;
}

const char *symbol_typeAsString(SymbolType type)
{
    if (type < 0 || type >= SYMBOL_TYPE_LABEL)
    {
        DEBUG_PRINT("symbol_typeAsString: Invalid SymbolType %d\n", type);
        return "UNKNOWN";
    }
    return symbol_symbolTypeAsString[type];
}

//----------------------------------------------------------

Symbol *symbol_variable_create(Arena *arena, const char *name, CmcType *type)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("symbol_variable_create: arena is NULL\n");
        return NULL;
    }

    if (name == NULL)
    {
        DEBUG_PRINT("symbol_variable_create: name is NULL\n");
        return NULL;
    }

    if (type == NULL)
    {
        DEBUG_PRINT("symbol_variable_create: type is NULL\n");
        return NULL;
    }

    SymbolValue value = { .variableType = type };
    return symbol_create(arena, name, SYMBOL_TYPE_VARIABLE, value);
}

Symbol *symbol_function_create(Arena *arena, const char *name, FunctionValue functionValue)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("symbol_function_create: arena is NULL\n");
        return NULL;
    }

    if (name == NULL)
    {
        DEBUG_PRINT("symbol_function_create: name is NULL\n");
        return NULL;
    }

    SymbolValue value = { .function = functionValue };
    return symbol_create(arena, name, SYMBOL_TYPE_FUNCTION, value);
}

Symbol *symbol_enum_constant_create(Arena *arena, const char *name)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("symbol_enum_constant_create: arena is NULL\n");
        return NULL;
    }

    if (name == NULL)
    {
        DEBUG_PRINT("symbol_enum_constant_create: name is NULL\n");
        return NULL;
    }

    SymbolValue value = { .function = NULL }; // No function value for enum constants
    return symbol_create(arena, name, SYMBOL_TYPE_ENUM_CONSTANT, value);
}

Symbol *symbol_label_create(Arena *arena, const char *name)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("symbol_label_create: arena is NULL\n");
        return NULL;
    }

    if (name == NULL)
    {
        DEBUG_PRINT("symbol_label_create: name is NULL\n");
        return NULL;
    }

    SymbolValue value = { .function = NULL }; // No function value for labels
    return symbol_create(arena, name, SYMBOL_TYPE_LABEL, value);
}

void symbol_print(const Symbol *symbol)
{
    if (symbol == NULL)
    {
        DEBUG_PRINT("symbol_print: symbol is NULL\n");
        return;
    }

    printf("Symbol {\n");
    if (symbol->name == NULL)
    {
        printf("    name: NULL,\n");
    }
    else
    {
        printf("    name: \"%s\",\n", symbol->name);
    }
    printf("    type: %s,\n", symbol_typeAsString(symbol->type));
    printf("    hash: %zu\n", symbol->hash);
    if (symbol->type == SYMBOL_TYPE_VARIABLE)
    {
        printf("    variable type: \n");
        cmcType_print(symbol->value.variableType);
    }
    else if (symbol->type == SYMBOL_TYPE_FUNCTION)
    {
        printf("    function return types: \n");
        for (size_t i = 0; i < symbol->value.function.returnCount; i++)
        {
            symbol_print(symbol->value.function.returnSymbols[i]);
        }
        printf("    function parameter types: \n");
        for (size_t i = 0; i < symbol->value.function.arity; i++)
        {
            symbol_print(symbol->value.function.paramSymbols[i]);
        }
    }
    printf("}\n");
}