
#ifndef STRING_H
#define STRING_H
#include <stdio.h>
#include <stdbool.h>

typedef struct String {
    int lenght;
    char *chars;
} String;

/**
 * Creates a string using malloc.
 */
String *createString(char **chars);

/**
 * Checks whether str1 and str2 are the same.
 */
bool areSame(String *str1, String *str2);

/**
 * Deallocates str.
 */
bool destroy(String *str);

#endif
