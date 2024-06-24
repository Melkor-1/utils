/**
 * Author: Melkor-1
 * Date: Friday, June 7, 2024
 * 
 * Defines utility functions declared in utils.h. */

#include "utils.h"

#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int util_vasprintf(char **restrict strp, 
                   const char fmt[restrict static 1],
                   va_list ap)
{
    va_list ap_copy;

    va_copy(ap_copy, ap);
    const int nwritten = vsnprintf(nullptr, 0, fmt, ap_copy);

    va_end(ap_copy);

    if (nwritten < 0) {
        goto fatal;
    }

    *strp = malloc((size_t) nwritten + 1);
    if (*strp == nullptr) {
        goto fatal;
    }

    const int status = vsprintf(*strp, fmt, ap);

    if (status < 0) {
        free(*strp);
        goto fatal;
    }

    return status;

  fatal:
    /* The BSD implementation sets *strp to nullptr on failure. Linux's leaves
     * the contents undefined. Neither C nor POSIX has standarized this
     * function as of yet. */
    *strp = nullptr;
    return -1;
}

int util_asprintf(char **restrict strp, const char fmt[static 1], ...)
{
    va_list argp;

    va_start(argp, fmt);
    *strp = nullptr;
    int nwritten = util_vasprintf(strp, fmt, argp);

    va_end(argp);
    return nwritten;
}

size_t util_strnlen(size_t n, const char s[static n])
{
    const char *const found = memchr(s, '\0', n);
    return found ? (size_t)(found - s) : n;
}

char *util_stpcpy(char dest[restrict static 1],
                  const char src[restrict static 1])
{
    const size_t len = strlen(src);

    return (char *) memcpy(dest, src, len + 1) + len;
}

#define gen_basename(version, ret_type, arg_type) \
    ret_type util_basename_##version(arg_type path[static 1]) { \
        char *const cp = strrchr(path, '/'); \
        return cp ? cp + 1 : path; \
    } 

gen_basename(vanilla, char *, char)
gen_basename(const, const char *, const char)

#define gen_strchrnul(version, ret_type, arg_type) \
    ret_type util_strchrnul_##version(arg_type s[static 1], int c) { \
        while (*s && *s != c) { ++s; } \
        return s; \
    }

gen_strchrnul(vanilla, char *, char)
gen_strchrnul(const, const char *, const char)

int util_strcasecmp(const char s[restrict static 1], 
                    const char t[restrict static 1])
{
    const unsigned char *us = (const unsigned char *)s;
    const unsigned char *ut = (const unsigned char *)t;
    unsigned int p, q;

    do {
        p = tolower(*us++);
        q = tolower(*ut++);
    } while (p == q && q != '\0');

    return (p > q) - (p < q);
}

void util_memswap(size_t psize,
                  void *restrict p1, 
                  void *restrict p2)
{
    unsigned char *a = p1;
    unsigned char *b = p2;
    unsigned char tmp;

    while (psize--) {
        tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}

void fatal_error(char fmt[static 1], ...)
{
    assert(fmt);
    
    va_list args;
    va_start(args);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}
