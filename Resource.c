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
