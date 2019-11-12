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


BodyNode *parseBody(ParserState *state) {
    BodyNode *node = createBodyNode();
    while (peek(state->list)->type != TOKEN_DEINDENT) 
        addBodyStatement(node, parseStatement(state->list));
    return node;
}

FuncNode *parseFunc() {
    return NULL;
}

CondNode *parseCond() {
    return NULL;
}

WhileNode *parseWhile() {
    return NULL;
}

StatementNode *parseStatement() {
    return NULL;
}

ExpressionNode *parseExpression() {
    return NULL;
}

