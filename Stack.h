#ifndef STACK_H
#define STACK_H
#include <stdlib.h>

typedef struct _Stack {
    void **items;
    int count;
} Stack;

Stack *createStack(void);
void *topStack(Stack *stack);
void pushStack(Stack *stack, void *item);
void *popStack(Stack *stack);
void destroyStack(Stack *stack);

#endif
