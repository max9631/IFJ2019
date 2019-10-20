#include "Scanner.h"

typedef struct LexerState {
	FILE *file;
	int currentChar;
} LexerState;

int nextCharacter(struct LexerState *state) {
	state->currentChar = getc(state->file);
	return state->currentChar;
}

bool isNumber(int c) { return c > 47 && c < 58; } // 0-9
bool isCharacter(int c) { return (c > 64 && c < 91) || (c > 96 && c < 123); } // a-z || A-Z
bool isOpeningCurlyBracket(int c) { return c == 123; } // {
bool isClosingCurlyBracker(int c) { return c == 125; } // }
bool isOpeningBracker(int c) { return c == 40; } // (
bool isClosingBracker(int c) { return c == 41; } // )
bool isDot(int c) { return c == 46; } // .
bool isColon(int c) { return c == 44; } // ,
bool isEqual(int c) { return c == 61; } // =
bool isApostroph(int c) { return c == 34; } // "
bool isNot(int c) { return c == 33; } // !
bool isGreater(int c) { return c == 62; } // >
bool isLessThan(int c) { return c == 60; } // <
bool isPlus(int c) { return c == 43; } // +
bool isMinus(int c) { return c == 45; } // -
bool isDevision(int c) { return c == 47; } // /
bool isMultiplication(int c) { return c == 42; } // *

bool isTerminator(int c) { return c == EOF || c == (int) ' '; }// || c == (int) '\n'; }

struct Token *defineValue(int *c, FILE *file) {

}

struct Token *defineIdentifier(int *c, FILE *file) {
    
}

struct Token *defineString(int *c, FILE *file) {

}

void scan(TokenList *list, FILE *document) {

}
