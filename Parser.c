#include "Parser.h"

ParserState *createParserState(List *list) {
    ParserState *state = (ParserState *)malloc(sizeof(ParserState));
    state->list = list;
    state->main = NULL;
    state->funcTable = createFuncTable();
    state->functionsCount = 0;
    state->functions = NULL;
    return state;
}

void addPraserFunction(ParserState *state, FuncNode *func) {
    state->functionsCount++;
    state->functions = (FuncNode **)realloc(state->functions, state->functionsCount * sizeof(FuncNode *));
    state->functions[state->functionsCount - 1] = func;
}

void DestroyParserState(ParserState *state) {
    if (state->main != NULL) destroyMainNode(state->main);
    if (state->funcTable != NULL) destroyHashTable(state->funcTable);
    for (int i = 0; i < state->functionsCount; i++)
        destroyFuncNode(state->functions[i]);
    if (state->functions != NULL) free(state->functions);
    free(state);
}

MainNode *parseTokens(ParserState *state) {
    state->main = createMainNode(createBodyNode(NULL, createSymTable()));
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

BodyNode *parseBody(ParserState *state, BodyNode *parrentBody, String **arguments, int argCount, HashTable *symtable) {
    BodyNode *body = createBodyNode(parrentBody, symtable);
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
    function->body = parseBody(state, body, function->args, function->argsCount, createSymTable());
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
    BodyNode *trueBody = parseBody(state, body, NULL, 0, body->symTable);
    consume(list, TOKEN_DEINDENT);
    consume(list, TOKEN_EOL);
    consume(list, KEYWORD_ELSE);
    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);
    BodyNode *falseBody = parseBody(state, body, NULL, 0, body->symTable);
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
    BodyNode *body = parseBody(state, parrentBody, NULL, 0, parrentBody->symTable);
    consume(list, TOKEN_DEINDENT);
    return createWhileNode(condition, body);
}

AssignNode *parseAssign(ParserState *state, BodyNode *body) {
    Token *identifier = consume(state->list, TOKEN_IDENTIFIER);
    registerSymbol(body, identifier->value);
    TokenType type = popToken(state->list)->type;
    switch (type) {
    case OPERATOR_ASSIGN: return createAssignNode(identifier->value, ASSIGN_NONE, parseExpression(state, body));
    case OPERATOR_DIV_ASSIGN: return createAssignNode(identifier->value, ASSIGN_DIV, parseExpression(state, body));
    case OPERATOR_MUL_ASSIGN: return createAssignNode(identifier->value, ASSIGN_MUL, parseExpression(state, body));
    case OPERATOR_ADD_ASSIGN: return createAssignNode(identifier->value, ASSIGN_ADD, parseExpression(state, body));
    case OPERATOR_SUB_ASSIGN: return createAssignNode(identifier->value, ASSIGN_SUB, parseExpression(state, body));
    default: handleError(SyntaxError, "Expected assign operator, but got %s", convertTokenTypeToString(type));
    }
    return NULL;
}


StatementNode *parseStatement(ParserState *state, BodyNode *body) {
    Token *nextToken = peek(state->list);
    switch (nextToken->type) {
    case TOKEN_IDENTIFIER: 
        if (isTokenAsignOperator(peekNext(state->list, 1)))
            return craeteStatementNode(parseAssign(state, body), STATEMENT_ASSIGN);
        return craeteStatementNode(parseExpression(state, body), STATEMENT_EXPRESSION);
    case KEYWORD_WHILE: return craeteStatementNode(parseWhile(state, body), STATEMENT_WHILE);
    case KEYWORD_IF: return craeteStatementNode(parseCond(state, body), STATEMENT_IF);
    case KEYWORD_PASS: return craeteStatementNode(consume(state->list, KEYWORD_PASS), STATEMENT_PASS);
    case KEYWORD_RETURN:
            consume(state->list, KEYWORD_RETURN);
            if (peek(state->list)->type != TOKEN_EOL)
                return craeteStatementNode(parseExpression(state, body), STATEMENT_RETURN);
            return craeteStatementNode(NULL, STATEMENT_RETURN);
    default: return craeteStatementNode(parseExpression(state, body), STATEMENT_EXPRESSION);
    }
}

