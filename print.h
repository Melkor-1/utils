#ifndef PRINT_H
#define PRINT_H 1

/* Get the corresponding format specifier of a type. */
#define PRINTF_FMT(T)                        \
    _Generic((T),                            \
        _Bool                   : "%d",      \
        char                    : "%c",      \
        signed char             : "%hhd",    \
        unsigned char           : "%hhu",    \
        short int               : "%hd",     \
        int                     : "%d",      \
        long int                : "%ld",     \
        long long int           : "%lld",    \
        unsigned short int      : "%hu",     \
        unsigned int            : "%u",      \
        unsigned long int       : "%lu",     \
        unsigned long long int  : "%llu",    \
        float                   : "%f",      \
        double                  : "%f",      \
        long double             : "%Lf",     \
        char *                  : "%s",      \
        wchar_t *               : "%ls",     \
        void *                  : "%p"       \
    )

#define print(x)    printf(PRINTF_FMT(x), x)

/* A separate call to putchar() is required because _Generic is not a macro, but
 * a primary expression. As such it is evaluated at a later translation phase (7)
 * than string concatenation (phase 6). */
#define println(x)  printf(PRINTF_FMT(x), x), putchar('\n')

#endif /* PRINT_H */
