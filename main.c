#include "main.h"

int main(int argc, char *argv[]) {
	UNUSED(argc);
	UNUSED(argv);

    inDebugMode = false;
    FILE *file;
    if (inDebugMode) {
        file = fopen(argv[1], "r");
        if (file == NULL)
            handleError(2, "Invalid file name");
    } else {
        file = stdin;
    }
	document = createDocument(file);
	tokenList = createList();
	scan(tokenList, document);
    printList(tokenList);

	ParserState *state = createParserState(tokenList);
	MainNode *tree = parseTokens(state);
    generateMain(createGenerator(), tree);

	//DestroyParserState(state); // TODO: Fix memory management.
}
