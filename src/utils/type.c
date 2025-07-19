#include "utils/type.h"

/**
 * Lookup table for CmcTypeEnum
 */
static const char *token_typeAsStrings[] = {
    [CMC_TYPE_INT_64] = "CMC_TYPE_INT_64",
    [CMC_TYPE_INT_32] = "CMC_TYPE_INT_32",
    [CMC_TYPE_INT_16] = "CMC_TYPE_INT_16",
    [CMC_TYPE_INT_8] = "CMC_TYPE_INT_8",
    [CMC_TYPE_UINT_64] = "CMC_TYPE_UINT_64",
    [CMC_TYPE_UINT_32] = "CMC_TYPE_UINT_32",
    [CMC_TYPE_UINT_16] = "CMC_TYPE_UINT_16",
    [CMC_TYPE_UINT_8] = "CMC_TYPE_UINT_8",
    [CMC_TYPE_FLOAT_64] = "CMC_TYPE_FLOAT_64",
    [CMC_TYPE_FLOAT_32] = "CMC_TYPE_FLOAT_32",
    [CMC_TYPE_BOOL] = "CMC_TYPE_BOOL",
    [CMC_TYPE_CHAR] = "CMC_TYPE_CHAR",
    [CMC_TYPE_STRING] = "CMC_TYPE_STRING",
    [CMC_TYPE_VOID] = "CMC_TYPE_VOID",
    [CMC_TYPE_STRUCT] = "CMC_TYPE_STRUCT",
    [CMC_TYPE_UNION] = "CMC_TYPE_UNION",
    [CMC_TYPE_ENUM] = "CMC_TYPE_ENUM",
    [CMC_ARRAY] = "CMC_ARRAY",
};

/**
 * @brief Converts a CmcTypeEnum to its string representation.
 * 
 * This function takes a CmcTypeEnum value and returns a string that represents
 * the type.
 * 
 * @param type The CmcTypeEnum value to convert.
 * @return A string representation of the CmcTypeEnum, or NULL if the type is invalid.
 */
const char *cmcTypeEnumToString(CmcTypeEnum type);

//----------------------------------------------------------

const char *cmcTypeEnumToString(CmcTypeEnum type)
{
    if (type < 0 || type >= CMC_ARRAY)
    {
        DEBUG_PRINT("cmcTypeEnumToString: invalid type %d\n", type);
        return NULL;
    }
    return token_typeAsStrings[type];
}

//----------------------------------------------------------

CmcType *cmcType_base_create(Arena *arena, CmcTypeEnum type)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("cmcType_base_create: arena is NULL\n");
        return NULL;
    }

    CmcType *new_type = (CmcType *)arena_alloc(arena, sizeof(CmcType), alignof(CmcType));
    if (new_type == NULL)
    {
        DEBUG_PRINT("cmcType_create: arena_alloc failed with errno %d\n", errno);
        return NULL;
    }

    new_type->type = type;
    new_type->value = (CmcTypeValue){0};
    new_type->memberCount = 0;
    new_type->name = NULL;
    new_type->hash = 0;

    return new_type;
}

CmcType *cmcType_structOrUnion_create(Arena *arena, CmcTypeEnum type, const char *name, Symbol **members, size_t memberCount)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("cmcType_structOrUnion_create: arena is NULL\n");
        return NULL;
    }

    if (type != CMC_TYPE_STRUCT && type != CMC_TYPE_UNION)
    {
        DEBUG_PRINT("cmcType_structOrUnion_create: type must be CMC_TYPE_STRUCT or CMC_TYPE_UNION\n");
        return NULL;
    }

    if (name == NULL)
    {
        DEBUG_PRINT("cmcType_structOrUnion_create: name is NULL\n");
        return NULL;
    }

    CmcType *new_type = cmcType_base_create(arena, type);
    if (new_type == NULL)
    {
        return NULL;
    }

    new_type->name = name; // Store the name of the struct or union
    new_type->value.structUnionMembers = members; // Store the members
    new_type->memberCount = memberCount; // Set the member count

    return new_type;
}

CmcType *cmcType_enum_create(Arena *arena, const char *name)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("cmcType_enum_create: arena is NULL\n");
        return NULL;
    }

    if (name == NULL)
    {
        DEBUG_PRINT("cmcType_enum_create: name is NULL\n");
        return NULL;
    }

    CmcType *new_type = cmcType_base_create(arena, CMC_TYPE_ENUM);
    if (new_type == NULL)
    {
        return NULL;
    }

    new_type->name = name; // Store the name of the enum
    new_type->value = (CmcTypeValue){0}; // Initialize the value union
    new_type->memberCount = 0; // Enums typically have no members in this context

    return new_type;
}

CmcType *cmcType_array_create(Arena *arena, CmcType *baseType)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("cmcType_array_create: arena is NULL\n");
        return NULL;
    }

    if (baseType == NULL)
    {
        DEBUG_PRINT("cmcType_array_create: baseType is NULL\n");
        return NULL;
    }

    CmcType *new_type = cmcType_base_create(arena, CMC_ARRAY);
    if (new_type == NULL)
    {
        return NULL;
    }

    new_type->value.arrayBase = baseType; // Set the base type for the array
    new_type->memberCount = 0; // Arrays typically have no members in this context
    new_type->name = NULL; // Arrays do not have a name in this context

    return new_type;
}

void cmcType_print(const CmcType *type)
{
    if (type == NULL)
    {
        DEBUG_PRINT("cmcType_print: type is NULL\n");
        return;
    }

    printf("CmcType {\n");
    printf("    Type: %s\n", cmcTypeEnumToString(type->type));

    if (type->type == CMC_ARRAY)
    {
        printf("    Array Base: \n");
        cmcType_print(type->value.arrayBase);
    }
    else if (type->type == CMC_TYPE_STRUCT)
    {
        printf("    Struct Name: %s\n", type->name);
        printf("    Struct Members: \n");
        for (size_t i = 0; i < type->memberCount; i++)
        {
            symbol_print(type->value.structUnionMembers[i]);
        }
    }
    else if (type->type == CMC_TYPE_UNION)
    {
        printf("    Union Name: %s\n", type->name);
        printf("    Union Members: \n");
        for (size_t i = 0; i < type->memberCount; i++)
        {
            symbol_print(type->value.structUnionMembers[i]);
        }
    }
    else if (type->type == CMC_TYPE_ENUM)
    {
        printf("    Enum Name: %s\n", type->name);
    }
    else
    {
        printf("    Value: N/A\n");
    }
    printf("}\n");
}