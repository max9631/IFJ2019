#include "Scanner.h"

Document *createDocument(FILE *file) {
	Document *document = (Document *) malloc(sizeof(Document));
	document->file = file;
	document->lastIndent = 0;
	document->column = 0;
	document->line = 0;
	document->currentChar = (int) '\n';
	nextCharacter(document);
    return document;
}

void destroyDocument(Document *document) {
	free(document);
}

int nextCharacter(Document *document) {
	if (isEndOfLine(document->currentChar)) {
		document->line++;
		document->column = 0;
	} else {
		document->column++;
	}
	document->currentChar = getc(document->file);
	return document->currentChar;
}

bool isNewLine(Document *document) { return document->column == 0; }
bool isEndOfLine(int c) { return c == (int) '\n'; }

bool isNumber(int c) { return c > 47 && c < 58; } // 0-9
bool isCharacter(int c) { return (c > 64 && c < 91) || (c > 96 && c < 123); } // a-z || A-Z
bool isOpeningParen(int c) { return c == (int) '('; }
bool isClosingParen(int c) { return c == (int) ')'; }
bool isDot(int c) { return c == (int) '.'; }
bool isColon(int c) { return c == (int) ','; }
bool isEqual(int c) { return c == (int) '='; }
bool isApostroph(int c) { return c == (int) '"'; }
bool isNot(int c) { return c == (int) '!'; }
bool isGreater(int c) { return c == (int) '>'; }
bool isLessThan(int c) { return c == (int) '<'; }
bool isPlus(int c) { return c == (int) '+'; }
bool isMinus(int c) { return c == (int) '-'; }
bool isDevision(int c) { return c == (int) '/'; }
bool isMultiplication(int c) { return c == (int) '*'; }
bool isSpace(int c) { return c == (int) ' '; }

bool isTerminator(int c) { return c == EOF || c == (int) ' ' || c == (int) '\n'; }

Token *defineValue(Document *document) {
	int c = document->currentChar;
	struct String *string = createStringFromChar(c);
	bool dotOccured = false;
	bool isValid = true;
	c = nextCharacter(document);
	while (!isTerminator(c)) {
		int ch = c;
		appendCharacter(string, ch);
		if (isNumber(ch)) {}
		else if (isDot(ch)) {
			if (!dotOccured) dotOccured = true;
			else isValid = false;
		} 
		else isValid = false;
		c = nextCharacter(document);
	}
	if (!isValid) handleError(LexError, "Invalid number syntax near %s", string->value);
	TokenType type = DATA_TOKEN_INT;
	if (dotOccured) 
		type = DATA_TOKEN_FLOAT; 
	return createToken(string, type);
}

Token *defineIdentifier(Document *document) {
	int c = document->currentChar;
	struct String *string = createStringFromChar(c);
	bool isValid = true;
	c = nextCharacter(document);
	while (!isTerminator(c) && !isOpeningParen(c) && !isColon(c)) {
		appendCharacter(string, c);
		if (!isCharacter(c) && !isNumber(c)) isValid = false;
		c = nextCharacter(document);
	}
	if (!isValid) handleError(SyntaxError, "Invalid number syntax near %s", string->value);
	return createToken(string, TOKEN_IDENTIFIER);
}

Token *defineString(Document *document) {
	int c = document->currentChar;
	struct String *string = createStringFromChar(c);
	c = nextCharacter(document);
	if (isApostroph(c)) {
		appendCharacter(string, c);
		c = nextCharacter(document);
	}
	while (!isApostroph(c)) {
		appendCharacter(string, c);
		c = nextCharacter(document);
	}
	if (c == EOF){
		printf("Invalid String: %s", string->value); 
		handleError(SyntaxError, "Invalid String: %s", string->value);
	}
	if (c == (int)'"') {
		appendCharacter(string, c);
		c = nextCharacter(document);
	}
	return createToken(string, DATA_TOKEN_STRING);
}

void countIndent(TokenList *list, Document *document) {
	int sum = 0;
	int ch;
	while (isSpace((ch = nextCharacter(document)))) 
		sum++;
	if (isEndOfLine(ch)) return;
	if (sum == document->lastIndent) 
		return;
	if (sum > document->lastIndent + 1) 
		handleError(SyntaxError, "Wrong number of indents at line %d column %d", document->line, document->column);
	else if (sum == document->lastIndent + 1)
		addTokenToList(createToken(NULL, TOKEN_INDENT), list);
	else if (sum < document->lastIndent) {
		int d = document->lastIndent - sum;
		for (int i = 0; i < d; i++)
			addTokenToList(createToken(NULL, TOKEN_DEINDENT), list);
	}
}

void scan(TokenList *list, Document *document) {
	struct Token *token = NULL;
	int current = nextCharacter(document);
	while (current != EOF) {
		bool tokenOccured = true;
		token = NULL;
		printf("Current char is: %c\n", current);
		if (isNumber(current)) token = defineValue(document);
		else if (isCharacter(current)) token = defineIdentifier(document);
		else if (isApostroph(current)) token = defineString(document);
		else if (isSpace(current) && isNewLine(document)) { tokenOccured = false; countIndent(list, document); }
		else if (isOpeningParen(current)) { token = createToken(createStringFromChar(current), TOKEN_OPAREN); current = nextCharacter(document); }
		else if (isClosingParen(current)) { token = createToken(createStringFromChar(current), TOKEN_CPAREN); current = nextCharacter(document); }
		else if (isColon(current)) { token = createToken(createStringFromChar(current), TOKEN_COLON); current = nextCharacter(document); }
		else if (isEqual(current)) { token = createToken(createStringFromChar(current), OPERATOR_EQL); current = nextCharacter(document); }
		else if (isNot(current)) { token = createToken(createStringFromChar(current), OPERATOR_NOT); current = nextCharacter(document); }
		else if (isGreater(current)) { token = createToken(createStringFromChar(current), OPERATOR_MORE); current = nextCharacter(document); }
		else if (isLessThan(current)) { token = createToken(createStringFromChar(current), OPERATOR_LESS); current = nextCharacter(document); }
		else if (isPlus(current)) { token = createToken(createStringFromChar(current), OPERATOR_ADD); current = nextCharacter(document); }
		else if (isMinus(current)) { token = createToken(createStringFromChar(current), OPERATOR_SUB); current = nextCharacter(document); }
		else if (isDevision(current)) { token = createToken(createStringFromChar(current), OPERATOR_DIV); current = nextCharacter(document); }
		else if (isMultiplication(current)) { token = createToken(createStringFromChar(current), OPERATOR_MUL); current = nextCharacter(document); }
		else if (isTerminator(current)) { tokenOccured = false; current = nextCharacter(document); }
		else {
			printf("%c is value %d\n", current, current);
			handleError(SyntaxError, "Invalid number syntax on line %d, column %d", document->line, document->column);
		}
		
		if (tokenOccured && token == NULL) {
			destroyList(list);
			printf("DEBUG: Last char is %c\n", current);
			handleError(11, "Scanner: Input file could not be loaded.");
		} else if (tokenOccured) {
			printf("new token: %s\n", token->value->value);
			addTokenToList(token, list);
		}
	}
}
