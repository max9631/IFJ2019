#include "main.h"

int main(int argc, char *argv[]) {
    inDebugMode = true;
	if(argc != 2)
		handleError(1, "Invalid argument");

	FILE *file = fopen(argv[1], "r");
	if (file == NULL) 
		handleError(2, "Invalid file name");

	document = createDocument(file);
	tokenList = createList();
	scan(tokenList, document);
    
    printTokenList(tokenList);
	parseTokens(tokenList);
}

