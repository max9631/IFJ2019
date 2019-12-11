/*
 * Author(s): Adam Salih (xsalih01)
 * File: symtable.h, Implementation of hash table structure
 */

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Error.h"
#include "String.h"

#define HTSIZE 61 //Hash table size

// Function metadata
// contains number of argument, reference count and a flag which indicates that this function has a variable number of arguments (such as print function)
typedef struct FunctionMeta {
    int argsCount;
    int referenceCount;
    bool hasVariableArgsCount;
} FunctionMeta;

// Symbol metadata
// Contains only reference count
typedef struct SymbolMeta {
    int referenceCount;
} SymbolMeta;

// Union with specific datatypes
// This union can be eather function meta, symbolmeta or deprecated int value.
typedef union HashTableValue {
    FunctionMeta *func;
    SymbolMeta *symbol;
    int intValue;
} HashTableValue;

// HashTableItem containing its key, data with a union, and pointer to next item with the same index
typedef struct HashTableItem{
	char *key;
	HashTableValue data;
	struct HashTableItem* ptrnext;
} HashTableItem;

// HashTable implemented as an array
typedef HashTableItem* HashTable[HTSIZE];

// Creating and destroying HashTable structure;
HashTable *createHashTable(void);
void destroyHashTable(HashTable *table);

// Managing data in HashTable
int indexForKey(char *key);
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

#endif //HASHTABLE_H
