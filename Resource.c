/*
 * Author(s): Adam Salih (xsalih01)
 * Project: Implementace prekladace imperativniho jazyka jazyka IFJ19
 * File: Resource.c, Support for global variables availability
 */

#include "Resource.h"
#include "List.h"

void cleanResources() {
    if(tokenList != NULL)
        destroyList(tokenList);
}

void msg(char *message, ...) {
    if (!inDebugMode)
        return;

    va_list argList;
    va_start(argList, message);
    vfprintf(stderr, message, argList);
    va_end(argList);
}
