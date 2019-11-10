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
bool isComma(int c) { return c == (int) ','; }
bool isColon(int c) { return c == (int) ':'; }
bool isEqual(int c) { return c == (int) '='; }
bool isDoubleQuote(int c) { return c == (int) '"'; }
bool isApostroph(int c) { return c == (int) '\''; }
bool isNot(int c) { return c == (int) '!'; }
bool isGreater(int c) { return c == (int) '>'; }
bool isLessThan(int c) { return c == (int) '<'; }
bool isPlus(int c) { return c == (int) '+'; }
bool isMinus(int c) { return c == (int) '-'; }
bool isDevision(int c) { return c == (int) '/'; }
bool isMultiplication(int c) { return c == (int) '*'; }
bool isSpace(int c) { return c == (int) ' '; }
bool isComment(int c) { return c == (int) '#'; }
bool isUnderscore(int c) { return c == (int) '_'; }
bool isExp(int c){ return (c == (int) 'E' || c == (int) 'e'); }

bool isTerminator(int c) { return c == EOF || isSpace(c) || isEndOfLine(c); }
bool isValidIdentifierCharacter(int c) { return isCharacter(c) || isNumber(c) || isUnderscore(c); }
bool isString(int c) { return isDoubleQuote(c) || isApostroph(c); }
bool isOperator(int c) {
	return isNot(c) || isGreater(c) || isLessThan(c) || isPlus(c) || isMinus(c) || isDevision(c) || isMultiplication(c) || isEqual(c);
}


int skipUntilNewLine(Document *document) {
	int ch = document->currentChar;
	while (ch != (int) '\n')
		ch = nextCharacter(document);
	return nextCharacter(document);
}

Token *defineValue(Document *document) {
	int c = document->currentChar;
	struct String *string = createStringFromChar(c);
	bool dotOccured = false, expOccured = false, dotOccuredLast = false;
	int i = 0;
	c = nextCharacter(document);

	while (isNumber(c) || isDot(c) || isExp(c)) {
		if(isNumber(c)){}
		else if(isDot(c) && !dotOccured && !expOccured){
			dotOccured = dotOccured || isDot(c);
			dotOccuredLast = dotOccured;
		}
		else if(isExp(c) && !expOccured && !dotOccuredLast){
			expOccured = expOccured || isExp(c);
		}
		else{
			handleError(LexError, "Invalid number syntax");
		}
		if(dotOccuredLast){
			i++;
			if(i > 1){
				dotOccuredLast = false, i = 0;
			}
		}
		appendCharacter(string, c);
		c = nextCharacter(document);
	}
	TokenType type = DATA_TOKEN_INT;
	if (dotOccured) 
		type = DATA_TOKEN_FLOAT; 
	return createToken(string, type);
}

Token *defineIdentifier(Document *document) {
	int ch = document->currentChar;
	struct String *string = createStringFromChar(ch);
	ch = nextCharacter(document);
	while (isValidIdentifierCharacter(ch)) {
		appendCharacter(string, ch);
		ch = nextCharacter(document);
	}
	TokenType type;  
	if(strcmp("def",string->value) == 0) type = KEYWORD_DEF;
	else if(strcmp("else",string->value) == 0) type = KEYWORD_ELSE;
	else if(strcmp("return",string->value) == 0) type = KEYWORD_RETURN;
	else if(strcmp("if",string->value) == 0) type = KEYWORD_IF;
	else if(strcmp("none",string->value) == 0) type = KEYWORD_NONE;
	else if(strcmp("while",string->value) == 0) type = KEYWORD_WHILE;
	else if(strcmp("pass",string->value) == 0) type = KEYWORD_PASS;
	else return createToken(string, TOKEN_IDENTIFIER);
	return createToken(string, type);
	// TODO: check if identifier is not a keyword
	// return createToken(string, TOKEN_IDENTIFIER);
}

Token *defineString(Document *document) {
	if (isDoubleQuote((document->currentChar)))
		return defineDoubleQuoteString(document);
	else if (isApostroph((document->currentChar)))
		return defineApostrophString(document);
	return NULL;
}

