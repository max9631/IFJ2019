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

Document *document;
List *tokenList;
bool inDebugMode;

#endif
