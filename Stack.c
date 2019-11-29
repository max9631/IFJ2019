#include "Stack.h"


Stack *createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->items = NULL;
    stack->count = 0;
    return stack;
}

void *topStack(Stack *stack) {
    return stack->items[stack->count - 1];
}

void pushStack(Stack *stack, void *item) {
    stack->count++;
    stack->items = realloc(stack->items, stack->count * sizeof(void *));
    stack->items[stack->count - 1] = item;
}

void *popStack(Stack *stack) {
    if (stack->count == 0) return NULL;
    void *item = stack->items[stack->count-1];
    stack->items[stack->count-1] = NULL;
    stack->count--;
    stack->items = realloc(stack->items, stack->count * sizeof(void *));
    return item;
}

void destroyStack(Stack *stack) {
    if (stack->count > 0) free(stack->items);
    free(stack);
}
