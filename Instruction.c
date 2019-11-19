#include "Instruction.h"

// Prace se zasobnikem, volani funkci.
void instrutionMove(String *var) {
    printf("MOVE %s\n", var->value);
}

void instrutionCreateFrame() {
    printf("CREATEFRAME\n");
}

void instrutionPushFrame() {
    printf("PUSHFRAME\n");
}

void instrutionPopFrame() {
    printf("POPRFRAME\n");
}

void instrutionDefVar(String *var) {
    printf("DEFVAR %s\n", var->value);
}

void instrutionCall(String *label) {
    printf("CALL %s\n", label->value);
}

void instrutionReturn() {
    printf("RETURN\n");
}

// Prace s datovym zasobnikem
void instrutionPushStack() {
    printf("PUSHS\n");
}

void instrutionPopStack(String *var) {
    printf("POPS %s\n", var->value);
}

void instrutionClearStack() {
    printf("CLEARS\n");
}

// Aritmeticke, relacni, booleovske a konverzni instrukce
void instrutionAdd(String *var) {
    printf("ADD %s\n", var->value);
}

void instrutionSub(String *var) {
    printf("SUB %s\n", var->value);
}

void instrutionMul(String *var) {
    printf("MUL %s\n", var->value);
}

void instrutionDiv(String *var) {
    printf("DIV %s\n", var->value);
}

void instrutionIDiv(String *var) {
    printf("IDIV %s\n", var->value);
}

void instrutionAddStack() {
    printf("ADDS\n");
}

void instrutionSubStack() {
    printf("SUBS\n");
}

void instrutionMulStack() {
    printf("MULS\n");
}

void instrutionDivStack() {
    printf("DIVS\n");
}

void instrutionIDivStack() {
    printf("IDIVS\n");
}

void instrutionLessThan(String *var) {
    printf("LT %s\n", var->value);
}

void instrutionGreaterThan(String *var) {
    printf("GT %s\n", var->value);
}

void instrutionEquals(String *var) {
    printf("EQ %s\n", var->value);
}

void instrutionLessThanStack() {
    printf("LTS\n");
}

void instrutionGreaterThanStack() {
    printf("GTS\n");
}

void instrutionEqualsStack() {
    printf("EQS\n");
}

void instrutionAnd(String *var) {
    printf("AND %s\n", var->value);
}

void instrutionOr(String *var) {
    printf("OR %s\n", var->value);
}

void instrutionNot(String *var) {
    printf("NOT %s\n", var->value);
}

void instrutionAndStack() {
    printf("ANDS\n");
}

void instrutionOrStack() {
    printf("ORS\n");
}

void instrutionNotStack() {
    printf("NOTS\n");
}

void instrutionIntToFloat(String *var) {
    printf("INT2FLOAT %s\n", var->value);
}

void instrutionFloatToInt(String *var) {
    printf("FLOAT2INT %s\n", var->value);
}

void instrutionIntToChar(String *var) {
    printf("INT2CHAR %s\n", var->value);
}

void instrutionStringToInt(String *var) {
    printf("STRI2INT %s\n", var->value);
}

void instrutionIntToFloats() {
    printf("INT2FLOATS\n");
}

void instrutionFloatToInts() {
    printf("FLOAT2INTS\n");
}

void instrutionIntToChars() {
    printf("INT2CHARS\n");
}

void instrutionStriToInts() {
    printf("STRI2INTS\n");
}

// Vstupne-Vystupni instrukce
void instrutionRead(String *var) {
    printf("READ %s\n", var->value);
}

void instrutionWrite() {
    printf("WRITE\n");
}

// Prace s reteci
void instrutionConcat(String *var) {
    printf("CONCAT %s\n", var->value);
}

void instrutionStrLen(String *var) {
    printf("STRLEN %s\n", var->value);
}

void instrutionGetChar(String *var) {
    printf("GETCHAR %s\n", var->value);
}

void instrutionSetChar(String *var) {
    printf("SETCHAR %s\n", var->value);
}

// Prace s typy
void instrutionType(String *var) {
    printf("TYPE %s\n", var->value);
}

// Instrukce pro rizeni toku programu
void instrutionLabel(String *label) {
    printf("LABEL %s\n", label->value);
}

void instrutionJump(String *label) {
    printf("JUMP %s\n", label->value);
}

void instrutionJumpIfEquls(String *label) {
    printf("JUMPIFEQ %s\n", label->value);
}

void instrutionJumpIfNotEquals(String *label) {
    printf("JUMPIFNEQ %s\n", label->value);
}

void instrutionJumpIfEqulsStack(String *label) {
    printf("JUMPIFEQS %s\n", label->value);
}

void instrutionJumpIfNotEqualsStack(String *label) {
    printf("JUMPIFNEQS %s\n", label->value);
}

void instrutionExit() {
    printf("EXIT\n");
}

// Ladici instrukce
void instrutionBreak() {
    printf("BREAK\n");
}

void instrutionDPrint() {
    printf("DPRINT\n");
}
