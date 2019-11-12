#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdlib.h>
#include <string.h>
#include "Error.h"
#include "String.h"

#define HTSIZE 61

typedef struct HashTableItem{
	char *key;
	void *data;
	struct HashTableItem* ptrnext;
} HashTableItem;

typedef HashTableItem* HashTable[HTSIZE];

int indexForKey(char *key);

HashTable *createHashTable();
HashTableItem *getItem(HashTable *table, char *key);
void insertItem(HashTable *table, char *key, void *data);
void deleteItem(HashTable *table, char *key);
void destroyHashTable(HashTable *table);

#endif
