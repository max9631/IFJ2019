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

StatementNode *craeteStatementNode(void *statement, StatementType type) {
    StatementNode *node = (StatementNode *) malloc(sizeof(StatementNode));
    node->statement = statement;
    node->type = type;
    return node;
}

ExpressionNode *createExpressionNode(void *expression, ExpressionType type) {
    ExpressionNode *node = (ExpressionNode *) malloc(sizeof(ExpressionNode));
    node->expression = expression;
    node->type = type;
    return node;
}

BodyNode *createBodyNode() {
    BodyNode *node = (BodyNode *) malloc(sizeof(BodyNode));
    return node;
}

MainNode *createMainNode(BodyNode *body) {
    MainNode *node = (MainNode *) malloc(sizeof(MainNode));
    node->body = body;
    return node;
}

void addBodyStatement(BodyNode *body, StatementNode *statement) {
	if (body == NULL) handleError(InternalError, "Error while adding StatementNode to BodyNode");
	body->statementsCount++;
	body->statements = (StatementNode **) realloc(body->statements, body->statementsCount * sizeof(StatementNode *));
	if (body->statements == NULL) handleError(InternalError, "Error while adding StatementNode to BodyNode");
	body->statements[body->statementsCount - 1] = statement;
}

void addFunctionArgument(FuncNode *function, String *argument) {
	if (function == NULL) handleError(InternalError, "Error while adding StatementNode to BodyNode");
	function->argsCount++;
	function->args = (String **) realloc(function->args, function->argsCount * sizeof(String *));
	if (function->args == NULL) handleError(InternalError, "Error while adding StatementNode to BodyNode");
	function->args[function->argsCount - 1] = createString(argument->value);
}

void destroyFuncNode(FuncNode *node) {
    destroyString(node->name);
    for (int i = 0; i < node->argsCount; i++) {
        destroyString(node->args[i]);
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

void destroyStatementNode(StatementNode *node) {
    // TODO: Destroy Statements for each type
    free(node);
}

void destroyExpressionNode(ExpressionNode *node) {
    // TODO: Destroy Expressions for each type
    free(node);
}

void destroyBodyNode(BodyNode *node) {
    for (int i = 0; i < node->statementsCount; i++)
        destroyStatementNode(node->statements[i]);
    free(node);
}

void destroyMainNode(MainNode *node) {
    destroyBodyNode(node->body);
    free(node);
}
