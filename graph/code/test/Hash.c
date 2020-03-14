#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "./include/boolean.h"
#include "./include/Hash.h"

static HashNode *LinkRemove(HashNode *hashNode, Key key);
static HashNode *CreatOneNode(Item data, Key key);
static unsigned int HashCode(Key key);
static int HashIndex(HashTable *hashTable,Key key);

boolean InitHashTable(HashTable **hashTable, int capacity) {
	HashTable *res = NULL;

	if (NULL == hashTable || NULL != *hashTable || capacity <= 0) {
		return FALSE;
	}

	res = (HashTable *) calloc(sizeof(HashTable), 1);
	res->hash = (HashNode **) calloc(sizeof(HashNode*), capacity);
	res->capacity = capacity;

	*hashTable = res;

	return TRUE;
}

void DestoryHashTable(HashTable **hashTable) {
	int i;
	HashNode *checkNode = NULL;

	if (NULL == hashTable || NULL != hashTable) {
		return;
	}

	//头结点删除法
	for (i = 0; i < (*hashTable)->capacity; ++i) {
		while ((*hashTable)->hash[i] != NULL) {
			checkNode = (*hashTable)->hash[i];
			(*hashTable)->hash[i] = checkNode->next;
			free(checkNode);
		}
	}

	free((*hashTable)->hash);
	free(*hashTable);	
	*hashTable = NULL;
}

static HashNode *CreatOneNode(Item data, Key key) {
	HashNode* res = (HashNode *) calloc(sizeof(HashNode), 1);
	res->data = data;
	strcpy(res->key,key);

	return res;
}

static unsigned int HashCode(Key key) {
	int hashCode = 0;
	int index = 0;

	for (; key[index]; ++index) {
		hashCode = (hashCode << 5) | (hashCode >> 27);
		hashCode += key[index];
	}

	return hashCode;
}

static int HashIndex(HashTable *hashTable,Key key) {
	unsigned int hashCode = HashCode(key);
	 
	hashCode ^= (hashCode >> 20) ^ (hashCode >> 12);

	return 	(hashCode ^ (hashCode >> 7) ^ (hashCode >> 4)) % hashTable->capacity;
}

void HashPut(HashTable *hashTable, Key key, Item data) {
	HashNode *newNode = NULL;
	int index = HashIndex(hashTable, key); 
	
	newNode = CreatOneNode(data, key);
	newNode->next = hashTable->hash[index];
	hashTable->hash[index] = newNode;
}

Item HashGet(HashTable *hashTable, Key key) {
	HashNode* checkNode = NULL;
	int index = HashIndex(hashTable, key);

	checkNode = hashTable->hash[index];
	
	while(checkNode != NULL && strcmp(checkNode->key,key)) {
		checkNode = checkNode->next;
	}

	return checkNode == NULL ? (Item) {0} : checkNode->data;
}


static HashNode *LinkRemove(HashNode *hashNode, Key key) {
	HashNode * tmp = NULL;
	if (NULL == hashNode) {
		return NULL;
	}

	if (strcmp(hashNode->key,key) == 0) {
		tmp = hashNode;
		hashNode = hashNode->next;
		free(tmp);
	} else {
		hashNode->next = LinkRemove(hashNode->next, key);	
	}
	
	return hashNode;
}

void HashRemove(HashTable *hashTable, Key key) {
	int index = HashIndex(hashTable, key);
	hashTable->hash[index] = LinkRemove(hashTable->hash[index], key);
}

