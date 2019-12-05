#include "Embedded.h"


void generateImplicitConversionFunction(Generator *generator) {
    instructionLabel(generator->implicitConversionFunction);
    instructionCreateFrame();
    
    String *arg1 = createString("TF@arg1");
    String *arg2 = createString("TF@arg2");
    String *type1 = createString("TF@type1");
    String *type2 = createString("TF@type2");
    
    instructionDefVar(arg1);
    instructionDefVar(arg2);
    instructionDefVar(type1);
    instructionDefVar(type2);
    instructionPopStack(arg2);
    instructionPopStack(arg1);
    instructionType(type1, arg1);
    instructionType(type2, arg2);
    
    String *notIntFloat = createString("_%d_if_not_int_float", generator->labelCount++);
    instructionEquals(generator->tmp1Var, type1, createString("string@int"));
    instructionEquals(generator->tmp2Var, type2, createString("string@float"));
    instructionAnd(generator->tmp3Var, generator->tmp1Var, generator->tmp2Var);
    instructionJumpIfNotEquals(notIntFloat, generator->tmp3Var, createString("bool@true"));
        instructionPushStack(arg1);
        instructionIntToFloatStack();
        instructionPushStack(arg2);
        instructionReturn();
    instructionLabel(notIntFloat);
    
    String *notFloatInt = createString("_%d_if_not_float_int", generator->labelCount++);
    instructionEquals(generator->tmp1Var, type1, createString("string@float"));
    instructionEquals(generator->tmp2Var, type2, createString("string@int"));
    instructionAnd(generator->tmp3Var, generator->tmp1Var, generator->tmp2Var);
    instructionJumpIfNotEquals(notFloatInt, generator->tmp3Var, createString("bool@true"));
        instructionPushStack(arg1);
        instructionPushStack(arg2);
        instructionIntToFloatStack();
        instructionReturn();
    instructionLabel(notFloatInt);
    
    String *notBoolInt = createString("_%d_if_not_bool_int", generator->labelCount++);
    instructionEquals(generator->tmp1Var, type1, createString("string@bool"));
    instructionEquals(generator->tmp2Var, type2, createString("string@int"));
    instructionAnd(generator->tmp3Var, generator->tmp1Var, generator->tmp2Var);
    instructionJumpIfNotEquals(notBoolInt, generator->tmp3Var, createString("bool@true"));
        String *boolIntIsFalse = createString("_%d_if_bool_is_false", generator->labelCount++);
        String *boolIntIsFalseEnd = createString("_%d_if_bool_is_false_end", generator->labelCount++);
        instructionJumpIfNotEquals(boolIntIsFalse, arg1, createString("bool@true"));
            instructionPushStack(createString("int@1"));
            instructionJump(boolIntIsFalseEnd);
        instructionLabel(boolIntIsFalse);
            instructionPushStack(createString("int@0"));
        instructionLabel(boolIntIsFalseEnd);
        instructionPushStack(arg2);
        instructionReturn();
    instructionLabel(notBoolInt);
    
    String *notIntBool = createString("_%d_if_not_int_bool", generator->labelCount++);
    instructionEquals(generator->tmp1Var, type1, createString("string@int"));
    instructionEquals(generator->tmp2Var, type2, createString("string@bool"));
    instructionAnd(generator->tmp3Var, generator->tmp1Var, generator->tmp2Var);
    instructionJumpIfNotEquals(notIntBool, generator->tmp3Var, createString("bool@true"));
        String *intBoolIsFalse = createString("_%d_if_bool_is_false", generator->labelCount++);
        instructionPushStack(arg1);
        instructionJumpIfNotEquals(intBoolIsFalse, arg2, createString("bool@true"));
            instructionPushStack(createString("int@1"));
            instructionReturn();
        instructionLabel(intBoolIsFalse);
        instructionPushStack(createString("int@0"));
        instructionReturn();
    instructionLabel(notIntBool);
    
    String *notBoolFloat = createString("_%d_if_not_bool_float", generator->labelCount++);
    instructionEquals(generator->tmp1Var, type1, createString("string@bool"));
    instructionEquals(generator->tmp2Var, type2, createString("string@float"));
    instructionAnd(generator->tmp3Var, generator->tmp1Var, generator->tmp2Var);
    instructionJumpIfNotEquals(notBoolFloat, generator->tmp3Var, createString("bool@true"));
        String *boolFloatIsFalse = createString("_%d_if_bool_is_false", generator->labelCount++);
        String *boolFloatsFalseEnd = createString("_%d_if_bool_is_false_end", generator->labelCount++);
        instructionJumpIfNotEquals(boolFloatIsFalse, arg1, createString("bool@true"));
            instructionPushStack(createString("float@0x1p+0"));
            instructionJump(boolFloatsFalseEnd);
        instructionLabel(boolFloatIsFalse);
            instructionPushStack(createString("float@0x0p+0"));
        instructionLabel(boolFloatsFalseEnd);
        instructionPushStack(arg2);
        instructionReturn();
    instructionLabel(notBoolFloat);
    
    String *notFloatBool = createString("_%d_if_not_float_bool", generator->labelCount++);
    instructionEquals(generator->tmp1Var, type1, createString("string@float"));
    instructionEquals(generator->tmp2Var, type2, createString("string@bool"));
    instructionAnd(generator->tmp3Var, generator->tmp1Var, generator->tmp2Var);
    instructionJumpIfNotEquals(notFloatBool, generator->tmp3Var, createString("bool@true"));
        String *floatBoolIsFalse = createString("_%d_if_bool_is_false", generator->labelCount++);
        instructionPushStack(arg1);
        instructionJumpIfNotEquals(floatBoolIsFalse, arg2, createString("bool@true"));
            instructionPushStack(createString("float@0x1p+0"));
            instructionReturn();
        instructionLabel(floatBoolIsFalse);
        instructionPushStack(createString("float@0x0p+0"));
        instructionReturn();
    instructionLabel(notFloatBool);
    
    instructionPushStack(arg1);
    instructionPushStack(arg2);
    instructionReturn();
}

