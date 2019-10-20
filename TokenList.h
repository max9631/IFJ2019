#ifndef TOKENLIST_H
#define TOKENLIST_H
#include <stdbool.h>
#include <stdlib.h>
#include "String.h"
#include "Token.h"

typedef struct TokenListItem {
    struct TokenListItem *nextItem;
    struct Token *token;
} TokenListItem;

typedef struct TokenList {
    struct TokenListItem *first;
    struct TokenListItem *last;
} TokenList;


/**
 * Allocates and initializes TokenList
 */
struct TokenList *createList();

/**
 * Creates TokenListItem and chains it to the list.
 */
bool addTokenToList(Token *token, TokenList *list);

/**
 * Returns first element of the list and sets list->first to firstElement->nextItem;
 */
struct TokenListItem *pop(TokenList *list);

/**
 * Returns element wheather the list is empty.
 */
bool isEmpty(TokenList *list);

/**
 * Deallocates item.
 */
void destroyItem(TokenListItem *item);

/**
 * Deallocates list.
 */
void destroyList(TokenList *list);

#endif
