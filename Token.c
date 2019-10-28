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
        sprintf(tokenTypeAsString, "TOKEN_IDENTIFIER");
        break;
    case DATA_TOKEN_INT:
        sprintf(tokenTypeAsString, "DATA_TOKEN_INT");
        break;
    case DATA_TOKEN_FLOAT:
        sprintf(tokenTypeAsString, "DATA_TOKEN_FLOAT");
        break;
    case DATA_TOKEN_STRING:
        sprintf(tokenTypeAsString, "DATA_TOKEN_STRING");
        break;
    case DATA_TOKEN_NONE:
        sprintf(tokenTypeAsString, "DATA_TOKEN_NONE");
        break;
    case OPERATOR_NOT:
        sprintf(tokenTypeAsString, "OPERATOR_NOT");
        break;
    case OPERATOR_NEQL:
        sprintf(tokenTypeAsString, "OPERATOR_NEQL");
        break;
    case OPERATOR_MORE:
        sprintf(tokenTypeAsString, "OPERATOR_MORE");
        break;
    case OPERATOR_MOREEQL:
        sprintf(tokenTypeAsString, "OPERATOR_MOREEQL");
        break;
    case OPERATOR_LESS:
        sprintf(tokenTypeAsString, "OPERATOR_LESS");
        break;
    case OPERATOR_LESSEQL:
        sprintf(tokenTypeAsString, "OPERATOR_LESSEQL");
        break;
    case OPERATOR_ADD:
        sprintf(tokenTypeAsString, "OPERATOR_ADD");
        break;
    case OPERATOR_ADD_ASSIGN:
        sprintf(tokenTypeAsString, "OPERATOR_ADD_ASSIGN");
        break;
    case OPERATOR_SUB:
        sprintf(tokenTypeAsString, "OPERATOR_SUB");
        break;
    case OPERATOR_SUB_ASSIGN:
        sprintf(tokenTypeAsString, "OPERATOR_SUB_ASSIGN");
        break;
    case OPERATOR_ASSIGN:
        sprintf(tokenTypeAsString, "OPERATOR_ASSIGN");
        break;
    case OPERATOR_EQL:
        sprintf(tokenTypeAsString, "OPERATOR_EQL");
        break;
    case OPERATOR_DIV:
        sprintf(tokenTypeAsString, "OPERATOR_DIV");
        break;
    case OPERATOR_DIV_ASSIGN:
        sprintf(tokenTypeAsString, "OPERATOR_DIV_ASSIGN");
        break;
    case OPERATOR_MUL:
        sprintf(tokenTypeAsString, "OPERATOR_MUL");
        break;
    case OPERATOR_MUL_ASSIGN:
        sprintf(tokenTypeAsString, "OPERATOR_MUL_ASSIGN");
        break;
    case TOKEN_OPAREN:
        sprintf(tokenTypeAsString, "TOKEN_OPAREN");
        break;
    case TOKEN_CPAREN:
        sprintf(tokenTypeAsString, "TOKEN_CPAREN");
        break;
    case TOKEN_COMMA:
        sprintf(tokenTypeAsString, "TOKEN_COMMA");
        break;
    case TOKEN_COLON:
        sprintf(tokenTypeAsString, "TOKEN_COLON");
        break;
    case TOKEN_INDENT:
        sprintf(tokenTypeAsString, "TOKEN_INDENT");
        break;
    case TOKEN_DEINDENT:
        sprintf(tokenTypeAsString, "TOKEN_DEINDENT");
        break;
    case TOKEN_EMPTY:
        sprintf(tokenTypeAsString, "TOKEN_EMPTY");
        break;
    case TOKEN_EOL:
        sprintf(tokenTypeAsString, "TOKEN_EOL");
        break;
    case TOKEN_EOF:
        sprintf(tokenTypeAsString, "TOKEN_EOF");
        break;
    case KEYWORD_DEF:
        sprintf(tokenTypeAsString, "KEYWORD_DEF");
        break;
    case KEYWORD_ELSE:
        sprintf(tokenTypeAsString, "KEYWORD_ELSE");
        break;
    case KEYWORD_END:
        sprintf(tokenTypeAsString, "KEYWORD_END");
        break;
    case KEYWORD_IF:
        sprintf(tokenTypeAsString, "KEYWORD_IF");
        break;
    case KEYWORD_NONE:
        sprintf(tokenTypeAsString, "KEYWORD_NONE");
        break;
    case KEYWORD_WHILE:
        sprintf(tokenTypeAsString, "KEYWORD_WHILE");
        break;
    case KEYWORD_PASS:
        sprintf(tokenTypeAsString, "KEYWORD_PASS");
        break;
    default: 
        sprintf(tokenTypeAsString, "InvalidToken");
        break;
    }
    return tokenTypeAsString;
}
