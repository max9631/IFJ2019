#import <stdio.h>
#import <stdbool.h>

struct String {
    int lenght;
    char *chars;
};

/**
 * Creates a string using malloc.
 */
struct String *createString(char **chars);

/**
 * Checks whether str1 and str2 are the same.
 */
bool areSame(struct String *str1, struct String *str2);

/**
 * Deallocates str.
 */
bool destroy(struct String *str);
