#ifndef STACK_H
#define STACK_H
#include <stdio.h> 
#include <stdlib.h>

#define STACK_INCREMENT_SIZE 10

typedef struct Stack
{
    void *data;
    size_t currentSize;
    size_t maxHeight;
    size_t elementSize;
} Stack;

Stack *initStack(size_t elementSize);

void deleteStack(Stack *stack);

#define push(__stack, __value) ({ \
    int __ret = 0; \
    if (__stack == NULL) { \
        fprintf(stderr, "ERROR: Stack is not initialized!\n"); \
    } \
    else if (__stack->elementSize != sizeof(__value)) { \
        fprintf(stderr, "ERROR: Type mismatch!\n"); \
    } \
    else { \
        if (isFull(__stack) > 0) { \
            int __size = STACK_INCREMENT_SIZE; \
            void *__temp = realloc(__stack->data, (__stack->maxHeight + __size) * __stack->elementSize); \
            if (__temp == NULL) { \
                fprintf(stderr, "ERROR: Memory reallocation failed!\n"); \
                deleteStack(__stack); \
            } \
            else { \
                __stack->data = __temp; \
                __stack->maxHeight += __size; \
                ((typeof(__value) *)__stack->data)[__stack->currentSize++] = __value; \
                __ret = 1; \
            } \
        } \
        else { \
            ((typeof(__value) *)__stack->data)[__stack->currentSize++] = __value; \
            __ret = 1; \
        } \
    } \
    __ret; \
})

#define pop(__stack, __type) ({ \
    __type __ret = (__type)NULL;; \
    if (__stack == NULL) { \
        fprintf(stderr, "ERROR: Stack is not initialized!\n"); \
    } \
    else if (__stack->elementSize != sizeof(__type)) { \
        fprintf(stderr, "ERROR: Type mismatch!\n"); \
    } \
    else if (isEmpty(__stack) == 0) { \
        fprintf(stderr, "ERROR: Stack is empty!\n"); \
    } \
    else { \
        __ret = ((__type *)__stack->data)[--__stack->currentSize]; \
    } \
    __ret; \
})

#define top(__stack, __type) ({ \
    __type __ret = (__type)NULL; \
    if (__stack == NULL) { \
        fprintf(stderr, "ERROR: Stack is not initialized!\n"); \
    } \
    else if (__stack->elementSize != sizeof(__type)) { \
        fprintf(stderr, "ERROR: Type mismatch!\n"); \
    } \
    else if (isEmpty(__stack) == 0) { \
        fprintf(stderr, "ERROR: Stack is empty!\n"); \
    } \
    else { \
        __ret = ((__type *)__stack->data)[__stack->currentSize - 1]; \
    } \
    __ret; \
})

#define peek(__stack, __depth, __type) ({ \
    __type __ret = (__type)NULL; \
    if (__stack == NULL) { \
        fprintf(stderr, "ERROR: Stack is not initialized!\n"); \
    } \
    else if (__stack->elementSize != sizeof(__type)) { \
        fprintf(stderr, "ERROR: Type mismatch!\n"); \
    } \
    else if (isEmpty(__stack) == 0) { \
        fprintf(stderr, "ERROR: Stack is empty!\n"); \
    } \
    else if (__depth >= __stack->currentSize) { \
        fprintf(stderr, "ERROR: Depth is out of range!\n"); \
    } \
    else { \
        __ret = ((__type *)__stack->data)[__stack->currentSize - 1 - __depth]; \
    } \
    __ret; \
})

int isFull(Stack *stack);

int isEmpty(Stack *stack);

int setEmpty(Stack *stack);

size_t length(Stack *stack);

#endif