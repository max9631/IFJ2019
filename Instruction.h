#ifndef ASSEMBLYDEFS_H
#define ASSEMBLYDEFS_H
#include "String.h"

void instructionIFJSign();

// Prace s ramci, volani funkci
void instructionMove(String *var, String *sym);
void instructionCreateFrame();
void instructionPushFrame();
void instructionPopFrame();
void instructionDefVar(String *var);
void instructionCall(String *label);
void instructionReturn();

// Prace s datovym zasobnikem
void instructionPushStack(String *var);
void instructionPopStack(String *var);
void instructionClearStack();

// Aritmeticke, relacni, booleovske a konverzni instrukce
void instructionAdd(String *var);
void instructionSub(String *var);
void instructionMul(String *var);
void instructionDiv(String *var);
void instructionIDiv(String *var);
void instructionAddStack();
void instructionSubStack();
void instructionMulStack();
void instructionDivStack();
void instructionIDivStack();
void instructionLessThan(String *var, String *sym1, String *sym2);
void instructionGreaterThan(String *var, String *sym1, String *sym2);
void instructionGreaterThanStack();
void instructionEqualsStack();
void instructionLessThanStack();
void instrutionEqualsStack();
void instructionAnd(String *var);
void instructionOr(String *var);
void instructionNot(String *var);
void instructionAndStack();
void instructionOrStack();
void instructionNotStack();
void instructionIntToFloat(String *var);
void instructionFloatToInt(String *var);
void instructionIntToChar(String *var, String *strchar);
void instructionStringToInt(String *var);
void instructionIntToFloatStack();
void instructionFloatToIntStack();
void instructionIntToCharStack();
void instructionStriToIntStack();

// Vstupne-Vystupni instrukce
void instructionRead(String *var, String *type);
void instructionWrite(String *symb);

// Prace s reteci
void instructionConcat(String *var, String *sym1, String *sym2);
void instructionStrLen(String *var, String *str);
void instructionGetChar(String *var, String *str, String *position);
void instructionSetChar(String *var);

// Prace s typy
void instructionType(String *var);

// Instrukce pro rizeni toku programu
void instructionLabel(String *label);
void instructionJump(String *label);
void instructionJumpIfEquals(String *label, String *symb1, String *symb2);
void instructionJumpIfNotEquals(String *label, String *symb1, String *symb2);
void instructionJumpIfEqualsStack(String *label);
void instructionJumpIfNotEqualsStack(String *label);
void instructionExit();

// Ladici instrukce
void instructionBreak(void);
void instructionDPrint(void);

#endif
