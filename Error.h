#ifndef Errors
#define Errors

#include <stdio.h>
#include <stdarg.h>

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

void cleanResources();
void handleError(ErrorCodes code, char* message, ...);

#endif