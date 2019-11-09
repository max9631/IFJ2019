#include "Node.h"

FuncNode *createFuncNode(String *name, BodyNode *body) {
    FuncNode *node = (FuncNode *) malloc(sizeof(FuncNode));
    node->name = name;
    node->argsCount = 0;
    node->body = body;
    return node;
}

void destroyFuncNode(FuncNode *node) {
    free(node->name->value);
    free(node->name);
    for (int i = 0; i < node->argsCount; i++) {
        free(node->args[i]->value);
        free(node->args[i]);
    }
    destroyBodyNode(node->body);
    free(node);
}

