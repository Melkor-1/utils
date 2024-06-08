#ifndef MIN_H
#define MIN_H 1

#include <limits.h>

#include "max.h"

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

#define gen_basic_min(return_type, param_type1, param_type2, suffix)   \
    ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline return_type min_##suffix(param_type1 a, param_type2 b) \
    { return a < b ? (return_type) a : (return_type) b; }

#define gen_nonbasic_min(return_type, param_type1, param_type2, cast_type, suffix) \
    ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline return_type min_##suffix(param_type1 a, param_type2 b) \
    { return max_##suffix(a, b) == a ? b : (cast_type) a; }

gen_basic_min(int, int, int, i_i)
gen_basic_min(long, int, long, i_li)
gen_basic_min(long long, int, long long, i_lli)

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline int min_i_ui(int a, unsigned b)
{
    return max_i_ui(a, b) == b ? a : (int) b;
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline int min_i_uli(int a, unsigned long b)
{
    return max_i_uli(a, b) == b ? a : (int) b;
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline int min_i_ulli(int a, unsigned long long b)
{
    return max_i_ulli(a, b) == b ? a : (int) b;
}

#define MIN_I(a, b)     _Generic((b) + 0,                               \
                            int:                    min_i_i,            \
                            unsigned int:           min_i_ui,           \
                            long int:               min_i_li,           \
                            unsigned long int:      min_i_uli,          \
                            long long int:          min_i_lli,          \
                            unsigned long long int: min_i_ulli)((a), (b))

gen_basic_min(unsigned, unsigned, unsigned, ui_ui)
gen_basic_min(unsigned, unsigned, unsigned long, ui_uli)
gen_basic_min(unsigned, unsigned, unsigned long long, ui_ulli)

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline int min_ui_i(unsigned a, int b)
{
    return min_i_ui(b, a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long min_ui_li(unsigned a, long b)
{
    #if LONG_MAX >= UINT_MAX
    return max_ui_li(a, b) == b ? (long) a : b;
    #else
    return max_ui_li(a, b) == a ? b : (long) a;
    #endif
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long long min_ui_lli(unsigned a, long long b)
{
    #if LLONG_MAX >= UINT_MAX
    return max_ui_lli(a, b) == b ? (long long) a : b;
    #else
    return max_ui_lli(a, b) == a ? b : (long long) a;
    #endif
}

#define MIN_UI(a, b)     _Generic((b) + 0,                              \
                            int:                    min_ui_i,           \
                            unsigned int:           min_ui_ui,          \
                            long int:               min_ui_li,          \
                            unsigned long int:      min_ui_uli,         \
                            long long int:          min_ui_lli,         \
                            unsigned long long int: min_ui_ulli)((a), (b))

gen_basic_min(long, long, int, li_i)
gen_basic_min(long, long, long, li_li)
gen_basic_min(long long, long, long long, li_lli)

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long min_li_ui(long a, unsigned b)
{
    return min_ui_li(b, a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long min_li_uli(long a, unsigned long b)
{
    return max_li_uli(a, b) == b ? a : (long) b;
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long min_li_ulli(long a, unsigned long long b)
{
    return max_li_ulli(a, b) == b ? a : (long) b;
}

#define MIN_LI(a, b)    _Generic((b) + 0,                               \
                            int:                    min_li_i,           \
                            unsigned int:           min_li_ui,          \
                            long int:               min_li_li,          \
                            unsigned long int:      min_li_uli,         \
                            long long int:          min_li_lli,         \
                            unsigned long long int: min_li_ulli)((a), (b))

gen_basic_min(unsigned, unsigned long, unsigned, uli_ui)
gen_basic_min(unsigned long, unsigned long, unsigned long, uli_uli)
gen_basic_min(unsigned long, unsigned long, unsigned long long, uli_ulli)

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline int min_uli_i(unsigned long a, int b)
{
    return min_i_uli(b, a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long min_uli_li(unsigned long a, long b)
{
    return min_li_uli(b, a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long long min_uli_lli(unsigned long a, long long b)
{
    #if LLONG_MAX >= ULONG_MAX
    return max_uli_lli(a, b) == b ? (long long) a : b;
    #else
    return max_uli_lli(a, b) == a ? b : (long long) a;
    #endif
}

#define MIN_ULI(a, b)   _Generic((b) + 0,                               \
                            int:                    min_uli_i,          \
                            unsigned int:           min_uli_ui,         \
                            long int:               min_uli_li,         \
                            unsigned long int:      min_uli_uli,        \
                            long long int:          min_uli_lli,        \
                            unsigned long long int: min_uli_ulli)((a), (b))

gen_basic_min(long long, long long, int, lli_i)
gen_basic_min(long long, long long, long, lli_li)
gen_basic_min(long long, long long, long long, lli_lli)

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long long min_lli_ui(long long a, unsigned b)
{
    return min_ui_lli(b, a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long long min_lli_uli(long long a, unsigned long b)
{
    return min_uli_lli(b, a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long long min_lli_ulli(long long a, unsigned long long b)
{
    return max_lli_ulli(a, b) == b ? a : (long long) b;
}

#define MIN_LLI(a, b)   _Generic((b) + 0,                               \
                            int:                    min_lli_i,          \
                            unsigned int:           min_lli_ui,         \
                            long int:               min_lli_li,         \
                            unsigned long int:      min_lli_uli,        \
                            long long int:          min_lli_lli,        \
                            unsigned long long int: min_lli_ulli)((a), (b))

gen_basic_min(unsigned, unsigned long long, unsigned, ulli_ui)
gen_basic_min(unsigned long, unsigned long long, unsigned long, ulli_uli)
gen_basic_min(unsigned long long, unsigned long long, unsigned long long, ulli_ulli)

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline int min_ulli_i(unsigned long long a, int b)
{
    return min_i_ulli(b, a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long min_ulli_li(unsigned long long a, long b)
{
    return min_li_ulli(b, a);
}

ATTRIB_ALWAYS_INLINE ATTRIB_CONST static inline long long min_ulli_lli(unsigned long long a, long long b)
{
    return min_lli_ulli(b, a);
}

#define MIN_ULLI(a, b)  _Generic((b) + 0,                               \
                            int:                    min_ulli_i,         \
                            unsigned int:           min_ulli_ui,        \
                            long int:               min_ulli_li,        \
                            unsigned long int:      min_ulli_uli,       \
                            long long int:          min_ulli_lli,       \
                            unsigned long long int: min_ulli_ulli)((a), (b))

/* + 0 to implicitly promotes types shorter than int to int. */
#define MIN(a, b)       _Generic((a) + 0,                               \
                            int:                    MIN_I((a), (b)),    \
                            unsigned int:           MIN_UI((a), (b)),   \
                            long int:               MIN_LI((a), (b)),   \
                            unsigned long int:      MIN_ULI((a), (b)),  \
                            long long int:          MIN_LLI((a), (b)),  \
                            unsigned long long int: MIN_ULLI((a), (b)))

#undef ATTRIB_ALWAYS_INLINE
#undef ATTRIB_CONST
#undef C23_PLACEHOLDER

#endif  /* MIN_H */
