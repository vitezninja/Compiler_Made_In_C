/**
 * @file arena.h
 * @brief Header file for the arena memory allocator.
 * 
 * This file defines the Arena structure and functions for creating, allocating,
 * resetting, and destroying an arena memory allocator. The arena is designed for
 * fast, linear memory allocation, suitable for temporary memory blocks.
 */

#ifndef ARENA_H
#define ARENA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

#include "logger.h"

/**
 * @def ONE_KB
 * @brief Macro defining 1 kilobyte in bytes.
 */
#define ONE_KB (1024)

/**
 * @def ONE_MB
 * @brief Macro defining 1 megabyte in bytes.
 */
#define ONE_MB (1024 * ONE_KB)

/**
 * @struct Arena
 * @brief Arena memory allocator structure.
 *
 * An Arena is a fast, linear memory allocator that supports efficient allocation 
 * of temporary memory blocks from a pre-allocated buffer.
 * 
 * Memory allocated via this structure must be released by calling `arena_destroy()`.
 */
typedef struct Arena 
{
    uint8_t *memory;     /** Pointer to the start of the memory block. */
    size_t capacity;     /** Total capacity of the arena in bytes. */
    size_t offset;       /** Current offset (next free byte) in the arena. */
} Arena;

/**
 * @brief Creates a new arena allocator with a specified capacity.
 *
 * @param size The total number of bytes to allocate for the arena.
 * @return Pointer to the new Arena, or NULL on failure. Set `errno` to indicate the error.
 * 
 * @note The arena is initialized with a default capacity of 2 MB.
 */
Arena *arena_create(void);

/**
 * @brief Allocates a block of memory from the arena with the specified size and alignment.
 *
 * @param arena Pointer to the Arena from which to allocate memory.
 * @param size Number of bytes to allocate.
 * @param alignment Alignment in bytes (must be a power of two).
 * @return Pointer to allocated memory, or NULL on failure. Set `errno` to indicate the error.
 * 
 * @note To determine the alignment requirement of a type, you can use the C11 `alignof()` operator
 * from `<stdalign.h>`, which works for primitive types, structs, unions, and typedefs. It is
 * supported on all major platforms (Windows, macOS, Linux) with modern compilers.
 */
void *arena_alloc(Arena *arena, size_t size, size_t alignment);

/**
 * @brief Resets the arena for reuse.
 *
 * This does not deallocate memory; it simply allows new allocations 
 * to reuse the existing buffer.
 *
 * @param arena Pointer to the Arena to reset.
 */
void arena_reset(Arena *arena);

/**
 * @brief Destroys the arena and frees all associated memory.
 *
 * @param arena Pointer to the Arena pointer. The pointer will be set to NULL after destruction.
 */
void arena_destroy(Arena **arena);

/**
 * @brief Prints the internal state of the arena for debugging.
 *
 * @param arena Pointer to the Arena to inspect.
 */
void arena_print(const Arena *arena);

#endif // ARENA_H