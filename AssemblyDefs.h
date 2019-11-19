#ifndef ASSEMBLYDEFS_H
#define ASSEMBLYDEFS_H
#include "string.h"

// Prace s ramci, volani funkci
void move();
void createFrame();
void pushFrame();
void popFrame();
void defvar();
void call(String *label);
void return_instr();

// Prace s datovym zasobnikem
void pushs();
void pops();
void clears();

// Aritmeticke, relacni, booleovske a konverzni instrukce
void add();
void sub();
void mul();
void div_instr();
void idiv();
void adds();
void subs();
void muls();
void divs();
void idivs();
void lt();
void gt();
void eq();
void lts();
void gts();
void eqs();
void and_instr();
void or_instr();
void not_instr();
void ands();
void ors();
void nots();
void intToFloat();
void floatToInt();
void intToChar();
void striToInt();
void intToFloats();
void floatToInts();
void intToChars();
void striToInts();

// Vstupne-Vystupni instrukce
void read();
void write();

// Prace s reteci
void concat();
void strlen_instr();
void getchar_instr();
void setchar();

// Prace s typy
void type();

// Instrukce pro rizeni toku programu
void label(String *label);
void jump(String *label);
void jumpifeq();
void jumpifneq();
void jumpifeqs(String *label);
void jumpifneqs(String *label);
void exit_instr();

// Ladici instrukce
void break_instr();
void dprint();

#endif // !ASSEMBLYDEFS_H
