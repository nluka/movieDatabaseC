#ifndef UTIL_H
#define UTIL_H

int getStringLengthNulTerminated(const char *string);

int getStringLengthNewlineTerminated(const char *string, int size);

const char* getStringWithNewlineCharReplacedByNulChar(const char *string, int size);

void exitIfPointerIsNull(void* ptr);

#endif