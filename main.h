/*
 * Author(s): Adam Salih (xsalih01)
 * File: main.h, Contains main body of the program
 */
 
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Scanner.h"
#include "String.h"
#include "Error.h"
#include "Parser.h"
#include "Generator.h"

Document *document;
List *tokenList;
bool inDebugMode;

#endif //MAIN_H
