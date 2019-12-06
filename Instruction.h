#ifndef ASSEMBLYDEFS_H
#define ASSEMBLYDEFS_H
#include "String.h"

void instructionIFJSign(void);

// Prace s ramci, volani funkci
void instructionMove(String *var, String *sym);
void instructionCreateFrame(void);
void instructionPushFrame(void);
void instructionPopFrame(void);
void instructionDefVar(String *var);
void instructionCall(String *label);
void instructionReturn(void);

// Prace s datovym zasobnikem
void instructionPushStack(String *var);
void instructionPopStack(String *var);
void instructionClearStack(void);

// Aritmeticke, relacni, booleovske a konverzni instrukce
void instructionAdd(String *var, String *symb1, String *symb2);
void instructionSub(String *var, String *symb1, String *symb2);
void instructionMul(String *var, String *symb1, String *symb2);
void instructionDiv(String *var, String *symb1, String *symb2);
void instructionIDiv(String *var, String *symb1, String *symb2);
void instructionAddStack(void);
void instructionSubStack(void);
void instructionMulStack(void);
void instructionDivStack(void);
void instructionIDivStack(void);
void instructionLessThan(String *var, String *sym1, String *sym2);
void instructionGreaterThan(String *var, String *sym1, String *sym2);
void instructionEquals(String *var, String *sym1, String *sym2);
void instructionGreaterThanStack(void);
void instructionEqualsStack(void);
void instructionLessThanStack(void);
void instructionAnd(String *var, String *sym1, String *sym2);
void instructionOr(String *var, String *sym1, String *sym2);
void instructionNot(String *var, String *sym);
void instructionAndStack(void);
void instructionOrStack(void);
void instructionNotStack(void);
void instructionIntToFloat(String *var, String *sy);
void instructionFloatToInt(String *var, String *sy);
void instructionIntToChar(String *var, String *strchar);
void instructionStringToInt(String *var, String *sym1, String *sym2);
void instructionIntToFloatStack(void);
void instructionFloatToIntStack(void);
void instructionIntToCharStack(void);
void instructionStriToIntStack(void);

// Vstupne-Vystupni instrukce
void instructionRead(String *var, String *type);
void instructionWrite(String *symb);

// Prace s reteci
void instructionConcat(String *var, String *sym1, String *sym2);
void instructionStrLen(String *var, String *str);
void instructionGetChar(String *var, String *str, String *position);
void instructionSetChar(String *var);

// Prace s typy
void instructionType(String *var, String *sym);

// Instrukce pro rizeni toku programu
void instructionLabel(String *label);
void instructionJump(String *label);
void instructionJumpIfEquals(String *label, String *symb1, String *symb2);
void instructionJumpIfNotEquals(String *label, String *symb1, String *symb2);
void instructionJumpIfEqualsStack(String *label);
void instructionJumpIfNotEqualsStack(String *label);
void instructionExit(int exitCode);

// Ladici instrukce
void instructionBreak(void);
void instructionDPrint(void);

#endif
