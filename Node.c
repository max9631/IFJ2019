#include "Node.h"

OperationNode *createOperationNode(OperationType type) {
    OperationNode *node = (OperationNode *) malloc(sizeof(OperationNode));
    node->value1 = NULL;
    node->value2 = NULL;
    node->type = type;
    return node;
}

ValueNode *createValueNode(String *str, ValueType type, bool isGlobal) {
    ValueNode *node = (ValueNode *) malloc(sizeof(ValueNode));
    node->value.stringVal = createString(str->value);
    node->type = type;
    node->isGlobal = isGlobal;
    return node;
}

CallNode *createCallNode(String *identifier) {
    CallNode *node = (CallNode *) malloc(sizeof(CallNode));
    node->identifier = createString(identifier->value);
    node->argsCount = 0;
    node->expressions = NULL;
    return node;
}

PrefixItem *createPrefixItem(void *value, PrefixType type) {
    PrefixItem *item = (PrefixItem *)malloc(sizeof(PrefixItem));
    item->prefix.value = value;
    item->type = type;
    return item;
}

FuncNode *createFuncNode(String *name, BodyNode *body) {
    FuncNode *node = (FuncNode *) malloc(sizeof(FuncNode));
    node->name = name;
    node->argsCount = 0;
    node->args = NULL;
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

AssignNode *createAssignNode(String *identifier, AssignOperator operator, ExpressionNode *expression, bool cretesVariable, bool isGlobal) {
    AssignNode *node = (AssignNode *)malloc(sizeof(AssignNode));
    node->identifier = createString(identifier->value);
    node->expression = expression;
    node->operator = operator;
    node->cretesVariable = cretesVariable;
    node->isGlobal = isGlobal;
    return node;
}

StatementNode *createStatementNode(void *statement, StatementType type) {
    StatementNode *node = (StatementNode *) malloc(sizeof(StatementNode));
    node->statement = statement;
    node->statementType = type;
    return node;
}

ExpressionNode *createExpressionNode(void *expression, ExpressionType type, ExpressionDataType dataType) {
    ExpressionNode *node = (ExpressionNode *) malloc(sizeof(ExpressionNode));
    node->expression = expression;
    node->type = type;
    node->dataType = dataType;
    return node;
}

BodyNode *createBodyNode(BodyNode *parrentBody, HashTable *symtable, bool isGlobal) {
    BodyNode *node = (BodyNode *) malloc(sizeof(BodyNode));
    node->symTable = symtable;
    node->statementsCount = 0;
    if (node->symTable == NULL)
        node->symTable = createSymbolTable();
    node->parrentBody = parrentBody;
    node->statements = NULL;
    node->isGlobal = isGlobal;
    return node;
}

MainNode *createMainNode(BodyNode *body) {
    MainNode *node = (MainNode *) malloc(sizeof(MainNode));
    node->body = body;
    node->funcTable = createFunctionTable();
    node->functionsCount = 0;
    node->functions = NULL;
    return node;
}

OperationType operationTypeForToken(Token *token) {
    switch(token->type) {
    case OPERATOR_ADD: return OPERATION_ADD;
    case OPERATOR_SUB: return OPERATION_SUB;
    case OPERATOR_MUL: return OPERATION_MUL;
    case OPERATOR_DIV: return OPERATION_DIV;
    case OPERATOR_EQL: return OPERATION_EQUALS;
    case OPERATOR_NEQL: return OPERATION_NOTEQUALS;
    case OPERATOR_MORE: return OPERATION_GREATER;
    case OPERATOR_MOREEQL: return OPERATION_GREATEROREQUALS;
    case OPERATOR_LESS: return OPERATION_LESS;
    case OPERATOR_LESSEQL: return OPERATION_LESSOREQUALS;
    case OPERATOR_AND: return OPERATION_AND;
    case OPERATOR_OR: return OPERATION_OR;
    case OPERATOR_IDIV: return OPERATION_IDIV;
    case OPERATOR_NOT: return OPERATION_NOT;
    default: handleError(SyntaxError, "Invalid Operation '%s'\nInvalid expression on line %d", token->value, token->line);
    }
    return OPERATION_OR;
}

void addBodyStatement(BodyNode *body, StatementNode *statement) {
	if (body == NULL) handleError(InternalError, "Error while adding StatementNode to BodyNode");
	body->statementsCount++;
	body->statements = (StatementNode **) realloc(body->statements, body->statementsCount * sizeof(StatementNode *));
	if (body->statements == NULL) handleError(InternalError, "Error while adding StatementNode to BodyNode");
	body->statements[body->statementsCount - 1] = statement;
}

void addFunctionArgument(FuncNode *function, String *argument) {
	if (function == NULL) handleError(InternalError, "Error while adding argument to FuncNode");
	function->argsCount++;
	function->args = (String **) realloc(function->args, function->argsCount * sizeof(String *));
	if (function->args == NULL) handleError(InternalError, "Error while adding argument to FuncNode");
	function->args[function->argsCount - 1] = createString(argument->value);
}

void addCallArgument(CallNode *call, ExpressionNode *expression) {
    if (call == NULL) handleError(InternalError, "Error while adding ExpressionNode to CallNode");
	call->argsCount++;
	call->expressions = (ExpressionNode **) realloc(call->expressions, call->argsCount * sizeof(ExpressionNode *));
	if (call->expressions == NULL) handleError(InternalError, "Error while adding ExpressionNode to CallNode");
	call->expressions[call->argsCount - 1] = expression;
}

void destroyPrefixItem(PrefixItem *item) {
    if (item == NULL) return;
    free(item);
}

void destroyOperationNode(OperationNode *node) {
    if (node->value1 != NULL) destroyExpressionNode(node->value1);
    if (node->value2 != NULL) destroyExpressionNode(node->value2);
    if (node != NULL) free(node);
}

void destroyValueNode(ValueNode *node) {
    if (node != NULL) {
        if (node != NULL) free(node);
    }
}

void destroyCallNode(CallNode *node) {
    destroyString(node->identifier);
    for (int i = 0; i < node->argsCount; i++)
        destroyExpressionNode(node->expressions[i]);
    if (node != NULL) free(node);
}

void destoyAssignNode(AssignNode *node) {
    destroyString(node->identifier);
    destroyExpressionNode(node->expression);
    if (node != NULL) free(node);
}

void destroyFuncNode(FuncNode *node) {
    destroyString(node->name);
    for (int i = 0; i < node->argsCount; i++) {
        destroyString(node->args[i]);
    }
    destroyBodyNode(node->body);
    if (node != NULL) free(node);
}

void destroyCondNode(CondNode *node) {
    destroyExpressionNode(node->condition);
    destroyBodyNode(node->trueBody);
    destroyBodyNode(node->falseBody);
    if (node != NULL) free(node);
}

void destroyWhileNode(WhileNode *node) {
    destroyExpressionNode(node->condition);
    destroyBodyNode(node->body);
    if (node != NULL) free(node);
}

void destroyStatementNode(StatementNode *node) {
    // TODO: Destroy Statements for each type
    if (node != NULL) free(node);
}

void destroyExpressionNode(ExpressionNode *node) {
    // TODO: Destroy Expressions for each type
    if (node != NULL) free(node);
}

void destroyBodyNode(BodyNode *node) {
    for (int i = 0; i < node->statementsCount; i++)
        destroyStatementNode(node->statements[i]);
    destroyHashTable(node->symTable);
    if (node != NULL) free(node);
}

void destroyMainNode(MainNode *node) {
    destroyBodyNode(node->body);
    if (node != NULL) free(node);
}
