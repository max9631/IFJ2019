#include "Instruction.h"

void instructionIFJSign() {
    printf(".IFJcode19\n");
}

// Prace se zasobnikem, volani funkci.
void instructionMove(String *var, String *sym) {
    printf("MOVE %s %s\n", var->value, sym->value);
}

void instructionCreateFrame() {
    printf("CREATEFRAME\n");
}

void instructionPushFrame() {
    printf("PUSHFRAME\n");
}

void instructionPopFrame() {
    printf("POPFRAME\n");
}

void instructionDefVar(String *var) {
    printf("DEFVAR %s\n", var->value);
}

void instructionCall(String *label) {
    printf("CALL %s\n", label->value);
}

void instructionReturn() {
    printf("RETURN\n");
}

// Prace s datovym zasobnikem
void instructionPushStack(String *var) {
    printf("PUSHS %s\n", var->value);
}

void instructionPopStack(String *var) {
    printf("POPS %s\n", var->value);
}

void instructionClearStack() {
    printf("CLEARS\n");
}

// Aritmeticke, relacni, booleovske a konverzni instrukce
void instructionAdd(String *var, String *symb1, String *symb2) {
    printf("ADD %s %s %s\n", var->value, symb1->value, symb2->value);
}

void instructionSub(String *var, String *symb1, String *symb2) {
    printf("SUB %s %s %s\n", var->value, symb1->value, symb2->value);
}

void instructionMul(String *var, String *symb1, String *symb2) {
    printf("MUL %s %s %s \n", var->value, symb1->value, symb2->value);
}

void instructionDiv(String *var, String *symb1, String *symb2) {
    printf("DIV %s %s %s\n", var->value, symb1->value, symb2->value);
}

void instructionIDiv(String *var, String *symb1, String *symb2) {
    printf("IDIV %s %s %s\n", var->value, symb1->value, symb2->value);
}

void instructionAddStack() {
    printf("ADDS\n");
}

void instructionSubStack() {
    printf("SUBS\n");
}

void instructionMulStack() {
    printf("MULS\n");
}

void instructionDivStack() {
    printf("DIVS\n");
}

void instructionIDivStack() {
    printf("IDIVS\n");
}

void instructionLessThan(String *var, String *sym1, String *sym2) {
    printf("LT %s %s %s\n", var->value, sym1->value, sym2->value);
}

void instructionGreaterThan(String *var, String *sym1, String *sym2) {
    printf("GT %s %s %s\n", var->value, sym1->value, sym2->value);
}

void instructionEquals(String *var, String *sym1, String *sym2) {
    printf("EQ %s %s %s\n", var->value, sym1->value, sym2->value);
}

void instructionLessThanStack() {
    printf("LTS\n");
}

void instructionGreaterThanStack() {
    printf("GTS\n");
}

void instructionEqualsStack() {
    printf("EQS\n");
}

void instructionAnd(String *var, String *sym1, String *sym2) {
    printf("AND %s %s %s\n", var->value, sym1->value, sym2->value);
}

void instructionOr(String *var, String *sym1, String *sym2) {
    printf("OR %s %s %s\n", var->value, sym1->value, sym2->value);
}

void instructionNot(String *var) {
    printf("NOT %s\n", var->value);
}

void instructionAndStack() {
    printf("ANDS\n");
}

void instructionOrStack() {
    printf("ORS\n");
}

void instructionNotStack() {
    printf("NOTS\n");
}

void instructionIntToFloat(String *var, String *sym) {
    printf("INT2FLOAT %s %s\n", var->value, sym->value);
}

void instructionFloatToInt(String *var, String *sym) {
    printf("FLOAT2INT %s %s\n", var->value, sym->value);
}

void instructionIntToChar(String *var, String *strchar) {
    printf("INT2CHAR %s %s\n", var->value, strchar->value);
}

void instructionStringToInt(String *var, String *sym1, String *sym2) {
    printf("STRI2INT %s %s %s\n", var->value, sym1->value, sym2->value);
}

void instructionIntToFloatStack() {
    printf("INT2FLOATS\n");
}

void instructionFloatToIntStack() {
    printf("FLOAT2INTS\n");
}

void instructionIntToCharStack() {
    printf("INT2CHARS\n");
}

void instructionStriToIntStack() {
    printf("STRI2INTS\n");
}

// Vstupne-Vystupni instrukce
void instructionRead(String *var, String *type) {
    printf("READ %s %s\n", var->value, type->value);
}

void instructionWrite(String *symb) {
    printf("WRITE %s\n", symb->value);
}

// Prace s reteci
void instructionConcat(String *var, String *sym1, String *sym2) {
    printf("CONCAT %s %s %s\n", var->value, sym1->value, sym2->value);
}

void instructionStrLen(String *var, String *str) {
    printf("STRLEN %s %s\n", var->value, str->value);
}

void instructionGetChar(String *var, String *str, String *position) {
    printf("GETCHAR %s %s %s\n", var->value, str->value, position->value);
}

void instructionSetChar(String *var) {
    printf("SETCHAR %s\n", var->value);
}

// Prace s typy
void instructionType(String *var, String *sym) {
    printf("TYPE %s %s\n", var->value, sym->value);
}

// Instrukce pro rizeni toku programu
void instructionLabel(String *label) {
    printf("LABEL %s\n", label->value);
}

void instructionJump(String *label) {
    printf("JUMP %s\n", label->value);
}

void instructionJumpIfEquals(String *label, String *symb1, String *symb2) {
    printf("JUMPIFEQ %s %s %s\n", label->value, symb1->value, symb2->value);
}

void instructionJumpIfNotEquals(String *label, String *symb1, String *symb2) {
    printf("JUMPIFNEQ %s %s %s\n", label->value, symb1->value, symb2->value);
}

void instructionJumpIfEqualsStack(String *label) {
    printf("JUMPIFEQS %s\n", label->value);
}

void instructionJumpIfNotEqualsStack(String *label) {
    printf("JUMPIFNEQS %s\n", label->value);
}

void instructionExit(int exitCode) {
    printf("EXIT int@%d\n", exitCode);
}

// Ladici instrukce
void instructionBreak() {
    printf("BREAK\n");
}

void instructionDPrint() {
    printf("DPRINT\n");
}
