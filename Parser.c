#include "Parser.h"

ParserState *createParserState(TokenList *list) {
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
            addPraserFunction(state, parseFunc());
        else
            addBodyStatement(body, parseStatement());
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

FuncNode *parseFunc() {
    return NULL;
}

CondNode *parseCond(ParserState *state) {
    TokenList *list = state->list;
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
    TokenList *list = state->list;
    consume(list, KEYWORD_WHILE);

    ExpressionNode *condition = parseExpression(state);

    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);

    BodyNode *body = parseBody(state);

    consume(list, TOKEN_DEINDENT);

    return createWhileNode(condition, body);
}

StatementNode *parseStatement() {
    return NULL;
}

ExpressionNode *parseExpression(ParserState *state) {
    return NULL;
}

