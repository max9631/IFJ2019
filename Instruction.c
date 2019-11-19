#include "Instruction.h"

// Prace se zasobnikem, volani funkci.
void instrutionMove(){
    printf("MOVE\n");
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
    printf("DEFVAR\n");
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

void instrutionPopStack() {
    printf("POPS\n");

}

void instrutionClearStack() {
    printf("CLEARS\n");
}

// Aritmeticke, relacni, booleovske a konverzni instrukce
void instrutionAdd() {
    printf("ADD\n");

}

void instrutionSub() {
    printf("SUB\n");

}

void instrutionMul() {
    printf("MUL\n");

}

void instrutionDiv() {
    printf("DIV\n");

}

void instrutionIDiv() {
    printf("IDIV\n");

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

void instrutionLessThan() {
    printf("LESSTHAN\n");

}

void instrutionGreaterThan() {
    printf("GREATERTHAN\n");

}

void instrutionEquals() {
    printf("EQUALS\n");

}

void instrutionLessThanStack() {
    printf("LESSTHANS\n");

}

void instrutionGreaterThanStack() {
    printf("GREATERTHANS\n");

}

void instrutionEqualsStack() {
    printf("EQUALSS\n");
    
}

void instrutionAnd() {
    printf("AND\n");

}

void instrutionOr() {
    printf("OR\n");

}

void instrutionNot() {
    printf("NOT\n");

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

void instrutionIntToFloat() {
    printf("INTTOFLOAT\n");

}

void instrutionFloatToInt() {
    printf("FLOATTOINT\n");

}

void instrutionIntToChar() {
    printf("INTTOCHAR\n");

}

void instrutionStringToInt() {
    printf("STRINGTOINT\n");

}

void instrutionIntToFloats() {
    printf("INTTOFLOATS\n");

}

void instrutionFloatToInts() {
    printf("FLOATTOINTS\n");

}

void instrutionIntToChars() {
    printf("INTTOCHARS\n");

}

void instrutionStriToInts() {
    printf("STRITOINTS\n");

}

// Vstupne-Vystupni instrukce
void instrutionRead() {
    printf("READ\n");

}

void instrutionWrite() {
    printf("WRITE\n");

}

// Prace s reteci
void instrutionConcat() {
    printf("CONCAT\n");

}

void instrutionStrLen() {
    printf("STRLEN\n");

}

void instrutionGetChar() {
    printf("GETCHAR\n");

}

void instrutionSetChar() {
    printf("SETCHAR\n");

}

// Prace s typy
void instrutionType() {
    printf("TYPE\n");

}

// Instrukce pro rizeni toku programu
void instrutionLabel(String *label) {
    printf("LABEL %s\n", label->value);
}

void instrutionJump(String *label) {
    printf("JUMP %s\n", label->value);
}

void instrutionJumpIfEquls() {
    printf("JUMPIFEQ\n");

}

void instrutionJumpIfNotEqulas() {
    printf("JUMPIFNEQ\n");

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
