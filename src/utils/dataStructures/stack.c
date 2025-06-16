#include "utils/stack.h"

Stack *stack_create(size_t capacity)
{
    fprintf(stderr, "stack_create: not implemented\n");
    return NULL;
}

bool stack_push(Stack *stack, void *item)
{
    fprintf(stderr, "stack_push: not implemented\n");
    return false;
}

bool stack_isFull(Stack *stack)
{
    if (!stack)
    {
        fprintf(stderr, "stack_isFull: stack is NULL\n");
        return false;
    }

    return stack->top == stack->capacity;
}

void *stack_pop(Stack *stack)
{
    fprintf(stderr, "stack_pop: not implemented\n");
    return NULL;
}

bool stack_isEmpty(Stack *stack)
{
    if (!stack)
    {
        fprintf(stderr, "stack_isEmpty: stack is NULL\n");
        return false;
    }
    return stack->top == 0;
}

void *stack_top(Stack *stack)
{
    fprintf(stderr, "stack_top: not implemented\n");
    return NULL;
}

void *stack_peek(Stack *stack)
{
    fprintf(stderr, "stack_peek: not implemented\n");
    return NULL;
}

void stack_reset(Stack *stack)
{
    fprintf(stderr, "stack_reset: not implemented\n");
    return;
}

void stack_destroy(Stack *stack)
{
    fprintf(stderr, "stack_destroy: not implemented\n");
    return;
}

void stack_print(Stack *stack)
{
    fprintf(stderr, "stack_print: not implemented\n");
    return;
}
