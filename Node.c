#include "Node.h"

FuncNode *createFuncNode(String *name, BodyNode *body) {
    FuncNode *node = (FuncNode *) malloc(sizeof(FuncNode));
    node->name = name;
    node->argsCount = 0;
    node->body = body;
    return node;
}

CondNode *createCondNode(ExpressionNode *condition, BodyNode *trueBody, BodyNode *falseBody) {
    CondNode *node = (CondNode *) malloc(sizeof(CondNode));
    node->condition = condition;
    node->trueBody = trueBody;    
    node->falseBody = falseBody;    
    return node;
}

WhileNode *createWhileNode(ExpressionNode *condition, BodyNode *body) {
    WhileNode *node = (WhileNode *) malloc(sizeof(WhileNode));
    node->condition = condition;
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

void destroyCondNode(CondNode *node) {
    destroyExpressionNode(node->condition);
    destroyBodyNode(node->trueBody);
    destroyBodyNode(node->falseBody);
    free(node);
}

void destroyWhileNode(WhileNode *node) {
    destroyExpressionNode(node->condition);
    destroyBodyNode(node->body);
    free(node);
}

