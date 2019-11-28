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
	if (document != NULL) free(document);
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
bool isHexadecimal(int c) { return ((c >= (int) '0') && (c <= (int) '9')) || ((c >= (int) 'A') && c <= (int) 'F') || ((c >= (int) 'a') && c <= (int) 'f'); }

bool isTerminator(int c) { return c == EOF || isSpace(c) || isEndOfLine(c); }
bool isValidIdentifierCharacter(int c) { return isCharacter(c) || isNumber(c) || isUnderscore(c); }
bool isString(int c) { return isDoubleQuote(c) || isApostroph(c); }
bool isOperator(int c) {
	return isNot(c) || isGreater(c) || isLessThan(c) || isPlus(c) || isMinus(c) || isDevision(c) || isMultiplication(c) || isEqual(c);
}


Token *skipUntilNewLine(Document *document) {
	int ch = document->currentChar;
	while (ch != (int) '\n')
		ch = nextCharacter(document);
    nextCharacter(document);
	return createToken(createStringFromChar(ch), TOKEN_EOL);
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
                dotOccuredLast = false;
                i = 0;
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
	else if(strcmp("None",string->value) == 0) type = DATA_TOKEN_NONE;
	else if(strcmp("while",string->value) == 0) type = KEYWORD_WHILE;
	else if(strcmp("pass",string->value) == 0) type = KEYWORD_PASS;
	else if(strcmp("True",string->value) == 0) type = DATA_TOKEN_BOOL;
	else if(strcmp("False",string->value) == 0) type = DATA_TOKEN_BOOL;
	else return createToken(string, TOKEN_IDENTIFIER);
	return createToken(string, type);
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
			return createToken(createString(""), DATA_TOKEN_STRING);
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
	int ch = document->currentChar;
	String *string;
	if(isApostroph(ch)){
		string = createString("");
	}
	else{
		string = recordStringUntilChar(document, (int) '\'');
	}
	nextCharacter(document);
	return createToken(string, DATA_TOKEN_STRING);
}

int getDecimalValueFromHexaChar(int hex) {
    if (isNumber(hex)) return hex - 48;
    switch (tolower(hex)) {
        case (int)'a': return 10;
        case (int)'b': return 11;
        case (int)'c': return 12;
        case (int)'d': return 13;
        case (int)'e': return 14;
        case (int)'f': return 15;
    }
    return 0;
}

int getDecimalChFromHexaCharsOnLine(int hex1, int hex2, int line) {
    if (!isHexadecimal(hex1) || !isHexadecimal(hex2)) {
        handleError(SyntaxError, "Expected hexadecimal notation after \\x in string on line %d", line);
    }
    int dec1 = getDecimalValueFromHexaChar(hex1);
    int dec2 = getDecimalValueFromHexaChar(hex2);
    return (16 * dec1) + dec2;
}

String *recordStringUntilChar(Document *document, int endChar) {
	int ch = document->currentChar;
	String *string = createString("");
	bool isEscaping = false;
	while (ch != endChar || isEscaping) {
        if (ch == (int) '\\') {
            isEscaping = true;
            ch = nextCharacter(document);
            continue;
        }
		if (!isEscaping) appendCharacter(string, ch);
        else if (ch == (int) 'n') appendCharacter(string, (int) '\n');
        else if (ch == (int) 't') appendCharacter(string, (int) '\t');
        else if (ch == (int) '\'' || ch == (int) '"') appendCharacter(string, ch);
        else if (ch == (int) 'x') {
            int line = document->line;
            int hex1 = nextCharacter(document);
            int hex2 = nextCharacter(document);
            int dec = getDecimalChFromHexaCharsOnLine(hex1, hex2, line);
            appendCharacter(string, dec);
        } else {
            appendCharacter(string, (int) '\\');
            appendCharacter(string, (int) ch);
        }
        isEscaping = (isEscaping) ? false : ch == (int) '\\';
    
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
        nextCharacter(document);
    } else if (type == OPERATOR_DIV && isDevision(nextCH)) {
        appendCharacter(string, nextCH);
        type = OPERATOR_IDIV;
    }
	return createToken(string, type); 
}

