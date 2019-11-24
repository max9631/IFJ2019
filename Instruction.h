#ifndef ASSEMBLYDEFS_H
#define ASSEMBLYDEFS_H
#include "String.h"

// Prace s ramci, volani funkci
void instructionMove(String *var);
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
void instructionLessThan(String *var);
void instructionGreaterThanStack();
void instructionEqualsStack();
void instructionLessThanStack();
void instrutionGreaterThanStack();
void instrutionEqualsStack();
void instructionAnd(String *var);
void instructionOr(String *var);
void instructionNot(String *var);
void instructionAndStack();
void instructionOrStack();
void instructionNotStack();
void instructionIntToFloat(String *var);
void instructionFloatToInt(String *var);
void instructionIntToChar(String *var);
void instructionStringToInt(String *var);
void instructionIntToFloats();
void instructionFloatToInts();
void instructionIntToChars();
void instructionStriToInts();

// Vstupne-Vystupni instrukce
void instructionRead(String *var);
void instructionWrite();

// Prace s reteci
void instructionConcat(String *var);
void instructionStrLen(String *var);
void instructionGetChar(String *var);
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
