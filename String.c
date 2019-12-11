/*
 * Author(s): Adam Salih (xsalih01), Jiří Veverka (xvever12)
 * Project: Implementace prekladace imperativniho jazyka jazyka IFJ19
 * File: String.c, adds support for strings
 */

#include "String.h"

String *createStringFromChar(char ch){
	String *str = (String *) malloc(sizeof(String));
	if (str == NULL) handleError(InternalError, "String Error: Could not initialize memory");
	str->value = NULL;
	str->lenght = 0;
	appendCharacter(str, ch);
	return str;
}

String *createString(char *chars, ...){
    va_list argList;
    va_start(argList, chars);

    String *str = (String *) malloc(sizeof(String));
    if (str == NULL) handleError(InternalError, "String Error: Could not initialize memory");
    size_t size = vsnprintf(NULL, 0, chars, argList)+1;

    va_end(argList);
    va_start(argList, chars);

    str->value = (char *) malloc(size);
    vsnprintf(str->value, size, chars, argList);
    if (str->value == NULL) handleError(InternalError, "String Error: Could not initialize memory");

    str->lenght = stringLength(str->value);

    va_end(argList);
    return str;
}

bool appendCharacter(String *str, int c) {
	if (str == NULL) return false;
	str->lenght++;
	str->value = (char *) realloc(str->value, (str->lenght + 1) * sizeof(char));
	if (str->value == NULL) return false;
	str->value[str->lenght - 1] = (char) c;
    str->value[str->lenght] = '\0';
	return true;
}

bool stringEquals(String *str1, char *str2){
    return strcmp(str1->value, str2) == 0;
}

void destroyString(String *str) {
    if (str == NULL) return;
	if (str->value != NULL) free(str->value);
	free(str);
}

int stringLength(char *str) {
   int c = 0;
   while (str[c] != '\0')
      c++;
   return c;
}

bool isValidHexaChar(int c) { return (c > 64 && c < 91) || (c > 96 && c < 123) || (c > 47 && c < 58); } // a-z || A-Z || 0-9

String *convertStringCharsToHexadecimal(String *fromStr) {
    String *str = createString("");
    for (int i = 0; i < fromStr->lenght; i++) {
        int ch = fromStr->value[i];
        if (isValidHexaChar(ch)) {
            appendCharacter(str, ch);
        } else {
            appendCharacter(str, (int) '\\');
            for (int n = 2; n >= 0; n--) {
                int pos = pow(10, n);
                int dec = (ch % (pos * 10)) / pos;
                dec += 48;
                appendCharacter(str, dec);
            }
        }
    }
    return str;
}

String *convertFloatToHexadecimal(String *fl) {
    String *str = (String *) malloc(sizeof(String));
    if (str == NULL) handleError(InternalError, "String Error: Could not initialize memory");
    size_t size = snprintf(NULL, 0, "%a", atof(fl->value)) + 1;
    str->value = (char *) malloc(size);
    snprintf(str->value, size, "%a", atof(fl->value));
    str->lenght = stringLength(str->value);
    return str;
}

String *convertBoolToLowercase(String *fl) {
    String *str = (String *) malloc(sizeof(String));
    if (str == NULL) handleError(InternalError, "String Error: Could not initialize memory");
    bool isTrue = stringEquals(fl, "True");
    str->lenght = isTrue ? 4 : 5;
    str->value = (char *) malloc(str->lenght * sizeof(char));
    str->value = isTrue ? "true" : "false";
    return str;
}
