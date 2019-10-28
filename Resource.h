#ifndef RESOURCE_H
#define RESOURCE_H
#include <stdbool.h>
#include <stdio.h>

struct TokenList;

extern struct TokenList *tokenList;
extern bool inDebugMode;

void cleanResources();
void msg(char *message, ...);

#endif
