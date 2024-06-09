#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BRACKET_OPEN_CHAR '['
#define BRACKET_CLOSE_CHAR ']'
#define SPACE_CHAR ' '
#define COMMA_CHAR ','
#define NULL_CHAR '\0'
#define DOUBLE_QUOTES_CHAR '\"'

#define pass (void)0

extern void CopyString(const char *, char *, size_t, size_t);
extern bool IsCharInString(const char *, char);
extern size_t NumCharInString(const char *, char);
extern int *StringToIntArr(const char *, size_t);
#endif
