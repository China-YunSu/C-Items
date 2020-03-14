#ifndef _HASH_H_
#define _HASH_H_ 

#include "boolean.h"

typedef int Item;
typedef char* Key;

typedef struct HashNode {
	Item data;
	char key[16];
	struct HashNode *next;
}HashNode;

typedef struct HashTable {
	HashNode **hash;
	int capacity;
}HashTable;

void HashRemove(HashTable *hashTable, Key key);
boolean InitHashTable(HashTable **hashTable, int capacity);
void DestoryHashTable(HashTable **hashTable);
void HashPut(HashTable *hashTable, Key key, Item data);
Item HashGet(HashTable *hashTable, Key key);

#endif