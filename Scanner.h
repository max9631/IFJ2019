#ifndef SCANNER_H
#define SCANNER_H
#include <stdio.h>
#include "TokenList.h"
#include "String.h"

typedef struct Document {
	FILE *file;
	int currentChar;
	int currentIndent;
} Document;

Document *createDocument(FILE *file);
void destroyDocument(Document *document);

void scan(TokenList *list, Document *document);

#endif
