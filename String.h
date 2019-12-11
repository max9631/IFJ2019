/*
 * Author(s): Adam Salih (xsalih01), Jiří Veverka (xvever12), Michal Halabica (xhalab00)
 * Project: Implementace prekladace imperativniho jazyka jazyka IFJ19
 * File: String.h, adds support for strings
 */
 
#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "Error.h"

//Struct containing defined string
typedef struct String {
    int lenght;
    char *value;
} String;


/**
 * Creates a string from array of chars using malloc. Accepts variable arguments
 */
String *createString(char *chars, ...);

/**
 * Creates a string from char using malloc.
 */
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
bool stringEquals(String *str1, char *str2);

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


/**
 * Converts string chars to hexa
 * [in] String *fromStr: Variable with input string
 * [out] string with valid hexa chars
 */
String *convertStringCharsToHexadecimal(String *fromStr);

/**
 * Converts string float numbers to hexa
 * [in] String *fl: Variable with input string
 * [out] string with valid float in hexa
 */
String *convertFloatToHexadecimal(String *fl);

/**
 * Converts bool to lowercase
 * [in] String *fl: Variable with input string containing bool
 * [out] string with bool in lowercase
 */
String *convertBoolToLowercase(String *fl);

#endif //STRING_H
