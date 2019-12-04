#ifndef EMBEDDED_H
#define EMBEDDED_H

#include "Instruction.h"
#include "Generator.h"

void generateImplicitConversionFunction(Generator *generator);
void generateCheckIfTypeFunction(Generator *generator);
void generateCheckIfNotTypeFunction(Generator *generator);
void generateConvertToFloatFunction(Generator *generator);
void generateConvertNilToNoneString(Generator *Generator);

void generateTypeSafeAddFunction(Generator *generator);
void generateTypeSafeSubFunction(Generator *generator);
void generateTypeSafeMulFunction(Generator *generator);
void generateTypeSafeDivFunction(Generator *generator);
void generateTypeSafeEqualsFunction(Generator *generator);
void generateTypeSafeGreaterFunction(Generator *generator);
void generateTypeSafeLessFunction(Generator *generator);
void generateTypeSafeAndFunction(Generator *generator);
void generateTypeSafeOrFunction(Generator *generator);
void generateTypeSafeIdivFunction(Generator *generator);
void generateTypeSafeNotFunction(Generator *generator);

void generateChrFunction(Generator *generator);
void generateOrdFunction(Generator *generator);
void generateSubStringFunction(Generator *generator);

#endif
