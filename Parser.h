/*
 * Author(s): Adam Salih (xsalih01), Michal Halabica (xhalab00)
 * Project: Implementace prekladace imperativniho jazyka jazyka IFJ19
 * File: Parser.h, implementation of semantic and syntax analysation
 */

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

//Parser state functions
ParserState *createParserState(List *list);
void addPraserFunction(ParserState *state, FuncNode *func);
void DestroyParserState(ParserState *state);


//Generate nodes from tokens
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


bool isTokenValue(Token *token); //Returns true or false depending if token is value
bool isTokenOperator(Token *token); //Returns true of false depending if token is operator
bool isTokenExpression(Token *token); //Returns true or false depending if token is expression
bool hasStackHigherOrEqualPrecedence(Stack *operators, TokenType type); //Returns true or false depending on precedence
bool containsFunction(ParserState *state, String *identifier); //Returns true or false depending if state contains function (identifier)
BodyNode *findBodyForIdentifier(BodyNode *body, String *identifier); //Returns pointer to a BodyNode specified by identifier
bool containsSymbol(BodyNode *body, String *identifier); //Returns true or false depending if body contains symbol
void registerSymbol(BodyNode *body, String *identifier); //Registers a new symbol in body to symtable
void registerFunction(ParserState *state, String *identifier, int argsCount); //Registers function identifier to function table 

/*DEBUG functions*/
void printFuncNode(FuncNode *node);

#endif //PARSER_H
