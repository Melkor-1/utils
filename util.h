#ifndef UTIL_H
#define UTIL_H 1

#include <stdarg.h>

int util_vasprintf(char **restrict strp,
                   const char fmt[restrict static 1], 
                   va_list ap);

[[gnu::format(printf, 2, 3)]] int util_asprintf(char **restrict strp,
                                                const char fmt[restrict static 1], 
                                                ...); 

[[gnu::returns_nonnull]] char *util_stpcpy(char dest[restrict static 1],
                                           const char src[restrict static 1]);

[[gnu::returns_nonnull]] char *util_basename_vanilla(char path[static 1]);

[[gnu::returns_nonnull]] const char *util_basename_const(const char path[static 1]);

#define util_basename(s)                         \
    _Generic((s),                                \
            char *:       util_basename_vanilla, \
            const char *: util_basename_const)(s)

[[gnu::pure, gnu::returns_nonnull]] char *util_strchrnul_vanilla(
        char s[static 1], 
        int c);

[[gnu::pure, gnu::returns_nonnull]] const char *util_strchrnul_const(
        const char s[static 1], 
        int c);

#define util_strchrnul(s, c)                      \
    _Generic((s),                                 \
            char *:       util_strchrnul_vanilla, \
            const char *: util_strchrnul_const)(s, c)

[[gnu::pure]] int util_strcasecmp(const char s[restrict static 1], 
                                  const char t[restrict static 1]);

#endif                          /* UTIL_H */
