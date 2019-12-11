/*
 * Author(s): Michal Halabica (xhalab00)
 * Project: Implementace prekladace imperativniho jazyka jazyka IFJ19
 * File: Error.c, Implementation of error codes and error handling
 */

#include "Error.h"

// prints message to stderr, clears memory and exits with specified error number.
void handleError(ErrorCodes code, char *message, ...) {
	fflush(stderr);
	fflush(stdout);
	va_list argList;
	va_start(argList, message);
	char *lineMsg = malloc(strlen(message) + 2);
	strcpy(lineMsg, message);
	strcat(lineMsg, "\n");
	vfprintf(stderr, lineMsg, argList);
	if (lineMsg != NULL) free(lineMsg);
	cleanResources();
	va_end(argList);
	exit(code);
}
