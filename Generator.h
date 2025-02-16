/*
 * Author(s): Jiří Veverka (xvever12), Michal Halabica (xhalab00), Adam Salih (xsalih01)
 * Project: Implementace prekladace imperativniho jazyka jazyka IFJ19
 * File: Generator.h, Generates assembly instructions from nodes
 */

#ifndef GENERATOR_H
#define GENERATOR_H
#include "Node.h"
#include "Instruction.h"
#include "String.h"

typedef struct _Generator {
    int labelCount;
    String *implicitConversionFunction;
    String *checkIfTypeTypeFunction;
    String *checkIfNotTypeTypeFunction;
    String *convertToFloatFunction;
    String *convertNilToNoneStrFunction;
    
    String *typeSafeAddFunction;
    String *typeSafeSubFunction;
    String *typeSafeMulFunction;
    String *typeSafeDivFunction;
    String *typeSafeEqualsFunction;
    String *typeSafeGreaterFunction;
    String *typeSafeLessFunction;
    String *typeSafeAndFunction;
    String *typeSafeOrFunction;
    String *typeSafeIdivFunction;
    String *typeSafeNotFunction;
    
    String *tmp1Var;
    String *tmp2Var;
    String *tmp3Var;
} Generator;

#include "Embedded.h"

Generator *createGenerator(void);

//Generates assembly code from nodes
void generateMain(Generator *generator, MainNode *main);
void generateBody(Generator *generator, BodyNode *body);
void generateFunc(Generator *generator, FuncNode *function);
void generateCond(Generator *generator, CondNode *condition);
void generateWhile(Generator *generator, WhileNode *whileNode);
void generateAssign(Generator *generator, AssignNode *assign);
void generateStatement(Generator *generator, StatementNode *statement);
void generateCall(Generator *generator, CallNode *call);
void generateExpression(Generator *generator, ExpressionNode *expression);
void generateReturn(Generator *generator, StatementNode *node);

//System functions

void generatePrint(Generator *generator, CallNode *call);
void generateInput(Generator *generator, String *type);
void generateLen(Generator *generator, ExpressionNode *expression);

#endif //GENERATOR_H
