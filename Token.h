#ifndef TOKEN_H
#define TOKEN_H
#include "String.h"
#include "TokenType.h"

typedef struct Token {
    String *value;
    TokenType type;
} Token;


typedef enum {
  TOKEN_IDENTIFIER, //Identifier  0
  TOKEN_VAR_IDENTIFIER, //Variable identifier  1
  TOKEN_FCE_IDENTIFIER, //Function identifier (can end with ? or !)  2
  //TOKEN_KEYWORD, //Keyword  3

  /* Data types */
  TOKEN_INT, //Integer  4
  TOKEN_FLOAT, //Float  5
  TOKEN_STRING, //String  6
  TOKEN_NONE, //NULL  7

  /* Operators */
  TOKEN_MUL, // *  8
  TOKEN_DIV, // /  9
  TOKEN_ADD, //+  10
  TOKEN_SUB, //-  11
  TOKEN_ASSIGN, //=  12

  TOKEN_EQL, //==  13
  TOKEN_NEQL,//!=  14
  TOKEN_LESS, //<  15
  TOKEN_LESSEQL, //<=  16
  TOKEN_MORE, //>  17
  TOKEN_MOREEQL, //>=  18

   /* Misc */
  TOKEN_LPAREN, //(  19
  TOKEN_RPAREN, //)  20
  TOKEN_COM, //Comma (,)  21

  TOKEN_EMPTY, //Token is empty (uninitaliued) 22
  TOKEN_EOL, //EOL 23
  TOKEN_EOF, //EOF  24

  /* Keywords */
  KEYWORD_DEF, //def 25
  KEYWORD_DO, //do 26
  KEYWORD_ELSE, //else 27
  KEYWORD_END, //end 28
  KEYWORD_IF, //if 29
  KEYWORD_NOT, //not 30
  KEYWORD_NONE, //none 31
  KEYWORD_THEN, //then 32
  KEYWORD_WHILE, //while 33
  KEYWORD_PASS //pass 34
} TokenType;

#endif
