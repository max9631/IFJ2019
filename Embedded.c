#include "Embedded.h"


void generateCheckExpressionTypesFunction(Generator *generator) {
    instructionLabel(generator->checkExpressionTypesFunctionLabel);
    instructionCreateFrame();
    
    String *needsFail = createString("TF@needsFail");
    String *arg1 = createString("TF@arg1");
    String *arg2 = createString("TF@arg2");
    String *type1 = createString("TF@type1");
    String *type2 = createString("TF@type2");
    
    instructionDefVar(needsFail);
    instructionDefVar(arg1);
    instructionDefVar(arg2);
    instructionDefVar(type1);
    instructionDefVar(type2);
    
    instructionPopStack(needsFail);
    instructionPopStack(arg2);
    instructionPopStack(arg1);
    instructionType(type1, arg1);
    instructionType(type2, arg2);
    
    String *notSameTypeLabel = createString("_%d_not_same_type", generator->labelCount++);
    
    instructionJumpIfNotEquals(notSameTypeLabel, type1, type2);
    
    instructionPushStack(arg1);
    instructionPushStack(arg2);
    instructionReturn();
    
    instructionLabel(notSameTypeLabel);
    
    String *leftCheckLabel = createString("_%d_left_check_not_int", generator->labelCount++);
    
    instructionEquals(generator->tmp1Var, type1, createString("string@int"));
    instructionEquals(generator->tmp2Var, type2, createString("string@float"));
    instructionAnd(generator->tmp3Var, generator->tmp1Var, generator->tmp2Var);
    instructionJumpIfNotEquals(leftCheckLabel, generator->tmp3Var, createString("bool@true"));
    
    instructionPushStack(arg1);
    instructionIntToFloatStack();
    instructionPushStack(arg2);
    instructionReturn();
    
    instructionLabel(leftCheckLabel);
    
    String *rightCheckLabel = createString("_%d_left_check_not_int", generator->labelCount++);
    
    instructionEquals(generator->tmp1Var, type1, createString("string@float"));
    instructionEquals(generator->tmp2Var, type2, createString("string@int"));
    instructionAnd(generator->tmp3Var, generator->tmp1Var, generator->tmp2Var);
    instructionJumpIfNotEquals(rightCheckLabel, generator->tmp3Var, createString("bool@true"));
    
    instructionPushStack(arg1);
    instructionPushStack(arg2);
    instructionIntToFloatStack();
    instructionReturn();
    
    instructionLabel(rightCheckLabel);
    
    String *doesntNeedFailLabel = createString("_%d_does_not_need_to_fail", generator->labelCount++);
    instructionJumpIfNotEquals(doesntNeedFailLabel, needsFail, createString("bool@true"));
    instructionExit(4);
    instructionLabel(doesntNeedFailLabel);
    
    instructionPushStack(arg1);
    instructionPushStack(arg2);
    instructionReturn();
}

void generateCheckTypeFunction(Generator *generator) {
    instructionLabel(generator->checkTypeFunctionLabel);
    instructionCreateFrame();
    
    String *type = createString("TF@type");
    String *arg = createString("TF@arg");
    String *argType = createString("TF@argType");
    
    instructionDefVar(type);
    instructionDefVar(arg);
    instructionPopStack(type);
    instructionPopStack(arg);
    instructionType(argType, arg);
    
    String *typeErrorLabel = createString("_%d_type_check_error", generator->labelCount++);
    
    instructionJumpIfNotEquals(typeErrorLabel, argType, type);
    
    instructionPushStack(arg);
    instructionReturn();
    
    instructionLabel(typeErrorLabel);
    instructionExit(4);
}

void generateConvertToFloatFunction(Generator *generator) {
    instructionLabel(generator->convertToFloatFunctionLabel);
    instructionCreateFrame();
    
    String *arg = createString("TF@arg");
    String *type = createString("TF@type");
    
    instructionDefVar(arg);
    instructionDefVar(type);
    instructionPopStack(arg);
    instructionType(type, arg);
    
    String *notfloatLabel = createString("_%d_not_float_cond", generator->labelCount++);
    
    instructionJumpIfNotEquals(notfloatLabel, type, createString("string@float"));
    
    instructionPushStack(arg);
    instructionReturn();
    
    instructionLabel(notfloatLabel);
    
    String *notIntLabel = createString("_%d_not_int_cond", generator->labelCount++);
    instructionJumpIfNotEquals(notIntLabel, type, createString("string@int"));
    
    instructionPushStack(arg);
    instructionIntToFloatStack();
    instructionReturn();
    
    instructionLabel(notIntLabel);
    
    instructionExit(4);
}

void generateAddOrConcat(Generator *generator) {
    // Call after expression type check
    instructionLabel(generator->addOrConcatFunction);
    int condID = generator->labelCount++;
    String *notString = createString("_%d_if__not_string", condID);
    instructionPopStack(generator->tmp1Var);
    instructionPushStack(generator->tmp1Var);
    instructionType(generator->tmp2Var, generator->tmp1Var);
    instructionJumpIfNotEquals(notString, generator->tmp2Var, createString("string@string"));
    instructionPopStack(generator->tmp2Var);
    instructionPopStack(generator->tmp1Var);
    instructionConcat(generator->tmp3Var, generator->tmp1Var, generator->tmp2Var);
    instructionPushStack(generator->tmp3Var);
    instructionReturn();
    instructionLabel(notString);
    instructionAddStack();
    instructionReturn();
    
}

void generateConvertNilToNoneString(Generator *generator) {
    String *notNilLabel = createString("_%d_not_nil_conversion", generator->labelCount);
    instructionLabel(generator->convertNilToNoneStrLabel);
    instructionPopStack(generator->tmp1Var);
    instructionJumpIfEquals(notNilLabel, generator->tmp1Var, createString("nil@nil"));
    instructionPushStack(createString("string@None"));
    instructionReturn();
    instructionLabel(notNilLabel);
    instructionPushStack(generator->tmp1Var);
    instructionReturn();
    
}

void generateChrFunction(Generator *generator) {
    int condID = generator->labelCount++;
    String *elseLabel = createString("_%d_if_else", condID);
    String *endLabel = createString("_%d_if_end", condID);
    
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
    int condID = generator->labelCount++;
    String *elseLabel = createString("_%d_if_else", condID);
    String *endLabel = createString("_%d_if_end", condID);
    
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
    
    int condID = generator->labelCount++;
    int whileID = generator->labelCount++;
    String *elseLabel = createString("_%d_if_else", condID);
    String *endLabel = createString("_%d_if_end", condID);
    String *whileLabel = createString("_%d_while", whileID);
    String *whileEndLabel = createString("_%d_while_end", whileID);
    
    String *str = createString("TF@s");
    String *subLen = createString("TF@n");
    String *index = createString("TF@i");
    String *length = createString("TF@length");
    
    instructionDefVar(str); //s
    instructionDefVar(subLen); //delka
    instructionDefVar(index); //index
    instructionDefVar(length);
    
    instructionPopStack(subLen);
    // TODO: check int
    instructionPopStack(index);
    // TODO: check int
    instructionPopStack(str);
    // TODO: check string
    instructionStrLen(length, str);
    
    instructionGreaterThan(generator->tmp1Var, index, length);
    instructionLessThan(generator->tmp2Var, index, createString("int@0"));
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
    instructionAdd(i, i, createString("int@1"));
    instructionJump(whileLabel);
    
    instructionLabel(whileEndLabel);
    instructionPushStack(finalStr);
    instructionReturn();
    
    instructionLabel(endLabel);
    
    instructionPushStack(createString("nil@nil"));
    instructionReturn();
}
