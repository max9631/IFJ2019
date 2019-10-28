#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

#include "TokenList.h"
#include "String.h"
#include "Token.h"
#include "Error.h"

typedef struct Document {
	FILE *file;
	int currentChar;
	int lastIndent;
	int line;
	int column;
} Document;

Document *createDocument(FILE *file);
int nextCharacter(Document *document);
void destroyDocument(Document *document);

bool isNewLine(Document *document);
bool isEndOfLine(int c);
bool isNumber(int c);
bool isCharacter(int c);
bool isOpeningParen(int c);
bool isClosingParen(int c);
bool isDot(int c);
bool isColon(int c);
bool isEqual(int c);
bool isApostroph(int c);
bool isNot(int c);
bool isGreater(int c);
bool isLessThan(int c);
bool isPlus(int c);
bool isMinus(int c);
bool isDevision(int c);
bool isMultiplication(int c);
bool isSpace(int c);
bool isTerminator(int c);
bool isOperator(int c);

Token *defineValue(Document *document);
Token *defineIdentifier(Document *document);
Token *defineString(Document *document);
void countIndent(TokenList *list, Document *document);

void scan(TokenList *list, Document *document);

#endif
