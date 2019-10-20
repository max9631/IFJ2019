#include "main.h"

TokenList *tokenList;


int error(int number, char *message, ...) {
	// prints message to stderr, clears memory and exits with specified error number.
	destroyList(tokenList);
	exit(number);
}

int main(int argc, char *argv[]) {
	if (argc != 2) error(1, "Invalid argument");
	FILE *file = fopen(argv[1], "r");
	if (file == NULL) error(2, "Invalid file name");
	tokenList = createList();
	scan(tokenList, file);
}
