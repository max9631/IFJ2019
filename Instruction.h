#ifndef ASSEMBLYDEFS_H
#define ASSEMBLYDEFS_H
#include "string.h"

// Prace s ramci, volani funkci
void instrutionMove();
void instrutionCreateFrame();
void instrutionPushFrame();
void instrutionPopFrame();
void instrutionDefVar();
void instrutionCall(String *label);
void instrutionReturn();

// Prace s datovym zasobnikem
void instrutionPushStack();
void instrutionPopStack();
void instrutionClearStack();

// Aritmeticke, relacni, booleovske a konverzni instrukce
void instrutionAdd();
void instrutionSub();
void instrutionMul();
void instrutionDiv();
void instrutionIDiv();
void instrutionAddStack();
void instrutionSubStack();
void instrutionMulStack();
void instrutionDivStack();
void instrutionIDivStack();
void instrutionLessThan();
void instrutionGreaterThan();
void instrutionEquals();
void instrutionLessThanStack();
void instrutionGreaterThanStack();
void instrutionEqualsStack();
void instrutionAnd();
void instrutionOr();
void instrutionNot();
void instrutionAndStack();
void instrutionOrStack();
void instrutionNotStack();
void instrutionIntToFloat();
void instrutionFloatToInt();
void instrutionIntToChar();
void instrutionStringToInt();
void instrutionIntToFloats();
void instrutionFloatToInts();
void instrutionIntToChars();
void instrutionStriToInts();

// Vstupne-Vystupni instrukce
void instrutionRead();
void instrutionWrite();

// Prace s reteci
void instrutionConcat();
void instrutionStrLen();
void instrutionGetChar();
void instrutionSetChar();

// Prace s typy
void instrutionType();

// Instrukce pro rizeni toku programu
void instrutionLabel(String *label);
void instrutionJump(String *label);
void instrutionJumpIfEquls();
void instrutionJumpIfNotEqulas();
void instrutionJumpIfEqulsStack(String *label);
void instrutionJumpIfNotEqualsStack(String *label);
void instrutionExit();

// Ladici instrukce
void instrutionBreak();
void instrutionDPrint();

#endif
