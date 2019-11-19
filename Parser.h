#ifndef PARSER_H
#define PARSER_H
#include "List.h"
#include "Node.h"
#include "symtable.h"
#include "Stack.h"

typedef struct _ParserState {
    List *list;
    MainNode *main;
    HashTable *funcTable;
    int functionsCount;
    FuncNode **functions;
} ParserState;

ParserState *createParserState(List *list);
void addPraserFunction(ParserState *state, FuncNode *func);
void DestroyParserState(ParserState *state);

MainNode *parseTokens(ParserState *state);
BodyNode *parseBody(ParserState *state);
FuncNode *parseFunc(ParserState *state);
CondNode *parseCond(ParserState *state);
WhileNode *parseWhile(ParserState *state);
AssignNode *parseAssign(ParserState *state);
StatementNode *parseStatement(ParserState *state);
CallNode *parseCall(ParserState *state);
ExpressionNode *parseValue(ParserState *state) ;
ExpressionNode *parseExpression(ParserState *state);
OperationNode *parseOperation(ParserState *state, Stack *prefix, OperationType type, int line);

bool isTokenValue(Token *token);
bool isTokenOperator(Token *token);
bool isTokenExpression(Token *token);
bool hasStackHigherOrEqualPrecedence(Stack *operators, TokenType type);

/*DEBUG functions*/
void printFuncNode(FuncNode *node);

#endif
