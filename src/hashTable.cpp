#include "hashTable.h"

int hashFunc(int key)
{
    return key % HashTable::SIZE;
}

void hashInsert(HashTable &ht, int key, int value)
{
    int index = hashFunc(key);

    for (int i = 0; i < HashTable::SIZE; i++)
    {
        int pos = (index + i) % HashTable::SIZE;

        if (!ht.table[pos].used)
        {
            ht.table[pos].used = true;
            ht.table[pos].key = key;
            ht.table[pos].value = value;
            return;
        }
    }
}

bool hashContains(const HashTable &ht, int key)
{
    int index = hashFunc(key);

    for (int i = 0; i < HashTable::SIZE; i++)
    {
        int pos = (index + i) % HashTable::SIZE;

        if (!ht.table[pos].used)
            return false;

        if (ht.table[pos].used && ht.table[pos].key == key)
            return true;
    }
    return false;
}

int hashGet(const HashTable &ht, int key)
{
    int index = hashFunc(key);

    for (int i = 0; i < HashTable::SIZE; i++)
    {
        int pos = (index + i) % HashTable::SIZE;

        if (!ht.table[pos].used)
            return -1;

        if (ht.table[pos].key == key)
            return ht.table[pos].value;
    }
    return -1;
}
