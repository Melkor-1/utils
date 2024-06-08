#ifndef MAX_H
#define MAX_H 1

#include <limits.h>

/* Current versions of gcc and clang support -std=c2x which sets 
 * __STDC_VERSION__ to this placeholder value. GCC 14.1 does not set
 * __STDC_VERSION__ to 202311L with the std=c23 flag, but Clang 18.1 does. */
#define C23_PLACEHOLDER 202000L
    
#if defined(__STDC_VERSION__) && __STDC_VERSION >= C23_PLACEHOLDER
    /* gnu::const is stricter than unsequenced, but it doesn't matter here. */
    #define ATTRIB_CONST            [[unsequenced]]
#elif defined(__GNUC__) || defined(__clang__) || defined(__INTEL_LLVM_COMPILER)
    #define ATTRIB_CONST            __attribute__((const))
#else
    #define ATTRIB_CONST            /**/
#endif

#if defined(__GNUC__) || defined(__clang__) || defined(__INTEL_LLVM_COMPILER)
    #define ATTRIB_ALWAYS_INLINE    __attribute__((always_inline))
#else
    #define ATTRIB_ALWAYS_INLINE    /**/
#endif

#define gen_basic_max(return_type, param_type1, param_type2, suffix)   \
    ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline return_type max_##suffix(param_type1 a, param_type2 b) \
    {   return a > b ? a : b;   }

