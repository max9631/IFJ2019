/*
 * Author(s): Adam Salih (xsalih01), Michal Halabica (xhalab00)
 * Project: Implementace prekladace imperativniho jazyka jazyka IFJ19
 * File: Token.h, token implementation and declaration of token types
 */
 
#ifndef TOKEN_H
#define TOKEN_H
#include <stdbool.h>
#include "String.h"

typedef enum {
    TOKEN_IDENTIFIER = 1, //Identifier

    /* Data types */
    DATA_TOKEN_INT, //Integer
    DATA_TOKEN_FLOAT, //Float
    DATA_TOKEN_STRING, //String
    DATA_TOKEN_NONE, //NULL
    DATA_TOKEN_BOOL, //BOOL

    /* Operators */
    OPERATOR_NOT, //!
    OPERATOR_NEQL,//!=
    OPERATOR_MORE, //>
    OPERATOR_MOREEQL, //>=
    OPERATOR_LESS, // <
    OPERATOR_LESSEQL, // <=
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
    OPERATOR_AND, // TODO and
    OPERATOR_OR, // TODO or
    OPERATOR_IDIV,

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
    KEYWORD_RETURN, //return
    KEYWORD_IF, //if
    KEYWORD_WHILE, //while
    KEYWORD_PASS //pass
 } TokenType;

//Struct defining token and its info
typedef struct Token {
    String *value;
    TokenType type;
    int line;
} Token;

//Creates new token
Token *createToken(String *string, TokenType type);

//Creates new token with a given value
Token *createTokenWithLine(String *string, TokenType type, int line);

//Converts token type to a string
String *convertTokenTypeToString(TokenType type);

//Destroys token
void destroyToken(Token *token);

//Checks if given token is an operator
bool isTokenAsignOperator(Token *token);

#endif //TOKEN_H
