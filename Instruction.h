/*
 * Author(s): Tomáš Rusín (xrusin04)
 * Project: Implementace prekladace imperativniho jazyka jazyka IFJ19
 * File: Instruction.h, definitions of assembly instructions
 */

#ifndef ASSEMBLYDEFS_H
#define ASSEMBLYDEFS_H
#include "String.h"

void instructionIFJSign(void);

// Work with frames and function calling instructions
void instructionMove(String *var, String *sym);
void instructionCreateFrame(void);
void instructionPushFrame(void);
void instructionPopFrame(void);
void instructionDefVar(String *var);
void instructionCall(String *label);
void instructionReturn(void);

// Data stack functions
void instructionPushStack(String *var);
void instructionPopStack(String *var);
void instructionClearStack(void);

// Arithmetic, relational, boolean and converting instructions
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

// Input-output instructions
void instructionRead(String *var, String *type);
void instructionWrite(String *symb);

// Work with strings
void instructionConcat(String *var, String *sym1, String *sym2);
void instructionStrLen(String *var, String *str);
void instructionGetChar(String *var, String *str, String *position);
void instructionSetChar(String *var);

// Work with types
void instructionType(String *var, String *sym);

// Functions for controling program flow
void instructionLabel(String *label);
void instructionJump(String *label);
void instructionJumpIfEquals(String *label, String *symb1, String *symb2);
void instructionJumpIfNotEquals(String *label, String *symb1, String *symb2);
void instructionJumpIfEqualsStack(String *label);
void instructionJumpIfNotEqualsStack(String *label);
void instructionExit(int exitCode);

// Debug instrictions
void instructionBreak(void);
void instructionDPrint(void);

#endif //ASSEMBLYDEFS_H
