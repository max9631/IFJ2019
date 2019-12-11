/*
 * Author(s): Adam Salih (xsalih01)
 * Project: Implementace prekladace imperativniho jazyka jazyka IFJ19
 * File: Stack.h, implementation of stack
 */

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

//Creates a data stack
Stack *createStack(void);

//Pointer to the top of stack
StackItem topStack(Stack *stack);

//Pushes item to the stack
void pushStack(Stack *stack, StackItem item);

//Pops last item from the stack
StackItem popStack(Stack *stack);

//Destroys (deallocates) stack
void destroyStack(Stack *stack);


//Function for pushing to the stack
void pushIntToStack(Stack *stack, int i);
void pushPrefixToStack(Stack *stack, PrefixItem *prefix);
void pushTokenToStack(Stack *stack, Token *token);

#endif //STACK_H
