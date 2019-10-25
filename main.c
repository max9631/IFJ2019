#include "main.h"

int main(int argc, char *argv[]) {
    inDebugMode = true;

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
        handleError(2, "Invalid file name");

    tokenList = createList();
    
    Token *token = malloc(sizeof(Token));
    token->type = InvalidToken;

    char *exStr = "ABCD";
    token->value = createString(&exStr);

    addTokenToList(token, tokenList);

    //scan(tokenList, file);
    printTokenList(tokenList);
}

