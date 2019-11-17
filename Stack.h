#ifndef Stack_H
#define STACK_H
#include <stdlib.h>

typedef struct _Stack {
    void **items;
    int count;
} Stack;

Stack *createStack(void);
void push(Stack *stack, void *item);
void *pop(Stack *stack);
void destroyStack(Stack *stack);

#endif
