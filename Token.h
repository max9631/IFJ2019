#ifndef TOKEN_H
#define TOKEN_H
#include "String.h"

typedef enum {
    TOKEN_IDENTIFIER = 1, //Identifier

    /* Data types */
    DATA_TOKEN_INT, //Integer
    DATA_TOKEN_FLOAT, //Float
    DATA_TOKEN_STRING, //String
    DATA_TOKEN_NONE, //NULL

    /* Operators */
    OPERATOR_NOT, //!
    OPERATOR_NEQL,//!=
    OPERATOR_MORE, //>
    OPERATOR_MOREEQL, //>=
    OPERATOR_LESS, //<
    OPERATOR_LESSEQL, //<=
    OPERATOR_ADD, //+
    OPERATOR_ADD_ASSIGN, //+=
    OPERATOR_SUB, //-
    OPERATOR_SUB_ASSIGN, //-=
    OPERATOR_ASSIGN, //=
    OPERATOR_EQL, //==
    OPERATOR_DIV, // /
    OPERATOR_DIV_ASSIGN, // /=
    OPERATOR_MUL, //*
    OPERATOR_MUL_ASSIGN, //*=

    /* Misc */
    TOKEN_OPAREN, //(
    TOKEN_CPAREN, //)
    TOKEN_COMMA, //Comma (,)
    TOKEN_COLON, //:

    TOKEN_INDENT,
    TOKEN_DEINDENT,

    TOKEN_EMPTY, //Token is empty (uninitaliued)
    TOKEN_EOL, //EOL
    TOKEN_EOF, //EOF

    /* Keywords */
    KEYWORD_DEF, //def
    KEYWORD_ELSE, //else
    KEYWORD_END, //end
    KEYWORD_IF, //if
    KEYWORD_NONE, //none
    KEYWORD_WHILE, //while
    KEYWORD_PASS //pass
 } TokenType;

typedef struct Token {
    String *value;
    TokenType type;
} Token;

Token *createToken(String *string, TokenType type);
char* convertTokenTypeToString(TokenType type);

#endif
