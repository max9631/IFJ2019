#include "Token.h"

Token *createToken(String *string, TokenType type) {
    Token *token = (Token *) malloc(sizeof(Token));
    if (token == NULL)
        handleError(InternalError, "Could not initialize Token");
    token->value = NULL;
    token->value = string;
    token->type = type;
    return token;
}

char* convertTokenTypeToString(TokenType type) {
    char *tokenTypeAsString = malloc(sizeof(char) * 500);
    switch (type){
    case TOKEN_IDENTIFIER:
        sprintf(tokenTypeAsString, "TOKEN_IDENTIFIER", type);
        break;
    case DATA_TOKEN_INT:
        sprintf(tokenTypeAsString, "DATA_TOKEN_INT", type);
        break;
    case DATA_TOKEN_FLOAT:
        sprintf(tokenTypeAsString, "DATA_TOKEN_FLOAT", type);
        break;
    case DATA_TOKEN_STRING:
        sprintf(tokenTypeAsString, "DATA_TOKEN_STRING", type);
        break;
    case DATA_TOKEN_NONE:
        sprintf(tokenTypeAsString, "DATA_TOKEN_NONE", type);
        break;
    case OPERATOR_NOT:
        sprintf(tokenTypeAsString, "OPERATOR_NOT", type);
        break;
    case OPERATOR_NEQL:
        sprintf(tokenTypeAsString, "OPERATOR_NEQL", type);
        break;
    case OPERATOR_MORE:
        sprintf(tokenTypeAsString, "OPERATOR_MORE", type);
        break;
    case OPERATOR_MOREEQL:
        sprintf(tokenTypeAsString, "OPERATOR_MOREEQL", type);
        break;
    case OPERATOR_LESS:
        sprintf(tokenTypeAsString, "OPERATOR_LESS", type);
        break;
    case OPERATOR_LESSEQL:
        sprintf(tokenTypeAsString, "OPERATOR_LESSEQL", type);
        break;
    case OPERATOR_ADD:
        sprintf(tokenTypeAsString, "OPERATOR_ADD", type);
        break;
    case OPERATOR_ADD_ASSIGN:
        sprintf(tokenTypeAsString, "OPERATOR_ADD_ASSIGN", type);
        break;
    case OPERATOR_SUB:
        sprintf(tokenTypeAsString, "OPERATOR_SUB", type);
        break;
    case OPERATOR_SUB_ASSIGN:
        sprintf(tokenTypeAsString, "OPERATOR_SUB_ASSIGN", type);
        break;
    case OPERATOR_ASSIGN:
        sprintf(tokenTypeAsString, "OPERATOR_ASSIGN", type);
        break;
    case OPERATOR_EQL:
        sprintf(tokenTypeAsString, "OPERATOR_EQL", type);
        break;
    case OPERATOR_DIV:
        sprintf(tokenTypeAsString, "OPERATOR_DIV", type);
        break;
    case OPERATOR_DIV_ASSIGN:
        sprintf(tokenTypeAsString, "OPERATOR_DIV_ASSIGN", type);
        break;
    case OPERATOR_MUL:
        sprintf(tokenTypeAsString, "OPERATOR_MUL", type);
        break;
    case OPERATOR_MUL_ASSIGN:
        sprintf(tokenTypeAsString, "OPERATOR_MUL_ASSIGN", type);
        break;
    case TOKEN_OPAREN:
        sprintf(tokenTypeAsString, "TOKEN_OPAREN", type);
        break;
    case TOKEN_CPAREN:
        sprintf(tokenTypeAsString, "TOKEN_CPAREN", type);
        break;
    case TOKEN_COMMA:
        sprintf(tokenTypeAsString, "TOKEN_COMMA", type);
        break;
    case TOKEN_COLON:
        sprintf(tokenTypeAsString, "TOKEN_COLON", type);
        break;
    case TOKEN_INDENT:
        sprintf(tokenTypeAsString, "TOKEN_INDENT", type);
        break;
    case TOKEN_DEINDENT:
        sprintf(tokenTypeAsString, "TOKEN_DEINDENT", type);
        break;
    case TOKEN_EMPTY:
        sprintf(tokenTypeAsString, "TOKEN_EMPTY", type);
        break;
    case TOKEN_EOL:
        sprintf(tokenTypeAsString, "TOKEN_EOL", type);
        break;
    case TOKEN_EOF:
        sprintf(tokenTypeAsString, "TOKEN_EOF", type);
        break;
    case KEYWORD_DEF:
        sprintf(tokenTypeAsString, "KEYWORD_DEF", type);
        break;
    case KEYWORD_ELSE:
        sprintf(tokenTypeAsString, "KEYWORD_ELSE", type);
        break;
    case KEYWORD_END:
        sprintf(tokenTypeAsString, "KEYWORD_END", type);
        break;
    case KEYWORD_IF:
        sprintf(tokenTypeAsString, "KEYWORD_IF", type);
        break;
    case KEYWORD_NONE:
        sprintf(tokenTypeAsString, "KEYWORD_NONE", type);
        break;
    case KEYWORD_WHILE:
        sprintf(tokenTypeAsString, "KEYWORD_WHILE", type);
        break;
    case KEYWORD_PASS:
        sprintf(tokenTypeAsString, "KEYWORD_PASS", type);
        break;
    default: 
        sprintf(tokenTypeAsString, "InvalidToken (%d)", type);
        break;
    }
    return tokenTypeAsString;
}