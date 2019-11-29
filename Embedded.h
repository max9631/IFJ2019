#ifndef EMBEDDED_H
#define EMBEDDED_H

#include "Instruction.h"
#include "Generator.h"

void generateCheckExpressionTypesFunction(Generator *generator);
void generateCheckTypeFunction(Generator *generator);
void generateConvertToFloatFunction(Generator *generator);
void generateConvertNilToNoneString(Generator *Generator);
void generateAddOrConcat(Generator *generator);
void generateChrFunction(Generator *generator);
void generateOrdFunction(Generator *generator);
void generateSubStringFunction(Generator *generator);

#endif
