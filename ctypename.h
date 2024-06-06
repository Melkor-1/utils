#ifndef CTYPENAME_H
#define CTYPENAME_H 1

#define C23_PLACEHOLDER 202000L

#if !(defined(__STDC_VERSION__) && __STDC_VERSION__ >= C23_PLACEHOLDER)
    #include <stdbool.h>
#endif
    
/* Get the name of a type. */
#define ctypename(T) _Generic((T),                                  \
                _Bool                   : "_Bool",                  \
                unsigned char           : "unsigned char",          \
                char                    : "char",                   \
                signed char             : "signed char",            \
                short int               : "short int",              \
                unsigned short int      : "unsigned short int",     \
                int                     : "int",                    \
                unsigned int            : "unsigned int",           \
                long int                : "long int",               \
                unsigned long int       : "unsigned long int",      \
                long long int           : "long long int",          \
                unsigned long long int  : "unsigned long long int", \
                float                   : "float",                  \
                double                  : "double",                 \
                long double             : "long double",            \
                char *                  : "char *",                 \
                void *                  : "void *",                 \
                default                 : "other")

#endif  /* CTYPENAME_H */
