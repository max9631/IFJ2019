#ifndef PARSER_H
#define PARSER_H
#include "TokenList.h"
#include "Node.h"

typedef struct _ParserState {
    TokenList *list;
} ParserState;

MainNode *parseTokens(TokenList *list);
BodyNode *parseBody();
FuncNode *parseFunc();
CondNode *parseCond();
WhileNode *parseWhile();
StatementNode *parseStatement();
ExpressionNode *parseExpression();

#endif
