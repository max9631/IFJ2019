#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Error.h"

typedef struct String {
    int lenght;
    char *value;
} String;


/**
 * Creates a string using malloc.
 */
String *createString(char **chars);
String *createStringFromChar(char ch);

/**
 * Adds a character to the string str
 * [in] string *str: Original string
 * [in] int c: Character to be added
 * [out] bool indicating whether operation has succeded or not
 */
bool appendCharacter(String *str, int c);

/**
 * Checks whether str1 and str2 are the same.
 */
bool stringEquals(String *str1, String *str2);

/**
 * Deallocates str.
 */
void destroyString(String *str);

/**
  * Returns length of a input string
  * [in] char *str: Variable with input string
  * [out] int with length of the string
  */

int stringLength(char *str);

#endif
