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

BodyNode *parseBody() {
    return NULL;
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

AssignNode *parseAssign(ParserState *state) {
    Token *identifier = consume(state->list, TOKEN_IDENTIFIER);
    TokenType type = pop(state->list)->type;
    switch (type) {
    case OPERATOR_ASSIGN: return createAssignNode(identifier->value, ASSIGN_NONE, parseExpression());
    case OPERATOR_DIV_ASSIGN: return createAssignNode(identifier->value, ASSIGN_DIV, parseExpression());
    case OPERATOR_MUL_ASSIGN: return createAssignNode(identifier->value, ASSIGN_MUL, parseExpression());
    case OPERATOR_ADD_ASSIGN: return createAssignNode(identifier->value, ASSIGN_ADD, parseExpression());
    case OPERATOR_SUB_ASSIGN: return createAssignNode(identifier->value, ASSIGN_SUB, parseExpression());
    default: handleError(SyntaxError, "Expected assign operator, but got %s", convertTokenTypeToString(type));
    }
    return NULL;
}


StatementNode *parseStatement(ParserState *state) {
    switch (peek(state->list)->type) {
    case TOKEN_IDENTIFIER: 
        if (peekNext(state->list, 1)->type == TOKEN_OPAREN)
            return craeteStatementNode(parseExpression(), STATEMENT_EXPRESSION);
        else
            return craeteStatementNode(parseAssign(state), STATEMENT_ASSIGN);
    case KEYWORD_WHILE: return craeteStatementNode(parseWhile(), STATEMENT_WHILE);
    case KEYWORD_IF: return craeteStatementNode(parseCond(), STATEMENT_IF);
    case KEYWORD_PASS: return craeteStatementNode(NULL, STATEMENT_PASS);
    case KEYWORD_RETURN: return craeteStatementNode(NULL, STATEMENT_RETURN);
    default: return craeteStatementNode(parseExpression(), STATEMENT_EXPRESSION);
    }
    return NULL;
}

ExpressionNode *parseExpression() {
    return NULL;
}

