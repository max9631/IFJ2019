#ifndef LIST_H
#define LIST_H
#include <stdbool.h>
#include <stdlib.h>
#include "String.h"
#include "Token.h"
#include "Resource.h"

typedef struct ListItem {
    struct ListItem *nextItem;
    void *value;
} ListItem;

typedef struct List {
    struct ListItem *first;
    struct ListItem *last;
} List;


bool addToList(void *item, List *list);
void *popList(List *list);
bool isEmpty(List *list);
void destroyListItem(ListItem *item);
void destroyList(List *list);


/**
 * Allocates and initializes List
 */
List *createList(void);

/**
 * Creates ListItem and chains it to the list.
 */
bool addTokenToList(Token *token, List *list);

/**
 * Returns first element of the list and sets list->first to firstElement->nextItem;
 */
Token *popToken(List *list);

/**
 * Returns element wheather the list is empty.
 */
bool isEmpty(List *list);

/**
 * Deallocates item.
 */
void destroyListItem(ListItem *item);

/**
 * Deallocates list.
 */
void destroyList(List *list);

/**
 * Returns first token.
*/
Token *peek(List *list);

/**
 * Returns token on specific offset.
*/
Token *peekNext(List *list, int offset);

/*
 * Prints content of token list to stdout.
*/
void printList(List *list);

/**
 * checks if next token is expected type and returns it, or raises an error
 */
Token *consume(List *list, TokenType expectedType);

/**
 * Retuns if next token is same type as provided TokenType
 */
bool isNextTokenOfType(List *list, TokenType type);

#endif
