#include "String.h"
#include "TokenType.h"

#ifndef TOKEN_H
#define TOKEN_H

typedef struct Token {
    String *value;
    TokenType type;
} Token;

#endif