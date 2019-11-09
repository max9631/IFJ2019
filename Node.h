#ifndef NODE_H
#define NODE_H
#include "String.h"

typedef enum _StatementType { 
    STATEMENT_ASSIGN, 
    STATEMENT_EXPRESSION, 
    STATEMENT_WHILE,
    STATEMENT_IF,
    STATEMENT_RETURN,
    STATEMENT_PASS,
    STATEMENT_BREAK
} StatementType;

typedef struct _StatementNode {
    void *statement;
    StatementType type;
} StatementNode;

typedef struct _FuncNode {
    String *name;
    int argsCount;
    String **args;
    BodyNode *body;
} FuncNode;

typedef struct _CondNode {
    ExpressionNode *condition;
    BodyNode *trueBody;
    BodyNode *falseBody;
} CondNode;

typedef struct _WhileNode {
    ExpressionNode *condition;
    BodyNode *body;
} WhileNode;

FuncNode *createFuncNode(String *name, BodyNode *body);
CondNode *createCondNode(ExpressionNode *condition, BodyNode *trueBody, BodyNode *falseBody);
WhileNode *createWhileNode(ExpressionNode *condition, BodyNode *body);
StatementNode *craeteStatementNode(void *statement, StatementType type);

void destroyFuncNode(FuncNode *node);
void destroyCondNode(CondNode *node);
void destroyWhileNode(WhileNode *node);
void destroyStatementNode(StatementNode *node);
#endif
