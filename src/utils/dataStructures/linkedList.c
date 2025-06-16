#include "utils/linkedList.h"

static LinkedList *linkedList_createEnd(Arena *arena, LinkedList *head, void *data)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("linkedList_create: arena is NULL\n");
        return NULL;
    }

    if (data == NULL)
    {
        DEBUG_PRINT("linkedList_create: data is NULL\n");
        return NULL;
    }

    LinkedList *node = (LinkedList *)arena_alloc(arena, sizeof(LinkedList), alignof(LinkedList));
    if (node == NULL)
    {
        DEBUG_PRINT("linkedList_create: arena_alloc failed with errno %d\n", errno);
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    if (head == NULL)
    {
        return node;
    }

    LinkedList *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = node;
    
    return head;
}

static LinkedList *linkedList_createStart(Arena *arena, LinkedList *head, void *data)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("linkedList_create: arena is NULL\n");
        return NULL;
    }

    if (data == NULL)
    {
        DEBUG_PRINT("linkedList_create: data is NULL\n");
        return NULL;
    }

    LinkedList *node = (LinkedList *)arena_alloc(arena, sizeof(LinkedList), alignof(LinkedList));
    if (node == NULL)
    {
        DEBUG_PRINT("linkedList_create: arena_alloc failed with errno %d\n", errno);
        return NULL;
    }

    node->data = data;
    node->next = head;

    return node;
}

LinkedList *linkedList_Token_create(Arena *arena, LinkedList *head, Token *data)
{
    LinkedList *node = linkedList_createEnd(arena, head, (void *)data);
    if (node == NULL)
    {
        DEBUG_PRINT("linkedList_Token_create: linkedList_createStart failed with errno %d\n", errno);
        return NULL;
    }
    return node;
}

LinkedList *linkedList_Error_create(Arena *arena, LinkedList *head, Error *data)
{
    LinkedList *node = linkedList_createEnd(arena, head, (void *)data);
    if (node == NULL)
    {
        DEBUG_PRINT("linkedList_Error_create: linkedList_createEnd failed with errno %d\n", errno);
        return NULL;
    }
    return node;
}

LinkedList *linkedList_HashTable_create(Arena *arena, LinkedList *head, struct HashTable *data)
{
    LinkedList *node = linkedList_createStart(arena, head, (void *)data);
    if (node == NULL)
    {
        DEBUG_PRINT("linkedList_HashTable_create: linkedList_createStart failed with errno %d\n", errno);
        return NULL;
    }
    return node;
}

LinkedList *linkedList_Symbol_create(Arena *arena, LinkedList *head, Symbol *data)
{
    LinkedList *node = linkedList_createEnd(arena, head, (void *)data);
    if (node == NULL)
    {
        DEBUG_PRINT("linkedList_Symbol_create: linkedList_createEnd failed with errno %d\n", errno);
        return NULL;
    }
    return node;
}

LinkedList *linkedList_String_create(Arena *arena, LinkedList *head, String *data)
{
    LinkedList *node = linkedList_createEnd(arena, head, (void *)data);
    if (node == NULL)
    {
        DEBUG_PRINT("linkedList_String_create: linkedList_createEnd failed with errno %d\n", errno);
        return NULL;
    }
    return node;
}

LinkedList *linkedList_Ast_create(Arena *arena, LinkedList *head, AstNode *data)
{
    LinkedList *node = linkedList_createEnd(arena, head, (void *)data);
    if (node == NULL)
    {
        DEBUG_PRINT("linkedList_Ast_create: linkedList_createEnd failed with errno %d\n", errno);
        return NULL;
    }
    return node;
}

void linkedList_print(const LinkedList *node, PrintFunction printFn)
{
    if (node == NULL)
    {
        DEBUG_PRINT("linkedList_print: node is NULL\n");
        return;
    }

    if (printFn == NULL)
    {
        DEBUG_PRINT("linkedList_print: printFn is NULL\n");
        return;
    }

    printf("LinkedList node {\n");
    printFn(node->data);
    printf("}\n");
}

void linkedList_printRecursive(const LinkedList *head, PrintFunction printFn)
{
    if (head == NULL)
    {
        DEBUG_PRINT("linkedList_printRecursive: head is NULL\n");
        return;
    }

    printf("LinkedList {\n");
    const LinkedList *current = head;
    while (current != NULL)
    {
        linkedList_print(current, printFn);
        current = current->next;
    }
    printf("}\n");
}