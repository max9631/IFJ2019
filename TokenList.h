#import <bool.h>
#import "String.h"

struct TokenList {
    TokenListItem *first;
    TokenListItem *last;

struct TokenListItem {
    TokenListItem *nextItem;
    String *token;
} TokenListItem;


/**
 * Allocates and initializes TokenList
 */
TokenList *createList();

/**
 * Creates TokenListItem and chains it to the list. 
 */
bool addTokenToList(String *token, TokenList *list);

/**
 * Returns first element of the list and sets list->first to firstElement->nextItem;
 */
TokenListItem *pop(TokenList *list);

/**
 * Returns element wheather the list is empty.
 */
bool isEmpty(TokenList *list);

/**
 * Deallocates item.
 */
bool destroy(TokenListItem *item);

/**
 * Deallocates list.
 */
bool destroy(TokenList *list);
