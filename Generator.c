/*
 * Author(s): Jiří Veverka (xvever12), Michal Halabica (xhalab00), Adam Salih (xsalih01)
 * Project: Implementace prekladace imperativniho jazyka jazyka IFJ19
 * File: Generator.c, Generates assembly instructions from nodes
 */

#include "Generator.h"

Generator *createGenerator() {
    Generator *generator = (Generator *)malloc(sizeof(Generator));
    generator->labelCount = 0;
    generator->tmp1Var = createString("GF@IFJ_TMP1");
    generator->tmp2Var = createString("GF@IFJ_TMP2");
    generator->tmp3Var = createString("GF@IFJ_TMP3");
    
    generator->typeSafeAddFunction = createString("_EmbeddedTypeSafeAddFunction");
    generator->typeSafeSubFunction = createString("_EmbeddedTypeSafeSubFunction");
    generator->typeSafeMulFunction = createString("_EmbeddedTypeSafeMulFunction");
    generator->typeSafeDivFunction = createString("_EmbeddedTypeSafeDivFunction");
    generator->typeSafeEqualsFunction = createString("_EmbeddedTypeSafeEqualsFunction");
    generator->typeSafeGreaterFunction = createString("_EmbeddedTypeSafeGreaterFunction");
    generator->typeSafeLessFunction = createString("_EmbeddedTypeSafeLessFunction");
    generator->typeSafeAndFunction = createString("_EmbeddedTypeSafeAndFunction");
    generator->typeSafeOrFunction = createString("_EmbeddedTypeSafeOrFunction");
    generator->typeSafeIdivFunction = createString("_EmbeddedTypeSafeIdivFunction");
    generator->typeSafeNotFunction = createString("_EmbeddedTypeSafeNotFunction");
    
    generator->implicitConversionFunction = createString("_EmbeddedExpressionTypeCheck");
    generator->checkIfTypeTypeFunction = createString("_EmbeddedCheckIfType");
    generator->checkIfNotTypeTypeFunction= createString("_EmbeddedCheckIfNotType");
    generator->convertToFloatFunction = createString("_EmbeddedConvertToFloat");
    generator->convertNilToNoneStrFunction = createString("_EmbeddedConvertNilToStr");
    return generator;
}

void generateDefVarInBody(BodyNode *body) {
    for (int i = 0; i < body->statementsCount; i++) {
        StatementNode *statement = body->statements[i];
        if (statement == NULL) continue;
        if (statement->statement == NULL) continue;
        switch (statement->statementType) {
        case STATEMENT_ASSIGN:;
            AssignNode *assign = (AssignNode *)statement->statement;
            if (assign->cretesVariable) {
                char *frame = assign->isGlobal ? "GF" : "TF";
                instructionDefVar(createString("%s@%s", frame, assign->identifier->value));
            }
            break;
        case STATEMENT_WHILE:;
            WhileNode *node = (WhileNode *)statement->statement;
            generateDefVarInBody(node->body);
            break;
        case STATEMENT_IF:;
            CondNode *condition = (CondNode *)statement->statement;
            generateDefVarInBody(condition->trueBody);
            generateDefVarInBody(condition->falseBody);
            break;
        case STATEMENT_EXPRESSION:
        case STATEMENT_RETURN:
        case STATEMENT_PASS:
            continue;
        }
    }
}

