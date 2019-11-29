#ifndef RESOURCE_H
#define RESOURCE_H
#include <stdbool.h>
#include <stdio.h>

struct List;

extern struct List *tokenList;
extern bool inDebugMode;

void cleanResources(void);
void msg(char *message, ...);

#endif
