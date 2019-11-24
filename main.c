#include "main.h"

int main(int argc, char *argv[]) {
	UNUSED(argc);
	UNUSED(argv);

    inDebugMode = true;

	FILE *file = stdin;
	document = createDocument(file);
	tokenList = createList();
	scan(tokenList, document);
    printList(tokenList);
	
	ParserState *state = createParserState(tokenList);
	MainNode *tree = parseTokens(state);
    generateMain(createGenerator(), tree);

	//DestroyParserState(state); // TODO: Fix memory management.
}

