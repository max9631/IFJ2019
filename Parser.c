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

BodyNode *parseBody(TokenList *list) {
    return NULL;
}

FuncNode *parseFunc() {
    return NULL;
}

CondNode *parseCond(TokenList *list) {
    consume(list, KEYWORD_IF);

    ExpressionNode *condition = parseExpression(list);

    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);

    BodyNode *trueBody = parseBody(list);

    consume(list, TOKEN_DEINDENT);
    consume(list, KEYWORD_ELSE);
    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);

    BodyNode *falseBody = parseBody(list);

    consume(list, TOKEN_DEINDENT);

    return createCondNode(condition, trueBody, falseBody);
}

WhileNode *parseWhile(TokenList *list) {
    consume(list, KEYWORD_WHILE);

    ExpressionNode *condition = parseExpression(list);

    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);

    BodyNode *body = parseBody(list);

    consume(list, TOKEN_DEINDENT);

    return createWhileNode(condition, body);
}

StatementNode *parseStatement() {
    return NULL;
}

ExpressionNode *parseExpression(TokenList *list) {
    return NULL;
}

