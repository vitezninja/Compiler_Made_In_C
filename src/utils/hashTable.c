#include "hashTable.h"

HashTable *initHashTable()
{
    HashTable *hashTable = malloc(sizeof(HashTable));
    if (hashTable == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation for HashTable structure failed!\n");
        return NULL;
    }

    hashTable->size = HASH_TABLE_SIZE_INCREMENT;
    hashTable->data = malloc(hashTable->size * sizeof(LinkedList *));
    if (hashTable->data == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation for HashTable data failed!\n");
        free(hashTable);
        return NULL;
    }

    hashTable->dataCount = 0;

    for (size_t i = 0; i < hashTable->size; i++)
    {
        hashTable->data[i] = initLinkedList();
    }

    return hashTable;
}

void deleteHashTable(HashTable *hashTable)
{
    if (hashTable != NULL)
    {
        if (hashTable->data != NULL)
        {
            for (size_t i = 0; i < hashTable->size; i++)
            {
                deleteLinkedList(hashTable->data[i]);
            }
            free(hashTable->data);
        }
        free(hashTable);
    }
}

void resizeHashTable(HashTable *hashTable)
{
    size_t newSize = hashTable->size + HASH_TABLE_SIZE_INCREMENT;
    LinkedList **newData = malloc(newSize * sizeof(LinkedList *));
    if (newData == NULL)
    {
        fprintf(stderr, "ERROR: Memory reallocation for new HashTable data failed!\n");
        return;
    }

    for (size_t i = 0; i < newSize; i++)
    {
        newData[i] = initLinkedList();
    }


    for (size_t i = 0; i < hashTable->size; i++)
    {
        size_t length = lengthLL(hashTable->data[i]);
        for (size_t j = 0; j < length; j++)
        {
            Node *node = popLL(hashTable->data[i]);
            int hashCode = hash(node->preHash, newSize);
            pushLL(newData[hashCode], node->value, node->preHash);
        }
        deleteLinkedList(hashTable->data[i]);
    }

    free(hashTable->data);
    hashTable->data = newData;
    hashTable->size = newSize;
}

int dataCount(const HashTable *const hashTable)
{
    return hashTable->dataCount;
}

int hash(const int preHash, const int modulo)
{
    return preHash % modulo;
}

int fullRatio(const HashTable *const hashTable)
{
    return hashTable->dataCount / (hashTable->size * 10) ;
}