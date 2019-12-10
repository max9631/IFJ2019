#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include "Node.h"
#include "Token.h"

typedef union StackItem {
    int intValue;
    PrefixItem *prefixItem;
    Token *token;
} StackItem;

typedef struct _Stack {
    StackItem *items;
    int count;
} Stack;

Stack *createStack(void);
StackItem topStack(Stack *stack);
void pushStack(Stack *stack, StackItem item);
StackItem popStack(Stack *stack);
void destroyStack(Stack *stack);

void pushIntToStack(Stack *stack, int i);
void pushPrefixToStack(Stack *stack, PrefixItem *prefix);
void pushTokenToStack(Stack *stack, Token *token);

#endif
