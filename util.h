#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include "attrib.h"

int vasprintf(char **restrict strp, const char *restrict fmt, va_list ap);
ATTRIBUTE_PRINTF_LIKE (2, 3) extern int asprintf (char **restrict strp, const char *restrict fmt, ...); 
char *strdup (const char *s); 
extern char *stpcpy (char *restrict dest, const char *restrict src); 
extern char *basename (char *path);

#endif /* UTIL_H */
