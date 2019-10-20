#ifndef TOKEN_H
#define TOKEN_H
#include "String.h"
#include "TokenType.h"

typedef struct Token {
    String *value;
    TokenType type;
} Token;

Token *createToken(String *string, TokenType type);

#endif
