#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __GNUC__
    #define HAVE_GNU_STRCHRNUL
#endif /* __GNUC__ */

#include <string.h>
#include <stdarg.h>

#include "util.h"

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

#ifdef TEST_MAIN

#include <assert.h>

int main(void)
{
    assert(strcmp(util_basename("/usr/lib"), "lib") == 0);
    assert(strcmp(util_basename("/usr/"), "") == 0);
    assert(strcmp(util_basename("usr"), "usr") == 0);
    assert(strcmp(util_basename("/"), "") == 0);
    assert(strcmp(util_basename("."), ".") == 0);
    assert(strcmp(util_basename(".."), "..") == 0);

    assert(util_strcasecmp("aPplE", "APPLE") == 0);
    assert(util_strcasecmp("apple", "apple") == 0);
    assert(util_strcasecmp("HELLO", "HELLO") == 0);
    assert(util_strcasecmp("", "") == 0);
    assert(util_strcasecmp("HrLLO", "HELLO"));

    char *formatted = {};
    int len = util_asprintf(&formatted, "%d", 10);
    assert(len == 2);
    assert(formatted);
    assert(strcmp(formatted, "10") == 0);
    free(formatted);
    
    static constexpr char haystack[] = "hello there";
    assert(util_strchrnul(haystack, 'o') == strchr(haystack, 'o'));
    assert(*util_strchrnul(haystack, 'p') == '\0');

#ifdef HAVE_GNU_STRCHRNUL
    /* Specify the prototype, because defining _GNU_SOURCE doesn't seem to. */
    char *strchrnul(const char *p, int ch);

    static constexpr char s[] = "hair"; 
    static constexpr char t[] = "gown"; 
    assert(util_strchrnul(s, 'h') == strchrnul(s, 'h'));
    assert(util_strchrnul(t, 'g') == strchrnul(t, 'g'));
#endif /* HAVE_GNU_STRCHRNUL */
}

#endif
