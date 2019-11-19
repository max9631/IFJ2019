#include "Instruction.h"

// Prace se zasobnikem, volani funkci.
void instrutionMove(){

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

void instrutionDefVar() {

}

void instrutionCall(String *label) { 
    printf("CALL %s\n", label->value); 
}

void instrutionReturn() { 
    printf("RETURN\n");
}

// Prace s datovym zasobnikem
void instrutionPushStack() {

}

void instrutionPopStack() {

}

void instrutionClearStack() {
    printf("CLEARS\n");
}

// Aritmeticke, relacni, booleovske a konverzni instrukce
void instrutionAdd() {

}

void instrutionSub() {

}

void instrutionMul() {

}

void instrutionDiv() {

}

void instrutionIDiv() {

}

void instrutionAddStack() {

}

void instrutionSubStack() {

}

void instrutionMulStack() {

}

void instrutionDivStack() {

}

void instrutionIDivStack() {

}

void instrutionLessThan() {

}

void instrutionGreaterThan() {

}

void instrutionEquals() {

}

void instrutionLessThanStack() {

}

void instrutionGreaterThanStack() {

}

void instrutionEqualsStack() {
    
}

void instrutionAnd() {

}

void instrutionOr() {

}

void instrutionNot() {

}

void instrutionAndStack() {

}

void instrutionOrStack() {

}

void instrutionNotStack() {
}

void instrutionIntToFloat() {

}

void instrutionFloatToInt() {

}

void instrutionIntToChar() {

}

void instrutionStringToInt() {

}

void instrutionIntToFloats() {

}

void instrutionFloatToInts() {

}

void instrutionIntToChars() {

}

void instrutionStriToInts() {

}

// Vstupne-Vystupni instrukce
void instrutionRead() {

}

void instrutionWrite()
{
}

// Prace s reteci
void instrutionConcat()
{
}

void instrutionStrLen()
{
}

void instrutionGetChar()
{
}

void instrutionSetChar()
{
}

// Prace s typy
void instrutionType()
{
}

// Instrukce pro rizeni toku programu
void instrutionLabel(String *label) {
    printf("LABEL %s\n", label->value);
}

void instrutionJump(String *label) { 
    printf("JUMP %s\n", label->value);
}

void instrutionJumpIfEquls()
{
}

void instrutionJumpIfNotEqulas()
{
}

void instrutionJumpIfEqulsStack(String *label) { 
    printf("JUMPIFEQS %s\n", label->value);
}

void instrutionJumpIfNotEqualsStack(String *label) { 
    printf("JUMPIFNEQS %s\n", label->value);
}

void instrutionExit() {
}

// Ladici instrukce
void instrutionBreak() { 
    printf("BREAK\n"); 
}

void dprint()
{
}
