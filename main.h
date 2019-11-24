#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Fakin hack, protoze GCC nedokaze vypnut warningy na nepouzivane promenne napric platformami.
#define UNUSED(x) (void)(x);

#include "List.h"
#include "Scanner.h"
#include "String.h"
#include "Error.h"
#include "Parser.h"
#include "Generator.h"

Document *document;
List *tokenList;
bool inDebugMode;

#endif
