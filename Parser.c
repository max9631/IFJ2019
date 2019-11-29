#include "Parser.h"

ParserState *createParserState(List *list) {
    ParserState *state = (ParserState *)malloc(sizeof(ParserState));
    state->list = list;
    state->main = NULL;
    return state;
}

void addPraserFunction(ParserState *state, FuncNode *func) {
    state->main->functionsCount++;
    state->main->functions = (FuncNode **)realloc(state->main->functions, state->main->functionsCount * sizeof(FuncNode *));
    state->main->functions[state->main->functionsCount - 1] = func;
}

void DestroyParserState(ParserState *state) {
    if (state->main != NULL) destroyMainNode(state->main);
    if (state->main->funcTable != NULL) destroyHashTable(state->main->funcTable);
    for (int i = 0; i < state->main->functionsCount; i++)
        destroyFuncNode(state->main->functions[i]);
    if (state->main->functions != NULL) free(state->main->functions);
    free(state);
}

MainNode *parseTokens(ParserState *state) {
    state->main = createMainNode(createBodyNode(NULL, createSymTable(), true));
    BodyNode *body = state->main->body;
    while (peek(state->list)->type != TOKEN_EOF) {
        if (peek(state->list)->type != TOKEN_EOL) {
            if (peek(state->list)->type == KEYWORD_DEF)
                addPraserFunction(state, parseFunc(state, body));
            else
                addBodyStatement(body, parseStatement(state, body));
        }
        consume(state->list, TOKEN_EOL);
    }
    return state->main;
}

BodyNode *parseBody(ParserState *state, BodyNode *parrentBody, String **arguments, int argCount, HashTable *symtable, bool isGlobal) {
    BodyNode *body = createBodyNode(parrentBody, symtable, isGlobal);
    for (int i = 0; i < argCount; i++)
        registerSymbol(body, arguments[i]);
    while (peek(state->list)->type != TOKEN_DEINDENT) {
        if (peek(state->list)->type != TOKEN_EOL) {
            addBodyStatement(body, parseStatement(state, body));
        }
        consume(state->list, TOKEN_EOL);
    }
    return body;
}

FuncNode *parseFunc(ParserState *state, BodyNode *body) {
    List *list = state->list;
    consume(list, KEYWORD_DEF);
    Token *name = consume(list, TOKEN_IDENTIFIER);
    if (containsFunction(state, name->value)) {
        handleError(SemanticIdentifierError, "Invalid redeclaration of a function '%s' on line %d", name->value->value, name->line);
    }
    consume(list, TOKEN_OPAREN);
    FuncNode *function = createFuncNode(name->value, NULL);
    int argsCount = 0;
    while(true) {
        Token *variable = consume(list, TOKEN_IDENTIFIER);
        addFunctionArgument(function, variable->value);
        argsCount++;
        if(isNextTokenOfType(list, TOKEN_CPAREN)) {
            consume(list, TOKEN_CPAREN);
            break;
        } else if (isNextTokenOfType(list, TOKEN_COMMA)) {
            consume(list, TOKEN_COMMA);
            continue;
        } else {
            handleError(SyntaxError, "Expected ')' or ',' in function declaration %s on line %d", name->value->value, variable->line);
        }
    }
    registerFunction(state, name->value, argsCount);
    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);
    function->body = parseBody(state, body, function->args, function->argsCount, createSymTable(), false);
    consume(list, TOKEN_DEINDENT);
    return function;
}

CondNode *parseCond(ParserState *state, BodyNode *body) {
    List *list = state->list;
    consume(list, KEYWORD_IF);
    ExpressionNode *condition = parseExpression(state, body);
    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);
    BodyNode *trueBody = parseBody(state, body, NULL, 0, body->symTable, body->isGlobal);
    consume(list, TOKEN_DEINDENT);
    consume(list, TOKEN_EOL);
    consume(list, KEYWORD_ELSE);
    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);
    BodyNode *falseBody = parseBody(state, body, NULL, 0, body->symTable, body->isGlobal);
    consume(list, TOKEN_DEINDENT);
    return createCondNode(condition, trueBody, falseBody);
}

WhileNode *parseWhile(ParserState *state, BodyNode *parrentBody) {
    List *list = state->list;
    consume(list, KEYWORD_WHILE);
    ExpressionNode *condition = parseExpression(state, parrentBody);
    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);
    BodyNode *body = parseBody(state, parrentBody, NULL, 0, parrentBody->symTable, parrentBody->isGlobal);
    consume(list, TOKEN_DEINDENT);
    return createWhileNode(condition, body);
}

