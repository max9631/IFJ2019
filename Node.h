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

typedef struct _BodyNode {
    int statementsCount;
    StatementNode **statements;
} BodyNode;

typedef struct _FuncNode {
    String *name;
    int argsCount;
    String **args;
    BodyNode *body;
} FuncNode;

typedef enum _ExpressionType { 
    EXPRESSION_CALL,
    EXPRESSION_PARREN,
    EXPRESSION_ADD,
    EXPRESSION_SUB,
    EXPRESSION_MUL,
    EXPRESSION_DIV,
    EXPRESSION_EQUALS,
    EXPRESSION_NOTEQUALS,
    EXPRESSION_GREATER,
    EXPRESSION_GREATEROREQUALS,
    EXPRESSION_LESS,
    EXPRESSION_LESSOREQUALS,
    EXPRESSION_AND,
    EXPRESSION_OR,
    EXPRESSION_VAR,
    EXPRESSION_INT,
    EXPRESSION_FLOAT,
    EXPRESSION_BOOL,
    EXPRESSION_STRING,
    EXPRESSION_NONE
} ExpressionType;

typedef struct _ExpressionNode {
    void *expression;
    ExpressionType type;
} ExpressionNode;

typedef struct _CondNode {
    ExpressionNode *condition;
    BodyNode *trueBody;
    BodyNode *falseBody;
} CondNode;

typedef struct _WhileNode {
    ExpressionNode *condition;
    BodyNode *body;
} WhileNode;

typedef struct _MainNode {
    BodyNode *body;
} MainNode;

FuncNode *createFuncNode(String *name, BodyNode *body);
CondNode *createCondNode(ExpressionNode *condition, BodyNode *trueBody, BodyNode *falseBody);
WhileNode *createWhileNode(ExpressionNode *condition, BodyNode *body);
StatementNode *craeteStatementNode(void *statement, StatementType type);
ExpressionNode *createExpressionNode(void *expressions, ExpressionType type);
BodyNode *createBodyNode();
MainNode *createMainNode(BodyNode *body);

void addBodyStatement(BodyNode *body, StatementNode *statement);

void destroyFuncNode(FuncNode *node);
void destroyCondNode(CondNode *node);
void destroyWhileNode(WhileNode *node);
void destroyStatementNode(StatementNode *node);
void destroyExpressionNode(ExpressionNode *node);
void destroyBodyNode(BodyNode *node);
void destroyMainNode(MainNode *node);

#endif
