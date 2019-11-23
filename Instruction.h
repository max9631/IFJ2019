#ifndef ASSEMBLYDEFS_H
#define ASSEMBLYDEFS_H
#include "String.h"

// Prace s ramci, volani funkci
void instructionMove(void);
void instructionCreateFrame(void);
void instructionPushFrame(void);
void instructionPopFrame(void);
void instructionDefVar(void);
void instructionCall(String *label);
void instructionReturn(void);

// Prace s datovym zasobnikem
void instructionPushStack(void);
void instructionPopStack(void);
void instructionClearStack(void);

// Aritmeticke, relacni, booleovske a konverzni instrukce
void instructionAdd(void);
void instructionSub(void);
void instructionMul(void);
void instructionDiv(void);
void instructionIDiv(void);
void instructionAddStack(void);
void instructionSubStack(void);
void instructionMulStack(void);
void instructionDivStack(void);
void instructionIDivStack(void);
void instructionLessThan(void);
void instructionGreaterThan(void);
void instructionEquals(void);
void instructionLessThanStack(void);
void instructionGreaterThanStack(void);
void instructionEqualsStack(void);
void instructionAnd(void);
void instructionOr(void);
void instructionNot(void);
void instructionAndStack(void);
void instructionOrStack(void);
void instructionNotStack(void);
void instructionIntToFloat(void);
void instructionFloatToInt(void);
void instructionIntToChar(void);
void instructionStringToInt(void);
void instructionIntToFloats(void);
void instructionFloatToInts(void);
void instructionIntToChars(void);
void instructionStriToInts(void);

// Vstupne-Vystupni instrukce
void instructionRead(void);
void instructionWrite(void);

// Prace s reteci
void instructionConcat(void);
void instructionStrLen(void);
void instructionGetChar(void);
void instructionSetChar(void);

// Prace s typy
void instructionType(void);

// Instrukce pro rizeni toku programu
void instructionLabel(String *label);
void instructionJump(String *label);
void instructionJumpIfEquls(void);
void instructionJumpIfNotEqulas(void);
void instructionJumpIfEqulsStack(String *label);
void instructionJumpIfNotEqualsStack(String *label);
void instructionExit(void);

// Ladici instrukce
void instructionBreak(void);
void instructionDPrint(void);

#endif
