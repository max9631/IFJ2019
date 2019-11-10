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

    int argumentNamesCapacity = 10; // Initial value
    String **argumentNames = (String**)malloc(argumentNamesCapacity * sizeof(String*));

    int argumentCount = 0;
    while(true) {
        Token *variable = consume(list, TOKEN_IDENTIFIER);

        if(argumentNamesCapacity == argumentCount) {
            argumentNamesCapacity *= 2;
            String **tmp = realloc(argumentNames, argumentNamesCapacity * sizeof(String*));

            if(tmp == NULL) {
                handleError(InternalError, "Invalid memory pointer after reallocation.");
            }

            argumentNames = tmp;
        }

        argumentNames[argumentCount] = variable->value;
        argumentCount++;

        Token *tempToken = peek(list);
        if(tempToken->type == TOKEN_CPAREN) {
            consume(list, TOKEN_CPAREN);
            break;
        } else if (tempToken->type == TOKEN_COMMA) {
            consume(list, TOKEN_COMMA);
            continue;
        } else {
            handleError(SyntaxError, "Syntax error. Expected ')' or ',', but got '%s'", tempToken->value->value);
        }
    }

    consume(list, TOKEN_COLON);
    consume(list, TOKEN_EOL);
    consume(list, TOKEN_INDENT);

    BodyNode *body = parseBody(list);
    consume(list, TOKEN_DEINDENT);

    FuncNode *node = createFuncNode(name->value, body);
    node->argsCount = argumentCount;
    node->args = argumentNames;

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
