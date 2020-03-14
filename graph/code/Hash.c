#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "./include/boolean.h"
#include "./include/Hash.h"

static HashNode *LinkRemove(HashNode *hashNode, Key key);
static HashNode *CreatOneNode(HashItem data, Key key);
static unsigned int HashCode(Key key);
static int HashIndex(HashTable *hashTable,Key key);
static boolean IsHad(HashNode *head, HashItem data);
static HashNode* IndexOf(HashTable *hashTable, Key key);

void KeyModify(HashTable *hashTable, Key key, HashItem data) {
	HashNode *index = IndexOf(hashTable, key);
	index == NULL ? (HashItem) {0} : (index->data = data);
}	

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

static HashNode *CreatOneNode(HashItem data, Key key) {
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

static boolean IsHad(HashNode *head, HashItem data) {
	HashNode *checkNode = head;
	while (checkNode != NULL && checkNode->data != data) {
		checkNode = checkNode->next;
	}
	return checkNode != NULL;
}

void HashPut(HashTable *hashTable, Key key, HashItem data) {
	HashNode *newNode = NULL;
	int index = HashIndex(hashTable, key); 
	
	if (hashTable->hash[index] != NULL 
		&& IsHad(hashTable->hash[index],data)) {
		return;
	}

	newNode = CreatOneNode(data, key);
	newNode->next = hashTable->hash[index];
	hashTable->hash[index] = newNode;
}

static HashNode* IndexOf(HashTable *hashTable, Key key) {
	HashNode* checkNode = NULL;
	int index = HashIndex(hashTable, key);

	checkNode = hashTable->hash[index];
	
	while(checkNode != NULL && strcmp(checkNode->key,key)) {
		checkNode = checkNode->next;
	}
	return checkNode == NULL ? NULL : checkNode;
	
}

HashItem HashGet(HashTable *hashTable, Key key) {
	HashNode *index = IndexOf(hashTable, key);

	return index == NULL ? (HashItem) {-1} : index->data;
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

