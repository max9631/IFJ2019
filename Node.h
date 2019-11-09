#ifndef NODE_H
#define NODE_H
#include "String.h"

typedef struct _FuncNode {
    String *name;
    int argsCount;
    String **args;
    BodyNode *body;
} FuncNode;

FuncNode *createFuncNode(String *name, BodyNode *body);
void destroyFuncNode(FuncNode *node);
#endif
