#include "Generator.h"

Generator *createGenerator() {
    Generator *generator = (Generator *)malloc(sizeof(Generator));
    generator->condCount = 0;
    generator->whileCount = 0;
    return generator;
}

void generateMain(Generator *generator, MainNode *main) {
    instructionJump(createString("_IFJ_START_"));
    for (int i = 0; i < main->functionsCount; i++)
        generateFunc(generator, main->functions[i]);
    instructionLabel(createString("_IFJ_START_"));
    generateBody(generator, main->body);
}

void generateBody(Generator *generator, BodyNode *body) {
    
}

void generateFunc(Generator *generator, FuncNode *function) {
    
}

void generateCond(Generator *generator, CondNode *condition) {
    
}

void generateWhile(Generator *generator, WhileNode *whileNode) {
    
}

void generateAssign(Generator *generator, AssignNode *assign) {
    
}

void generateStatement(Generator *generator, StatementNode *statement) {
    
}

void generateCall(Generator *generator, CallNode *call) {
    
}

void generateExpression(Generator *generator, ExpressionNode *expression) {
    
}

