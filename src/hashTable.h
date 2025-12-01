#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>

struct HashEntry
{
    int key;   // idPelicula
    int value; // puntuación
    bool used;

    HashEntry() : key(0), value(0), used(false) {}
};

struct HashTable
{
    static const int SIZE = 503; // primo
    HashEntry table[SIZE];
};

// Inserta (key,value)
void hashInsert(HashTable &ht, int key, int value);

// Verifica si existe la clave
bool hashContains(const HashTable &ht, int key);

// Obtiene valor asociado
int hashGet(const HashTable &ht, int key);

#endif
