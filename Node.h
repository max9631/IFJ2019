/*
 * Author(s): Adam Salih (xsalih01)
 * File: Node.h, implementation of node structure
 */

// This file contains set of nodes that togather makes a derivation tree.
// The top of a derivation tree is allways MainNode.

#ifndef NODE_H
#define NODE_H
#include "String.h"
#include "Token.h"
#include "symtable.h"

typedef union _Value {
    String *intVal;
    String *floatVal;
    String *stringVal;
    String *identifier;
    String *boolVal;
    String *isNone;
} Value;

typedef enum _ValueType {
    VALUE_CONSTANT,
    VALUE_VARIABLE
} ValueType;


typedef struct _ValueNode {
    Value value;
    ValueType type;
    bool isGlobal;
} ValueNode;

typedef enum _ExpressionType {
    EXPRESSION_CALL,
    EXPRESSION_VALUE,
    EXPRESSION_OPERATION,
    EXPRESSION_CONVERSION_INT_TO_FLOAT
} ExpressionType;

typedef enum _ExpressionDataType {
    EXPRESSION_DATA_TYPE_NONE,
    EXPRESSION_DATA_TYPE_INT,
    EXPRESSION_DATA_TYPE_FLOAT,
    EXPRESSION_DATA_TYPE_BOOL,
    EXPRESSION_DATA_TYPE_STRING,
    EXPRESSION_DATA_TYPE_UNKNOWN
} ExpressionDataType;

typedef struct _ExpressionNode {
    void *expression;
    ExpressionType type;
    ExpressionDataType dataType;
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
    OPERATION_OR,
    OPERATION_NOT,
    OPERATION_IDIV
} OperationType;

typedef struct _OperationNode {
    ExpressionNode *value1;
    ExpressionNode *value2;
    OperationType type;
} OperationNode;

typedef enum _StatementType {
    STATEMENT_ASSIGN,
    STATEMENT_EXPRESSION,
    STATEMENT_WHILE,
    STATEMENT_IF,
    STATEMENT_RETURN,
    STATEMENT_PASS
} StatementType;

typedef struct _StatementNode {
    void *statement;
    StatementType statementType;
} StatementNode;

typedef enum _AssignOperator {
    ASSIGN_NONE,
    ASSIGN_ADD,
    ASSIGN_SUB,
    ASSIGN_DIV,
    ASSIGN_MUL
} AssignOperator;

typedef struct _AssignNode {
    String *identifier;
    ExpressionNode *expression;
    AssignOperator operator;
    bool cretesVariable;
    bool isGlobal;
    SymbolMeta *meta;
} AssignNode;

typedef struct _BodyNode {
    HashTable *symTable;
    struct _BodyNode *parrentBody;
    int statementsCount;
    bool isGlobal;
    StatementNode **statements;
} BodyNode;

typedef struct _FuncNode {
    String *name;
    int argsCount;
    String **args;
    BodyNode *body;
    FunctionMeta *meta;
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
    HashTable *funcTable;
    int functionsCount;
    FuncNode **functions;
} MainNode;

// Allocates given node structure, initializes its values and returns its pointer
PrefixItem *createPrefixItem(void *value, PrefixType type);
OperationNode *createOperationNode(OperationType type);
ValueNode *createValueNode(String *str, ValueType type, bool isGlobal);
CallNode *createCallNode(String *identifier);
FuncNode *createFuncNode(String *name, BodyNode *body, FunctionMeta *meta);
CondNode *createCondNode(ExpressionNode *condition, BodyNode *trueBody, BodyNode *falseBody);
WhileNode *createWhileNode(ExpressionNode *condition, BodyNode *body);
AssignNode *createAssignNode(String *identifier, AssignOperator operator, ExpressionNode *expression, SymbolMeta *meta, bool cretesVariable, bool isGlobal);
StatementNode *createStatementNode(void *statement, StatementType type);
ExpressionNode *createExpressionNode(void *expressions, ExpressionType type, ExpressionDataType dataType);
BodyNode *createBodyNode(BodyNode *parrentBody, HashTable *symtable, bool isGlobal);
MainNode *createMainNode(BodyNode *body);

OperationType operationTypeForToken(Token *token);

// Adds statement node to body node
void addBodyStatement(BodyNode *body, StatementNode *statement);
// Add argument identifier to function node
void addFunctionArgument(FuncNode *function, String *argument);
// Add argument value to call node
void addCallArgument(CallNode *call, ExpressionNode *expression);

// Deallocates given node structure and its siblings.
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

#endif //NODE_H
