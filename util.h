#ifndef UTIL_H
#define UTIL_H

#include <stdarg.h>
#include "attrib.h"

ATTRIBUTE_PRINTF_LIKE (2, 3) extern int asprintf (char **restrict strp, const char *restrict fmt, ...); 
int vasprintf(char **restrict strp, const char *restrict fmt, va_list ap);
char *strdup (const char *s); 
char *stpcpy (char *restrict dest, const char *restrict src); 
char *basename (char *path);

#endif /* UTIL_H */
