#import <stdbool.h>
#import "String.h"


struct TokenListItem {
    struct TokenListItem *nextItem;
    struct String *token;
};

struct TokenList {
    struct TokenListItem *first;
    struct TokenListItem *last;
};


/**
 * Allocates and initializes TokenList
 */
struct TokenList *createList();

/**
 * Creates TokenListItem and chains it to the list. 
 */
bool addTokenToList(struct String *token, struct TokenList *list);

/**
 * Returns first element of the list and sets list->first to firstElement->nextItem;
 */
struct TokenListItem *pop(struct TokenList *list);

/**
 * Returns element wheather the list is empty.
 */
bool isEmpty(struct TokenList *list);

/**
 * Deallocates item.
 */
void destroyItem(struct TokenListItem *item);

/**
 * Deallocates list.
 */
void destroyList(struct TokenList *list);