void generateMain(Generator *generator, MainNode *main) {
    instructionIFJSign();
    instructionDefVar(generator->tmp1Var);
    instructionDefVar(generator->tmp2Var);
    instructionDefVar(generator->tmp3Var);
    instructionCreateFrame();
    instructionJump(createString("_ifj_start"));
    generateConvertNilToNoneString(generator);
    generateImplicitConversionFunction(generator);
    generateCheckIfTypeFunction(generator);
    generateCheckIfNotTypeFunction(generator);
    generateConvertToFloatFunction(generator);

    generateTypeSafeAddFunction(generator);
    generateTypeSafeSubFunction(generator);
    generateTypeSafeMulFunction(generator);
    generateTypeSafeDivFunction(generator);
    generateTypeSafeEqualsFunction(generator);
    generateTypeSafeGreaterFunction(generator);
    generateTypeSafeLessFunction(generator);
    generateTypeSafeAndFunction(generator);
    generateTypeSafeOrFunction(generator);
    generateTypeSafeIdivFunction(generator);
    
    generateChrFunction(generator);
    generateOrdFunction(generator);
    generateSubStringFunction(generator);
    for (int i = 0; i < main->functionsCount; i++)
        generateFunc(generator, main->functions[i]);
    instructionLabel(createString("_ifj_start"));
    generateDefVarInBody(main->body);
    generateBody(generator, main->body);
}

void generateBody(Generator *generator, BodyNode *body) {
    for (int i = 0; i < body->statementsCount; i++)
        generateStatement(generator, body->statements[i]);
}

void generateFunc(Generator *generator, FuncNode *function) {
    instructionLabel(function->name);
    instructionCreateFrame();
    for(int i = function->argsCount-1; i >= 0; i-- ) {
        String *identifier = createString("TF@%s", function->args[i]->value);
        instructionDefVar(identifier);
        instructionPopStack(identifier);
    }
    generateDefVarInBody(function->body);
    generateBody(generator, function->body);
    instructionPushStack(createString("nil@nil"));
    instructionReturn();
}

void generateCond(Generator *generator, CondNode *condition) {
    int coundId = generator->labelCount++;
    String *condFalseLabel = createString("_%d_if_else", coundId);
    String *condEndLabel = createString("_%d_if_end_", coundId);

    generateExpression(generator, condition->condition);
    instructionPushStack(createString("bool@false"));
    instructionJumpIfEqualsStack(condFalseLabel);

    //if
    generateBody(generator, condition->trueBody);
    instructionJump(condEndLabel);

    //else
    instructionLabel(condFalseLabel);
    generateBody(generator, condition->falseBody);

    instructionLabel(condEndLabel);
}

void generateWhile(Generator *generator, WhileNode *whileNode) {
    int whileId = generator->labelCount++;
    String *whileLabel = createString("_%d_while", whileId);
    String *whileLabel_end = createString("_%d_while_end", whileId);

    instructionLabel(whileLabel);

    generateExpression(generator, whileNode->condition);
    instructionPushStack(createString("bool@false"));
    instructionJumpIfEqualsStack(whileLabel_end);

    generateBody(generator, whileNode->body);

    instructionJump(whileLabel);
    instructionLabel(whileLabel_end);
}

void generateAssign(Generator *generator, AssignNode *assign) {
    char *frame = assign->isGlobal ? "GF" : "TF";
    String *identifier = createString("%s@%s", frame, assign->identifier->value);
    if (assign->operator != ASSIGN_NONE) {
        instructionPushStack(identifier);
    }
    generateExpression(generator, assign->expression);
    switch (assign->operator) {
        case ASSIGN_NONE:
            break;
        case ASSIGN_ADD:
            instructionPushFrame();
            instructionCall(generator->typeSafeAddFunction);
            instructionPopFrame();
            break;
        case ASSIGN_SUB:
            instructionPushFrame();
            instructionCall(generator->typeSafeSubFunction);
            instructionPopFrame();
            break;
        case ASSIGN_DIV:
            instructionPushFrame();
            instructionCall(generator->typeSafeDivFunction);
            instructionPopFrame();
            break;
        case ASSIGN_MUL:
            instructionPushFrame();
            instructionCall(generator->typeSafeMulFunction);
            instructionPopFrame();
            break;
    }
    instructionPopStack(identifier);
}

void generateStatement(Generator *generator, StatementNode *statement) {
    if (statement == NULL) return;
    switch (statement->statementType) {
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
            if (exprNode->type == EXPRESSION_CALL) {
                generateExpression(generator, exprNode);
                instructionPopStack(generator->tmp1Var);
            }
            break;
        case STATEMENT_ASSIGN:;
            AssignNode *assignNode = (AssignNode *)statement->statement;
            generateAssign(generator, assignNode);
            break;
    }
}

