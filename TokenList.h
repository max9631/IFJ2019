#ifndef TOKENLIST_H
#define TOKENLIST_H
#include <stdbool.h>
#include <stdlib.h>
#include "String.h"
#include "Token.h"
#include "Resource.h"

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
TokenList *createList();

/**
 * Creates TokenListItem and chains it to the list.
 */
bool addTokenToList(Token *token, TokenList *list);

/**
 * Returns first element of the list and sets list->first to firstElement->nextItem;
 */
Token *pop(TokenList *list);

/**
 * Returns element wheather the list is empty.
 */
bool isEmpty(TokenList *list);

/**
 * Deallocates item.
 */
void destroyListItem(TokenListItem *item);

/**
 * Deallocates list.
 */
void destroyList(TokenList *list);

/**
 * Returns first token.
*/
Token *peek(TokenList *list);

/**
 * Returns token on specific offset.
*/
Token *peekNext(TokenList *list, int offset);

/*
 * Prints content of token list to stdout.
*/
void printTokenList(TokenList *list);

#endif
