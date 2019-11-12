#include "Parser.h"

MainNode *parseTokens(TokenList *list) {
    return NULL;
}

BodyNode *parseBody(TokenList *list) {
    return createBodyNode(); //TODO Implement
}

FuncNode *parseFunc(TokenList *list) {
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

    node->body = parseBody(list);
    consume(list, TOKEN_DEINDENT);

    return node;
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

/* --------------- DEBUG Functions ----------------- */
void printFuncNode(FuncNode *node) {
    if(!inDebugMode)
        return;

    printf("<FuncNode name=\"%s\" argsCount=\"%d\">\n", node->name->value, node->argsCount);
    
    for(int i = 0; i < node->argsCount; i++)
        printf("   <Argument index=\"%d\" name=\"%s\" />\n", i, node->args[i]->value);

    printf("</FuncNode>\n");
}
