#ifndef PARSER_H
#define PARSER_H
#include "TokenList.h"
#include "Node.h"
#include "HashTable.h"

typedef struct _ParserState {
    TokenList *list;
    MainNode *main;
    HashTable *funcTable;
    int functionsCount;
    FuncNode **functions;
} ParserState;

ParserState *createParserState(TokenList *list);
void addPraserFunction(ParserState *state, FuncNode *func);
void DestroyParserState(ParserState *state);

BodyNode *parseBody(ParserState *state);
FuncNode *parseFunc();
CondNode *parseCond();
WhileNode *parseWhile();
StatementNode *parseStatement();
ExpressionNode *parseExpression();

#endif
