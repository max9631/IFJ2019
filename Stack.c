/*
 * Author(s): Adam Salih (xsalih01)
 * Project: Implementace prekladace imperativniho jazyka jazyka IFJ19
 * File: Stack.c, implementation of stack
 */

#include "Stack.h"


Stack *createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->items = NULL;
    stack->count = 0;
    return stack;
}

StackItem topStack(Stack *stack) {
    return stack->items[stack->count - 1];
}

void pushStack(Stack *stack, StackItem item) {
    stack->count++;
    stack->items = realloc(stack->items, stack->count * sizeof(void *));
    stack->items[stack->count - 1] = item;
}

void pushIntToStack(Stack *stack, int i) {
    StackItem item;
    item.intValue = i;
    pushStack(stack, item);
}

void pushPrefixToStack(Stack *stack, PrefixItem *prefix) {
    StackItem item;
    item.prefixItem = prefix;
    pushStack(stack, item);
}

void pushTokenToStack(Stack *stack, Token *token) {
    StackItem item;
    item.token = token;
    pushStack(stack, item);
}

StackItem popStack(Stack *stack) {
    StackItem item;
    item.intValue = 0;
    if (stack->count == 0) return item;
    item = stack->items[stack->count-1];
    stack->count--;
    stack->items = realloc(stack->items, stack->count * sizeof(void *));
    return item;
}

void destroyStack(Stack *stack) {
    if (stack->count > 0) free(stack->items);
    free(stack);
}
