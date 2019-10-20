#include "main.h"

TokenList *tokenList = NULL;

int main(int argc, char *argv[]) {
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

    if(isDebug(argc, argv)) {
        debugPrintTokenList(tokenList);
    }
}

bool isDebug(int argc, char **argv) {
    if(argc == 1)
        return false;

    for(int i = 0; i < argc; i++) {
        if(strcmp(argv[i], "--debug") == 0)
            return true;
    }

    return false;
}

void cleanResources() {
    if(tokenList != NULL)
        destroyList(tokenList);
}
