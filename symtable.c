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

HashTable *createFuncTable() {
	HashTable *table = createHashTable();
	insertHashTableItem(table, "print", (void *) __LONG_MAX__);
	insertHashTableItem(table, "inputi", (void *) __LONG_MAX__);
	insertHashTableItem(table, "inputs", (void *) __LONG_MAX__);
	insertHashTableItem(table, "inputf", (void *) __LONG_MAX__);
	insertHashTableItem(table, "len", (void *) __LONG_MAX__);
	insertHashTableItem(table, "substr", (void *) __LONG_MAX__);
	insertHashTableItem(table, "ord", (void *) __LONG_MAX__);
	insertHashTableItem(table, "chr", (void *) __LONG_MAX__);
	return table;
}

HashTable *createSymTable() {
	return createHashTable();
}

HashTableItem* getHashTableItem(HashTable *table, char *key) {
	if (table == NULL) return NULL;
	HashTableItem *item = (*table)[indexForKey(key)];
	while (item != NULL && strcmp(item->key, key) != 0) item = item->ptrnext;
	if (item == NULL) return NULL;
	return item;
}

void insertHashTableItem(HashTable *table, char *key, void *data) {
	if (table == NULL) return;
	HashTableItem *item = getHashTableItem(table, key);
	if (item != NULL) {
		item->data = data;
		return;
	}
	HashTableItem *newItem = (HashTableItem *) malloc(sizeof(HashTableItem));
	if (newItem == NULL) return;
    newItem->key = malloc(strlen(key) * sizeof(char));
	newItem->key = strcpy(newItem->key, key);
	newItem->data = data;
	newItem->ptrnext = (*table)[indexForKey(key)];
	(*table)[indexForKey(key)] = newItem;
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
    if (item->data != NULL) free(item->data);
    free(item);
}

void destroyHashTable(HashTable *table) {
	if (table == NULL) return;
	for (int i = 0; i < HTSIZE; i++) {
		HashTableItem *item = (*table)[i];
		while (item != NULL) {
			HashTableItem *tmp = item->ptrnext;
            if (item != NULL) {
                if (item->key != NULL) free(item->key);
                if (item->data != NULL) free(item->data);
                free(item);
            }
			item = tmp;
		}
		(*table)[i] = NULL;
	}
}

String *getString(HashTable *table, char *key) {
    HashTableItem *item = getHashTableItem(table, key);
    return (String *)item->data;
}

bool contains(HashTable *table, char *key) {
	return getHashTableItem(table, key) != NULL;
}