void generateIndent(List *list, Document *document) {
	int sum = 0;
	int ch = document->currentChar;
	while (isSpace(ch)) {
		sum++;
		ch = nextCharacter(document);
	}
	if(isComment(ch))
		return;
	if (isEndOfLine(ch))
		return;
	if (sum == document->lastIndent)
		return;
	if (sum > document->lastIndent + 1)
		handleError(SyntaxError, "Wrong number of indents at line %d column %d", document->line, document->column);
	else if (sum == document->lastIndent + 1) {
		addTokenToList(createTokenWithLine(NULL, TOKEN_INDENT, document->line), list);
	} else if (sum < document->lastIndent) {
		int d = document->lastIndent - sum;
        for (int i = 0; i < d; i++) {
			addTokenToList(createTokenWithLine(NULL, TOKEN_DEINDENT, document->line), list);
            addTokenToList(createTokenWithLine(NULL, TOKEN_EOL, document->line), list);
        }
	}
	document->lastIndent = sum;
}

Token * defineOneCharToken(Document *document, int ch, TokenType type) {
	String *string = createStringFromChar((char) ch);
	nextCharacter(document);
	return createToken(string, type);
}

void removeDuplicitEOLsFromList(List *list) {
    ListItem *lastItem = NULL;
    ListItem *item = list->first;
    bool lastWasEOL = false;
    while (item != NULL) {
        Token *token = (Token *) item->value;
        if (token->type == TOKEN_EOL) {
            if (lastWasEOL) {
                lastItem->nextItem = item->nextItem;
                Token *lastManStanding = (Token *)item->value;
                destroyToken(lastManStanding);
                destroyListItem(item);
                item = lastItem;
            }
            lastWasEOL = true;
        } else {
            lastWasEOL = false;
        }
        lastItem = item;
        item = item->nextItem;
    }
}

void scan(List *list, Document *document) {
	while (document->currentChar != EOF) {
		int current = document->currentChar;
		int line = document->line;
		Token *token = NULL;
		if (isNewLine(document)) {
			generateIndent(list, document);
			current = document->currentChar;
		}
		if (isComment(current))
            token = skipUntilNewLine(document);
		else if (isNumber(current)) token = defineValue(document);
		else if (isCharacter(current) || isUnderscore(current)) token = defineIdentifier(document);
		else if (isString(current)) token = defineString(document);
		else if (isOperator(current)) token = defineOperator(document, current);
		else if (isOpeningParen(current)) token = defineOneCharToken(document, current, TOKEN_OPAREN);
		else if (isClosingParen(current)) token = defineOneCharToken(document, current, TOKEN_CPAREN);
		else if (isColon(current)) token = defineOneCharToken(document, current, TOKEN_COLON);
		else if (isComma(current)) token = defineOneCharToken(document, current, TOKEN_COMMA);
		else if (isEndOfLine(current)) {
			token = createToken(createStringFromChar('\n'), TOKEN_EOL);
			nextCharacter(document);
		}
		else if (isTerminator(current)) nextCharacter(document);
		else {
			msg("%c is value of %d\n", current, current);
			handleError(SyntaxError, "Invalid number syntax on line %d, column %d", document->line, document->column);
		}
		if (token != NULL) {
			msg("new token: %s\n", token->value->value);
			token->line = line;
			addTokenToList(token, list);
		}
	}
    for (int i = 0; i < document->lastIndent; i++) {
        addTokenToList(createTokenWithLine(NULL, TOKEN_DEINDENT, document->line), list);
        addTokenToList(createTokenWithLine(NULL, TOKEN_EOL, document->line), list);
    }
    addTokenToList(createTokenWithLine(NULL, TOKEN_EOL, document->line), list);
	addTokenToList(createTokenWithLine(NULL, TOKEN_EOF, document->line), list);
    removeDuplicitEOLsFromList(list);
}
