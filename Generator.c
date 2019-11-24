#include "Generator.h"

Generator *createGenerator() {
    Generator *generator = (Generator *)malloc(sizeof(Generator));
    generator->condCount = 0;
    generator->whileCount = 0;
    generator->trashVar = createString("GF@IFJ_TRASH");
    return generator;
}

void generateMain(Generator *generator, MainNode *main) {
    instructionDefVar(generator->trashVar);
    instructionJump(createString("_IFJ_START_"));
    for (int i = 0; i < main->functionsCount; i++)
        generateFunc(generator, main->functions[i]);
    instructionLabel(createString("_IFJ_START_"));
    generateBody(generator, main->body);
}

void generateBody(Generator *generator, BodyNode *body) {
    for (int i = 0; i < body->statementsCount; i++)
        generateStatement(generator, body->statements[i]);
}

void generateFunc(Generator *generator, FuncNode *function) {
    instructionLabel(function->name);
    generateBody(generator, function->body);
    instructionReturn();
}

void generateCond(Generator *generator, CondNode *condition) {
    String *condTrueLabel = createString("_COND_JMP_LABEL_TRUE_%d", generator->condCount++);
    String *condFalseLabel = createString("_COND_JMP_LABEL_FALSE_%d", generator->condCount);

    instructionJumpIfEquls(condTrueLabel, condition->condition, "bool@true");
    instructionJumpIfNotEqulas(condFalseLabel, condition->condition, "bool@false");

    instructionLabel(condTrueLabel);
    generateBody(generator, condition->trueBody);
    instructionReturn();

    instructionLabel(condFalseLabel);
    generateBody(generator, condition->falseBody);
    instructionReturn();
}

void generateWhile(Generator *generator, WhileNode *whileNode) {
    String *whileLabel = createString("_WHILE_JMP_LABEL_%d", generator->whileCount++);
    String *LocalFrame_val = createString("");
    instructionLabel(whileLabel);
    generateExpression(generator, whileNode->condition);
    instructionPopStack(LocalFrame_val);
    instructionJumpIfEquls(whileLabel, LocalFrame_val, "bool@true");
    instructionReturn();
}

void generateAssign(Generator *generator, AssignNode *assign) {
    
}

void generateStatement(Generator *generator, StatementNode *statement) {
    switch (statement->type) {
        case STATEMENT_IF:;
            CondNode *condNode = (CondNode *)statement->statement;
            generateCond(generator, condNode);
            break;
        case STATEMENT_WHILE:;
            WhileNode *whileNode = (WhileNode *)statement->statement;
            generateWhile(generator, whileNode);
            break;
        case STATEMENT_PASS:
            break;
        case STATEMENT_RETURN:;
            generateReturn(generator, statement);
            break;
        case STATEMENT_EXPRESSION:;
            ExpressionNode *exprNode = (ExpressionNode *)statement->statement;
            generateExpression(generator, exprNode);
            break;
        case STATEMENT_ASSIGN:
        case STATEMENT_ASSIGN_ADD:
        case STATEMENT_ASSIGN_DIV:
        case STATEMENT_ASSIGN_MUL:
        case STATEMENT_ASSIGN_SUB:;
            AssignNode *assignNode = (AssignNode *)statement->statement;
            generateAssign(generator, assignNode);
            break;
    }
}

void generateReturn(Generator *generator, StatementNode *statement) {
    instructionPopStack(generator->trashVar);

    if(statement->statement != NULL) {
        ExpressionNode *exprNode = (ExpressionNode *)statement->statement;
        generateExpression(generator, exprNode);
    }

    instructionReturn();
}

void generateCall(Generator *generator, CallNode *call) {
    
}

void generateExpression(Generator *generator, ExpressionNode *expression) {
    // TODO: generate code for type checking. If data types of operand are not compatible, exit with code 4.
}
