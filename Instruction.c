#include "Instruction.h"

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
void instructionAdd(String *var) {
    printf("ADD %s\n", var->value);
}

void instructionSub(String *var) {
    printf("SUB %s\n", var->value);
}

void instructionMul(String *var) {
    printf("MUL %s\n", var->value);
}

void instructionDiv(String *var) {
    printf("DIV %s\n", var->value);
}

void instructionIDiv(String *var) {
    printf("IDIV %s\n", var->value);
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
    printf("LT %s %s %S\n", var->value, sym1->value, sym2->value);
}

void instructionGreaterThan(String *var, String *sym1, String *sym2) {
    printf("GT %s %s %S\n", var->value, sym1->value, sym2->value);
}

void instructionEquals(String *var) {
    printf("EQ %s\n", var->value);
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

void instructionAnd(String *var) {
    printf("AND %s\n", var->value);
}

void instructionOr(String *var) {
    printf("OR %s\n", var->value);
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

void instructionIntToFloat(String *var) {
    printf("INT2FLOAT %s\n", var->value);
}

void instructionFloatToInt(String *var) {
    printf("FLOAT2INT %s\n", var->value);
}

void instructionIntToChar(String *var, String *strchar) {
    printf("INT2CHAR %s %s\n", var->value, strchar->value);
}

void instructionStringToInt(String *var) {
    printf("STRI2INT %s\n", var->value);
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
void instructionType(String *var) {
    printf("TYPE %s\n", var->value);
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

void instructionExit() {
    printf("EXIT\n");
}

// Ladici instrukce
void instructionBreak() {
    printf("BREAK\n");
}

void instructionDPrint() {
    printf("DPRINT\n");
}
