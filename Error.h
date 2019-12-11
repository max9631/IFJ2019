/*
 * Author(s): Michal Halabica (xhalab00)
 * File: Error.h, Implementation of error codes and error handling
 */
 
#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "Resource.h"

//Enum containing error codes
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

//Handles error and prints error message
void handleError(ErrorCodes code, char* message, ...);

#endif //ERROR_H
