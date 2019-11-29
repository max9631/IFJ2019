#ifndef Error_H
#define Error_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "Resource.h"

typedef enum ErrorCodes {
    OK = 0,
    LexError = 1,
    SyntaxError = 2,
    SemanticIdentifierError = 3,
    SemanticTypeError = 4,
    SemanticArgumentError = 5,
    SemanticGeneralError = 6,
    ZeroDivision = 9,
    InternalError = 99
} ErrorCodes;

void handleError(ErrorCodes code, char* message, ...);

#endif