AssignNode *parseAssign(ParserState *state, BodyNode *body) {
    Token *identifier = consume(state->list, TOKEN_IDENTIFIER);
    bool createsVar = true;
    bool isGlobal = body->isGlobal;
    if (containsSymbol(body, identifier->value)) {
        createsVar = false;
    } else {
        registerSymbol(body, identifier->value);
    }
    TokenType type = popToken(state->list)->type;
    switch (type) {
    case OPERATOR_ASSIGN: return createAssignNode(identifier->value, ASSIGN_NONE, parseExpression(state, body), createsVar, isGlobal);
    case OPERATOR_DIV_ASSIGN: return createAssignNode(identifier->value, ASSIGN_DIV, parseExpression(state, body), createsVar, isGlobal);
    case OPERATOR_MUL_ASSIGN: return createAssignNode(identifier->value, ASSIGN_MUL, parseExpression(state, body), createsVar, isGlobal);
    case OPERATOR_ADD_ASSIGN: return createAssignNode(identifier->value, ASSIGN_ADD, parseExpression(state, body), createsVar, isGlobal);
    case OPERATOR_SUB_ASSIGN: return createAssignNode(identifier->value, ASSIGN_SUB, parseExpression(state, body), createsVar, isGlobal);
    default: handleError(SyntaxError, "Expected assign operator, but got %s", convertTokenTypeToString(type));
    }
    return NULL;
}


StatementNode *parseStatement(ParserState *state, BodyNode *body) {
    Token *nextToken = peek(state->list);
    switch (nextToken->type) {
    case TOKEN_IDENTIFIER:
        if (isTokenAsignOperator(peekNext(state->list, 1)))
            return createStatementNode(parseAssign(state, body), STATEMENT_ASSIGN);
        return createStatementNode(parseExpression(state, body), STATEMENT_EXPRESSION);
    case KEYWORD_WHILE: return createStatementNode(parseWhile(state, body), STATEMENT_WHILE);
    case KEYWORD_IF: return createStatementNode(parseCond(state, body), STATEMENT_IF);
    case KEYWORD_PASS: return createStatementNode(consume(state->list, KEYWORD_PASS), STATEMENT_PASS);
    case KEYWORD_RETURN:
            consume(state->list, KEYWORD_RETURN);
            if (peek(state->list)->type != TOKEN_EOL)
                return createStatementNode(parseExpression(state, body), STATEMENT_RETURN);
            return createStatementNode(NULL, STATEMENT_RETURN);
    default:
        if (isTokenExpression(nextToken))
            return createStatementNode(parseExpression(state, body), STATEMENT_EXPRESSION);
        handleError(SyntaxError, "Invalid syntax on line %d", nextToken->line);
        return NULL;
    }
}

CallNode *parseCall(ParserState *state, BodyNode *body) {
    Token* identifier = consume(state->list, TOKEN_IDENTIFIER);
    if (!containsFunction(state, identifier->value)) {
        handleError(SemanticIdentifierError, "Unknown function identifier '%s' on line %d", identifier->value->value, identifier->line);
    }
    CallNode *call = createCallNode(identifier->value);
    consume(state->list, TOKEN_OPAREN);
    long argsCount = 0;
    if (peek(state->list)->type != TOKEN_CPAREN) {
        while(true) {
            if (!isTokenExpression(peek(state->list)))
                handleError(SyntaxError, "Invalid call syntax on line %d", peek(state->list)->line);
            addCallArgument(call, parseExpression(state, body));
            argsCount++;
            if (peek(state->list)->type == TOKEN_CPAREN)
                break;
            consume(state->list, TOKEN_COMMA);
        }
    }
    long correctNumberOfArguments = getArgumentsCountForFuntion(state, identifier->value);
    if (argsCount != correctNumberOfArguments && correctNumberOfArguments != __LONG_MAX__)
        handleError(SemanticArgumentError, "Wrong number of arguments one line %d. Should be %d, but got %d", identifier->line, correctNumberOfArguments, argsCount);
    consume(state->list, TOKEN_CPAREN);
    return call;
}

