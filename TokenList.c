#include "TokenList.h"

struct TokenList *createList() {
    struct TokenList *list = (struct TokenList *) malloc(sizeof(struct TokenList));
    list->first = NULL;
    list->last = NULL;
    return list;

}

bool addTokenToList(Token *token, struct TokenList *list) {
    struct TokenListItem *item = (struct TokenListItem *) malloc(sizeof(struct TokenList));
    item->nextItem = NULL;
    item->token = token;
    if (item == NULL) return false;
    if (isEmpty(list)) {
        list->first = item;
        list->last = item;
    } else {
        list->last->nextItem = item;
        list->last = item;
    }
    return true;
}

Token *pop(struct TokenList *list) {
    struct TokenListItem *item = list->first;
    list->first = item->nextItem;
    if (list->first == NULL) {
        list->last = NULL;
    }
    return item->token;
}

bool isEmpty(struct TokenList *list) {
    return list->first == NULL;
}

void destroyItem(struct TokenListItem *item) {
    free(item);
}

void destroyList(struct TokenList *list) {
    TokenListItem *item = list->first;
    while (item != NULL) {
        TokenListItem *tmp = item;
        item = tmp->nextItem;
        destroyItem(tmp);
    }
    free(list);
}

Token *peek(TokenList *list) {
    return peekNext(list, 0);
}

Token *peekNext(TokenList *list, int offset) {
    if(list == NULL)
        return NULL;

    TokenListItem *item = list->first;

    if(item == NULL)
        return NULL;

    if(offset == 0)
        return item->token;

    for(int i = 0; i < offset; i++) {
        item = item->nextItem;

        if(item == NULL) 
            return NULL;
    }

    return item->token;
}