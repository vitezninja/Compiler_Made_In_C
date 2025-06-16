#include "utils/arena.h"

Arena *arena_create(size_t size)
{
    errno = 0;
    Arena *arena = malloc(sizeof(Arena));
    if (!arena) 
    {
        DEBUG_PRINT("arena_create: failed to allocate Arena struct\n");
        fprintf(stderr, "[Fatal Error] : Memory allocation failed with error: %s\n", strerror(errno));
        return NULL;
    }

    errno = 0;
    arena->memory = malloc(size);
    if (!arena->memory)
    {
        DEBUG_PRINT("arena_create: failed to allocate memory block\n");
        fprintf(stderr, "[Fatal Error] : Memory allocation failed with error: %s\n", strerror(errno));
        free(arena);
        return NULL;
    }

    arena->capacity = size;
    arena->offset = 0;
    return arena;
}

void *arena_alloc(Arena *arena, size_t size, size_t alignment)
{
    if (!arena)
    {
        DEBUG_PRINT("arena_alloc: arena is NULL\n");
        return NULL;  
    }

    if (size == 0)
    {
        DEBUG_PRINT("arena_alloc: size must be greater than 0\n");
        return NULL;
    }

    if (alignment == 0 || (alignment & (alignment - 1)) != 0)
    {
        DEBUG_PRINT("arena_alloc: alignment must be a power of two\n");
        return NULL;
    }

    uintptr_t current_ptr = (uintptr_t)(arena->memory + arena->offset);
    uintptr_t aligned_ptr = (current_ptr + (alignment - 1)) & ~(alignment - 1);
    size_t padding = aligned_ptr - current_ptr;

    if (arena->offset + padding + size > arena->capacity)
    {
        DEBUG_PRINT("arena_alloc: not enough memory in arena\n");
        fprintf(stderr, "[Fatal Error] : Memory allocation failed with error: %s\n", strerror(ENOMEM));
        errno = ENOMEM;
        return NULL;
    }

    void *result = (void *)aligned_ptr;
    arena->offset += padding + size;
    return result;
}

void arena_reset(Arena *arena)
{
    if (!arena)
    {
        DEBUG_PRINT("arena_reset: arena is NULL\n");
        return;
    }
    arena->offset = 0;
}

void arena_destroy(Arena **arena_ptr)
{
    if (!arena_ptr || !*arena_ptr)
    {
        DEBUG_PRINT("arena_destroy: arena pointer is NULL\n");
        return;
    }

    Arena *arena = *arena_ptr;

    if (arena->memory)
    {
        free(arena->memory);
        arena->memory = NULL;
    }

    free(arena);
    *arena_ptr = NULL;
}

void arena_print(const Arena *arena)
{
    if (!arena)
    {
        DEBUG_PRINT("arena_print: arena is NULL\n");
        return;
    }

    printf("Arena {\n");
    printf("    Memory: %p\n", (void *)arena->memory);
    printf("    Capacity: %zu\n", arena->capacity);
    printf("    Offset: %zu\n", arena->offset);
    printf("    Load Factor: %.2f%%\n", (double)arena->offset / arena->capacity * 100);
    printf("}\n");
}