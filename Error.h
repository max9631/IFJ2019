#ifndef Error_H
#define Error_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "Resource.h"

typedef enum ErrorCodes {
    OK = 0,
    LexError = 1,
    SyntaxError = 2,
    SEM_UndefinedVariable = 3,
    SEM_TypeError = 4,
    SEM_InvalidParamsCount = 5,
    SEM_Other = 6,
    ZeroDivision = 9,
    InternalError = 99
} ErrorCodes;

void handleError(ErrorCodes code, char* message, ...);

#endif
