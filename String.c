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
