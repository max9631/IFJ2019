#include "String.h"

//struct string;

String *createString(char **chars){
	String *str = (struct String *) malloc(sizeof(struct String));
	if (str == NULL) handleError(InternalError, "String Error: Could not initialize memory");
	str->value = (char *) malloc(sizeof(char*));
	if (str->value == NULL) handleError(InternalError, "String Error: Could not initialize memory");
	memcpy (&str->value, &*chars, sizeof(**chars) );
	str->lenght = stringLength(*chars);
	return str;
}

bool appendCharacter(String *str, int c) {
	if (str == NULL) return false;
	str->lenght = str->lenght + 1;
	str->value = (char *) realloc(str->value, str->lenght * sizeof(char));
	if (str->value == NULL) return false;
	str->value[str->lenght - 1] = (char) c;
	return true;
}

void stringDestroy(String *str) {
	free(str->value);
	free(str);
}

int stringLength(char *str) {
   int c = 0;
   while (str[c] != '\0')
      c++;
   return c;
}
