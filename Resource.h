/*
 * Author(s): Adam Salih (xsalih01)
 * Project: Implementace prekladace imperativniho jazyka jazyka IFJ19
 * File: Resource.h, Support for global variables availability
 */

#ifndef RESOURCE_H
#define RESOURCE_H
#include <stdbool.h>
#include <stdio.h>

struct List;

extern struct List *tokenList;
extern bool inDebugMode;

//Cleans all resources
void cleanResources(void);

//In debug mode prints debug message
void msg(char *message, ...);

#endif //RESOURCE_H
