#include "utils/hashTable.h"

int hashTable_hash(const char *str);

void hashTable_resize(HashTable *hashTable);

// ---------------------------------------------------------------------------------

int hashTable_hash(const char *str)
{
    if (str == NULL)
    {
        DEBUG_PRINT("hashTable_hash: str is NULL\n");
        return -1;
    }

    // FNV-1a hash algorithm
    // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    size_t hash = 14695981039346656037ULL; // offset basis
    while (*str)
    {
        hash ^= (unsigned char)(*str++);
        hash *= 1099511628211ULL; // FNV prime
    }
    return hash;
}

void hashTable_resize(HashTable *hashTable)
{
    if (hashTable == NULL)
    {
        DEBUG_PRINT("hashTable_resize: hashTable is NULL\n");
        return;
    }

    if (hashTable->itemCount <= hashTable->bucketCount * 3)
    {
        return;
    }

    size_t newBucketCount = hashTable->bucketCount + INITIAL_BUCKET_COUNT;
    LinkedList **newBuckets = (LinkedList **)arena_alloc(hashTable->arena, sizeof(LinkedList *) * newBucketCount, alignof(LinkedList *));
    if (newBuckets == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("hashTable_resize: arena_alloc failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("hashTable_resize: arena_alloc failed with unknown error\n");
        }

        return;
    }

    for (size_t i = 0; i < newBucketCount; ++i)
    {
        newBuckets[i] = NULL;
    }

    for (size_t i = 0; i < hashTable->bucketCount; ++i)
    {
        LinkedList *bucket = hashTable->buckets[i];
        while (bucket != NULL)
        {
            LinkedList *next = bucket->next;

            Symbol *symbol = (Symbol *)bucket->data;
            int index = symbol->hash % newBucketCount;

            bucket->next = newBuckets[index];
            newBuckets[index] = bucket;

            bucket = next;
        }
    }

    hashTable->bucketCount = newBucketCount;
    hashTable->buckets = newBuckets;
}

// ---------------------------------------------------------------------------------

HashTable *hashTable_create(Arena *arena)
{
    if (arena == NULL)
    {
        DEBUG_PRINT("hashTable_create: arena is NULL\n");
        return NULL;
    }

    HashTable *hashTable = (HashTable *)arena_alloc(arena, sizeof(HashTable), alignof(HashTable));
    if (hashTable == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("hashTable_create: arena_alloc failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("hashTable_create: arena_alloc failed with unknown error\n");
        }

        return NULL;
    }

    hashTable->arena = arena;
    hashTable->bucketCount = INITIAL_BUCKET_COUNT;
    hashTable->itemCount = 0;

    hashTable->buckets = (LinkedList **)arena_alloc(arena, sizeof(LinkedList *) * hashTable->bucketCount, alignof(LinkedList *));
    if (hashTable->buckets == NULL)
    {
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("hashTable_create: arena_alloc for buckets failed with errno %d\n", errno);
        }
        else
        {
            DEBUG_PRINT("hashTable_create: arena_alloc for buckets failed with unknown error\n");
        }

        return NULL;
    }

    for (size_t i = 0; i < hashTable->bucketCount; ++i)
    {
        hashTable->buckets[i] = NULL;
    }

    return hashTable;
}

String *hashTable_String_tryInsert(HashTable *hashTable, const char *name, size_t length)
{
    if (hashTable == NULL)
    {
        DEBUG_PRINT("hashTable_tryInsert: hashTable is NULL\n");
        return NULL;
    }

    if (name == NULL)
    {
        DEBUG_PRINT("hashTable_tryInsert: name is NULL\n");
        return NULL;
    }

    int hashValue = hashTable_hash(name);
    if (hashValue == -1)
    {
        DEBUG_PRINT("hashTable_tryInsert: hash failed\n");
        return NULL;
    }

    int index = hashValue % hashTable->bucketCount;
    String *string = NULL;
    if (hashTable->buckets[index] == NULL)
    {
        string = string_create(hashTable->arena, name, length, hashValue);
        if (string == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("hashTable_tryInsert: string_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("hashTable_tryInsert: string_create failed with unknown error\n");
            }

            return NULL;
        }

        LinkedList *head = linkedList_String_create(hashTable->arena, NULL, string);
        if (head == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("hashTable_tryInsert: linkedList_String_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("hashTable_tryInsert: linkedList_String_create failed with unknown error\n");
            }

            return NULL;
        }

        hashTable->buckets[index] = head;
        hashTable->itemCount++;
    }
    else
    {
        LinkedList *bucket = hashTable->buckets[index];

        LinkedList *previous = NULL;
        while (bucket != NULL)
        {
            String *bucketData = (String *)bucket->data;
            if (strcmp(bucketData->name, name) == 0)
            {
                return bucketData;
            }
            previous = bucket;
            bucket = bucket->next;
        }

        string = string_create(hashTable->arena, name, length, hashValue);
        if (string == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("hashTable_tryInsert: string_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("hashTable_tryInsert: string_create failed with unknown error\n");
            }

            return NULL;
        }

        LinkedList *head = linkedList_String_create(hashTable->arena, previous, string);
        if (head == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("hashTable_tryInsert: linkedList_String_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("hashTable_tryInsert: linkedList_String_create failed with unknown error\n");
            }

            return NULL;
        }

        hashTable->itemCount++;
    }

    if (hashTable->itemCount > hashTable->bucketCount * 3)
    {
        hashTable_resize(hashTable);
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("hashTable_tryInsert: hashTable_resize failed with errno %d\n", errno);
            return NULL;
        }
    }

    return string;
}

