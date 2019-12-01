#include "symtable.h"

int indexForKey(char *key){
	int retval = 1;
	unsigned long keylen = strlen(key);
	for (unsigned long i=0; i<keylen; i++ )
		retval += key[i];
	return ( retval % HTSIZE );
}

HashTable *createHashTable () {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
	if (table == NULL) handleError(InternalError, "Error while creating HashTable.");
	for (int i = 0; i < HTSIZE; i++)
		(*table)[i] = NULL;
    return table;
}

void destroyHashTable(HashTable *table) {
    if (table == NULL) return;
    for (int i = 0; i < HTSIZE; i++) {
        HashTableItem *item = (*table)[i];
        while (item != NULL) {
            HashTableItem *tmp = item->ptrnext;
            if (item != NULL) {
                if (item->key != NULL) free(item->key);
                free(item);
            }
            item = tmp;
        }
        (*table)[i] = NULL;
    }
}

HashTableItem* getHashTableItem(HashTable *table, char *key) {
	if (table == NULL) return NULL;
	HashTableItem *item = (*table)[indexForKey(key)];
	while (item != NULL && strcmp(item->key, key) != 0) item = item->ptrnext;
	if (item == NULL) return NULL;
	return item;
}

HashTableItem *insertHashTableItem(HashTable *table, char *key, HashTableValue data) {
	if (table == NULL) return NULL;
	HashTableItem *item = getHashTableItem(table, key);
	if (item != NULL) {
		item->data = data;
		return item;
	}
	HashTableItem *newItem = (HashTableItem *) malloc(sizeof(HashTableItem));
	if (newItem == NULL) return NULL;
    newItem->key = malloc(strlen(key) * sizeof(char));
	newItem->key = strcpy(newItem->key, key);
	newItem->data = data;
	newItem->ptrnext = (*table)[indexForKey(key)];
	(*table)[indexForKey(key)] = newItem;
    return newItem;
}

bool contains(HashTable *table, char *key) {
    return getHashTableItem(table, key) != NULL;
}

void removeHashTableItem(HashTable *table, char *key) {
	if (table == NULL) return;
	int index = indexForKey(key);
	HashTableItem *lastItem = NULL;
	HashTableItem *item = (*table)[index];
	while (item != NULL && item->key != key) {
		lastItem = item;
		item = item->ptrnext;
	}
	if (item == NULL) return;
	if (lastItem != NULL)
		lastItem->ptrnext = item->ptrnext;
	else
		(*table)[index] = item->ptrnext;
    if (item == NULL) return;
    if (item->key != NULL) free(item->key);
    free(item);
}

HashTable *copyHashTable(HashTable *table) {
    HashTable *copy = createHashTable();
    for (int i = 0; i < HTSIZE; i++) {
        HashTableItem *item = (*table)[i];
        while (item != NULL) {
            insertHashTableItem(copy, item->key, item->data);
            item = item->ptrnext;
        }
    }
    return copy;
}

HashTable *mergeHashTables(HashTable *table1, HashTable *table2) {
    HashTable *mergeTable = table1;
    for (int i = 0; i < HTSIZE; i++) {
        HashTableItem *item = (*table2)[i];
        while (item != NULL) {
            insertHashTableItem(mergeTable, item->key, item->data);
            item = item->ptrnext;
        }
    }
    return mergeTable;
}

HashTable *createFunctionTable() {
    HashTable *table = createHashTable();
    HashTableItem *print = insertHashTableFunction(table, "print", 0);
    print->data.func->hasVariableArgsCount = true;
    insertHashTableFunction(table, "inputi", 0);
    insertHashTableFunction(table, "inputs", 0);
    insertHashTableFunction(table, "inputf", 0);
    insertHashTableFunction(table, "len", 1);
    insertHashTableFunction(table, "substr", 3);
    insertHashTableFunction(table, "ord", 2);
    insertHashTableFunction(table, "chr", 1);
    return table;
}

HashTableItem *insertHashTableFunction(HashTable *table, char* key, int numberOfArguments) {
    HashTableValue value;
    value.func = malloc(sizeof(FunctionMeta));
    value.func->argsCount = numberOfArguments;
    value.func->hasVariableArgsCount = false;
    value.func->referenceCount = 0;
    return insertHashTableItem(table, key, value);
}

FunctionMeta *getFunctionMeta(HashTable *table, char* key) {
    return getHashTableItem(table, key)->data.func;
}

HashTable *createSymbolTable() {
    return createHashTable();
}

void insertHashTableSymbol(HashTable *table, char* key) {
    HashTableValue value;
    value.symbol = malloc(sizeof(SymbolMeta));
    value.symbol->referenceCount = 0;
    insertHashTableItem(table, key, value);
}