void generateReturn(Generator *generator, StatementNode *statement) {
    if(statement->statement != NULL) {
        ExpressionNode *exprNode = (ExpressionNode *)statement->statement;
        generateExpression(generator, exprNode);
    } else {
        instructionPushStack(createString("nil@nil"));
    }
    instructionReturn();
}

void generatePrint(Generator *generator, CallNode *call) {
    for (int i = 0; i < call->argsCount; i++) {
        if (i != 0) instructionWrite(createString("string@\\032"));
        generateExpression(generator, call->expressions[i]);
        instructionCall(generator->convertNilToNoneStrFunction);
        instructionPopStack(generator->tmp1Var);
        instructionWrite(generator->tmp1Var);
    }
    instructionWrite(createString("string@\\010"));
    instructionPushStack(createString("nil@nil"));
}

void generateInput(Generator *generator, String *type) {
    instructionRead(generator->tmp1Var, type);
    instructionPushStack(generator->tmp1Var);
}

void generateLen(Generator *generator, ExpressionNode *expression) {
    generateExpression(generator, expression);
    //TODO: Check if expression is String
    instructionPopStack(generator->tmp1Var);
    instructionStrLen(generator->tmp2Var, generator->tmp1Var);
    instructionPushStack(generator->tmp2Var);
}

void generateCall(Generator *generator, CallNode *call) {
    if (stringEquals(call->identifier, "print")) generatePrint(generator, call);
    else if (stringEquals(call->identifier, "inputi")) generateInput(generator, createString("int"));
    else if (stringEquals(call->identifier, "inputs")) generateInput(generator, createString("string"));
    else if (stringEquals(call->identifier, "inputf")) generateInput(generator, createString("float"));
    else if (stringEquals(call->identifier, "len")) generateLen(generator, call->expressions[0]);
    else {
        for(int i = 0; i < call->argsCount; i++){
            generateExpression(generator, call->expressions[i]);
        }
        instructionPushFrame();
        instructionCall(call->identifier);
        instructionPopFrame();
    }
}

String *convertValueToIFJ(ValueNode *value, ExpressionDataType dataType) {
    if (value->type == VALUE_CONSTANT) {
        switch (dataType) {
            case EXPRESSION_DATA_TYPE_NONE: return createString("nil@nil");
            case EXPRESSION_DATA_TYPE_INT: return createString("int@%s", value->value.intVal->value);
            case EXPRESSION_DATA_TYPE_FLOAT: return createString("float@%s", convertFloatToHexadecimal(value->value.floatVal)->value);
            case EXPRESSION_DATA_TYPE_BOOL: return createString("bool@%s", convertBoolToLowercase(value->value.boolVal)->value);
            case EXPRESSION_DATA_TYPE_STRING: return createString("string@%s", convertStringCharsToHexadecimal(value->value.stringVal)->value);
            case EXPRESSION_DATA_TYPE_UNKNOWN: return createString("nil@nil");
        }
    } else if (value->type == VALUE_VARIABLE) {
        char *prefix = value->isGlobal ? "GF" : "TF";
        return createString("%s@%s", prefix, value->value.identifier->value);
    }
    return createString("nil@nil");
}

