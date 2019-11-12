#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "TokenList.h"
#include "Scanner.h"
#include "String.h"
#include "Error.h"
#include "Parser.h"

Document *document;
TokenList *tokenList;
bool inDebugMode;

#endif
