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


String *convertTokenTypeToString(TokenType type) {
    switch (type){
    case TOKEN_IDENTIFIER: return createString("TOKEN_IDENTIFIER");
    case DATA_TOKEN_INT: return createString("DATA_TOKEN_INT");
    case DATA_TOKEN_FLOAT: return createString("DATA_TOKEN_FLOAT");
    case DATA_TOKEN_STRING: return createString("DATA_TOKEN_STRING");
    case DATA_TOKEN_NONE: return createString("DATA_TOKEN_NONE");
    case OPERATOR_NOT: return createString("OPERATOR_NOT");
    case OPERATOR_NEQL: return createString("OPERATOR_NEQL");
    case OPERATOR_MORE: return createString("OPERATOR_MORE");
    case OPERATOR_MOREEQL: return createString("OPERATOR_MOREEQL");
    case OPERATOR_LESS: return createString("OPERATOR_LESS");
    case OPERATOR_LESSEQL: return createString("OPERATOR_LESSEQL");
    case OPERATOR_ADD: return createString("OPERATOR_ADD");
    case OPERATOR_ADD_ASSIGN: return createString("OPERATOR_ADD_ASSIGN");
    case OPERATOR_SUB: return createString("OPERATOR_SUB");
    case OPERATOR_SUB_ASSIGN: return createString("OPERATOR_SUB_ASSIGN");
    case OPERATOR_ASSIGN: return createString("OPERATOR_ASSIGN");
    case OPERATOR_EQL: return createString("OPERATOR_EQL");
    case OPERATOR_DIV: return createString("OPERATOR_DIV");
    case OPERATOR_DIV_ASSIGN: return createString("OPERATOR_DIV_ASSIGN");
    case OPERATOR_MUL: return createString("OPERATOR_MUL");
    case OPERATOR_MUL_ASSIGN: return createString("OPERATOR_MUL_ASSIGN");
    case TOKEN_OPAREN: return createString("TOKEN_OPAREN");
    case TOKEN_CPAREN: return createString("TOKEN_CPAREN");
    case TOKEN_COMMA: return createString("TOKEN_COMMA");
    case TOKEN_COLON: return createString("TOKEN_COLON");
    case TOKEN_INDENT: return createString("TOKEN_INDENT");
    case TOKEN_DEINDENT: return createString("TOKEN_DEINDENT");
    case TOKEN_EMPTY: return createString("TOKEN_EMPTY");
    case TOKEN_EOL: return createString("TOKEN_EOL");
    case TOKEN_EOF: return createString("TOKEN_EOF");
    case KEYWORD_DEF: return createString("KEYWORD_DEF");
    case KEYWORD_ELSE: return createString("KEYWORD_ELSE");
    case KEYWORD_RETURN: return createString("KEYWORD_RETURN");
    case KEYWORD_IF: return createString("KEYWORD_IF");
    case KEYWORD_WHILE: return createString("KEYWORD_WHILE");
    case KEYWORD_PASS: return createString("KEYWORD_PASS");
    default: handleError(InternalError, "Unkown token type");
    }
    return NULL;
}

void destroyToken(Token *token) {
    destroyString(token->value);
    free(token);
}