gen_basic_max(int, int, int, i_i)
gen_basic_max(long, int, long, i_li)
gen_basic_max(long long, int, long long, i_lli)

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned int max_i_ui(int a, unsigned b)
{
    return a < 0 ? b : (b > (unsigned) a ? b : (unsigned) a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned long max_i_uli(int a, unsigned long b)
{
    return a < 0 ? b : (b > (unsigned long) a ? b : (unsigned long) a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned long long max_i_ulli(int a, unsigned long long b)
{
    return a < 0 ? b : (b > (unsigned long long) a ? b : (unsigned long long) a);
}

#define MAX_I(a, b)     _Generic((b) + 0,                               \
                            int:                    max_i_i,            \
                            unsigned int:           max_i_ui,           \
                            long int:               max_i_li,           \
                            unsigned long int:      max_i_uli,          \
                            long long int:          max_i_lli,          \
                            unsigned long long int: max_i_ulli)((a), (b))

gen_basic_max(unsigned, unsigned, unsigned, ui_ui)
gen_basic_max(unsigned long, unsigned, unsigned long, ui_uli)
gen_basic_max(unsigned long long, unsigned, unsigned long long, ui_ulli)

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned max_ui_i(unsigned a, int b)
{
    return max_i_ui(b, a);
}

#if LONG_MAX >= UINT_MAX
ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long max_ui_li(unsigned a, long b)
{
    return (long) a > b ? (long) a : b;
}
#else
ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned max_ui_li(unsigned a, long b)
{
    return b < 0 ? a : (a > (unsigned) b ? a : (unsigned) b);
}
#endif

#if LLONG_MAX >= UINT_MAX
ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long long max_ui_lli(unsigned a, long long b)
{
    return (long long) a > b ? (long long) a : b;
}
#else
ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned max_ui_lli(unsigned a, long long b)
{
    return b < 0 ? a : (a > (unsigned) b ? a : (unsigned) b);
}
#endif

#define MAX_UI(a, b)     _Generic((b) + 0,                              \
                            int:                    max_ui_i,           \
                            unsigned int:           max_ui_ui,          \
                            long int:               max_ui_li,          \
                            unsigned long int:      max_ui_uli,         \
                            long long int:          max_ui_lli,         \
                            unsigned long long int: max_ui_ulli)((a), (b))

gen_basic_max(long, long, int, li_i)
gen_basic_max(long, long, long, li_li)
gen_basic_max(long long, long, long long, li_lli)

#if LONG_MAX >= UINT_MAX
ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long max_li_ui(long a, unsigned b)
#else 
ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned max_li_ui(long a, unsigned b)
#endif
{
    return max_ui_li(b, a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned long max_li_uli(long a, unsigned long b)
{
    return a < 0 ? b : (b > (unsigned long) a ? b : (unsigned long) a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned long long max_li_ulli(long a, unsigned long long b)
{
    return a < 0 ? b : (b > (unsigned long long) a ? b : (unsigned long long) a);
}


#define MAX_LI(a, b)    _Generic((b) + 0,                               \
                            int:                    max_li_i,           \
                            unsigned int:           max_li_ui,          \
                            long int:               max_li_li,          \
                            unsigned long int:      max_li_uli,         \
                            long long int:          max_li_lli,         \
                            unsigned long long int: max_li_ulli)((a), (b))

gen_basic_max(unsigned long, unsigned long, unsigned, uli_ui)
gen_basic_max(unsigned long, unsigned long, unsigned long, uli_uli)
gen_basic_max(unsigned long long, unsigned long, unsigned long long, uli_ulli)

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned long max_uli_i(unsigned long a, int b)
{
    return max_i_uli(b, a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned long max_uli_li(unsigned long a, long b)
{
    return max_li_uli(b, a);
}

#if LLONG_MAX >= ULONG_MAX
ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long long max_uli_lli(unsigned long a, long long b)
{
    return (long long) a > b ? (long long) a : b;
}
#else 
ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned long max_uli_lli(unsigned long a, long long b)
{
    return b < 0 ? a : (a > (unsigned long) b ? a : (unsigned long) b);
}
#endif

#define MAX_ULI(a, b)   _Generic((b) + 0,                               \
                            int:                    max_uli_i,          \
                            unsigned int:           max_uli_ui,         \
                            long int:               max_uli_li,         \
                            unsigned long int:      max_uli_uli,        \
                            long long int:          max_uli_lli,        \
                            unsigned long long int: max_uli_ulli)((a), (b))

gen_basic_max(long long, long long, int, lli_i)
gen_basic_max(long long, long long, long, lli_li)
gen_basic_max(long long, long long, long long, lli_lli)

#if LLONG_MAX >= UINT_MAX
ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long long max_lli_ui(long long a, unsigned b)
#else 
ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned max_lli_ui(long long a, unsigned b)
#endif
{
    return max_ui_lli(b, a);
}

#if LLONG_MAX >= ULONG_MAX
ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long long max_lli_uli(long long a, unsigned long b)
#else
ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned long max_lli_uli(long long a, unsigned long b)
#endif
{
    return max_uli_lli(b, a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned long long max_lli_ulli(long long a, unsigned long long b)
{
    return a < 0 ? b : (b > (unsigned long long) a ? b : (unsigned long long) a);
}

#define MAX_LLI(a, b)   _Generic((b) + 0,                               \
                            int:                    max_lli_i,          \
                            unsigned int:           max_lli_ui,         \
                            long int:               max_lli_li,         \
                            unsigned long int:      max_lli_uli,        \
                            long long int:          max_lli_lli,        \
                            unsigned long long int: max_lli_ulli)((a), (b))

gen_basic_max(unsigned long long, unsigned long long, unsigned, ulli_ui)
gen_basic_max(unsigned long long, unsigned long long, unsigned long, ulli_uli)
gen_basic_max(unsigned long long, unsigned long long, unsigned long long, ulli_ulli)

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned long long max_ulli_i(unsigned long long a, int b)
{
    return max_i_ulli(b, a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned long long max_ulli_li(unsigned long long a, long b)
{
    return max_li_ulli(b, a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline unsigned long long max_ulli_lli(unsigned long long a, long long b)
{
    return max_lli_ulli(b, a);
}

#define MAX_ULLI(a, b)  _Generic((b),                                   \
                            int:                    max_ulli_i,         \
                            unsigned int:           max_ulli_ui,        \
                            long int:               max_ulli_li,        \
                            unsigned long int:      max_ulli_uli,       \
                            long long int:          max_ulli_lli,       \
                            unsigned long long int: max_ulli_ulli)((a), (b))

#define MAX(a, b)       _Generic((a) + 0,                               \
                            int:                    MAX_I((a), (b)),    \
                            unsigned int:           MAX_UI((a), (b)),   \
                            long int:               MAX_LI((a), (b)),   \
                            unsigned long int:      MAX_ULI((a), (b)),  \
                            long long int:          MAX_LLI((a), (b)),  \
                            unsigned long long int: MAX_ULLI((a), (b)))

#undef ATTRIB_ALWAYS_INLINE
#undef ATTRIB_CONST
#undef C23_PLACEHOLDER

#endif  /* MAX_H */
