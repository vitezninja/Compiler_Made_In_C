#include "utils/type.h"

/**
 * Lookup table for CmcTypeEnum
 */
static const char *type_typeAsStrings[] = {
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
 * Lookup table for CmcTypeEnum names
 * This is used to provide a human-readable name for each type.
 */
static const char *type_typeAsNames[] = {
    [CMC_TYPE_INT_64] = "int64",
    [CMC_TYPE_INT_32] = "int32",
    [CMC_TYPE_INT_16] = "int16",
    [CMC_TYPE_INT_8] = "int8",
    [CMC_TYPE_UINT_64] = "uint64",
    [CMC_TYPE_UINT_32] = "uint32",
    [CMC_TYPE_UINT_16] = "uint16",
    [CMC_TYPE_UINT_8] = "uint8",
    [CMC_TYPE_FLOAT_64] = "float64",
    [CMC_TYPE_FLOAT_32] = "float32",
    [CMC_TYPE_BOOL] = "bool",
    [CMC_TYPE_CHAR] = "char",
    [CMC_TYPE_STRING] = "string",
    [CMC_TYPE_VOID] = "void",
    [CMC_TYPE_STRUCT] = "struct",
    [CMC_TYPE_UNION] = "union",
    [CMC_TYPE_ENUM] = "enum",
};

/**
 * Lookup table for TypeSpecEnum
 */
static const char *type_specifierEnumAsStrings[] = {
    [TYPE_SPEC_CONST] = "TYPE_SPEC_CONST",
    [TYPE_SPEC_PTR] = "TYPE_SPEC_PTR",
    [TYPE_SPEC_CONST_PTR] = "TYPE_SPEC_CONST_PTR",
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

/**
 * @brief Converts a TypeSpecEnum to its string representation.
 * 
 * This function takes a TypeSpecEnum value and returns a string that represents
 * the type specifier.
 * 
 * @param type The TypeSpecEnum value to convert.
 * @return A string representation of the TypeSpecEnum, or NULL if the type is invalid.
 */
const char *type_specifierEnumToString(TypeSpecEnum type);

//----------------------------------------------------------

const char *cmcTypeEnumToString(CmcTypeEnum type)
{
    if (type < 0 || type >= CMC_ARRAY)
    {
        DEBUG_PRINT("cmcTypeEnumToString: invalid type %d\n", type);
        return NULL;
    }
    return type_typeAsStrings[type];
}

const char *type_specifierEnumToString(TypeSpecEnum type)
{
    if (type < TYPE_SPEC_CONST || type >= TYPE_SPEC_CONST_PTR)
    {
        DEBUG_PRINT("type_specifierEnumToString: invalid type %d\n", type);
        return NULL;
    }
    return type_specifierEnumAsStrings[type];
}

//----------------------------------------------------------

CmcType *cmcType_base_create(Arena *arena, CmcTypeEnum type, TypeSpec specifiers)
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
    new_type->name = type_typeAsNames[type]; // Use the predefined name for base types
    new_type->hash = 0;
    new_type->value = (CmcTypeValue){0};
    new_type->specifiers = specifiers; // Set the type specifiers

    return new_type;
}

CmcType *cmcType_structOrUnion_create(Arena *arena, CmcTypeEnum type, const char *name, CmcTypeStructUnionValue members)
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

    CmcType *new_type = cmcType_base_create(arena, type, (TypeSpec){0});
    if (new_type == NULL)
    {
        return NULL;
    }

    new_type->name = name; // Store the name of the struct or union
    new_type->value.structUnion = members; // Store the members

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

    CmcType *new_type = cmcType_base_create(arena, CMC_TYPE_ENUM, (TypeSpec){0});
    if (new_type == NULL)
    {
        return NULL;
    }

    new_type->name = name; // Store the name of the enum

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

    CmcType *new_type = cmcType_base_create(arena, CMC_ARRAY, (TypeSpec){0});
    if (new_type == NULL)
    {
        return NULL;
    }

    new_type->value.arrayBase = baseType; // Set the base type for the array

    return new_type;
}

CmcType *cmcType_copy(Arena *arena, const CmcType *type)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("cmcType_copy: arena is NULL\n");
        return NULL;
    }

    if (type == NULL)
    {
        DEBUG_PRINT("cmcType_copy: type is NULL\n");
        return NULL;
    }

    CmcType *new_type = (CmcType *)arena_alloc(arena, sizeof(CmcType), alignof(CmcType));
    if (new_type == NULL)
    {
        DEBUG_PRINT("cmcType_copy: arena_alloc failed with errno %d\n", errno);
        return NULL;
    }

    new_type->type = type->type;
    new_type->name = type->name; // Copy the name (if applicable)
    new_type->value = type->value; // Copy the value (e.g., array base type, struct/union members)

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
    printf("    Name: %s\n", type->name);


    if (type->type == CMC_ARRAY)
    {
        printf("    Array Base: \n");
        cmcType_print(type->value.arrayBase);
    }
    else if (type->type == CMC_TYPE_STRUCT)
    {
        printf("    Struct Members: \n");
        for (size_t i = 0; i < type->value.structUnion.memberCount; i++)
        {
            symbol_print(type->value.structUnion.structUnionMembers[i]);
        }
    }
    else if (type->type == CMC_TYPE_UNION)
    {
        printf("    Union Members: \n");
        for (size_t i = 0; i < type->value.structUnion.memberCount; i++)
        {
            symbol_print(type->value.structUnion.structUnionMembers[i]);
        }
    }
    else if (type->type != CMC_TYPE_ENUM)
    {
        printf("    Specifiers: \n");
        for (size_t i = 0; i < type->specifiers.count; i++)
        {
            printf("        %s\n", type_specifierEnumToString(type->specifiers.types[i]));
        }
        printf("    Value: N/A\n");
    }
    printf("}\n");
}