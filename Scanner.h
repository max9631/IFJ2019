/*
 * Author(s): Adam Salih (xsalih01), Tomáš Rusín (xrusin04), Jiří Veverka (xvever12)
 * File: Scanner.h, scans and tokenizes input file
 */

#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "List.h"
#include "String.h"
#include "Token.h"
#include "Error.h"
#include "Resource.h"
#include "Stack.h"

//Struct Document containing a IFJ19 code
typedef struct Document {
	FILE *file; //Input file
	int currentChar; //Position of current char
    Stack *indents; //Number of indents
	int line; //Position of current line
	int column; //Position of current column
} Document;


/**
 * Creates a document to scan from a file
 * [in] FILE *file: file containing IFJ19 code
 * [out] returns struct document
 */
Document *createDocument(FILE *file);
int nextCharacter(Document *document);
void destroyDocument(Document *document);

/**
 * Checking if input document is on new line
 * [in] Document *document: struct containing info about document
 * [out] returns true if possible, otherwise false
 */
bool isNewLine(Document *document);

/**
 * Checking if input char ascii value is EOL
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isEndOfLine(int c);

/**
 * Checking if input char ascii value is 0-9
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isNumber(int c);

/**
 * Checking if input char ascii value is a-z || A-Z
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isCharacter(int c);

/**
 * Checking if input char ascii value is (
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isOpeningParen(int c);

/**
 * Checking if input char ascii value is )
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isClosingParen(int c);

/**
 * Checking if input char ascii value is .
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isDot(int c);

/**
 * Checking if input char ascii value is ,
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isComma(int c);

/**
 * Checking if input char ascii value is :
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isColon(int c);

/**
 * Checking if input char ascii value is =
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isEqual(int c);

/**
 * Checking if input char ascii value is '
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isApostroph(int c);

/**
 * Checking if input char ascii value is !
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isNot(int c);

/**
 * Checking if input char ascii value is >
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isGreater(int c);

/**
 * Checking if input char ascii value is <
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isLessThan(int c);

/**
 * Checking if input char ascii value is +
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isPlus(int c);

/**
 * Checking if input char ascii value is -
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isMinus(int c);

/**
 * Checking if input char ascii value is /
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isDevision(int c);

/**
 * Checking if input char ascii value is *
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isMultiplication(int c);

/**
 * Checking if input char ascii value is space
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isSpace(int c);

/**
 * Checking if input char ascii value is #
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isComment(int c);

/**
 * Checking if input char ascii value is _
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isUnderscore(int c);

/**
 * Checking if input char ascii value is exponent
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isExp(int c);

/**
 * Checking if input char ascii value is valid hexa char
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isHexadecimal(int c);

/**	
 * Checking if input char ascii value is EOF
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isTerminator(int c);

/**
 * Checking if input char ascii value is operator
 * [in] int c: variable containing ascii value of char
 * [out] returns true if possible, otherwise false
 */
bool isOperator(int c);



/**
 * Defines numeric value of input character
 * [in] Document *document: Struct containing current position in document
 * [out] returns DATA_TOKEN_FLOAT or DATA_TOKEN_INT
 */
Token *defineValue(Document *document);

/**
 * Defines identifier from input character
 * [in] Document *document: Struct containing current position in document
 * [out] returns KEYWORD, DATA, OPERATOR od IDENTIFIER type token
 */
Token *defineIdentifier(Document *document);

/**
 * Defines string from array of input characters
 * [in] Document *document: Struct containing current position in document
 * [out] returns call on function or NULL
 */
Token *defineString(Document *document);

/**
 * Defines string from array of input characters
 * [in] Document *document: Struct containing current position in document
 * [out] returns DATA_TOKEN_STRINGL
 */
Token *defineDoubleQuoteString(Document *document);

/**
 * Defines string from array of input characters
 * [in] Document *document: Struct containing current position in document
 * [out] returns DATA_TOKEN_STRINGL
 */
Token *defineApostrophString(Document *document);

/**
 * Records a string until first appearance of given char (endChar)
 * [in] Document *document: Struct containing current position in document
 * [in] int endChar: variable containing ascii value of char
 * [out] returns string containing recorded string
 */
String *recordStringUntilChar(Document *document, int endChar);

/**
 * Generates indent od dedent tokens and adds it to the list
 * [in] List *list: Struct containing a list of tokens
 * [in] Document *document: Struct containing current position in document
 */
void generateIndent(List *list, Document *document);


/**
 * Scans and tokenizes input document and adds scanned tokens to the list
 * [in] List *list: Struct containing a list of tokens
 * [in] Document *document: Struct containing current position in document
 */
void scan(List *list, Document *document);

#endif //SCANNER_H
