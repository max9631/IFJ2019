#include "Instruction.h"

// Prace se zasobnikem, volani funkci.
void instructionMove(){
    printf("MOVE\n");
}

void instructionCreateFrame() {
    printf("CREATEFRAME\n");
}

void instructionPushFrame() {
    printf("PUSHFRAME\n");
}

void instructionPopFrame() {
    printf("POPRFRAME\n");
}

void instructionDefVar() {
    printf("DEFVAR\n");
}


void instructionCall(String *label) {
    printf("CALL %s\n", label->value); 
}

void instructionReturn() {
    printf("RETURN\n");
}

// Prace s datovym zasobnikem
void instructionPushStack() {
    printf("PUSHS\n");

}

void instructionPopStack() {
    printf("POPS\n");

}

void instructionClearStack() {
    printf("CLEARS\n");
}

// Aritmeticke, relacni, booleovske a konverzni instrukce
void instructionAdd() {
    printf("ADD\n");

}

void instructionSub() {
    printf("SUB\n");

}

void instructionMul() {
    printf("MUL\n");

}

void instructionDiv() {
    printf("DIV\n");

}

void instructionIDiv() {
    printf("IDIV\n");

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

void instructionLessThan() {
    printf("LESSTHAN\n");

}

void instructionGreaterThan() {
    printf("GREATERTHAN\n");

}

void instructionEquals() {
    printf("EQUALS\n");

}

void instructionLessThanStack() {
    printf("LESSTHANS\n");

}

void instructionGreaterThanStack() {
    printf("GREATERTHANS\n");

}

void instructionEqualsStack() {
    printf("EQUALSS\n");
    
}

void instructionAnd() {
    printf("AND\n");

}

void instructionOr() {
    printf("OR\n");

}

void instructionNot() {
    printf("NOT\n");

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

void instructionIntToFloat() {
    printf("INTTOFLOAT\n");

}

void instructionFloatToInt() {
    printf("FLOATTOINT\n");

}

void instructionIntToChar() {
    printf("INTTOCHAR\n");

}

void instructionStringToInt() {
    printf("STRINGTOINT\n");

}

void instructionIntToFloats() {
    printf("INTTOFLOATS\n");

}

void instructionFloatToInts() {
    printf("FLOATTOINTS\n");

}

void instructionIntToChars() {
    printf("INTTOCHARS\n");

}

void instructionStriToInts() {
    printf("STRITOINTS\n");

}

// Vstupne-Vystupni instrukce
void instructionRead() {
    printf("READ\n");

}

void instructionWrite() {
    printf("WRITE\n");

}

// Prace s reteci
void instructionConcat() {
    printf("CONCAT\n");

}

void instructionStrLen() {
    printf("STRLEN\n");

}

void instructionGetChar() {
    printf("GETCHAR\n");

}

void instructionSetChar() {
    printf("SETCHAR\n");

}

// Prace s typy
void instructionType() {
    printf("TYPE\n");

}

// Instrukce pro rizeni toku programu
void instructionLabel(String *label) {
    printf("LABEL %s\n", label->value);
}

void instructionJump(String *label) {
    printf("JUMP %s\n", label->value);
}

void instructionJumpIfEquls() {
    printf("JUMPIFEQ\n");

}

void instructionJumpIfNotEqulas() {
    printf("JUMPIFNEQ\n");

}

void instructionJumpIfEqulsStack(String *label) {
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
