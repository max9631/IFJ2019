#ifndef GENERATOR_H
#define GENERATOR_H
#include "Node.h"
#include "Instruction.h"

typedef struct _Generator {
    int condCount;
    int whileCount;
} Generator;

Generator *createGenerator(void);

void generateMain(Generator *generator, MainNode *main);
void generateBody(Generator *generator, BodyNode *body);
void generateFunc(Generator *generator, FuncNode *function);
void generateCond(Generator *generator, CondNode *condition);
void generateWhile(Generator *generator, WhileNode *whileNode);
void generateAssign(Generator *generator, AssignNode *assign);
void generateStatement(Generator *generator, StatementNode *statement);
void generateCall(Generator *generator, CallNode *call);
void generateExpression(Generator *generator, ExpressionNode *expression);

#endif
