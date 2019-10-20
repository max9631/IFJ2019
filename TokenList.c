#include "TokenList.h"

TokenList *createList() {
    TokenList *list = (TokenList *) malloc(sizeof(TokenList));
    list->first = NULL;
    list->last = NULL;
    return list;
}

bool addTokenToList(Token *token, TokenList *list) {
    TokenListItem *item = (TokenListItem *) malloc(sizeof(TokenList));
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

Token *pop(TokenList *list) {
    TokenListItem *item = list->first;
    list->first = item->nextItem;
    if (list->first == NULL) {
        list->last = NULL;
    }

    Token *token = item->token;
    destroyListItem(item);
    return token;
}

bool isEmpty(TokenList *list) {
    return list->first == NULL;
}

void destroyListItem(TokenListItem *item) {
    free(item);
}

void destroyList(TokenList *list) {
    TokenListItem *item = list->first;
    while (item != NULL) {
        TokenListItem *tmp = item;
        item = tmp->nextItem;
        destroyListItem(tmp);
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
