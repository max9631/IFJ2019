#ifndef NODE_H
#define NODE_H
#include "String.h"
#include "Token.h"
#include "HashTable.h"

typedef union _Value {
    String *intVal;
    String *floatVal;
    String *stringVal;
    String *identifier;
    String *boolVal;
    String *isNone;
} Value;

typedef enum _ValueType {
    VALUE_INT,
    VALUE_FLOAT,
    VALUE_STRING,
    VALUE_IDENTIFIER,
    VALUE_BOOL,
    VALUE_NONE
} ValueType;


typedef struct _ValueNode {
    Value value;
    ValueType type;
} ValueNode;

typedef enum _ExpressionType { 
    EXPRESSION_CALL,
    EXPRESSION_VALUE,
    EXPRESSION_OPERATION
} ExpressionType;

typedef struct _ExpressionNode {
    void *expression;
    ExpressionType type;
} ExpressionNode;

typedef enum _PrefixType {
    PREFIX_VALUE_EXPRESSION,
    PREFIX_OPERATOR_TOKEN
} PrefixType;

typedef union _Prefix {
    ExpressionNode *value;
    Token *operator;
} Prefix;

typedef struct _PrefixItem {
    Prefix prefix;
    PrefixType type;
} PrefixItem;

typedef struct _CallNode {
    String *identifier;
    int argsCount;
    ExpressionNode **expressions;
} CallNode;

typedef enum _OperationType {
    OPERATION_ADD,
    OPERATION_SUB,
    OPERATION_MUL,
    OPERATION_DIV,
    OPERATION_EQUALS,
    OPERATION_NOTEQUALS,
    OPERATION_GREATER,
    OPERATION_GREATEROREQUALS,
    OPERATION_LESS,
    OPERATION_LESSOREQUALS,
    OPERATION_AND,
    OPERATION_OR
} OperationType;

typedef struct _OperationNode {
    ExpressionNode *value1;
    ExpressionNode *value2;
    OperationType type;
} OperationNode;

typedef enum _StatementType { 
    STATEMENT_ASSIGN,
    STATEMENT_ASSIGN_MUL,
    STATEMENT_ASSIGN_DIV,
    STATEMENT_ASSIGN_ADD,
    STATEMENT_ASSIGN_SUB,
    STATEMENT_EXPRESSION, 
    STATEMENT_WHILE,
    STATEMENT_IF,
    STATEMENT_RETURN,
    STATEMENT_PASS
} StatementType;

typedef struct _StatementNode {
    void *statement;
    StatementType type;
} StatementNode;

typedef enum _AssignOperator {
    ASSIGN_NONE, ASSIGN_ADD, ASSIGN_SUB, ASSIGN_DIV, ASSIGN_MUL
} AssignOperator;

typedef struct _AssignNode {
    String *identifier;
    ExpressionNode *expression;
    AssignOperator operator;
} AssignNode;

typedef struct _BodyNode {
    HashTable *symTable;
    struct _BodyNode *parrentBody;
    int statementsCount;
    StatementNode **statements;
} BodyNode;

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

typedef struct _MainNode {
    BodyNode *body;
} MainNode;

PrefixItem *createPrefixItem(void *value, PrefixType type);
OperationNode *createOperationNode(OperationType type);
ValueNode *createValueNode(String *str, ValueType type);
CallNode *createCallNode(String *identifier);
FuncNode *createFuncNode(String *name, BodyNode *body);
CondNode *createCondNode(ExpressionNode *condition, BodyNode *trueBody, BodyNode *falseBody);
WhileNode *createWhileNode(ExpressionNode *condition, BodyNode *body);
AssignNode *createAssignNode(String *identifier, AssignOperator operator, ExpressionNode *expression);
StatementNode *craeteStatementNode(void *statement, StatementType type);
ExpressionNode *createExpressionNode(void *expressions, ExpressionType type);
BodyNode *createBodyNode(BodyNode *parrentBody);
MainNode *createMainNode(BodyNode *body);

OperationType operationTypeForToken(Token *token);

void addBodyStatement(BodyNode *body, StatementNode *statement);
void addFunctionArgument(FuncNode *function, String *argument);
void addCallArgument(CallNode *call, ExpressionNode *expression);

void destroyPrefixItem(PrefixItem *item);
void destroyOperationNode(OperationNode *node);
void destroyValueNode(ValueNode *node);
void destroyCallNode(CallNode *node);
void destoyAssignNode(AssignNode *node);
void destroyFuncNode(FuncNode *node);
void destroyCondNode(CondNode *node);
void destroyWhileNode(WhileNode *node);
void destroyStatementNode(StatementNode *node);
void destroyExpressionNode(ExpressionNode *node);
void destroyBodyNode(BodyNode *node);
void destroyMainNode(MainNode *node);

#endif