Symbol *hashTable_Symbol_tryInsert(HashTable *hashTable, const char* name, SymbolType type)
{
    if (hashTable == NULL)
    {
        DEBUG_PRINT("hashTable_tryInsert: hashTable is NULL\n");
        return NULL;
    }

    if (name == NULL)
    {
        DEBUG_PRINT("hashTable_tryInsert: name is NULL\n");
        return NULL;
    }

    if (type < 0)
    {
        DEBUG_PRINT("hashTable_tryInsert: type is invalid\n");
        return NULL;
    }

    int hashValue = hashTable_hash(name);
    if (hashValue == -1)
    {
        DEBUG_PRINT("hashTable_tryInsert: hash failed\n");
        return NULL;
    }

    int index = hashValue % hashTable->bucketCount;
    Symbol *symbol = NULL;
    if (hashTable->buckets[index] == NULL)
    {
        symbol = symbol_create(hashTable->arena, name, type, hashValue);
        if (symbol == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("hashTable_tryInsert: symbol_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("hashTable_tryInsert: symbol_create failed with unknown error\n");
            }

            return NULL;
        }

        LinkedList *head = linkedList_Symbol_create(hashTable->arena, NULL, symbol);
        if (head == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("hashTable_tryInsert: linkedList_Symbol_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("hashTable_tryInsert: linkedList_Symbol_create failed with unknown error\n");
            }

            return NULL;
        }

        hashTable->buckets[index] = head;
        hashTable->itemCount++;
    }
    else
    {
        LinkedList *bucket = hashTable->buckets[index];

        LinkedList *previous = NULL;
        while (bucket != NULL)
        {
            Symbol *bucketData = (Symbol *)bucket->data;
            if (strcmp(bucketData->name, name) == 0)
            {
                return bucketData;
            }
            previous = bucket;
            bucket = bucket->next;
        }

        symbol = symbol_create(hashTable->arena, name, type, hashValue);
        if (symbol == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("hashTable_tryInsert: symbol_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("hashTable_tryInsert: symbol_create failed with unknown error\n");
            }

            return NULL;
        }

        LinkedList *head = linkedList_Symbol_create(hashTable->arena, previous, symbol);
        if (head == NULL)
        {
            if (errno == ENOMEM)
            {
                DEBUG_PRINT("hashTable_tryInsert: linkedList_Symbol_create failed with errno %d\n", errno);
            }
            else
            {
                DEBUG_PRINT("hashTable_tryInsert: linkedList_Symbol_create failed with unknown error\n");
            }

            return NULL;
        }

        hashTable->itemCount++;
    }

    if (hashTable->itemCount > hashTable->bucketCount * 3)
    {
        hashTable_resize(hashTable);
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("hashTable_tryInsert: hashTable_resize failed with errno %d\n", errno);
            return NULL;
        }
    }

    return symbol;
}

String *hashTable_String_find(HashTable *hashTable, const char *name)
{
    if (hashTable == NULL)
    {
        DEBUG_PRINT("hashTable_find: hashTable is NULL\n");
        return NULL;
    }

    if (name == NULL)
    {
        DEBUG_PRINT("hashTable_find: name is NULL\n");
        return NULL;
    }

    int hashValue = hashTable_hash(name);
    if (hashValue == -1)
    {
        DEBUG_PRINT("hashTable_tryInsert: hash failed\n");
        return NULL;
    }

    int index = hashValue % hashTable->bucketCount;
    LinkedList *bucket = hashTable->buckets[index];

    while (bucket != NULL)
    {
        String *string = (String *)bucket->data;
        if (strcmp(string->name, name) == 0)
        {
            return string;
        }
        bucket = bucket->next;
    }

    return NULL;
}

Symbol *hashTable_Symbol_find(HashTable *hashTable, const char *name)
{
    if (hashTable == NULL)
    {
        DEBUG_PRINT("hashTable_find: hashTable is NULL\n");
        return NULL;
    }

    if (name == NULL)
    {
        DEBUG_PRINT("hashTable_find: name is NULL\n");
        return NULL;
    }

    int hashValue = hashTable_hash(name);
    if (hashValue == -1)
    {
        DEBUG_PRINT("hashTable_tryInsert: hash failed\n");
        return NULL;
    }

    int index = hashValue % hashTable->bucketCount;
    LinkedList *bucket = hashTable->buckets[index];

    while (bucket != NULL)
    {
        Symbol *symbol = (Symbol *)bucket->data;
        if (strcmp(symbol->name, name) == 0)
        {
            return symbol;
        }
        bucket = bucket->next;
    }

    return NULL;
}

void hashTable_print(const HashTable *hashTable, PrintFunction printFn)
{
    if (hashTable == NULL)
    {
        DEBUG_PRINT("hashTable_print: hashTable is NULL\n");
        return;
    }

    printf("HashTable {\n");
    printf("    Bucket Count: %zu\n", hashTable->bucketCount);
    printf("    Item Count: %zu\n", hashTable->itemCount);
    printf("    Buckets:\n");
    for (size_t i = 0; i < hashTable->bucketCount; ++i)
    {
        LinkedList *bucket = hashTable->buckets[i];
        linkedList_printRecursive(bucket, printFn);
    }
    printf("}\n");
}