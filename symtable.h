#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

HashTable *createHashTable(void);
HashTable *createFuncTable(void);
HashTable *createSymTable(void);
HashTableItem *getHashTableItem(HashTable *table, char *key);
void insertHashTableItem(HashTable *table, char *key, void *data);
void removeHashTableItem(HashTable *table, char *key);
void destroyHashTable(HashTable *table);

String *getString(HashTable *table, char *key);
bool contains(HashTable *table, char *key);

#endif
