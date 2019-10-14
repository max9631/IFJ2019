#import <stdlib.h>
#import "TokenList.h"

struct TokenList *createList() {
    struct TokenList *list = (struct TokenList *) malloc(sizeof(struct TokenList));
    list->first = NULL;
    list->last = NULL;
    return list;

}

bool addTokenToList(struct String *token, struct TokenList *list) {
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

struct TokenListItem *pop(struct TokenList *list) {
    struct TokenListItem *item = list->first;
    list->first = item->nextItem;
    if (list->first == NULL) {
        list->last = NULL;
    }
    return item;
}

bool isEmpty(struct TokenList *list) {
    return list->first == NULL;
}

void destroyItem(struct TokenListItem *item) {
    free(item);
}

void destroyList(struct TokenList *list) {
    free(list);
}

int main() {
    return 0;
}