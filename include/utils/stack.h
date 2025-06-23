#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "utils/logger.h"

// Forward declaration of the Stack structure
typedef struct Stack Stack;

struct Stack
{
    uint8_t *data;
    size_t capacity;
    size_t top;
};

// Maybe use Arena for the stack memory
Stack *stack_create(size_t capacity);
bool stack_push(Stack *stack, void *item);
bool stack_isFull(Stack *stack);
void *stack_pop(Stack *stack);
bool stack_isEmpty(Stack *stack);
void *stack_top(Stack *stack);
void *stack_peek(Stack *stack);
void stack_reset(Stack *stack);
void stack_destroy(Stack *stack);
void stack_print(Stack *stack);

#endif // STACK_H