void generateCheckIfTypeFunction(Generator *generator) {
    instructionLabel(generator->checkIfTypeTypeFunction);
    instructionCreateFrame();
    
    String *type = createString("TF@type");
    String *arg = createString("TF@arg");
    String *argType = createString("TF@argType");
    
    instructionDefVar(type);
    instructionDefVar(arg);
    instructionDefVar(argType);
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

void generateCheckIfNotTypeFunction(Generator *generator) {
    instructionLabel(generator->checkIfNotTypeTypeFunction);
    instructionCreateFrame();
    
    String *type = createString("TF@type");
    String *arg = createString("TF@arg");
    String *argType = createString("TF@argType");
    
    instructionDefVar(type);
    instructionDefVar(arg);
    instructionDefVar(argType);
    instructionPopStack(type);
    instructionPopStack(arg);
    instructionType(argType, arg);
    
    String *typeErrorLabel = createString("_%d_type_check_error", generator->labelCount++);
    instructionJumpIfEquals(typeErrorLabel, argType, type);
        instructionPushStack(arg);
        instructionReturn();
    instructionLabel(typeErrorLabel);
    instructionExit(4);
}

void generateConvertToFloatFunction(Generator *generator) {
    instructionLabel(generator->convertToFloatFunction);
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
    
    String *notBoolLabel = createString("_%d_not_bool_cond", generator->labelCount++);
    instructionJumpIfNotEquals(notBoolLabel, type, createString("string@bool"));
        String *boolFalse = createString("_%d_bollFalse");
        instructionJumpIfNotEquals(boolFalse, arg, createString("bool@true"));
            instructionPushStack(createString("float@0x1p+0"));
            instructionReturn();
        instructionLabel(boolFalse);
        instructionPushStack(createString("float@0x0p+00"));
        instructionReturn();
    instructionLabel(notBoolLabel);
    
    instructionExit(4);
}

void generateTypeSafeAddFunction(Generator *generator) {
    String *arg1 = createString("TF@arg1");
    String *arg2 = createString("TF@arg2");
    String *arg1Type = createString("TF@arg1Type");
    String *arg2Type = createString("TF@arg2Type");
    
    instructionLabel(generator->typeSafeAddFunction);
    instructionCall(generator->implicitConversionFunction);
    instructionCreateFrame();
    
    instructionDefVar(arg1);
    instructionDefVar(arg2);
    instructionDefVar(arg1Type);
    instructionDefVar(arg2Type);
    instructionPopStack(arg2);
    instructionPopStack(arg1);
    instructionType(arg1Type, arg1);
    instructionType(arg2Type, arg2);
    
    String *areSame = createString("_%d_are_Same", generator->labelCount++);
    instructionJumpIfEquals(areSame, arg1Type, arg2Type);
        instructionExit(4);
    instructionLabel(areSame);
    
    String *notNil = createString("_%d_if_not_nil", generator->labelCount++);
    instructionJumpIfNotEquals(notNil, arg1Type, createString("string@nil"));
        instructionExit(4);
    instructionLabel(notNil);
    
    String *notConcat = createString("_%d_if_not_concat", generator->labelCount++);
    instructionJumpIfNotEquals(notConcat, arg1Type, createString("string@string"));
        instructionConcat(generator->tmp1Var, arg1, arg2);
        instructionPushStack(generator->tmp1Var);
        instructionReturn();
    instructionLabel(notConcat);
    
    String *notBool = createString("_%d_if_not_concat", generator->labelCount++);
    instructionJumpIfNotEquals(notBool, arg1Type, createString("string@bool"));
        String *bool1IntIsFalse = createString("_%d_if_bool_is_false", generator->labelCount++);
        String *bool1IntIsFalseEnd = createString("_%d_if_bool_is_false_end", generator->labelCount++);
        String *bool2IntIsFalse = createString("_%d_if_bool_is_false", generator->labelCount++);
        String *bool2IntIsFalseEnd = createString("_%d_if_bool_is_false_end", generator->labelCount++);
    
        instructionJumpIfNotEquals(bool1IntIsFalse, arg1, createString("bool@true"));
            instructionMove(arg1, createString("int@1"));
            instructionJump(bool1IntIsFalseEnd);
        instructionLabel(bool1IntIsFalse);
            instructionMove(arg1, createString("int@0"));
        instructionLabel(bool1IntIsFalseEnd);
        instructionType(arg1Type, arg1);
    
        instructionJumpIfNotEquals(bool2IntIsFalse, arg2, createString("bool@true"));
            instructionMove(arg2, createString("int@1"));
            instructionJump(bool2IntIsFalseEnd);
        instructionLabel(bool2IntIsFalse);
            instructionMove(arg2, createString("int@0"));
        instructionLabel(bool2IntIsFalseEnd);
        instructionType(arg2Type, arg2);
    instructionLabel(notBool);
    
    instructionAdd(generator->tmp1Var, arg1, arg2);
    instructionPushStack(generator->tmp1Var);
    instructionReturn();
}

void generateTypeSafeSubFunction(Generator *generator) {
    String *arg1 = createString("TF@arg1");
    String *arg2 = createString("TF@arg2");
    String *arg1Type = createString("TF@arg1Type");
    String *arg2Type = createString("TF@arg2Type");
    
    instructionLabel(generator->typeSafeSubFunction);
    instructionCall(generator->implicitConversionFunction);
    instructionCreateFrame();
    
    instructionDefVar(arg1);
    instructionDefVar(arg2);
    instructionDefVar(arg1Type);
    instructionDefVar(arg2Type);
    instructionPopStack(arg2);
    instructionPopStack(arg1);
    instructionType(arg1Type, arg1);
    instructionType(arg2Type, arg2);
    
    String *areSame = createString("_%d_are_Same", generator->labelCount++);
    instructionJumpIfEquals(areSame, arg1Type, arg2Type);
        instructionExit(4);
    instructionLabel(areSame);
    
    String *notNil = createString("_%d_if_not_nil", generator->labelCount++);
    instructionJumpIfNotEquals(notNil, arg1Type, createString("string@nil"));
        instructionExit(4);
    instructionLabel(notNil);
    
    String *notString = createString("_%d_if_not_string", generator->labelCount++);
    instructionJumpIfNotEquals(notString, arg1Type, createString("string@string"));
        instructionExit(4);
    instructionLabel(notString);
    
    String *notBool = createString("_%d_if_not_concat", generator->labelCount++);
    instructionJumpIfNotEquals(notBool, arg1Type, createString("string@bool"));
        String *bool1IntIsFalse = createString("_%d_if_bool_is_false", generator->labelCount++);
        String *bool1IntIsFalseEnd = createString("_%d_if_bool_is_false_end", generator->labelCount++);
        String *bool2IntIsFalse = createString("_%d_if_bool_is_false", generator->labelCount++);
        String *bool2IntIsFalseEnd = createString("_%d_if_bool_is_false_end", generator->labelCount++);
    
        instructionJumpIfNotEquals(bool1IntIsFalse, arg1, createString("bool@true"));
            instructionMove(arg1, createString("int@1"));
            instructionJump(bool1IntIsFalseEnd);
        instructionLabel(bool1IntIsFalse);
            instructionMove(arg1, createString("int@0"));
        instructionLabel(bool1IntIsFalseEnd);
        instructionType(arg1Type, arg1);
    
        instructionJumpIfNotEquals(bool2IntIsFalse, arg2, createString("bool@true"));
            instructionMove(arg2, createString("int@1"));
            instructionJump(bool2IntIsFalseEnd);
        instructionLabel(bool2IntIsFalse);
            instructionMove(arg2, createString("int@0"));
        instructionLabel(bool2IntIsFalseEnd);
        instructionType(arg2Type, arg2);
    instructionLabel(notBool);
    
    instructionSub(generator->tmp1Var, arg1, arg2);
    instructionPushStack(generator->tmp1Var);
    instructionReturn();
}

void generateTypeSafeMulFunction(Generator *generator) {
    String *arg1 = createString("TF@arg1");
    String *arg2 = createString("TF@arg2");
    String *arg1Type = createString("TF@arg1Type");
    String *arg2Type = createString("TF@arg2Type");
    
    instructionLabel(generator->typeSafeMulFunction);
    instructionCall(generator->implicitConversionFunction);
    instructionCreateFrame();
    
    instructionDefVar(arg1);
    instructionDefVar(arg2);
    instructionDefVar(arg1Type);
    instructionDefVar(arg2Type);
    instructionPopStack(arg2);
    instructionPopStack(arg1);
    instructionType(arg1Type, arg1);
    instructionType(arg2Type, arg2);
    
    String *areSame = createString("_%d_are_Same", generator->labelCount++);
    instructionJumpIfEquals(areSame, arg1Type, arg2Type);
        instructionExit(4);
    instructionLabel(areSame);
    
    String *notNil = createString("_%d_if_not_nil", generator->labelCount++);
    instructionJumpIfNotEquals(notNil, arg1Type, createString("string@nil"));
        instructionExit(4);
    instructionLabel(notNil);
    
    String *notString = createString("_%d_if_not_string", generator->labelCount++);
    instructionJumpIfNotEquals(notString, arg1Type, createString("string@string"));
        instructionExit(4);
    instructionLabel(notString);
    
    String *notBool = createString("_%d_if_not_concat", generator->labelCount++);
    instructionJumpIfNotEquals(notBool, arg1Type, createString("string@bool"));
        String *bool1IntIsFalse = createString("_%d_if_bool_is_false", generator->labelCount++);
        String *bool1IntIsFalseEnd = createString("_%d_if_bool_is_false_end", generator->labelCount++);
        String *bool2IntIsFalse = createString("_%d_if_bool_is_false", generator->labelCount++);
        String *bool2IntIsFalseEnd = createString("_%d_if_bool_is_false_end", generator->labelCount++);
    
        instructionJumpIfNotEquals(bool1IntIsFalse, arg1, createString("bool@true"));
            instructionMove(arg1, createString("int@1"));
            instructionJump(bool1IntIsFalseEnd);
        instructionLabel(bool1IntIsFalse);
            instructionMove(arg1, createString("int@0"));
        instructionLabel(bool1IntIsFalseEnd);
        instructionType(arg1Type, arg1);
    
        instructionJumpIfNotEquals(bool2IntIsFalse, arg2, createString("bool@true"));
            instructionMove(arg2, createString("int@1"));
            instructionJump(bool2IntIsFalseEnd);
        instructionLabel(bool2IntIsFalse);
            instructionMove(arg2, createString("int@0"));
        instructionLabel(bool2IntIsFalseEnd);
        instructionType(arg1Type, arg1);
    instructionLabel(notBool);
    
    instructionMul(generator->tmp1Var, arg1, arg2);
    instructionPushStack(generator->tmp1Var);
    instructionReturn();
}

void generateTypeSafeDivFunction(Generator *generator) {
    String *arg1 = createString("TF@arg1");
    String *arg2 = createString("TF@arg2");
    
    instructionLabel(generator->typeSafeDivFunction);
    instructionCall(generator->implicitConversionFunction);
    instructionCreateFrame();
    
    instructionDefVar(arg1);
    instructionDefVar(arg2);
    instructionPopStack(arg2);
    instructionPopStack(arg1);
    
    instructionPushStack(arg1);
    instructionPushFrame();
    instructionCall(generator->convertToFloatFunction);
    instructionPopFrame();
    instructionPopStack(arg1);
    
    instructionPushStack(arg2);
    instructionPushFrame();
    instructionCall(generator->convertToFloatFunction);
    instructionPopFrame();
    instructionPopStack(arg2);
    
    String *notDevisionByZero = createString("_%d_not_devision_by_zero", generator->labelCount++);
    instructionJumpIfNotEquals(notDevisionByZero, arg2, createString("float@0x0p+0"));
        instructionExit(9);
    instructionLabel(notDevisionByZero);
    
    instructionDiv(generator->tmp1Var, arg1, arg2);
    instructionPushStack(generator->tmp1Var);
    instructionReturn();
}


void generateTypeSafeIdivFunction(Generator *generator) {
    instructionLabel(generator->typeSafeIdivFunction);
    instructionCall(generator->implicitConversionFunction);
    instructionCreateFrame();
    
    String *arg1 = createString("TF@arg1");
    String *arg2 = createString("TF@arg2");
    String *arg1Type = createString("TF@arg1Type");
    String *arg2Type = createString("TF@arg2Type");
    
    instructionDefVar(arg1);
    instructionDefVar(arg2);
    instructionDefVar(arg1Type);
    instructionDefVar(arg2Type);
    instructionPopStack(arg2);
    instructionPopStack(arg1);
    instructionType(arg1Type, arg1);
    instructionType(arg2Type, arg2);
    
    String *areSame = createString("_%d_are_Same", generator->labelCount++);
    instructionJumpIfEquals(areSame, arg1Type, arg2Type);
        instructionExit(4);
    instructionLabel(areSame);
    
    String *notBool = createString("_%d_if_not_concat", generator->labelCount++);
    instructionJumpIfNotEquals(notBool, arg1Type, createString("string@bool"));
        String *bool1IntIsFalse = createString("_%d_if_bool_is_false", generator->labelCount++);
        String *bool1IntIsFalseEnd = createString("_%d_if_bool_is_false_end", generator->labelCount++);
        String *bool2IntIsFalse = createString("_%d_if_bool_is_false", generator->labelCount++);
        String *bool2IntIsFalseEnd = createString("_%d_if_bool_is_false_end", generator->labelCount++);
    
        instructionJumpIfNotEquals(bool1IntIsFalse, arg1, createString("bool@true"));
            instructionMove(arg1, createString("int@1"));
            instructionJump(bool1IntIsFalseEnd);
        instructionLabel(bool1IntIsFalse);
            instructionMove(arg1, createString("int@0"));
        instructionLabel(bool1IntIsFalseEnd);
        instructionType(arg1Type, arg1);
    
        instructionJumpIfNotEquals(bool2IntIsFalse, arg2, createString("bool@true"));
            instructionMove(arg2, createString("int@1"));
            instructionJump(bool2IntIsFalseEnd);
        instructionLabel(bool2IntIsFalse);
            instructionMove(arg2, createString("int@0"));
        instructionLabel(bool2IntIsFalseEnd);
        instructionType(arg2Type, arg2);
    instructionLabel(notBool);
    
    String *notInt = createString("_%d_if_not_int");
    instructionEquals(generator->tmp1Var, arg1Type, createString("string@int"));
    instructionEquals(generator->tmp2Var, arg2Type, createString("string@int"));
    instructionAnd(generator->tmp3Var, generator->tmp2Var, generator->tmp1Var);
    instructionJumpIfNotEquals(notInt, generator->tmp3Var, createString("bool@true"));
        String *notDevisionByZero = createString("_%d_not_devision_by_zero", generator->labelCount++);
        instructionJumpIfNotEquals(notDevisionByZero, arg2, createString("int@0"));
            instructionExit(9);
        instructionLabel(notDevisionByZero);
        instructionIDiv(generator->tmp1Var, arg1, arg2);
        instructionPushStack(generator->tmp1Var);
        instructionReturn();
    instructionLabel(notInt);
    instructionExit(4);
}

void generateTypeSafeEqualsFunction(Generator *generator) {
    String *arg1 = createString("TF@arg1");
    String *arg2 = createString("TF@arg2");
    String *arg1Type = createString("TF@arg1Type");
    String *arg2Type = createString("TF@arg2Type");
    
    instructionLabel(generator->typeSafeEqualsFunction);
    instructionCall(generator->implicitConversionFunction);
    instructionCreateFrame();
    
    instructionDefVar(arg1);
    instructionDefVar(arg2);
    instructionDefVar(arg1Type);
    instructionDefVar(arg2Type);
    instructionPopStack(arg2);
    instructionPopStack(arg1);
    instructionType(arg1Type, arg1);
    instructionType(arg2Type, arg2);
    
    String *areNil = createString("_%d_are_nil", generator->labelCount++);
    instructionEquals(generator->tmp1Var, arg1Type, createString("string@nil"));
    instructionEquals(generator->tmp2Var, arg2Type, createString("string@nil"));
    instructionOr(generator->tmp3Var, generator->tmp1Var, generator->tmp2Var);
    instructionJumpIfNotEquals(areNil, generator->tmp3Var, createString("bool@true"));
        instructionEquals(generator->tmp1Var, arg1, arg2);
        instructionPushStack(generator->tmp1Var);
        instructionReturn();
    instructionLabel(areNil);
    
    String *areSame = createString("_%d_are_Same", generator->labelCount++);
    instructionJumpIfEquals(areSame, arg1Type, arg2Type);
        instructionExit(4);
    instructionLabel(areSame);
    
    instructionEquals(generator->tmp1Var, arg1, arg2);
    instructionPushStack(generator->tmp1Var);
    instructionReturn();
}

void generateTypeSafeGreaterFunction(Generator *generator) {
    String *arg1 = createString("TF@arg1");
    String *arg2 = createString("TF@arg2");
    String *arg1Type = createString("TF@arg1Type");
    String *arg2Type = createString("TF@arg2Type");
    
    instructionLabel(generator->typeSafeGreaterFunction);
    instructionCall(generator->implicitConversionFunction);
    instructionCreateFrame();
    
    instructionDefVar(arg1);
    instructionDefVar(arg2);
    instructionDefVar(arg1Type);
    instructionDefVar(arg2Type);
    instructionPopStack(arg2);
    instructionPopStack(arg1);
    instructionType(arg1Type, arg1);
    instructionType(arg2Type, arg2);
    
    String *areSame = createString("_%d_are_Same", generator->labelCount++);
    instructionJumpIfEquals(areSame, arg1Type, arg2Type);
        instructionExit(4);
    instructionLabel(areSame);
    
    String *notNil = createString("_%d_if_not_nil", generator->labelCount++);
    instructionJumpIfNotEquals(notNil, arg1Type, createString("string@nil"));
        instructionExit(4);
    instructionLabel(notNil);
    
    instructionGreaterThan(generator->tmp1Var, arg1, arg2);
    instructionPushStack(generator->tmp1Var);
    instructionReturn();
}

void generateTypeSafeLessFunction(Generator *generator) {
    String *arg1 = createString("TF@arg1");
    String *arg2 = createString("TF@arg2");
    String *arg1Type = createString("TF@arg1Type");
    String *arg2Type = createString("TF@arg2Type");
    
    instructionLabel(generator->typeSafeLessFunction);
    instructionCall(generator->implicitConversionFunction);
    instructionCreateFrame();
    
    instructionDefVar(arg1);
    instructionDefVar(arg2);
    instructionDefVar(arg1Type);
    instructionDefVar(arg2Type);
    instructionPopStack(arg2);
    instructionPopStack(arg1);
    instructionType(arg1Type, arg1);
    instructionType(arg2Type, arg2);
    
    String *areSame = createString("_%d_are_Same", generator->labelCount++);
    instructionJumpIfEquals(areSame, arg1Type, arg2Type);
        instructionExit(4);
    instructionLabel(areSame);
    
    String *notNil = createString("_%d_if_not_nil", generator->labelCount++);
    instructionJumpIfNotEquals(notNil, arg1Type, createString("string@nil"));
        instructionExit(4);
    instructionLabel(notNil);
    
    instructionLessThan(generator->tmp1Var, arg1, arg2);
    instructionPushStack(generator->tmp1Var);
    instructionReturn();

}

void generateTypeSafeAndFunction(Generator *generator) {
    instructionLabel(generator->typeSafeAndFunction);
    instructionCreateFrame();
    
    String *arg1 = createString("TF@arg1");
    String *arg2 = createString("TF@arg2");
    String *arg1Type = createString("TF@arg1Type");
    String *arg2Type = createString("TF@arg2Type");
    
    instructionDefVar(arg1);
    instructionDefVar(arg2);
    instructionDefVar(arg1Type);
    instructionDefVar(arg2Type);
    instructionPopStack(arg2);
    instructionPopStack(arg1);
    instructionType(arg1Type, arg1);
    instructionType(arg2Type, arg2);
    
    String *notBool = createString("_%d_if_not_bool", generator->labelCount++);
    instructionEquals(generator->tmp1Var, arg1Type, createString("string@bool"));
    instructionEquals(generator->tmp2Var, arg2Type, createString("string@bool"));
    instructionAnd(generator->tmp3Var, generator->tmp2Var, generator->tmp1Var);
    instructionJumpIfNotEquals(notBool, generator->tmp3Var, createString("bool@true"));
        instructionOr(generator->tmp1Var, arg1, arg2);
        instructionPushStack(generator->tmp1Var);
        instructionReturn();
    instructionLabel(notBool);
    instructionExit(4);
}

void generateTypeSafeOrFunction(Generator *generator) {
    instructionLabel(generator->typeSafeOrFunction);
    instructionCreateFrame();
    
    String *arg1 = createString("TF@arg1");
    String *arg2 = createString("TF@arg2");
    String *arg1Type = createString("TF@arg1Type");
    String *arg2Type = createString("TF@arg2Type");
    
    instructionDefVar(arg1);
    instructionDefVar(arg2);
    instructionDefVar(arg1Type);
    instructionDefVar(arg2Type);
    instructionPopStack(arg2);
    instructionPopStack(arg1);
    instructionType(arg1Type, arg1);
    instructionType(arg2Type, arg2);
    
    String *notBool = createString("_%d_if_not_bool", generator->labelCount++);
    instructionEquals(generator->tmp1Var, arg1Type, createString("string@bool"));
    instructionEquals(generator->tmp2Var, arg2Type, createString("string@bool"));
    instructionAnd(generator->tmp3Var, generator->tmp2Var, generator->tmp1Var);
    instructionJumpIfNotEquals(notBool, generator->tmp3Var, createString("bool@true"));
        instructionOr(generator->tmp1Var, arg1, arg2);
        instructionPushStack(generator->tmp1Var);
        instructionReturn();
    instructionLabel(notBool);
    instructionExit(4);
}

void generateTypeSafeNotFunction(Generator *generator) {
    instructionLabel(generator->typeSafeNotFunction);
    instructionCreateFrame();
    
    String *arg = createString("TF@arg");
    String *argType = createString("TF@argType");
    
    instructionDefVar(arg);
    instructionDefVar(argType);
    instructionPopStack(arg);
    instructionType(argType, arg);
    
    String *notBool = createString("_%d_if_not_bool", generator->labelCount++);
    instructionJumpIfNotEquals(notBool, argType, createString("bool@true"));
        instructionNot(generator->tmp1Var, arg);
        instructionPushStack(generator->tmp1Var);
        instructionReturn();
    instructionLabel(notBool);
    instructionExit(4);
}

void generateConvertNilToNoneString(Generator *generator) {
    String *notNilLabel = createString("_%d_not_nil_conversion", generator->labelCount);
    instructionLabel(generator->convertNilToNoneStrFunction);
    instructionPopStack(generator->tmp1Var);
    instructionJumpIfNotEquals(notNilLabel, generator->tmp1Var, createString("nil@nil"));
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
    instructionCreateFrame();
    String *position = createString("tf@position");
    instructionDefVar(position);
    instructionPopStack(position);
    
    // check if position is int
    instructionPushStack(position);
    instructionPushStack(createString("string@int"));
    instructionPushFrame();
    instructionCall(generator->checkIfTypeTypeFunction);
    instructionPopFrame();
    instructionPopStack(generator->tmp1Var);
    
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
    instructionCreateFrame();
    String *str = createString("tf@str");
    String *position = createString("tf@position");
    String *len = createString("tf@len");
    
    instructionDefVar(str);
    instructionDefVar(position);
    instructionDefVar(len);
    
    instructionPopStack(position);
    instructionPopStack(str);
    
    // Check if str is string
    instructionPushStack(str);
    instructionPushStack(createString("string@string"));
    instructionPushFrame();
    instructionCall(generator->checkIfTypeTypeFunction);
    instructionPopFrame();
    instructionPopStack(generator->tmp1Var);
    
    // Check if position is int
    instructionPushStack(position);
    instructionPushStack(createString("string@int"));
    instructionPushFrame();
    instructionCall(generator->checkIfTypeTypeFunction);
    instructionPopFrame();
    instructionPopStack(generator->tmp1Var);
    
    instructionStrLen(len, str);
    
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
    instructionLabel(elseLabel);
        instructionStringToInt(generator->tmp1Var, str, position);
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
