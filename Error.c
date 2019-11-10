#include "Error.h"

// prints message to stderr, clears memory and exits with specified error number.
void handleError(ErrorCodes code, char *message, ...) {
	if (!inDebugMode) 
		return;

	fflush(stderr);
	fflush(stdout);
	
	va_list argList;
	va_start(argList, message);

	vfprintf(stderr, message, argList);

	cleanResources();

	va_end(argList);
	exit(code);
}