ExpressionNode *parseValue(ParserState *state, BodyNode *body) {
    Token *token = peek(state->list);
    switch(token->type) {
    case TOKEN_IDENTIFIER:
        if (peekNext(state->list, 1)->type == TOKEN_OPAREN)
            return createExpressionNode(parseCall(state, body), EXPRESSION_CALL, EXPRESSION_DATA_TYPE_UNKNOWN);
        if (!containsSymbol(body, token->value))
            handleError(SemanticIdentifierError, "Uknown identier '%s' on line %d", token->value->value, token->line);
        return createExpressionNode(createValueNode(popToken(state->list)->value, VALUE_VARIABLE, body->isGlobal), EXPRESSION_VALUE, EXPRESSION_DATA_TYPE_UNKNOWN);
    case DATA_TOKEN_INT: return createExpressionNode(createValueNode(popToken(state->list)->value, VALUE_CONSTANT, false), EXPRESSION_VALUE, EXPRESSION_DATA_TYPE_INT);
    case DATA_TOKEN_FLOAT: return createExpressionNode(createValueNode(popToken(state->list)->value, VALUE_CONSTANT, false), EXPRESSION_VALUE, EXPRESSION_DATA_TYPE_FLOAT);
    case DATA_TOKEN_STRING: return createExpressionNode(createValueNode(popToken(state->list)->value, VALUE_CONSTANT, false), EXPRESSION_VALUE, EXPRESSION_DATA_TYPE_STRING);
    case DATA_TOKEN_BOOL: return createExpressionNode(createValueNode(popToken(state->list)->value, VALUE_CONSTANT, false), EXPRESSION_VALUE, EXPRESSION_DATA_TYPE_BOOL);
    case DATA_TOKEN_NONE: return createExpressionNode(createValueNode(popToken(state->list)->value, VALUE_CONSTANT, false), EXPRESSION_VALUE, EXPRESSION_DATA_TYPE_NONE);
    default: handleError(SyntaxError, "Uknown value %s on line %d", token->value->value, token->line);
    }
    return NULL;
}

bool isTokenValue(Token *token) {
    return token->type == TOKEN_IDENTIFIER ||
        token->type == DATA_TOKEN_INT ||
        token->type == DATA_TOKEN_FLOAT ||
        token->type == DATA_TOKEN_STRING ||
        token->type == DATA_TOKEN_BOOL ||
        token->type == DATA_TOKEN_NONE;
}

bool isTokenOperator(Token *token) {
    return token->type == OPERATOR_NEQL ||
        token->type == OPERATOR_MORE ||
        token->type == OPERATOR_MOREEQL ||
        token->type == OPERATOR_LESS ||
        token->type == OPERATOR_LESSEQL ||
        token->type == OPERATOR_ADD ||
        token->type == OPERATOR_SUB ||
        token->type == OPERATOR_EQL ||
        token->type == OPERATOR_DIV ||
        token->type == OPERATOR_IDIV ||
        token->type == OPERATOR_NOT ||
        token->type == OPERATOR_MUL;
}

ExpressionNode *parseOperation(ParserState *state, Stack *prefix, OperationType type, int line, BodyNode *body) {
    OperationNode *operation = createOperationNode(type);
    PrefixItem *item;
    ExpressionNode *operands[2];

    bool isSingleValue = type == OPERATION_NOT;
    int startVal = isSingleValue ? 0 : 1;
    for (int i = startVal; i >= 0; i--) {
        item = (PrefixItem *) popStack(prefix);
        if (item->type == PREFIX_OPERATOR_TOKEN) {
            Token *token = (Token *) item->prefix.operator;
            operands[i] = parseOperation(state, prefix, operationTypeForToken(token), line, body);
        } else if (item->type == PREFIX_VALUE_EXPRESSION) {
            operands[i] = item->prefix.value;
        } else
            handleError(SyntaxError, "Invalid expression on line %d", line);
    }
    
    operation->value1 = operands[0];
    if (!isSingleValue) {
        operation->value2 = operands[1];
    }
    ExpressionDataType dataType = EXPRESSION_DATA_TYPE_UNKNOWN;
    return createExpressionNode(operation, EXPRESSION_OPERATION, dataType);
}

bool isTokenExpression(Token *token) {
    return isTokenValue(token) || isTokenOperator(token) ||
        token->type == TOKEN_OPAREN || token->type == TOKEN_CPAREN;
}

