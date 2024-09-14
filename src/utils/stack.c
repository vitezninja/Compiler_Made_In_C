#include "stack.h"

Stack *initStack(size_t elementSize)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation for Stack structure failed!\n");
        return NULL;
    }
    
    stack->data = malloc(STACK_INCREMENT_SIZE * elementSize);
    if (stack->data == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation for Stack data failed!\n");
        free(stack);
        return NULL;
    }

    stack->currentSize = 0;
    stack->maxHeight = STACK_INCREMENT_SIZE;
    stack->elementSize = elementSize;

    return stack;
}

void deleteStack(Stack *stack)
{
    if (stack != NULL)
    {
        if (stack->data != NULL)
        {
            free(stack->data);
        }
        free(stack);
    }
}

int isFull(Stack *stack)
{
    if (stack == NULL)
    {
        fprintf(stderr, "ERROR: Stack is not initialized!\n");
        return 0;
    }

    return stack->currentSize == stack->maxHeight;
}

int isEmpty(Stack *stack)
{
    if (stack == NULL)
    {
        fprintf(stderr, "ERROR: Stack is not initialized!\n");
        return 0;
    }

    return stack->currentSize == 0;
}

int setEmpty(Stack *stack)
{
    if (stack == NULL)
    {
        fprintf(stderr, "ERROR: Stack is not initialized!\n");
        return 0;
    }

    stack->currentSize = 0;
    return 1;
}

size_t length(Stack *stack)
{
    if (stack == NULL)
    {
        fprintf(stderr, "ERROR: Stack is not initialized!\n");
        return 0;
    }

    return stack->currentSize;
}