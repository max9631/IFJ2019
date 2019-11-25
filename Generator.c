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
    instructionCreateFrame();
    for(int i = function->argsCount-1; i >= 0; i-- ) {
        String *identifier = createString("TF@%s", function->args[i]);
        instructionDefVar(identifier);
        instructionPopStack(identifier);
    }
    instructionPushStack(createString("nil@nil"));
    generateBody(generator, function->body);
    instructionReturn();
}

void generateCond(Generator *generator, CondNode *condition) {
    String *condEndLabel = createString("_COND_JMP_LABEL_END_%d", generator->condCount++);
    String *condFalseLabel = createString("_COND_JMP_LABEL_FALSE_%d", generator->condCount++);

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
    String *whileLabel = createString("_WHILE_JMP_LABEL_%d", generator->whileCount++);
    String *whileLabel_end = createString("_WHILE_END_JMP_LABEL_%d", generator->whileCount);
    String *LocalFrame_val = createString("");

    instructionLabel(whileLabel);

    //Check the while condition
    generateExpression(generator, whileNode->condition);
    instructionJumpIfEqualsStack(whileLabel_end);

    //Generate while body
    generateBody(generator, whileNode->body);
    instructionJump(whileLabel);

    //While end
    instructionLabel(whileLabel_end);
    instructionPopStack(LocalFrame_val); //TODO: LocalFrame_val -- fix this for global?
    instructionPopStack(LocalFrame_val); //TODO: LocalFrame_val -- fix this for global?
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
    if(statement->statement != NULL) {
        instructionPopStack(generator->trashVar);
        ExpressionNode *exprNode = (ExpressionNode *)statement->statement;
        generateExpression(generator, exprNode);
    }

    instructionReturn();
}

void generateCall(Generator *generator, CallNode *call) {
    for(int i = 0; i < call->argsCount; i++){
        generateExpression(generator, call->expressions[i]);
    }
    instructionCall(call->identifier);
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
        case OPERATION_ADD: return instructionAddStack();
        case OPERATION_SUB:
            instructionSubStack();
        case OPERATION_MUL:
            instructionMulStack();
        case OPERATION_DIV:
            instructionDivStack();
        case OPERATION_EQUALS:
            instructionEqualsStack();
        case OPERATION_NOTEQUALS:
            instructionEqualsStack();
            instructionNotStack();
        case OPERATION_GREATER:
            instructionGreaterThanStack();
        case OPERATION_GREATEROREQUALS:
            instructionGreaterThanStack();
            generateExpression(generator, operation->value1);
            generateExpression(generator, operation->value2);
            instructionEqualsStack();
            instructionOrStack();
            break;
        case OPERATION_LESS:
            instructionLessThanStack();
        case OPERATION_LESSOREQUALS:
            instructionLessThanStack();
            generateExpression(generator, operation->value1);
            generateExpression(generator, operation->value2);
            instructionEqualsStack();
            instructionOrStack();
            break;
        case OPERATION_AND:
            instructionAndStack();
        case OPERATION_OR:
            instructionOrStack();
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
    }
}
