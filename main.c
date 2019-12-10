#include "main.h"

int main(int argc, char *argv[]) {
    inDebugMode = false;
    FILE *file;
    #ifdef IS_XCODE
        if (argc == 0)
            handleError(InternalError, "Unspecified file name");
        file = fopen(argv[1], "r");
        if (file == NULL)
            handleError(InternalError, "Invalid file name");
    #else
        file = stdin;
    #endif
	document = createDocument(file);
	tokenList = createList();
	scan(tokenList, document);
    printList(tokenList);

	ParserState *state = createParserState(tokenList);
	MainNode *tree = parseTokens(state);
    generateMain(createGenerator(), tree);
}
