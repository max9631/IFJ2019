#include "Parser.h"

ParserState *createParserState(List *list) {
    ParserState *state = (ParserState *)malloc(sizeof(ParserState));
    state->list = list;
    state->main = NULL;
    state->funcTable = createHashTable();
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
    state->main = createMainNode(createBodyNode());
    BodyNode *body = state->main->body;
    while (peek(state->list)->type != TOKEN_EOF) {
        if (peek(state->list)->type == KEYWORD_DEF)
            addPraserFunction(state, parseFunc(state));
        else
            addBodyStatement(body, parseStatement(state));
        consume(state->list, TOKEN_EOL);
    }
    return state->main;
}

BodyNode *parseBody(ParserState *state) {
    BodyNode *node = createBodyNode();
    while (peek(state->list)->type != TOKEN_DEINDENT) 
        addBodyStatement(node, parseStatement(state));
    return node;
}

FuncNode *parseFunc(ParserState *state) {
    List *list = state->list;
    consume(list, KEYWORD_DEF);
    
    Token *name = consume(list, TOKEN_IDENTIFIER);
    consume(list, TOKEN_OPAREN);

    FuncNode *node = createFuncNode(name->value, NULL);

    while(true) {
        Token *variable = consume(list, TOKEN_IDENTIFIER);
        addFunctionArgument(node, variable->value);

        if(isNextTokenOfType(list, TOKEN_CPAREN)) {
            consume(list, TOKEN_CPAREN);
            break;
        } else if (isNextTokenOfType(list, TOKEN_COMMA)) {
            consume(list, TOKEN_COMMA);
            continue;
        } else {
            handleError(SyntaxError, "Syntax error. Expected ')' or ',', in function %s", name->value->value);
        }
    }

    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);

    node->body = parseBody(state);
    consume(list, TOKEN_DEINDENT);

    return node;
}

CondNode *parseCond(ParserState *state) {
    List *list = state->list;
    consume(list, KEYWORD_IF);

    ExpressionNode *condition = parseExpression(state);

    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);

    BodyNode *trueBody = parseBody(state);

    consume(list, TOKEN_DEINDENT);
    consume(list, KEYWORD_ELSE);
    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);

    BodyNode *falseBody = parseBody(state);

    consume(list, TOKEN_DEINDENT);

    return createCondNode(condition, trueBody, falseBody);
}

WhileNode *parseWhile(ParserState *state) {
    List *list = state->list;
    consume(list, KEYWORD_WHILE);

    ExpressionNode *condition = parseExpression(state);

    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);

    BodyNode *body = parseBody(state);

    consume(list, TOKEN_DEINDENT);

    return createWhileNode(condition, body);
}

AssignNode *parseAssign(ParserState *state) {
    Token *identifier = consume(state->list, TOKEN_IDENTIFIER);
    TokenType type = popToken(state->list)->type;
    switch (type) {
    case OPERATOR_ASSIGN: return createAssignNode(identifier->value, ASSIGN_NONE, parseExpression(state));
    case OPERATOR_DIV_ASSIGN: return createAssignNode(identifier->value, ASSIGN_DIV, parseExpression(state));
    case OPERATOR_MUL_ASSIGN: return createAssignNode(identifier->value, ASSIGN_MUL, parseExpression(state));
    case OPERATOR_ADD_ASSIGN: return createAssignNode(identifier->value, ASSIGN_ADD, parseExpression(state));
    case OPERATOR_SUB_ASSIGN: return createAssignNode(identifier->value, ASSIGN_SUB, parseExpression(state));
    default: handleError(SyntaxError, "Expected assign operator, but got %s", convertTokenTypeToString(type));
    }
    return NULL;
}


StatementNode *parseStatement(ParserState *state) {
    switch (peek(state->list)->type) {
    case TOKEN_IDENTIFIER: 
        if (peekNext(state->list, 1)->type == TOKEN_OPAREN)
            return craeteStatementNode(parseExpression(state), STATEMENT_EXPRESSION);
        else
            return craeteStatementNode(parseAssign(state), STATEMENT_ASSIGN);
    case KEYWORD_WHILE: return craeteStatementNode(parseWhile(state), STATEMENT_WHILE);
    case KEYWORD_IF: return craeteStatementNode(parseCond(state), STATEMENT_IF);
    case KEYWORD_PASS: return craeteStatementNode(NULL, STATEMENT_PASS);
    case KEYWORD_RETURN: return craeteStatementNode(NULL, STATEMENT_RETURN);
    default: return craeteStatementNode(parseExpression(state), STATEMENT_EXPRESSION);
    }
    return NULL;
}

ExpressionNode *parseExpression(ParserState *state) {
    return NULL;
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
