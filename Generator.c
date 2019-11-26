#include "Generator.h"

Generator *createGenerator() {
    Generator *generator = (Generator *)malloc(sizeof(Generator));
    generator->condCount = 0;
    generator->whileCount = 0;
    generator->tmp1Var = createString("GF@IFJ_TMP1");
    generator->tmp2Var = createString("GF@IFJ_TMP2");
    generator->tmp3Var = createString("GF@IFJ_TMP3");
    return generator;
}

void generateMain(Generator *generator, MainNode *main) {
    instructionDefVar(generator->tmp1Var);
    instructionDefVar(generator->tmp2Var);
    instructionDefVar(generator->tmp3Var);
    instructionCreateFrame();
    instructionJump(createString("_ifj_start"));
    generateChrFunction(generator);
    generateOrdFunction(generator);
    generateSubStringFunction(generator);
    for (int i = 0; i < main->functionsCount; i++)
        generateFunc(generator, main->functions[i]);
    instructionLabel(createString("_ifj_start"));
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
    instructionPushStack(createString("nil@nil"));
    generateBody(generator, function->body);
    instructionReturn();
}

void generateCond(Generator *generator, CondNode *condition) {
    String *condFalseLabel = createString("_%d_if_else", generator->condCount++);
    String *condEndLabel = createString("_%d_if_end_", generator->condCount++);

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
    String *whileLabel = createString("_%d_while", generator->whileCount++);
    String *whileLabel_end = createString("_%d_while_end", generator->whileCount++);
    
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
    if (assign->cretesVariable) {
        instructionDefVar(identifier);
    }
    switch (assign->operator) {
        case ASSIGN_NONE:
            break;
        case ASSIGN_ADD:
        case ASSIGN_SUB:
        case ASSIGN_DIV:
        case ASSIGN_MUL:
            instructionPushStack(identifier);
            break;
    }
    generateExpression(generator, assign->expression);
    switch (assign->operator) {
        case ASSIGN_NONE:
            break;
        case ASSIGN_ADD:
            instructionAddStack();
            break;
        case ASSIGN_SUB:
            instructionSubStack();
            break;
        case ASSIGN_DIV:
            instructionDivStack();
            break;
        case ASSIGN_MUL:
            instructionMulStack();
            break;
    }
    instructionPopStack(identifier);
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
        case STATEMENT_ASSIGN:;
            AssignNode *assignNode = (AssignNode *)statement->statement;
            generateAssign(generator, assignNode);
            break;
    }
}

void generateReturn(Generator *generator, StatementNode *statement) {
    if(statement->statement != NULL) {
        instructionPopStack(generator->tmp1Var);
        ExpressionNode *exprNode = (ExpressionNode *)statement->statement;
        generateExpression(generator, exprNode);
    }
    instructionReturn();
}