Token *defineDoubleQuoteString(Document *document) {
	int ch = nextCharacter(document);
	bool isMultilineString = false;
	if (isDoubleQuote(ch)) {
		ch = nextCharacter(document);
		if (isDoubleQuote(ch)) {
			isMultilineString = true;
			ch = nextCharacter(document);
		} else {
			return createToken(NULL, DATA_TOKEN_STRING);
		}
	}
	String *string = recordStringUntilChar(document, (int) '"');
	if (isMultilineString) {
		for (int i = 0; i < 2; i++) {
			ch = nextCharacter(document);
			if (!isDoubleQuote(ch)) {
				handleError(LexError, "Incorrect string end");
			}
		}
	}
	nextCharacter(document);
	return createToken(string, DATA_TOKEN_STRING);
}

Token *defineApostrophString(Document *document) {
	nextCharacter(document);
	String *string = recordStringUntilChar(document, (int) '\'');
	nextCharacter(document);
	return createToken(string, DATA_TOKEN_STRING);
}

String *recordStringUntilChar(Document *document, int endChar) {
	int ch = document->currentChar;
	String *string = createStringFromChar(ch);
	bool isEscaping = false;
	ch = nextCharacter(document);
	while (ch != endChar || isEscaping) {
		isEscaping = (isEscaping) ? false : ch == (int) '\\';
		if (!isEscaping) appendCharacter(string, ch);
		ch = nextCharacter(document);
	}
	return string;
}

Token *defineOperator(Document *document, int c) {
	String *string = createStringFromChar(c);
	TokenType type;

	if (isNot(c)) type = OPERATOR_NOT;
	else if (isGreater(c)) type = OPERATOR_MORE;
	else if (isLessThan(c)) type = OPERATOR_LESS;
	else if (isPlus(c)) type = OPERATOR_ADD;
	else if (isMinus(c)) type = OPERATOR_SUB;
	else if (isEqual(c)) type = OPERATOR_ASSIGN;
	else if (isDevision(c)) type = OPERATOR_DIV;
	else if (isMultiplication(c)) type = OPERATOR_MUL;
	else return NULL;

	int nextCH = nextCharacter(document);
	if (isEqual(nextCH)) {
		appendCharacter(string, nextCH);
		type += 1;
	}
	
	return createToken(string, type); 
}

void generateIndent(TokenList *list, Document *document) {
	int sum = 0;
	int ch = document->currentChar;
	while (isSpace(ch)) {
		sum++;
		ch = nextCharacter(document);
	}
	if(isComment(ch)){
		skipUntilNewLine(document);
		return;
	}
	if (isEndOfLine(ch))
		return;
	if (sum == document->lastIndent) 
		return;
	if (sum > document->lastIndent + 1) 
		handleError(SyntaxError, "Wrong number of indents at line %d column %d", document->line, document->column);
	else if (sum == document->lastIndent + 1) {
		addTokenToList(createToken(NULL, TOKEN_INDENT), list);
	} else if (sum < document->lastIndent) {
		int d = document->lastIndent - sum;
		for (int i = 0; i < d; i++)
			addTokenToList(createToken(NULL, TOKEN_DEINDENT), list);
	}
	document->lastIndent = sum;
}

Token * defineOneCharToken(Document *document, int ch, TokenType type) {
	String *string = createStringFromChar((char) ch);
	nextCharacter(document);
	return createToken(string, type);
}

void scan(TokenList *list, Document *document) {
	while (document->currentChar != EOF) {
		int current = document->currentChar;
		Token *token = NULL;
		if (isNewLine(document)) {
			generateIndent(list, document);
			current = document->currentChar;
		}
		if (isComment(current)) skipUntilNewLine(document);
		else if (isNumber(current)) token = defineValue(document);
		else if (isCharacter(current) || isUnderscore(current)) token = defineIdentifier(document);
		else if (isString(current)) token = defineString(document);
		else if (isOperator(current)) token = defineOperator(document, current);
		else if (isOpeningParen(current)) token = defineOneCharToken(document, current, TOKEN_OPAREN);
		else if (isClosingParen(current)) token = defineOneCharToken(document, current, TOKEN_CPAREN);
		else if (isColon(current)) token = defineOneCharToken(document, current, TOKEN_COLON);
		else if (isComma(current)) token = defineOneCharToken(document, current, TOKEN_COMMA);
		else if (isTerminator(current)) nextCharacter(document);
		else if (isEndOfLine(current)) token = createToken(NULL, TOKEN_EOL);
		else {
			msg("%c is value of %d\n", current, current);
			handleError(SyntaxError, "Invalid number syntax on line %d, column %d", document->line, document->column);
		}
		if (token != NULL) {
			msg("new token: %s\n", token->value->value);
			addTokenToList(token, list);
		}
	}
}
