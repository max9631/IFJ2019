#include "main.h"

TokenList *tokenList = NULL;

int main(int argc, char *argv[]) {
	if(argc != 2)
		handleError(1, "Invalid argument %s", "test");

	FILE *file = fopen(argv[1], "r");
	if (file == NULL) 
		handleError(2, "Invalid file name");
	tokenList = createList();
	scan(tokenList, file);
}

void cleanResources() {
	if(tokenList != NULL)
		destroyList(tokenList);
}