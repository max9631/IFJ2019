#include "HashTable.h"

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

HashTableItem* getItem(HashTable *table, char *key) {
	if (table == NULL) return NULL;
	HashTableItem *item = (*table)[indexForKey(key)];
	while (item != NULL && item->key != key) item = item->ptrnext;
	if (item == NULL) return NULL;
	return item;
}

void insertItem(HashTable *table, char *key, void *data) {
	if (table == NULL) return;
	HashTableItem *item = getItem(table, key);
	if (item != NULL) {
		item->data = data;
		return;
	}
	HashTableItem *newItem = (HashTableItem *) malloc(sizeof(HashTableItem));
	if (newItem == NULL) return;
	newItem->key = strcpy(newItem->key, key);
	newItem->data = data;
	newItem->ptrnext = (*table)[indexForKey(key)];
	(*table)[indexForKey(key)] = newItem;
}

void deleteItem(HashTable *table, char *key) {
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
    HashTableItem *item = getItem(table, key);
    return (String *)item->data;
}

bool contains(HashTable *table, char *key) {
	return getItem(table, key) != NULL;
}
