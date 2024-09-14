#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

typedef struct HashTable
{
    LinkedList **data;
    size_t size;
    size_t dataCount;
} HashTable;

#define HASH_TABLE_SIZE_INCREMENT 10

HashTable *initHashTable();

void deleteHashTable(HashTable *hashTable);

void resizeHashTable(HashTable *hashTable);

#define insert(__hashTable, __preHash, __data) ({ \
    int __ret = 0; \
    if (__hashTable == NULL) { \
        fprintf(stderr, "ERROR: Hash Table is not initialized!\n"); \
    } \
    else { \
        int __hash = hash(__preHash, __hashTable->size); \
        if (contains(__hashTable->data[__hash], __preHash)) { \
            fprintf(stderr, "ERROR: Data already exists in the Hash Table!\n"); \
        } \
        else { \
            if (fullRatio(__hashTable)) { \
                resizeHashTable(__hashTable); \
                __hash = hash(__preHash, __hashTable->size); \
            } \
            __hashTable->dataCount += pushLL(__hashTable->data[__hash], __data, __preHash); \
            __ret = 1; \
        } \
    } \
    __ret; \
})

#define removeData(__hashTable, __preHash, __type) ({ \
    __type *__ret = (__type *)NULL; \
    if (__hashTable == NULL) { \
        fprintf(stderr, "ERROR: Hash Table is not initialized!\n"); \
    } \
    else { \
        int __hash = hash(__preHash, __hashTable->size); \
        Node *__node = popAtHash(__hashTable->data[__hash], __preHash); \
        if (__node == NULL) { \
            fprintf(stderr, "ERROR: Data not found in the Hash Table!\n"); \
        } \
        else { \
            __hashTable->dataCount--; \
            __ret = __node->value; \
            free(__node); \
        } \
    } \
    __ret; \
})

#define find(__hashTable, __preHash, __type) ({ \
    __type *__ret = (__type)NULL; \
    if (__hashTable == NULL) { \
        fprintf(stderr, "ERROR: Hash Table is not initialized!\n"); \
    } \
    else { \
        int __hash = hash(__preHash, __hashTable->size); \
        Node *__node = valueAtHash(__hashTable->data[__hash], __preHash); \
        if (__node == NULL) { \
            fprintf(stderr, "ERROR: Data not found in the Hash Table!\n"); \
        } \
        else { \
            __ret = __node->value; \
        } \
    } \
    __ret; \
})

int dataCount(const HashTable *const hashTable);

int hash(const int preHash, const int modulo);

int fullRatio(const HashTable *const hashTable);

#endif