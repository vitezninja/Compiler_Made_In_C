#include "utils/hashTable.h"

/**
 * @brief Hashes a string using the FNV-1a algorithm.
 * 
 * This function computes a hash value for the input string, which can be used for quick lookups.
 * 
 * @param str The input string to hash.
 * @return The hash value of the input string.
 */
int hashTable_hash(const char *str);

/**
 * @brief Resizes the hash table if the number of items exceeds a threshold.
 * 
 * This function increases the bucket count and redistributes existing items to maintain performance.
 * 
 * @param hashTable Pointer to the hash table to resize.
 */
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
        DEBUG_PRINT("hashTable_resize: arena_alloc failed with errno %d\n", errno);
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

            // This type can be String, Symbol, or CmcType
            // We use chose one that has a hash field
            // WARNING: This assumes all types have a hash field
            // WARNING: This could break or have undefined behavior
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
        DEBUG_PRINT("hashTable_create: arena_alloc failed with errno %d\n", errno);
        return NULL;
    }

    hashTable->arena = arena;
    hashTable->bucketCount = INITIAL_BUCKET_COUNT;
    hashTable->itemCount = 0;

    hashTable->buckets = (LinkedList **)arena_alloc(arena, sizeof(LinkedList *) * hashTable->bucketCount, alignof(LinkedList *));
    if (hashTable->buckets == NULL)
    {
        DEBUG_PRINT("hashTable_create: arena_alloc for buckets failed with errno %d\n", errno);
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
        DEBUG_PRINT("hashTable_String_tryInsert: hashTable is NULL\n");
        return NULL;
    }

    if (name == NULL)
    {
        DEBUG_PRINT("hashTable_String_tryInsert: name is NULL\n");
        return NULL;
    }

    int hashValue = hashTable_hash(name);
    if (hashValue == -1)
    {
        DEBUG_PRINT("hashTable_String_tryInsert: hash failed\n");
        return NULL;
    }

    int index = hashValue % hashTable->bucketCount;
    String *string = NULL;
    if (hashTable->buckets[index] == NULL)
    {
        string = string_create(hashTable->arena, name, length, hashValue);
        if (string == NULL)
        {
            DEBUG_PRINT("hashTable_String_tryInsert: string_create failed with errno %d\n", errno);
            return NULL;
        }

        LinkedList *head = linkedList_String_create(hashTable->arena, NULL, string);
        if (head == NULL)
        {
            DEBUG_PRINT("hashTable_String_tryInsert: linkedList_String_create failed with errno %d\n", errno);
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
            DEBUG_PRINT("hashTable_String_tryInsert: string_create failed with errno %d\n", errno);
            return NULL;
        }

        LinkedList *head = linkedList_String_create(hashTable->arena, previous, string);
        if (head == NULL)
        {
            DEBUG_PRINT("hashTable_String_tryInsert: linkedList_String_create failed with errno %d\n", errno);
            return NULL;
        }
        hashTable->itemCount++;
    }

    if (hashTable->itemCount > hashTable->bucketCount * 3)
    {
        hashTable_resize(hashTable);
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("hashTable_String_tryInsert: hashTable_resize failed with errno %d\n", errno);
            return NULL;
        }
    }

    return string;
}

bool hashTable_Symbol_tryInsert(HashTable *hashTable, Symbol *symbol)
{
    if (hashTable == NULL)
    {
        DEBUG_PRINT("hashTable_Symbol_tryInsert: hashTable is NULL\n");
        return false;
    }

    if (symbol == NULL)
    {
        DEBUG_PRINT("hashTable_Symbol_tryInsert: symbol is NULL\n");
        return false;
    }

    int hashValue = hashTable_hash(symbol->name);
    if (hashValue == -1)
    {
        DEBUG_PRINT("hashTable_Symbol_tryInsert: hash failed\n");
        return false;
    }
    symbol->hash = hashValue; // Ensure the symbol has the correct hash value

    int index = hashValue % hashTable->bucketCount;
    if (hashTable->buckets[index] == NULL)
    {
        LinkedList *head = linkedList_Symbol_create(hashTable->arena, NULL, symbol);
        if (head == NULL)
        {
            DEBUG_PRINT("hashTable_Symbol_tryInsert: linkedList_Symbol_create failed with errno %d\n", errno);
            return false;
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
            if (strcmp(bucketData->name, symbol->name) == 0)
            {
                return false; // Symbol already exists
            }
            previous = bucket;
            bucket = bucket->next;
        }

        LinkedList *head = linkedList_Symbol_create(hashTable->arena, previous, symbol);
        if (head == NULL)
        {
            DEBUG_PRINT("hashTable_Symbol_tryInsert: linkedList_Symbol_create failed with errno %d\n", errno);
            return false;
        }
        hashTable->itemCount++;
    }

    if (hashTable->itemCount > hashTable->bucketCount * 3)
    {
        hashTable_resize(hashTable);
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("hashTable_Symbol_tryInsert: hashTable_resize failed with errno %d\n", errno);
            return false;
        }
    }
    return true;
}

bool hashTable_CmcType_tryInsert(HashTable *hashTable, CmcType *type)
{
    if (hashTable == NULL)
    {
        DEBUG_PRINT("hashTable_CmcType_tryInsert: hashTable is NULL\n");
        return false;
    }

    if (type == NULL)
    {
        DEBUG_PRINT("hashTable_CmcType_tryInsert: type is NULL\n");
        return false;
    }

    int hashValue = hashTable_hash(type->name);
    if (hashValue == -1)
    {
        DEBUG_PRINT("hashTable_CmcType_tryInsert: hash failed\n");
        return false;
    }
    type->hash = hashValue; // Ensure the type has the correct hash value

    int index = hashValue % hashTable->bucketCount;
    if (hashTable->buckets[index] == NULL)
    {
        LinkedList *head = linkedList_CmcType_create(hashTable->arena, NULL, type);
        if (head == NULL)
        {
            DEBUG_PRINT("hashTable_CmcType_tryInsert: linkedList_CmcType_create failed with errno %d\n", errno);
            return false;
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
            CmcType *bucketData = (CmcType *)bucket->data;
            if (strcmp(bucketData->name, type->name) == 0)
            {
                return false; // Type already exists
            }
            previous = bucket;
            bucket = bucket->next;
        }

        LinkedList *head = linkedList_CmcType_create(hashTable->arena, previous, type);
        if (head == NULL)
        {
            DEBUG_PRINT("hashTable_CmcType_tryInsert: linkedList_CmcType_create failed with errno %d\n", errno);
            return false;
        }
        hashTable->itemCount++;
    }

    if (hashTable->itemCount > hashTable->bucketCount * 3)
    {
        hashTable_resize(hashTable);
        if (errno == ENOMEM)
        {
            DEBUG_PRINT("hashTable_CmcType_tryInsert: hashTable_resize failed with errno %d\n", errno);
            return false;
        }
    }
    return true;
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

CmcType *hashTable_CmcType_find(HashTable *hashTable, const char *name)
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
        CmcType *type = (CmcType *)bucket->data;
        if (strcmp(type->name, name) == 0)
        {
            return type;
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
        if (bucket == NULL)
        {
            printf("        Bucket %zu: NULL\n", i);
        }
        else
        {
            linkedList_printRecursive(bucket, printFn);
        }
    }
    printf("}\n");
}