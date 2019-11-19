#include "AssemblyDefs.h"

// Prace se zasobnikem, volani funkci.
void move()
{
}

void createFrame() { printf("CREATEFRAME\n"); }
void pushFrame() { printf("PUSHFRAME\n"); }
void popFrame() { printf("POPRFRAME\n"); }

void defvar()
{
}

void call(String *label) { printf("CALL %s\n", label->value); }
void return_instr() { printf("RETURN\n"); }

// Prace s datovym zasobnikem
void pushs()
{
}

void pops()
{
}

void clears() { printf("CLEARS\n"); }

// Aritmeticke, relacni, booleovske a konverzni instrukce
void add()
{
}

void sub()
{
}

void mul()
{
}

void div_instr()
{
}

void idiv()
{
}

void adds()
{
}

void subs()
{
}

void muls()
{
}

void divs()
{
}

void idivs()
{
}

void lt()
{
}

void gt()
{
}

void eq()
{
}

void lts()
{
}

void gts()
{
}

void eqs()
{
}

void and_instr()
{
}

void or_instr()
{
}

void not_instr()
{
}

void ands()
{
}

void ors()
{
}

void nots()
{
}

void intToFloat()
{
}

void floatToInt()
{
}

void intToChar()
{
}

void striToInt()
{
}

void intToFloats()
{
}

void floatToInts()
{
}

void intToChars()
{
}

void striToInts()
{
}

// Vstupne-Vystupni instrukce
void read()
{
}

void write()
{
}

// Prace s reteci
void concat()
{
}

void strlen_instr()
{
}

void getchar_instr()
{
}

void setchar()
{
}

// Prace s typy
void type()
{
}

// Instrukce pro rizeni toku programu
void label(String *label) { printf("LABEL %s\n", label->value); }
void jump(String *label) { printf("JUMP %s\n", label->value); }

void jumpifeq()
{
}

void jumpifneq()
{
}

void jumpifeqs(String *label) { printf("JUMPIFEQS %s\n", label->value); }
void jumpifneqs(String *label) { printf("JUMPIFNEQS %s\n", label->value); }

void exit_instr()
{
}

// Ladici instrukce
void break_instr() { printf("BREAK\n"); }

void dprint()
{
}
