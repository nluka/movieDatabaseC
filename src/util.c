#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"
#include "ExitCode.h"

int getStringLengthNulTerminated(const char *string) {
    int i = 0;
    while (string[i] != '\0') {
        i++;
    }
    return i;
}

int getStringLengthNewlineTerminated(const char *string, int size) {
    int i = 0;
    while (string[i] != '\n' && i < size) {
        i++;
    }
    return i;
}

const char* getStringWithNewlineCharReplacedByNulChar(const char *string, int size) {
    if (string[0] == '\n') {
        const char* newString = { "\0" };
        return newString;
    }

    int i = getStringLengthNewlineTerminated(string, size);
    char* newString = malloc( sizeof(char) * (i + 1) );
    if (newString == NULL) {
        exit(1);
    }
    strncpy(newString, string, (size_t)i);
    newString[i] = '\0';
    return (const char*)newString;
}

void exitIfPointerIsNull(void* ptr) {
    if (ptr == NULL) {
        exit(NO_MEMORY_LEFT);
    }
}