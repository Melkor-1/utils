#ifndef PRINT_H
#define PRINT_H 

/* Get the corresponding format specifier of a type. */
#define PRINTF_FMT(T) _Generic((T),                                 \
                _Bool                   : "%d",                     \
                char                    : "%c",                     \
                signed char             : "%hhd",                   \
                unsigned char           : "%hhu",                   \
                short int               : "%hd",                    \
                int                     : "%d",                     \
                long int                : "%ld",                    \
                long long int           : "%lld",                   \
                unsigned short int      : "%hu",                    \
                unsigned int            : "%u",                     \
                unsigned long int       : "%lu",                    \
                unsigned long long int  : "%llu",                   \
                float                   : "%f",                     \
                double                  : "%f",                     \
                long double             : "%Lf",                    \
                char *                  : "%s",                     \
                wchar_t *               : "%ls",                    \
                default                 : TO_VOID_PTR(T))

#define PTR_FORMAT(P) _Generic(TO_VOID_PTR(P),  \
                void const *: "%p",             \
                void *      : "%p")

/* If either of the if-true or if-false expressions of ?: is void *, then the
 * of the result shall also be void * (plus const if either is const). */
#define TO_VOID_PTR(P)  (1 ? (P) : (void *)(P))

#define print(x)    printf(PRINTF_FMT(x), x)

/* A separate call to putchar() is required because _Generic is not a macro, but
 * a primary expression. As such it is evaluated at a later translation phase (7)
 * than string concatenation (phase 6). */
#define println(x)  printf(PRINTF_FMT(x), x), putchar('\n')

#endif /* PRINT_H */
