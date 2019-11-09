#ifndef NODE_H
#define NODE_H
#include "String.h"

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

FuncNode *createFuncNode(String *name, BodyNode *body);
CondNode *createCondNode(ExpressionNode *condition, BodyNode *trueBody, BodyNode *falseBody);

void destroyFuncNode(FuncNode *node);
void destroyCondNode(CondNode *node);
#endif
