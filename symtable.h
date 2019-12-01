#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Error.h"
#include "String.h"

#define HTSIZE 61

typedef struct FunctionMeta {
    int argsCount;
    int referenceCount;
    bool hasVariableArgsCount;
} FunctionMeta;

typedef struct SymbolMeta {
    int referenceCount;
} SymbolMeta;

typedef union HashTableValue {
    FunctionMeta *func;
    SymbolMeta *symbol;
    int intValue;
} HashTableValue;

typedef struct HashTableItem{
	char *key;
	HashTableValue data;
	struct HashTableItem* ptrnext;
} HashTableItem;

typedef HashTableItem* HashTable[HTSIZE];

// Creating and destroying HashTable structure;
HashTable *createHashTable(void);
void destroyHashTable(HashTable *table);

// Managing data in HashTable
HashTableItem *getHashTableItem(HashTable *table, char *key);
HashTableItem *insertHashTableItem(HashTable *table, char *key, HashTableValue data);
bool contains(HashTable *table, char *key);
void removeHashTableItem(HashTable *table, char *key);

// Concurency
HashTable *copyHashTable(HashTable *table);
HashTable *mergeHashTables(HashTable *table1, HashTable *table2);

// HashTable of functions
HashTable *createFunctionTable(void);
HashTableItem *insertHashTableFunction(HashTable *table, char* key, int numberOfArguments);
FunctionMeta *getFunctionMeta(HashTable *table, char* key);

// HashTable of Functions
HashTable *createSymbolTable(void);
void insertHashTableSymbol(HashTable *table, char* key);
SymbolMeta *getSymbolMeta(HashTable *table, char* key);

#endif
