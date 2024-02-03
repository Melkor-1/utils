#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>

#include "attrib.h"
#include "util.h"

#define FAIL -1

int vasprintf(char **restrict strp, const char *restrict fmt, va_list ap)
{
    va_list ap_copy;

    va_copy(ap_copy, ap);
    int const nwritten = vsnprintf(0, 0, fmt, ap_copy);

    va_end(ap_copy);

    if (nwritten < 0) {
        goto fatal;
    }

    *strp = malloc((size_t) nwritten + 1);
    if (!(*strp)) {
        goto fatal;
    }

    int const ret_val = vsprintf(*strp, fmt, ap);

    if (ret_val < 0) {
        free(*strp);
        goto fatal;
    }

    return ret_val;

  fatal:
    *strp = 0;                  /* The BSD implementation set *strp to NULL on failure. */
    return FAIL;
}

ATTRIBUTE_PRINTF_LIKE(2, 3)
int asprintf(char **restrict strp, const char *restrict fmt, ...)
{
    va_list argp;

    va_start(argp, fmt);
    *strp = 0;
    int const nwritten = kilo_vasprintf(strp, fmt, argp);

    va_end(argp);

    return nwritten;
}

char *strdup(const char *s)
{
    const size_t len = strlen(s);

    /* This could instead use asprintf(). */
    void *new = malloc(len + 1);

    if (!new) {
        goto fatal;
    }
    return memcpy(new, s, len + 1);

  fatal:
    return 0;
}

char *stpcpy(char *restrict dest, const char *restrict src)
{
    const size_t len = strlen(src);

    /* The cast is required because pointer arithmetic on a void * 
     * is not a valid operation. 
     */
    return (char *) memcpy(dest, src, len + 1) + len;
}

char *basename(char *path)
{
    char *cp = strrchr(path, '/');

    return cp ? strdup(cp + 1) : strdup(path);
}
