#ifndef PARSER_H
#define PARSER_H
#include "List.h"
#include "Node.h"
#include "symtable.h"
#include "Stack.h"

typedef struct _ParserState {
    List *list;
    MainNode *main;
} ParserState;

ParserState *createParserState(List *list);
void addPraserFunction(ParserState *state, FuncNode *func);
void DestroyParserState(ParserState *state);

MainNode *parseTokens(ParserState *state);
BodyNode *parseBody(ParserState *state, BodyNode *body, String **arguments, int argCount, HashTable *symtable, bool isGlobal);
FuncNode *parseFunc(ParserState *state, BodyNode *body);
CondNode *parseCond(ParserState *state, BodyNode *body);
WhileNode *parseWhile(ParserState *state, BodyNode *body);
AssignNode *parseAssign(ParserState *state, BodyNode *body);
StatementNode *parseStatement(ParserState *state, BodyNode *body);
CallNode *parseCall(ParserState *state, BodyNode *body);
ExpressionNode *parseExpression(ParserState *state, BodyNode *body);

ExpressionNode *parseValue(ParserState *state, BodyNode *body) ;
ExpressionNode *parseOperation(ParserState *state, Stack *prefix, OperationType type, int line, BodyNode *body);

bool isTokenValue(Token *token);
bool isTokenOperator(Token *token);
bool isTokenExpression(Token *token);
bool hasStackHigherOrEqualPrecedence(Stack *operators, TokenType type);
bool containsFunction(ParserState *state, String *identifier);
BodyNode *findBodyForIdentifier(BodyNode *body, String *identifier);
bool containsSymbol(BodyNode *body, String *identifier);
void registerSymbol(BodyNode *body, String *identifier);
void registerFunction(ParserState *state, String *identifier, int argsCount);

/*DEBUG functions*/
void printFuncNode(FuncNode *node);

#endif