void stackInstructionForOperationType(Generator *generator, OperationNode *operation) {
    switch (operation->type) {
        case OPERATION_ADD:
            instructionPushFrame();
            instructionCall(generator->typeSafeAddFunction);
            instructionPopFrame();
            break;
        case OPERATION_SUB:
            instructionPushFrame();
            instructionCall(generator->typeSafeSubFunction);
            instructionPopFrame();
            break;
        case OPERATION_MUL:
            instructionPushFrame();
            instructionCall(generator->typeSafeMulFunction);
            instructionPopFrame();
            break;
        case OPERATION_DIV:
            instructionPushFrame();
            instructionCall(generator->typeSafeDivFunction);
            instructionPopFrame();
            break;
        case OPERATION_IDIV:
            instructionPushFrame();
            instructionCall(generator->typeSafeIdivFunction);
            instructionPopFrame();
            break;
        case OPERATION_EQUALS:
            instructionPushFrame();
            instructionCall(generator->typeSafeEqualsFunction);
            instructionPopFrame();
            break;
        case OPERATION_NOTEQUALS:
            instructionPushFrame();
            instructionCall(generator->typeSafeEqualsFunction);
            instructionPopFrame();
            instructionNotStack();
            break;
        case OPERATION_GREATER:
            instructionPushFrame();
            instructionCall(generator->typeSafeGreaterFunction);
            instructionPopFrame();
            break;
        case OPERATION_GREATEROREQUALS:
            instructionPushFrame();
            instructionCall(generator->typeSafeGreaterFunction);
            instructionPopFrame();
            
            generateExpression(generator, operation->value1);
            generateExpression(generator, operation->value2);
            
            instructionPushFrame();
            instructionCall(generator->typeSafeEqualsFunction);
            instructionPopFrame();
            instructionOrStack();
            break;
        case OPERATION_LESS:
            instructionPushFrame();
            instructionCall(generator->typeSafeLessFunction);
            instructionPopFrame();
            break;
        case OPERATION_LESSOREQUALS:
            instructionPushFrame();
            instructionCall(generator->typeSafeLessFunction);
            instructionPopFrame();
            
            generateExpression(generator, operation->value1);
            generateExpression(generator, operation->value2);
            
            instructionPushFrame();
            instructionCall(generator->typeSafeEqualsFunction);
            instructionPopFrame();
            instructionOrStack();
            break;
        case OPERATION_AND:
            instructionPushFrame();
            instructionCall(generator->typeSafeAndFunction);
            instructionPopFrame();
            break;
        case OPERATION_OR:
            instructionPushFrame();
            instructionCall(generator->typeSafeOrFunction);
            instructionPopFrame();
            break;
        case OPERATION_NOT:
        instructionPushFrame();
        instructionCall(generator->typeSafeNotFunction);
        instructionPopFrame();
            break;
    }
}

bool isOneOperandOperations(OperationNode *operation) {
    return operation->type == OPERATION_NOT;
}

bool requiresFail(OperationNode *operation) {
    switch (operation->type) {
    case OPERATION_ADD:
    case OPERATION_SUB:
    case OPERATION_MUL:
    case OPERATION_DIV:
    case OPERATION_IDIV:
    case OPERATION_GREATER:
    case OPERATION_GREATEROREQUALS:
    case OPERATION_LESS:
    case OPERATION_LESSOREQUALS:
        return true;
    case OPERATION_EQUALS:
    case OPERATION_NOTEQUALS:
    case OPERATION_AND:
    case OPERATION_OR:
    case OPERATION_NOT:
    default:
        return false;
    }
}

void generateExpression(Generator *generator, ExpressionNode *expression) {
    switch (expression->type) {
        case EXPRESSION_CALL:;
            CallNode *call = (CallNode *)expression->expression;
            generateCall(generator, call);
            break;
        case EXPRESSION_VALUE:;
            ValueNode *value = (ValueNode *) expression->expression;
            instructionPushStack(convertValueToIFJ(value, expression->dataType));
            break;
        case EXPRESSION_OPERATION:;
            OperationNode *operation = (OperationNode *) expression->expression;
            
            if (isOneOperandOperations(operation)) {
                generateExpression(generator, operation->value1);
                stackInstructionForOperationType(generator, operation);
                return;
            }
            
            generateExpression(generator, operation->value1);
            generateExpression(generator, operation->value2);
            
            stackInstructionForOperationType(generator, operation);
            break;
        case EXPRESSION_CONVERSION_INT_TO_FLOAT:
            generateExpression(generator, expression->expression);
            instructionIntToFloatStack();
            break;
    }
}
