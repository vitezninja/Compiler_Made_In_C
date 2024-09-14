#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int preHash;
    void *value;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *head;
    size_t length;
} LinkedList;

LinkedList *initLinkedList();

void deleteLinkedList(LinkedList *linkedList);

#define pushLL(__linkedList, __value, __preHash) ({ \
    int __ret = 0; \
    if (__linkedList == NULL) { \
        fprintf(stderr, "ERROR: Linked List is not initialized!\n"); \
    } \
    else { \
        Node *__newNode = malloc(sizeof(Node)); \
        if (__newNode == NULL) { \
            fprintf(stderr, "ERROR: Memory allocation for new Node failed!\n"); \
            deleteLinkedList(__linkedList); \
        } \
        else { \
            __newNode->value = __value; \
            __newNode->preHash = __preHash; \
            __newNode->next = __linkedList->head; \
            __linkedList->head = __newNode; \
            __linkedList->length++; \
            __ret = 1; \
        } \
    } \
    __ret; \
})

void removeLL(LinkedList *linkedList);

Node *popLL(LinkedList *linkedList);

void removeAt(LinkedList *linkedList, int index);

Node *popAt(LinkedList *linkedList, int index);

Node *popAtHash(LinkedList *linkedList, int preHash);

#define valueAt(__linkedList, __index) ({ \
    Node  *__ret = (Node *)NULL; \
    if (__linkedList == NULL) { \
        fprintf(stderr, "ERROR: Linked List is not initialized!\n"); \
    } \
    else if (__linkedList->head == NULL) { \
        fprintf(stderr, "ERROR: No elements in the Linked List!\n"); \
    } \
    else if (__index < 0) { \
        fprintf(stderr, "ERROR: Index out of bound!\n"); \
    } \
    else { \
        Node *__ptr = __linkedList->head; \
        int __counter = 0; \
        while (__ptr != NULL) { \
            if (__counter == __index) { \
                break; \
            } \
            __ptr = __ptr->next; \
            __counter++; \
        } \
        if (__ptr == NULL) { \
            fprintf(stderr, "ERROR: Index out of bound!\n"); \
        } \
        else { \
            __ret = __ptr; \
        } \
    } \
    __ret; \
})

#define valueAtHash(__linkedList, __preHash) ({ \
    Node *__ret = (Node *)NULL; \
    if (__linkedList == NULL) { \
        fprintf(stderr, "ERROR: Linked List is not initialized!\n"); \
    } \
    else if (__linkedList->head == NULL) { \
        fprintf(stderr, "ERROR: No elements in the Linked List!\n"); \
    } \
    else { \
        Node *__ptr = __linkedList->head; \
        while (__ptr != NULL) { \
            if (__ptr->preHash == __preHash) { \
                break; \
            } \
            __ptr = __ptr->next; \
        } \
        if (__ptr == NULL) { \
            fprintf(stderr, "ERROR: Hash not found!\n"); \
        } \
        else { \
            __ret = __ptr; \
        } \
    } \
    __ret; \
})

int contains(const LinkedList *const linkedList, const int preHash);

size_t lengthLL(const LinkedList *const linkedList);

#endif