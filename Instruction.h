#ifndef ASSEMBLYDEFS_H
#define ASSEMBLYDEFS_H
#include "String.h"

// Prace s ramci, volani funkci
void instrutionMove(String *var);
void instrutionCreateFrame();
void instrutionPushFrame();
void instrutionPopFrame();
void instrutionDefVar(String *var);
void instrutionCall(String *label);
void instrutionReturn();

// Prace s datovym zasobnikem
void instrutionPushStack();
void instrutionPopStack(String *var);
void instrutionClearStack();

// Aritmeticke, relacni, booleovske a konverzni instrukce
void instrutionAdd(String *var);
void instrutionSub(String *var);
void instrutionMul(String *var);
void instrutionDiv(String *var);
void instrutionIDiv(String *var);
void instrutionAddStack();
void instrutionSubStack();
void instrutionMulStack();
void instrutionDivStack();
void instrutionIDivStack();
void instrutionLessThan(String *var);
void instrutionGreaterThan(String *var);
void instrutionEquals(String *var);
void instrutionLessThanStack();
void instrutionGreaterThanStack();
void instrutionEqualsStack();
void instrutionAnd(String *var);
void instrutionOr(String *var);
void instrutionNot(String *var);
void instrutionAndStack();
void instrutionOrStack();
void instrutionNotStack();
void instrutionIntToFloat(String *var);
void instrutionFloatToInt(String *var);
void instrutionIntToChar(String *var);
void instrutionStringToInt(String *var);
void instrutionIntToFloats();
void instrutionFloatToInts();
void instrutionIntToChars();
void instrutionStriToInts();

// Vstupne-Vystupni instrukce
void instrutionRead(String *var);
void instrutionWrite();

// Prace s reteci
void instrutionConcat(String *var);
void instrutionStrLen(String *var);
void instrutionGetChar(String *var);
void instrutionSetChar(String *var);

// Prace s typy
void instrutionType(String *var);

// Instrukce pro rizeni toku programu
void instrutionLabel(String *label);
void instrutionJump(String *label);
void instrutionJumpIfEquls(String *label);
void instrutionJumpIfNotEquals(String *label);
void instrutionJumpIfEqulsStack(String *label);
void instrutionJumpIfNotEqualsStack(String *label);
void instrutionExit();

// Ladici instrukce
void instrutionBreak();
void instrutionDPrint();

#endif