CallNode *parseCall(ParserState *state, BodyNode *body) {
    Token* identifier = consume(state->list, TOKEN_IDENTIFIER);
    if (!containsFunction(state, identifier->value)) {
        handleError(SemanticIdentifierError, "Unknown function identifier '%s' on line %d", identifier->value, identifier->line);
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
    if (argsCount != correctNumberOfArguments)
        handleError(SemanticArgumentError, "Wrong number of arguments one line %d. Should be %d, but got %d", identifier->line, correctNumberOfArguments, argsCount);
    consume(state->list, TOKEN_CPAREN);
    return call;
}

ExpressionNode *parseValue(ParserState *state, BodyNode *body) {
    Token *token = peek(state->list);
    switch(token->type) {
    case TOKEN_IDENTIFIER:
        if (peekNext(state->list, 1)->type == TOKEN_OPAREN)
            return createExpressionNode(parseCall(state, body), EXPRESSION_CALL);
        if (!containsSymbol(body, token->value))
            handleError(SemanticIdentifierError, "Uknown identier '%s' on line %d", token->value->value, token->line);
        return createExpressionNode(createValueNode(popToken(state->list)->value, VALUE_IDENTIFIER), EXPRESSION_VALUE);
    case DATA_TOKEN_INT: return createExpressionNode(createValueNode(popToken(state->list)->value, VALUE_CONSTANT), EXPRESSION_VALUE, EXPRESSION_DATA_TYPE_INT);
    case DATA_TOKEN_FLOAT: return createExpressionNode(createValueNode(popToken(state->list)->value, VALUE_CONSTANT), EXPRESSION_VALUE, EXPRESSION_DATA_TYPE_FLOAT);
    case DATA_TOKEN_STRING: return createExpressionNode(createValueNode(popToken(state->list)->value, VALUE_CONSTANT), EXPRESSION_VALUE, EXPRESSION_DATA_TYPE_STRING);
    case DATA_TOKEN_BOOL: return createExpressionNode(createValueNode(popToken(state->list)->value, VALUE_CONSTANT), EXPRESSION_VALUE, EXPRESSION_DATA_TYPE_BOOL);
    case DATA_TOKEN_NONE: return createExpressionNode(createValueNode(popToken(state->list)->value, VALUE_CONSTANT), EXPRESSION_VALUE, EXPRESSION_DATA_TYPE_NONE);
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
        token->type == OPERATOR_MUL;
}

ExpressionNode *parseOperation(ParserState *state, Stack *prefix, OperationType type, int line, BodyNode *body) {
    OperationNode *operation = createOperationNode(type);
    Token *token;
    ExpressionNode *operands[2];
    
    for (int i = 1; i >= 0; i--) {
        token = (Token *) pop(prefix);
        if(isTokenOperator(token)) operands[i] = parseOperation(state, prefix, operationTypeForToken(token), line, body);
        else if (isTokenValue(token)) operands[i] = parseValue(state, body);
        else handleError(SyntaxError, "Invalid expression on line %d", line);
    }
    
    operation->value1 = operands[0];
    operation->value2 = operands[1];
    ExpressionDataType dataType;
    if (operands[0]->dataType == EXPRESSION_DATA_TYPE_FLOAT && operands[1]->dataType == EXPRESSION_DATA_TYPE_INT) {
        
    }
    
    ExpressionDataType dataType;
    return createExpressionNode(operation, EXPRESSION_OPERATION, dataType);
}

bool isTokenExpression(Token *token) {
    return isTokenValue(token) || isTokenOperator(token) ||
        token->type == TOKEN_OPAREN || token->type == TOKEN_CPAREN;
}

bool hasStackHigherOrEqualPrecedence(Stack *operators, TokenType type) {
    return ((Token *)operators->items[operators->count - 1])->type >= type;
}

// End for expressions: "\n", ",", ")"
ExpressionNode *parseExpression(ParserState *state, BodyNode *body) {
    Stack *prefix = createStack();
    Stack *operators = createStack();
    int parensCount = 0;
    int line = peek(state->list)->line;
    while (isTokenExpression(peek(state->list))) {
        Token *token = peek(state->list);
        if (isTokenValue(token))
            push(prefix, createPrefixItem(parseValue(state, body), PREFIX_VALUE_EXPRESSION));
        else if (isTokenOperator(token)) {
            Token *token = popToken(state->list);
            while (operators->count != 0 && hasStackHigherOrEqualPrecedence(operators, token->type))
                push(prefix, createPrefixItem(pop(operators), PREFIX_OPERATOR_TOKEN));
            push(operators, token);
        } else if (token->type == TOKEN_OPAREN) {
            parensCount++;
            push(operators, popToken(state->list));
        } else if (token->type == TOKEN_CPAREN) {
            if (parensCount == 0)
                break;
            popToken(state->list);
            Token *operator;
            while (operators->count != 0 && (operator = pop(operators))->type != TOKEN_OPAREN ) {
                push(prefix, createPrefixItem(operator, PREFIX_OPERATOR_TOKEN));
            }
            parensCount--;
        }
    }
    while(operators->count != 0)
        push(prefix, createPrefixItem(pop(operators), PREFIX_OPERATOR_TOKEN));
    destroyStack(operators);
    PrefixItem *item = (PrefixItem *) pop(prefix);
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
    return contains(state->funcTable, identifier->value);
}

bool containsSymbol(BodyNode *body, String *identifier) {
    while (body != NULL) {
        if (contains(body->symTable, identifier->value))
            return true;
        body = body->parrentBody;
    }
    return false;
}

long getArgumentsCountForFuntion(ParserState *state, String *functionName) {
    HashTableItem *item = getHashTableItem(state->funcTable, functionName->value);
    long currentCount = (long) item->data;
    return currentCount;
}


void registerSymbol(BodyNode *body, String *identifier) {
    insertHashTableItem(body->symTable, identifier->value, NULL);
}

void registerFunction(ParserState *state, String *identifier, int argsCount) {
    long bigCount = (long)argsCount;
    void *data = (void *)bigCount;
    insertHashTableItem(state->funcTable, identifier->value, data);
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
