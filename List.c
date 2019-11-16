#include "List.h"

List *createList() {
    List *list = (List *) malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    return list;
}

bool addToList(void *item, List *list) {
    ListItem *listItem = (ListItem *) malloc(sizeof(List));
    listItem->nextItem = NULL;
    listItem->value = item;
    if (listItem == NULL) return false;
    if (isEmpty(list)) {
        list->first = listItem;
        list->last = listItem;
    } else {
        list->last->nextItem = listItem;
        list->last = listItem;
    }
    return true;
}

void *popList(List *list) {
    if (list->first == NULL) return NULL;
    ListItem *listItem = list->first;
    list->first = listItem->nextItem;
    if (list->first == NULL) {
        list->last = NULL;
    }
    void *item = listItem->value;
    destroyListItem(listItem);
    return item;
}

bool isEmpty(List *list) {
    return list->first == NULL;
}
void destroyListItem(ListItem *item) {
    if (item != NULL) free(item);
}

void destroyList(List *list) {
    ListItem *item = list->first;
    while (item != NULL) {
        ListItem *tmp = item;
        item = tmp->nextItem;
        destroyListItem(tmp);
    }
    if (list != NULL) free(list);
}

bool addTokenToList(Token *token, List *list) {
    return addToList(token, list);
}

Token *popToken(List *list) {
    return (Token *)popList(list);
}

Token *peek(List *list) {
    return peekNext(list, 0);
}

Token *peekNext(List *list, int offset) {
    if(list == NULL)
        return NULL;

    ListItem *item = list->first;

    if(item == NULL)
        return NULL;

    if(offset == 0)
        return (Token *)item->value;

    for(int i = 0; i < offset; i++) {
        item = item->nextItem;

        if(item == NULL) 
            return NULL;
    }

    return (Token *)item->value;
}

void printList(List *list) {
    if(!inDebugMode) return;

    if (list == NULL) handleError(InternalError, "List not initialized");

    ListItem *item = list->first;
    printf("Token List:\n");
    while(item != NULL) {
        Token *token = item->value;
        String *type = convertTokenTypeToString(token->type);
        printf("%d: %s ( %s )\n",
           token->line,
           type->value,
           token->value == NULL ? "NULL" : ( token->type != TOKEN_EOL ? token->value->value : "\\n")
        );
//        destroyString(type);
        item = item->nextItem;
    }
}

Token *consume(List *list, TokenType expectedType) {
    Token *token = popToken(list);
    if (token->type == expectedType)
        return token;
    handleError(SyntaxError, "Expected token type of %s, but got %s on line %d", convertTokenTypeToString(expectedType)->value, convertTokenTypeToString(token->type)->value, token->line);
    return NULL;
}

bool isNextTokenOfType(List *list, TokenType type) {
    Token *token = peek(list);
    return token->type == type;
}
