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
    size_t size = vsnprintf(NULL, 0, chars, argList);
    str->value = (char *) malloc(size);
    vsprintf(str->value, chars, argList);
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

bool stringEquals(String *str1, String *str2){
  if(stringLength(str1->value) != stringLength(str2->value)) return false;
  for(int i = 0; i < stringLength(str1->value); i++){
    if(str1->value[i] != str2->value[i]) return false;
  }
  return true;
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
