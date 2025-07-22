/**
 * @file type.h
 * @brief Defines types and enumerations used in the compiler.
 * 
 * This file contains definitions for various types used in the compiler, including
 * primitive types, user-defined types, and enumerations for symbol types.
 */

#ifndef TYPE_H
#define TYPE_H

#include <stdalign.h>
#include <errno.h>
#include <stdio.h>

typedef struct TypeSpec TypeSpec;
typedef struct CmcTypeStructUnionValue CmcTypeStructUnionValue;
typedef struct CmcType CmcType;
typedef union CmcTypeValue CmcTypeValue;

#include "utils/arena.h"
#include "utils/logger.h"
#include "utils/symbol.h"

/**
 * @enum CmcTypeEnum
 * @brief Enumerates possible types in the compiler.
 * 
 * This enum defines the various types that can be represented in the compiler,
 * including primitive types, arrays, and user-defined types such as structs and unions.
 */
typedef enum CmcTypeEnum
{
    CMC_TYPE_INT_64,    /** Represents a 64-bit signed integer type */
    CMC_TYPE_INT_32,    /** Represents a 32-bit signed integer type */
    CMC_TYPE_INT_16,    /** Represents a 16-bit signed integer type */
    CMC_TYPE_INT_8,     /** Represents an 8-bit signed integer type */
    CMC_TYPE_UINT_64,   /** Represents a 64-bit unsigned integer type */
    CMC_TYPE_UINT_32,   /** Represents a 32-bit unsigned integer type */
    CMC_TYPE_UINT_16,   /** Represents a 16-bit unsigned integer type */
    CMC_TYPE_UINT_8,    /** Represents an 8-bit unsigned integer type */
    CMC_TYPE_FLOAT_64,  /** Represents a 64-bit floating-point type */
    CMC_TYPE_FLOAT_32,  /** Represents a 32-bit floating-point type */
    CMC_TYPE_BOOL,      /** Represents a boolean type */
    CMC_TYPE_CHAR,      /** Represents a character type */
    CMC_TYPE_STRING,    /** Represents a string type */
    CMC_TYPE_VOID,      /** Represents a void type */
    CMC_TYPE_STRUCT,    /** Represents a struct type */
    CMC_TYPE_UNION,     /** Represents a union type */
    CMC_TYPE_ENUM,      /** Represents an enum type */
    CMC_ARRAY,          /** Represents an array type */
} CmcTypeEnum;

/**
 * @enum TypeSpecEnum
 * @brief Enumerates type specifiers for CmcType.
 * 
 * This enum defines various type specifiers that can be applied to types,
 * such as const, pointer, and const pointer.
 */
typedef enum TypeSpecEnum
{
    TYPE_SPEC_CONST,       /** Constant type specifier **/
    TYPE_SPEC_PTR,         /** Pointer type specifier **/
    TYPE_SPEC_CONST_PTR,   /** Constant pointer type specifier **/
} TypeSpecEnum;

struct TypeSpec
{
    TypeSpecEnum *types;     /** Type of the specifier (e.g., const, pointer) */
    size_t count;           /** Number of times this specifier is applied */
};

struct CmcTypeStructUnionValue
{
    Symbol **structUnionMembers;    /** Members of a struct or union if this is a user-defined type (if applicable) */
    size_t memberCount;             /** Number of members if this is a struct or union type */
};

/**
 * @union CmcTypeValue
 * @brief Holds additional information for user-defined types.
 * 
 * This union is used to store additional information for user-defined types such as
 * structs and unions. It can hold the base type for arrays or the members of a struct or union.
 */
union CmcTypeValue
{
    CmcType *arrayBase;              /** The type of the array elements if this is an array type (if applicable) */
    CmcTypeStructUnionValue structUnion;  /** Members of a struct or union if this is a user-defined type (if applicable) */
}; 

/**
 * @struct CmcType
 * @brief Represents a type in the compiler, including primitive types, arrays, and user-defined types.
 * 
 * This structure is used to represent various types in the compiler, including
 * primitive types (e.g., int, float), arrays, and user-defined types (e.g., structs, unions).
 */
struct CmcType
{
    CmcTypeEnum type;         /** The type of the CmcType (e.g., int, float, struct) */
    const char *name;         /** Name of the type (null-terminated string) */
    size_t hash;              /** Precomputed hash of the type's name for quick comparisons */
    CmcTypeValue value;       /** Additional information for user-defined types (e.g., struct members, array base type) */
    TypeSpec specifiers;      /** Type specifiers (e.g., const, pointer) applied to this type */
};

/**
 * @brief Creates a base CmcType with the specified type.
 * 
 * This function allocates and initializes a base CmcType structure with the given type.
 * 
 * @param arena Pointer to the memory arena for allocation.
 * @param type The CmcTypeEnum value representing the type.
 * @param specifiers Array of type specifiers (can be NULL).
 * @return Pointer to the newly created CmcType, or NULL on failure. Set `errno` to indicate the error.
 */
CmcType *cmcType_base_create(Arena *arena, CmcTypeEnum type, TypeSpec specifiers);

/**
 * @brief Creates a CmcType representing a struct or union.
 * 
 * This function allocates and initializes a CmcType for a struct or union,
 * including its name and members.
 * 
 * @param arena Pointer to the memory arena for allocation.
 * @param type The CmcTypeEnum value (CMC_TYPE_STRUCT or CMC_TYPE_UNION).
 * @param name Name of the struct or union (null-terminated string).
 * @param members Members of the struct or union (if applicable).
 * @return Pointer to the newly created CmcType, or NULL on failure. Set `errno` to indicate the error.
 */
CmcType *cmcType_structOrUnion_create(Arena *arena, CmcTypeEnum type, const char *name, CmcTypeStructUnionValue members);

/**
 * @brief Creates a CmcType representing an enum.
 * 
 * This function allocates and initializes a CmcType for an enum,
 * including its name. Enums typically have no members in this context.
 * 
 * @param arena Pointer to the memory arena for allocation.
 * @param name Name of the enum (null-terminated string).
 * @return Pointer to the newly created CmcType, or NULL on failure. Set `errno` to indicate the error.
 */
CmcType *cmcType_enum_create(Arena *arena, const char *name);

/**
 * @brief Creates a CmcType representing an array.
 * 
 * This function allocates and initializes a CmcType for an array,
 * including its base type. Arrays typically have no members in this context.
 * 
 * @param arena Pointer to the memory arena for allocation.
 * @param baseType Pointer to the CmcType representing the base type of the array.
 * @return Pointer to the newly created CmcType, or NULL on failure. Set `errno` to indicate the error.
 */
CmcType *cmcType_array_create(Arena *arena, CmcType *baseType);

/**
 * @brief Copies a CmcType.
 * 
 * This function allocates and initializes a new CmcType that is a copy of the provided type.
 * This does not copy the hash and the specifiers, only the type, name and value.
 * 
 * @param arena Pointer to the memory arena for allocation.
 * @param type Pointer to the CmcType to copy.
 * @return Pointer to the newly created CmcType, or NULL on failure. Set `errno` to indicate the error.
 */
CmcType *cmcType_copy(Arena *arena, const CmcType *type);

/**
 * @brief Prints a CmcType to stdout for debugging.
 * 
 * Displays the type and, if applicable, the base type for arrays.
 * 
 * @param type Pointer to the CmcType to print.
 */
void cmcType_print(const CmcType *type);

#endif // TYPE_H