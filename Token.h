#ifndef TOKEN_H
#define TOKEN_H
#include "String.h"
#include "TokenType.h"

typedef struct Token {
    String *value;
    TokenType type;
} Token;

#endif