int priorityForOperator(TokenType type) {
    switch (type) {
        case OPERATOR_NOT:
        case OPERATOR_AND:
        case OPERATOR_OR:
            return 4;
        case OPERATOR_NEQL:
        case OPERATOR_MORE:
        case OPERATOR_MOREEQL:
        case OPERATOR_LESS:
        case OPERATOR_LESSEQL:
        case OPERATOR_EQL:
            return 3;
        case OPERATOR_ADD:
        case OPERATOR_SUB:
            return 2;
        case OPERATOR_DIV:
        case OPERATOR_MUL:
        case OPERATOR_IDIV:
            return 1;
        default:
            return 0;
    }
}

bool hasStackHigherOrEqualPrecedence(Stack *operators, TokenType type) {
    Token *top = (Token *)operators->items[operators->count - 1];
    return priorityForOperator(top->type) >= priorityForOperator(type);
}

// End for expressions: "\n", ",", ")"
ExpressionNode *parseExpression(ParserState *state, BodyNode *body) {
    Stack *prefix = createStack();
    Stack *operators = createStack();
    int parensCount = 0;
    int line = peek(state->list)->line;
    Token *token;
    while (isTokenExpression(peek(state->list))) {
        token = peek(state->list);
        if (isTokenValue(token)) {
            pushStack(prefix, createPrefixItem(parseValue(state, body), PREFIX_VALUE_EXPRESSION));
        } else if (isTokenOperator(token)) {
            Token *token = popToken(state->list);
            while (operators->count != 0 && hasStackHigherOrEqualPrecedence(operators, token->type))
                pushStack(prefix, createPrefixItem(popStack(operators), PREFIX_OPERATOR_TOKEN));
            pushStack(operators, token);
        } else if (token->type == TOKEN_OPAREN) {
            parensCount++;
            pushStack(operators, popToken(state->list));
        } else if (token->type == TOKEN_CPAREN) {
            if (parensCount == 0)
                break;
            popToken(state->list);
            Token *operator;
            while (operators->count != 0 && (operator = popStack(operators))->type != TOKEN_OPAREN ) {
                pushStack(prefix, createPrefixItem(operator, PREFIX_OPERATOR_TOKEN));
            }
            parensCount--;
        }
    }
    while(operators->count != 0)
        pushStack(prefix, createPrefixItem(popStack(operators), PREFIX_OPERATOR_TOKEN));
    destroyStack(operators);
    PrefixItem *item = (PrefixItem *) popStack(prefix);
    if (item == NULL)
        handleError(SyntaxError, "Invalid expression on line %d", line);
    if(item->type == PREFIX_OPERATOR_TOKEN) {
        ExpressionNode *node = parseOperation(state, prefix, operationTypeForToken(item->prefix.operator), line, body);
        if (prefix->count > 0) handleError(SyntaxError, "Invalid expression on line %d", line);
        return node;
    } else if (prefix->count == 0) return item->prefix.value;
    handleError(SyntaxError, "Invalid expression on line %d", line);
    return NULL;
}

bool containsFunction(ParserState *state, String *identifier) {
    return contains(state->main->funcTable, identifier->value);
}

bool containsSymbol(BodyNode *body, String *identifier) {
    return findBodyForIdentifier(body, identifier) != NULL;
}

BodyNode *findBodyForIdentifier(BodyNode *body, String *identifier) {
    while (body != NULL) {
        if (contains(body->symTable, identifier->value))
            break;
        body = body->parrentBody;
    }
    return body;
}

long getArgumentsCountForFuntion(ParserState *state, String *functionName) {
    HashTableItem *item = getHashTableItem(state->main->funcTable, functionName->value);
    long currentCount = (long) item->data;
    return currentCount;
}


void registerSymbol(BodyNode *body, String *identifier) {
    insertHashTableItem(body->symTable, identifier->value, NULL);
}

void registerFunction(ParserState *state, String *identifier, int argsCount) {
    long bigCount = (long)argsCount;
    void *data = (void *)bigCount;
    insertHashTableItem(state->main->funcTable, identifier->value, data);
}

/* --------------- DEBUG Functions ----------------- */
void printFuncNode(FuncNode *node) {
    if(!inDebugMode)
        return;
    printf("<FuncNode name=\"%s\" argsCount=\"%d\">\n", node->name->value, node->argsCount);
    for(int i = 0; i < node->argsCount; i++)
        printf("   <Argument index=\"%d\" name=\"%s\" />\n", i, node->args[i]->value);
    printf("</FuncNode>\n");
}