void generatePrint(Generator *generator, CallNode *call) {
    for (int i = 0; i < call->argsCount; i++) {
        if (i == 0) instructionWrite(createString("string@\032"));
        generateExpression(generator, call->expressions[i]);
        instructionPopStack(generator->tmp1Var);
        // TODO: check if not nil
        instructionWrite(generator->tmp1Var);
    }
    instructionWrite(createString("string@\010"));
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

void generateChrFunction(Generator *generator) {
    String *elseLabel = createString("_%d_if_else", generator->condCount++);
    String *endLabel = createString("_%d_if_end", generator->condCount++);
    
    instructionLabel(createString("chr"));
    String *position = createString("tf@position");
    instructionDefVar(position);
    instructionPopStack(position);
    // TODO: check if int
    
    // if 0  > expression && expression > 255: return None
    instructionPushStack(position);
    instructionPushStack(createString("int@0"));
    instructionLessThanStack();
    instructionPushStack(position);
    instructionPushStack(createString("int@255"));
    instructionGreaterThanStack();
    instructionAndStack();
    instructionPushStack(createString("bool@false"));
    instructionJumpIfEqualsStack(elseLabel);
    
    //if
    instructionPushStack(createString("nil@nil"));
    instructionJump(endLabel);
    
    //else
    instructionLabel(elseLabel);
    instructionPushStack(position);
    instructionIntToCharStack();
    instructionLabel(endLabel);
    instructionReturn();
}

void generateOrdFunction(Generator *generator) {
    String *elseLabel = createString("_%d_if_else", generator->condCount++);
    String *endLabel = createString("_%d_if_end", generator->condCount++);
    
    instructionLabel(createString("ord"));
    String *str = createString("tf@str");
    String *position = createString("tf@position");
    String *len = createString("tf@len");
    
    instructionDefVar(str);
    instructionDefVar(position);
    instructionDefVar(len);
    
    instructionPopStack(position);
    // TODO: Check if int
    instructionPopStack(str);
    // TODO: Check if string
    instructionStrLen(len, generator->tmp1Var);
    
    instructionPopStack(generator->tmp2Var); // position
    instructionPopStack(generator->tmp1Var); // value
    instructionStrLen(generator->tmp3Var, generator->tmp1Var); //strlen
    
    // if 0  > position && expression > len(str): return None
    instructionPushStack(position);
    instructionPushStack(createString("int@0"));
    instructionLessThanStack();
    instructionPushStack(position);
    instructionPushStack(len);
    instructionGreaterThanStack();
    instructionAndStack();
    instructionPushStack(createString("bool@false"));
    instructionJumpIfEqualsStack(elseLabel);
    instructionPushStack(createString("nil@nil"));
    instructionJump(endLabel);
    
    //else
    instructionLabel(elseLabel);
    instructionGetChar(generator->tmp3Var, generator->tmp1Var, generator->tmp3Var);
    instructionIntToChar(generator->tmp1Var, generator->tmp3Var);
    instructionPushStack(generator->tmp1Var);
    instructionLabel(endLabel);
    
    instructionReturn();

}

void generateSubStringFunction(Generator *generator) {
    instructionLabel(createString("substr"));
    instructionCreateFrame();
    
    String *elseLabel = createString("_%d_if_else", generator->condCount++);
    String *endLabel = createString("_%d_if_end", generator->condCount++);
    String *whileLabel = createString("_%d_while", generator->whileCount++);
    String *whileEndLabel = createString("_%d_while_end", generator->whileCount++);
    
    String *str = createString("TF@s");
    String *subLen = createString("TF@n");
    String *index = createString("TF@i");
    String *length = createString("TF@length");
    
    instructionDefVar(str);
    instructionDefVar(subLen);
    instructionDefVar(index);
    instructionDefVar(length);
    
    instructionPopStack(subLen);
    // TODO: check int
    instructionPopStack(index);
    // TODO: check int
    instructionPopStack(str);
    // TODO: check string
    instructionStrLen(length, str);
    
    instructionLessThan(generator->tmp1Var, index, length);
    instructionGreaterThan(generator->tmp2Var, index, createString("int@0"));
    instructionLessThan(generator->tmp3Var, subLen, createString("int@0"));
    
    // if
    instructionPushStack(generator->tmp1Var);
    instructionPushStack(generator->tmp2Var);
    instructionAndStack();
    instructionPushStack(generator->tmp3Var);
    instructionOrStack();
    instructionPushStack(createString("bool@false"));
    instructionJumpIfEqualsStack(elseLabel);
    // if true
    instructionPushStack(createString("nil@nil"));
    instructionReturn();
    // else not true
    instructionLabel(elseLabel);
    
    String *finalStr = createString("TF@ch");
    instructionDefVar(finalStr);
    instructionMove(finalStr, createString("string@"));
    
    String *i = createString("TF@index");
    instructionDefVar(i);
    instructionMove(i, index);
    
    instructionLabel(whileLabel);
    instructionPushStack(i);
    instructionPushStack(index);
    instructionPushStack(subLen);
    instructionAddStack();
    instructionLessThanStack();
    instructionPushStack(i);
    instructionPushStack(length);
    instructionLessThanStack();
    instructionAndStack();
    instructionPushStack(createString("bool@false"));
    instructionJumpIfEqualsStack(whileEndLabel);
    instructionGetChar(generator->tmp1Var, str, i);
    instructionConcat(finalStr, finalStr, generator->tmp1Var);
    instructionJump(whileLabel);
    
    instructionLabel(whileEndLabel);
    instructionPushStack(finalStr);
    instructionReturn();
    
    instructionLabel(endLabel);
    
    instructionPushStack(createString("nil@nil"));
    instructionReturn();
}

void generateCall(Generator *generator, CallNode *call) {
    if (stringEquals(call->identifier, "print")) generatePrint(generator, call);
    else if (stringEquals(call->identifier, "inputi")) generateInput(generator, createString("string@int"));
    else if (stringEquals(call->identifier, "inputs")) generateInput(generator, createString("string@string"));
    else if (stringEquals(call->identifier, "inputf")) generateInput(generator, createString("string@float"));
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
            case EXPRESSION_DATA_TYPE_FLOAT: return createString("float@%s", value->value.floatVal->value);
            case EXPRESSION_DATA_TYPE_BOOL: return createString("bool@%s", value->value.boolVal->value);
            case EXPRESSION_DATA_TYPE_STRING: return createString("string@\"%s\"", value->value.stringVal->value);
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
            instructionAddStack();
            break;
        case OPERATION_SUB:
            instructionSubStack();
            break;
        case OPERATION_MUL:
            instructionMulStack();
            break;
        case OPERATION_DIV:
            instructionDivStack();
            break;
        case OPERATION_EQUALS:
            instructionEqualsStack();
            break;
        case OPERATION_NOTEQUALS:
            instructionEqualsStack();
            instructionNotStack();
            break;
        case OPERATION_GREATER:
            instructionGreaterThanStack();
            break;
        case OPERATION_GREATEROREQUALS:
            instructionGreaterThanStack();
            generateExpression(generator, operation->value1);
            generateExpression(generator, operation->value2);
            instructionEqualsStack();
            instructionOrStack();
            break;
        case OPERATION_LESS:
            instructionLessThanStack();
            break;
        case OPERATION_LESSOREQUALS:
            instructionLessThanStack();
            generateExpression(generator, operation->value1);
            generateExpression(generator, operation->value2);
            instructionEqualsStack();
            instructionOrStack();
            break;
        case OPERATION_AND:
            instructionAndStack();
            break;
        case OPERATION_OR:
            instructionOrStack();
            break;
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
            generateExpression(generator, operation->value1);
            generateExpression(generator, operation->value2);
            
            // TODO: generate code for type checking. If data types of operand are not compatible, exit with code 4.
            stackInstructionForOperationType(generator, operation);
            break;
        case EXPRESSION_CONVERSION_INT_TO_FLOAT:
            generateExpression(generator, expression->expression);
            instructionIntToFloatStack();
            break;
    }
}
