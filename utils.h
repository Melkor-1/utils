#ifndef UTIL_H
#define UTIL_H 1

/**
 * Author: Melkor-1
 * Date: Friday, June 7, 2024
 * 
 * Declares utility constants, macros, and functions. */

#include <complex.h>
#include <inttypes.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

/* Would these be better as `static constexpr unsigned char`s? */
#define CHARIFY_0   '0' 
#define CHARIFY_1   '1'
#define CHARIFY_2   '2' 
#define CHARIFY_3   '3'
#define CHARIFY_4   '4'
#define CHARIFY_5   '5'
#define CHARIFY_6   '6'
#define CHARIFY_7   '7'
#define CHARIFY_8   '8'
#define CHARIFY_9   '9'
#define CHARIFY_A   'A'
#define CHARIFY_B   'B'
#define CHARIFY_C   'C'
#define CHARIFY_D   'D'
#define CHARIFY_E   'E'
#define CHARIFY_F   'F'
#define CHARIFY_G   'G'
#define CHARIFY_H   'H'
#define CHARIFY_I   'I'
#define CHARIFY_J   'J'
#define CHARIFY_K   'K'
#define CHARIFY_L   'L'
#define CHARIFY_M   'M'
#define CHARIFY_N   'N'
#define CHARIFY_O   'O'
#define CHARIFY_P   'P'
#define CHARIFY_Q   'Q'
#define CHARIFY_R   'R'
#define CHARIFY_S   'S'
#define CHARIFY_T   'T'
#define CHARIFY_U   'U'
#define CHARIFY_V   'V'
#define CHARIFY_W   'W'
#define CHARIFY_X   'X'
#define CHARIFY_Y   'Y'
#define CHARIFY_Z   'Z'
#define CHARIFY__   '_'
#define CHARIFY_a   'a'
#define CHARIFY_b   'b'
#define CHARIFY_c   'c'
#define CHARIFY_d   'd'
#define CHARIFY_e   'e'
#define CHARIFY_f   'f'
#define CHARIFY_g   'g'
#define CHARIFY_h   'h'
#define CHARIFY_i   'i'
#define CHARIFY_j   'j'
#define CHARIFY_k   'k'
#define CHARIFY_l   'l'
#define CHARIFY_m   'm'
#define CHARIFY_n   'n'
#define CHARIFY_o   'o'
#define CHARIFY_p   'p'
#define CHARIFY_q   'q'
#define CHARIFY_r   'r'
#define CHARIFY_s   's'
#define CHARIFY_t   't'
#define CHARIFY_u   'u'
#define CHARIFY_v   'v'
#define CHARIFY_w   'w'
#define CHARIFY_x   'x'
#define CHARIFY_y   'y'
#define CHARIFY_z   'z'

#define CONCAT2_INDIRECT(A, B)      A ## B
#define STRINGIFY_INDIRECT(A)       #A

/**
 * Concatenate A to B together to form a single token. */
#define CONCAT2(A, B)               CONCAT2_INDIRECT(A, B)

/**
 * Macro that "char-ifies" its argument, e.g., CHARIFY(x) becomes 'x'.
 *
 * X can only be in the set [0-9_A-Za-z]. */
#define CHARIFY(X)                  CONCAT2(CHARIFY_, X)

/**
 * Macro that "string-ifies" its argument, e.g., STRINGIFY(x) becomes "x".
 *
 * X - The unquoted string to stringify. */
#define STRINGIFY(X)                STRINGIFY_INDIRECT(X)

/**
 * Synthesises a name prefixed by PREFIX unique to the line on which it is used.
 *
 * Notes: 
 * 1) All uses for a given PREFIX that refer to the same name must be on the same
 *    line. This is not a problem within macro definitions, but would not work
 *    outside of them since there is no way to refer to a previously used unique
 *    name. But if the intent is to have multiple "unique" names on a single line,
 *    the value of PREFIX must be different. 
 *
 * 2) If UNIQUE_NAME is used within a macro and that macro does not expose
 *    PREFIX (but picks one), then using the macro twice on the same line
 *    (possibly nested, as in MAX(a, MAX(b, c)) ) will cause different
 *    variables to end up with the same unique names.
 *
 * This is generally useful in macros to avoid any conflict with existing
 * identifiers, and also because having a unique name allows you to use the
 * same macro multiple times in the same scope or nested scopes and avoid
 * "shadows" warnings. */
#define UNIQUE_NAME(PREFIX)         CONCAT2(CONCAT2(PREFIX, _), __LINE__)     

/**
 * C version of C++'s const_char.
 *
 * T    - The type to cast to.
 * EXPR - The expression to cast.
 *
 * Note: This macro can not actually implement C++'s const char because there 
 * is no way to do it in C. It merely serves as a visual cue for the type of 
 * cast meant. */
#define CONST_CAST(T, EXPR)         ((T)(EXPR))

/**
 * C version of C++'s static_cast. 
 *
 * T    - The type to cast to.
 * EXPR - The expression to cast.
 *
 * Note: This macro can not actually implement C++'s static_cast because there
 * is no way to do it in C. It serves merely as a visual cue for the type of
 * cast meant. */
#define STATIC_CAST(T, EXPR)        ((T)(EXPR))

/**
 * Cast either from or to an integral type --- similar to C++'s 
 * reinterpret_cast, but for integers only.
 *
 * T    - The type to cast to.
 * EXPR - The expression to cast.
 *
 * Note: In C++, this would be done via reinterpret_cast, but it is not
 * posible to implement that in C that works for both pointers and integers. */
#define INTEGER_CAST(T, EXPR)       ((T)(uintmax_t)(EXPR))

/**
 * Cast either from or to a pointer type --- similar to C++'s
 * reinterpret_cast, but for pointers only.
 *
 * T    - The type to cast to.
 * EXPR - The expression to cast.
 *
 * Note: This macro silences a "cast to pointer from integer of different size"
 * warning. In C++, this would be done via reinterpret_cast, but it is not
 * possible to implement that in C that works for both pointers and integers. */
#define POINTER_CAST(T, EXPR)       ((T)(uintptr_t)(EXPR))

/**
 * Expands to 1 (true) if VAL is within the range of LO to HI (inclusive),
 * else 0 (false).
 *
 * Note: RANGE() evaluates VAL_ more than once. */
#define RANGE(VAL, LO, HI)   \
    (((VAL) >= (LO)) && ((VAL) <= (HI)))

/**
 * Expands to 1 (true) if VAL is within the range of LO to HI (exclusive),
 * else 0 (false).
 *
 * Note: RANGE() evaluates VAL more than once. */ 
#define RANGEM1(VAL, LO, HI) \
    (((VAL) >= (LO)) && ((VAL) < (HI)))

/**
 * Embeds the given statements into a compound statement block. */
#define BLOCK(...)                  do { __VA_ARGS__ } while (false)

/**
 * To enable debugging trace, define DEBUG. */
#ifdef DEBUG
    #define TRACE_ON    1
#else
    #define TRACE_ON    0
#endif

/**
 * When debugging trace is enabled, TRACE() prints to stderr with the formatted
 * message, source file name, line number, and function name. 
 *
 * FMT - The printf() format string literal to use.
 * ... - The printf() arguments. */
#define TRACE(FMT, ...)                                             \
    BLOCK(                                                          \
        if (TRACE_ON) {                                             \
            /* "" provides rudimentary type-checking. */            \
            fprintf(stderr, "%s::%d::%s():: " FMT "", __FILE__,     \
                    __LINE__, __func__, __VA_OPT__(,) __VA_ARGS__); \
        }                                                           \
    )

/**
 * Asserts that this line of code is run at most once --- useful in
 * initialization functions that must be called at most once. For example:
 *
 *     void initialize(void) {
 *         ASSERT_RUN_ONCE();
 *         // ...
 *     } 
 *
 * Note: This implementation is not thread-safe. */
#ifndef NDEBUG
    #define ASSERT_RUN_ONCE()                   \
        BLOCK(                                  \
            static bool UNIQUE_NAME(called);    \
            assert(!UNIQUE_NAME(called));       \
            UNIQUE_NAME(called) = true;         \
        )
#else
    #define ASSERT_RUN_ONCE()       (void)0
#endif  /* NDEBUG */

/**
 * Convenience macro for iterating N times. */
#define FOR_N_TIMES(N)                                                        \
    for (size_t UNIQUE_NAME(i) = 0;                                           \
         UNIQUE_NAME(i) < STATIC_CAST(size_t, (N));                           \
         STATIC_ASSERT_EXPR(IS_INTEGRAL(N), #N " must be an integral type."), \
         ++UNIQUE_NAME(i))

/**
 * Checks (at compile-time) if an expression is compatible with a type.
 *
 * EXPR - An expression. It is not evaluted.
 * T    - The type to check against.
 *
 * Note: Only an expression can be compared with a type. Two expressions or 
 * two type names can not be directly compared. 
 *
 * To compare two types, a compound literal can be used to create a literal of
 * a given type like so:
 *     
 *     IS_COMPATIBLE((size_t){0}, unsigned long);
 *
 * To test two variables for type compatibility, typeof can be used like so:
 *     
 *     IS_COMPATIBLE(x, typeof(y));
 *
 * Also note that this would not work for arrays, nor when one argument is a
 * pointer and another an array.
 *
 * Returns to 1 (true) if EXPR is compatible with T, 0 (false) elsewise. */
#define IS_COMPATIBLE(EXPR, T) \
    _Generic((EXPR),           \
        T      : 1,            \
        default: 0             \
    )     

/**
 * Checks (at compile-time) if T has type nullptr_t.
 *
 * T - An expression. It is not evaluted. 
 *
 * Returns 1 (true) if T is the type nullptr_t, 0 (false) elsewise. */
#define IS_NULLPTR(T) \
    _Generic((T),     \
        nullptr_t: 1, \
        default  : 0  \
    )

/**
 * Checks (at compile-time) if T has type FILE *.
 *
 * T - An expression. It is not evaluted. 
 *
 * Returns 1 (true) if T is the type FILE *, 0 (false) elsewise. */
#define IS_FILE_PTR(T) \
    _Generic((T),      \
        FILE * : 1,    \
        default: 0     \
    )

/**
 * Checks (at compile-time) whether T is an array.
 *
 * T - An expression. It is not evaluted. 
 *
 * Note: IS_ARRAY() distinguishes between arrays and pointers, not between
 *       arrays and arbitrary other types.
 * 
 * Returns 1 (true) only if T is an array; 0 (false) elsewise. 
 *
 * See also: https://stackoverflow.com/a/77881417/99089 */
#define IS_ARRAY(T)                 \
    _Generic( &(T),                 \
        typeof(*T) (*)[]    : 1,    \
        default             : 0     \
    )

/**
 * Checks (at compile-time) whether A is a pointer.
 *
 * T - An expression. It is not evaluted. 
 *
 * Note: IS_POINTER() distinguishes between arrays and pointers, not between
 *       pointers and arbitrary other types.
 * 
 * Returns 1 (true) only if T is a pointer; 0 (false) elsewise. 
 *
 * See also: https://stackoverflow.com/a/77881417/99089 */
#define IS_POINTER(T)   !IS_ARRAY(T)

/**
 * Implements a "static if" similar to "if constexpr" in C++.
 *
 * EXPR - An expression (evaluated at compile-time).
 * THEN - An expression returned only if EXPR is non-zero (true).
 * ELSE - An expression returned only if EXPR is zero (false).
 *
 * Returns:
 *     THEN only if EXPR is non-zero (true); or:
 *     ELSE only if EXPR is zero (false). */
#define STATIC_IF(EXPR, THEN, ELSE)     \
    _Generic( &(char[1 + !!(EXPR)]){0}, \
        char (*)[2]: (THEN),            \
        char (*)[1]: (ELSE)             \
    )

/**
 * Checks (at compile-time) whether char is signed or unsigned.
 *
 * Returns 1 (true) if char is signed, else 0 (false). */
#define IS_CHAR_SIGNED          STATIC_IF((char)-1 < 0, 1, 0)

/**
 * Checks (at compile-time) whether sig_atomic_t is signed or unsigned.
 *
 * Returns 1 (true) if sig_atomic_t is signed, else 0 (false). */
#define IS_SIG_ATOMIC_T_SIGNED  STATIC_IF((sig_atomic_t)-1 < 0, 1, 0)

/**
 * Checks (at compile-time) whether wint_t is signed or unsigned.
 *
 * Returns 1 (true) if wint_t is signed, else 0 (false). */
#define IS_WINT_T_SIGNED        STATIC_IF((wint_t)-1 < 0, 1, 0)

/**
 * Checks (at compile-time) whether wchar_t is signed or unsigned.
 *
 * Returns 1 (true) if wchar_t is signed, else 0 (false). */
#define IS_WCHAR_T_SIGNED       STATIC_IF((wchar_t)-1 < 0, 1, 0)

#define IS_SIGNED15(T)                                  \
    _Generic((T),                                       \
        wchar_t               : IS_WCHAR_T_SIGNED,      \
        default               : 0                       \
    )

#define IS_SIGNED14(T)                                  \
    _Generic((T),                                       \
        wint_t                : IS_WINT_T_SIGNED,       \
        default               : IS_SIGNED15(T)          \
    )

#define IS_SIGNED13(T)                                  \
    _Generic((T),                                       \
        sig_atomic_t          : IS_SIG_ATOMIC_T_SIGNED, \
        default               : IS_SIGNED14(T)          \
    )

#define IS_SIGNED12(T)                                  \
    _Generic((T),                                       \
        int_fast64_t          : 1,                      \
        default               : IS_SIGNED13(T)          \
    )

#define IS_SIGNED11(T)                                  \
    _Generic((T),                                       \
        int_fast32_t          : 1,                      \
        default               : IS_SIGNED12(T)          \
    )

#define IS_SIGNED10(T)                                  \
    _Generic((T),                                       \
        int_fast16_t          : 1,                      \
        default               : IS_SIGNED11(T)          \
    )

#define IS_SIGNED9(T)                                   \
    _Generic((T),                                       \
        int_fast8_t           : 1,                      \
        default               : IS_SIGNED10(T)          \
    )

#define IS_SIGNED8(T)                                   \
    _Generic((T),                                       \
        int_least64_t          : 1,                     \
        default                : IS_SIGNED9(T)          \
    )
#define IS_SIGNED7(T)                                   \
    _Generic((T),                                       \
        int_least32_t          : 1,                     \
        default                : IS_SIGNED8(T)          \
    )
#define IS_SIGNED6(T)                                   \
    _Generic((T),                                       \
        int_least16_t          : 1,                     \
        default                : IS_SIGNED7(T)          \
    )

#define IS_SIGNED5(T)                                   \
    _Generic((T),                                       \
        int_least8_t           : 1,                     \
        default                : IS_SIGNED6(T)          \
    )

#define IS_SIGNED4(T)                                   \
    _Generic((T),                                       \
        int8_t                 : 1,                     \
        int16_t                : 1,                     \
        int32_t                : 1,                     \
        int64_t                : 1,                     \
        default                : IS_SIGNED5(T)          \
    )

#define IS_SIGNED3(T)                                   \
    _Generic((T),                                       \
        intptr_t               : 1,                     \
        default                : IS_SIGNED4(T)          \
    )

#define IS_SIGNED2(T)                                   \
    _Generic((T),                                       \
        intmax_t               : 1,                     \
        default                : IS_SIGNED3(T)          \
    )

#define IS_SIGNED1(T)                                   \
    _Generic((T),                                       \
        ptrdiff_t              : 1,                     \
        default                : IS_SIGNED2(T)          \
    )

/**
 * Checks (at compile-time) whether the type of T is a signed type. 
 *
 * T - An expression. It is not evaluated. 
 *
 * Note: This would not detect _BitInt. 
 *
 * Returns 1 (true) only if T is a signed type; 0 (false) elsewise. */
#define IS_SIGNED(T)                                    \
    _Generic((T),                                       \
        char                   : IS_CHAR_SIGNED,        \
        short int              : 1,                     \
        int                    : 1,                     \
        long int               : 1,                     \
        long long int          : 1,                     \
        default                : IS_SIGNED1(T)          \
    )

#define IS_UNSIGNED15(T)                                \
    _Generic((T),                                       \
        wchar_t               : !IS_WCHAR_T_SIGNED,     \
        default               : 0                       \
    )

#define IS_UNSIGNED14(T)                                \
    _Generic((T),                                       \
        wint_t                : !IS_WINT_T_SIGNED,      \
        default               : IS_UNSIGNED15(T)        \
    )

#define IS_UNSIGNED13(T)                                \
    _Generic((T),                                       \
        sig_atomic_t          : !IS_SIG_ATOMIC_T_SIGNED,\
        default               : IS_UNSIGNED14(T)        \
    )

#define IS_UNSIGNED12(T)                                \
    _Generic((T),                                       \
        uint_fast64_t          : 1,                     \
        default               : IS_UNSIGNED13(T)        \
    )

#define IS_UNSIGNED11(T)                                \
    _Generic((T),                                       \
        uint_fast32_t          : 1,                     \
        default               : IS_UNSIGNED12(T)        \
    )

#define IS_UNSIGNED10(T)                                \
    _Generic((T),                                       \
        uint_fast16_t          : 1,                     \
        default               : IS_UNSIGNED11(T)        \
    )

#define IS_UNSIGNED9(T)                                 \
    _Generic((T),                                       \
        uint_fast8_t           : 1,                     \
        default               : IS_UNSIGNED10(T)        \
    )

#define IS_UNSIGNED8(T)                                 \
    _Generic((T),                                       \
        uint_least64_t          : 1,                    \
        default                : IS_UNSIGNED9(T)        \
    )
#define IS_UNSIGNED7(T)                                 \
    _Generic((T),                                       \
        uint_least32_t          : 1,                    \
        default                : IS_UNSIGNED8(T)        \
    )
#define IS_UNSIGNED6(T)                                 \
    _Generic((T),                                       \
        uint_least16_t          : 1,                    \
        default                : IS_UNSIGNED7(T)        \
    )

#define IS_UNSIGNED5(T)                                 \
    _Generic((T),                                       \
        uint_least8_t           : 1,                    \
        default                : IS_UNSIGNED6(T)        \
    )

#define IS_UNSIGNED4(T)                                 \
    _Generic((T),                                       \
        uint8_t                : 1,                     \
        uint16_t               : 1,                     \
        uint32_t               : 1,                     \
        uint64_t               : 1,                     \
        default                : IS_UNSIGNED5(T)        \
    )

#define IS_UNSIGNED3(T)                                 \
    _Generic((T),                                       \
        uintptr_t              : 1,                     \
        default                : IS_UNSIGNED4(T)        \
    )

#define IS_UNSIGNED2(T)                                 \
    _Generic((T),                                       \
        uintmax_t              : 1,                     \
        default                : IS_UNSIGNED3(T)        \
    )

#define IS_UNSIGNED1(T)                                 \
    _Generic((T),                                       \
        size_t                 : 1,                     \
        default                : IS_UNSIGNED2(T)        \
    )

/**
 * Checks (at compile-time) whether the type of T is a unsigned type. 
 *
 * T - An expression. It is not evaluated. 
 *
 * Note: This would not detect _BitInt. 
 *
 * Returns 1 (true) only if T is a unsigned type; 0 (false) elsewise. */
#define IS_UNSIGNED(T)                                  \
    _Generic((T),                                       \
        _Bool                  : 1,                     \
        char                   : !IS_CHAR_SIGNED,       \
        unsigned char          : 1,                     \
        unsigned short int     : 1,                     \
        unsigned int           : 1,                     \
        unsigned long int      : 1,                     \
        unsigned long long int : 1,                     \
        default                : IS_UNSIGNED1(T)        \
    )

/**
 * Checks (at compile-time) whether the type of T is any integral type. 
 *
 * T - An expression. It is not evaluated. 
 *
 * Note: This would not detect _BitInt.
 * 
 * Returns 1 (true) if T is any integral type, 0 (false) elsewise. */
#define IS_INTEGRAL(T)  (IS_SIGNED(T) || IS_UNSIGNED(T))

/**
 * Checks (at compile-time) whether the type of T is a floating-point type.
 *
 * T - An expression. It is not evaluated. 
 *
 * Returns 1 (true) if T is a floating-point type, 0 (false) elsewise. */
#if defined(__STDC_IEC_60559_DFP__)         \
    && defined(__STDC_IEC_60559_COMPLEX__)  \
    && defined(_Imaginary_I)
    #define IS_FLOATING_POINT(T)            \
        _Generic((T),                       \
            float                 : 1,      \
            double                : 1,      \
            long double           : 1,      \
            float _Complex        : 1,      \
            double _Complex       : 1,      \
            long double _Complex  : 1,      \
            float _Imaginary      : 1,      \
            double _Imaginary     : 1,      \
            long double _Imaginary: 1,      \
            _Decimal32            : 1,      \
            _Decimal64            : 1,      \
            _Decimal128           : 1,      \
            default               : 0       \
        )
#elif defined(__STDC_IEC_60559_COMPLEX__)   \
      && defined(_Imaginary_I)              \
      && !defined(__STDC_IEC_60559_DFP__)
    #define IS_FLOATING_POINT(T)            \
        _Generic((T),                       \
            float                 : 1,      \
            double                : 1,      \
            long double           : 1,      \
            float _Complex        : 1,      \
            double _Complex       : 1,      \
            long double _Complex  : 1,      \
            float _Imaginary      : 1,      \
            double _Imaginary     : 1,      \
            long double _Imaginary: 1,      \
            default               : 1       \
        )
#elif defined(__STDC_IEC_60559_COMPLEX__)   \
      && defined(__STDC_IEC_60559_DFP__)    \
      && !defined(_Imaginary_I)
    #define IS_FLOATING_POINT(T)            \
        _Generic((T),                       \
            float                 : 1,      \
            double                : 1,      \
            long double           : 1,      \
            float _Complex        : 1,      \
            double _Complex       : 1,      \
            long double _Complex  : 1,      \
            _Decimal32            : 1,      \
            _Decimal64            : 1,      \
            _Decimal128           : 1,      \
            default               : 0       \
        )
#elif defined(__STDC_IEC_60559_DFP__) && !defined(__STDC_IEC_60559_COMPLEX__)
    #define IS_FLOATING_POINT(T)            \
        _Generic((T),                       \
            float               : 1,        \
            double              : 1,        \
            long double         : 1,        \
            _Decimal32          : 1,        \
            _Decimal64          : 1,        \
            _Decimal128         : 1,        \
            default             : 0         \
        )
#elif defined(__STDC_IEC_60559_COMPLEX__) && !defined(__STDC_IEC_60559_DFP__)
    #define IS_FLOATING_POINT(T)            \
        _Generic((T),                       \
            float                 : 1,      \
            double                : 1,      \
            long double           : 1,      \
            float _Complex        : 1,      \
            double _Complex       : 1,      \
            long double _Complex  : 1,      \
            default               : 0       \
        )
#else
    #define IS_FLOATING_POINT(T)            \
        _Generic((T),                       \
            float      : 1,                 \
            double     : 1,                 \
            long double: 1,                 \
            default    : 0                  \
        )
#endif

/**
 * Checks (at compile-time) whether the type of T is any arithmetic type. 
 *
 * T - An expression. It is not evaluated. 
 *
 * Note: This would not detect _BitInt.
 *
 * Returns 1 (true) only if T is a C is any arithmetic type, 0 (false) elsewise. */
#define IS_ARITHMETIC(T)    (IS_INTEGRAL(T) || IS_FLOATING_POINT(T))

/**
 * Checks (at compile-time) whether the type of T is a C string type, i.e.
 * char *, or char const *.
 *
 * T - An expression. It is not evaluated.
 *
 * Returns 1 (true) only if T is a C string type, 0 (false) elsewise. */
#define IS_C_STR(T)         \
    _Generic((T),           \
        char *      : 1,    \
        char const *: 1,    \
        default     : 0     \
    )

/** 
 * Checks (at compile-time) whether the type of T is compatible with the type
 * of an array of length N.
 *
 * T - An expression. It is not evaluated.
 * N - Length of array.
 *
 * Returns 1 (true) only if T is compatible with array of length N, 0 (false)
 * elsewise. */
#define IS_COMPATIBLE_WITH_ARRAY_OF_LENGTH_N(T, N)  \
    _Generic(&(T),                                  \
        typeof(*T) (*)[N]: 1,                       \
        default          : 0                        \
    )

/**
 * Checks (at compile-time) whether the type of T is variable-length array or
 * an unspecified-length array.
 *
 * T - An expression. It is not evaluated.
 *
 * Returns 1 (true) only if T is a VLA or a ULA, 0 (false) elsewise.
 *
 * See also: https://stackoverflow.com/a/78597305/20017547 */
#define IS_VLA_OR_ULA(T)                            \
    (IS_COMPATIBLE_WITH_ARRAY_OF_LENGTH_N(T, 1)     \
    && IS_COMPATIBLE_WITH_ARRAY_OF_LENGTH_N(T, 2))

/**
 * Checks (at compile-time) whether the type of T is a function type.
 *
 * T - An expression. It is not evaluated.
 *
 * Returns 1 (true) only if T is a function type, 0 (false) elsewise. 
 *
 * See also: https://stackoverflow.com/a/78601265/20017547 */
#define IS_FUNCTION(T)      \
    _Generic((T),           \
        typeof(T)*: true,   \
        default:    false   \
    )

/**
 * Like C11's _Static_assert() except that it can be used in an expression.
 *
 * EXPR - The expression to check.
 * MSG  - The string literal of the error message to print only if EXPR evalutes
 *        to false.
 *
 * Always returns true. */
#define STATIC_ASSERT_EXPR(EXPR, MSG) \
    (!!sizeof( struct { static_assert ( (EXPR), MSG ); char c; } ))

/**
 * Gets the number of elements of the given array. */
#define ARRAY_CARDINALITY(ARRAY) (      \
    sizeof(ARRAY) / sizeof(0[ARRAY])    \
    * STATIC_ASSERT_EXPR( IS_ARRAY(ARRAY), #ARRAY " must be an array" ))

/**
 * Strips trailing linefeed from S.
 *
 * S - The C string to strip the linefeed from. 
 *
 * Note: STRIP_LF() evalutes S more than once. */
#define STRIP_LF(S) \
    (((S) + (STATIC_ASSERT_EXPR(IS_C_STR(S), \
    #S " must be a C string") - 1))[strcspn((S), "\r\n")]  = '\0')

/**
 * Gets the length of S.
 *
 * S - The C string literal to get the length of. 
 *
 * Note: STRLITLEN() evalutes S more than once. */
#define STRLITLEN(S) \
    (ARRAY_CARDINALITY(S) - STATIC_ASSERT_EXPR(IS_C_STR(S), \
    #S " must be a C string literal"))

/**
 * Advances S over all CHARS.
 *
 * S     - The C string pointer to advance.
 * CHARS - A C string containing the characters to skip over.
 * 
 * Returns the updated S. 
 *
 * Note: SKIP_CHARS() evalutes S more than once. */
#define SKIP_CHARS(S, CHARS) \
    ((S) += strspn((S), (CHARS)))

/**
 * Advances S over all whitespace.
 *
 * S - The string pointer to advance.
 *
 * Returns the updated S. 
 *
 * Note: SKIP_WS() evalutes S more than once. */
#define SKIP_WS(S) \
    SKIP_CHARS((S), " \n\t\r\f\v")

/**
 * Convenience macro for iterating over the elements of a fixed-length array.
 *
 * VAR   - The element loop variable.
 * ARRAY - The array to iterate over. */
#define FOREACH_ARRAY_ELEMENT(VAR, ARRAY) \
    for (typeof(*ARRAY) const *VAR = (ARRAY); VAR < (ARRAY) + ARRAY_CARDINALITY(ARRAY); ++VAR)

/**
 * The machinery to vectorize any function that takes any type of pointer.
 *
 * TYPE - The type of pointer the function takes. For a function that takes in
 *        a void *, this shall be void.
 * FN   - The function to vectorize.
 * ...  - The arguments. */
#define FN_APPLY(TYPE, FN, ...)                         \
    BLOCK(                                              \
        void *stopper = (int[]){0};                     \
		TYPE **list = (TYPE*[]){ __VA_ARGS__, stopper};	\
		for (size_t i = 0; list[i]; i++) {	            \
			STATIC_ASSERT_EXPR(IS_FUNCTION(FN),         \
                #FN " should be a function.");          \
            FN(list[i]);	                            \
        }                                               \
    )

/**
 * Calls the free() function individually on all arguments --- useful for
 * replacing multiple individual calls to free() like these:
 *
 *      free(a);
 *      free(b);
 *      free(c);
 *      free(d);
 */
#define FREE_ALL(...)               FN_APPLY(void, free, __VA_ARGS__)

/**
 * Initializes memory pointed to by a pointer with values of a specified type 
 * and number of elements. 
 *
 * PTR    - The pointer to memory to be initialized. 
 * TYPE   - The type of the elements.
 * NELEMS - The number of elements.
 * ...    - The elements. */
#define INIT(PTR, TYPE, NELEMS, ...) \
    memcpy(PTR, (TYPE []) {__VA_ARGS__}, NELEMS * sizeof(TYPE))

/**
 * Takes two type names (or expressions representing types) and evalutes to the
 * size (in bytes) of the larget type. 
 *
 * MAXSIZE() never evalutes either X or Y. */
#define MAXSIZE(X, Y)               (sizeof(X) > sizeof(Y) ? sizeof(X) : sizeof(Y))

/**
 * Takes two type names (or expressions representing types) and evalutes to the
 * size (in bytes) of the smaller type. 
 *
 * MINSIZE() never evalutes either X or Y. */
#define MINSIZE(X, Y)               (sizeof(X) < sizeof(Y) ? sizeof(X) : sizeof(Y))

/**
 * Copies the minimum of the sizes of T and S from S to T. */
#define BYTECOPY(T, S)              memcpy(&(T), &(S), MINSIZE(T, S))

/**
 * A special-case of INTERNAL_ERROR() that prints an unexpected integer value.
 *
 * EXPR - The expression having the unexpected value. */
#define UNEXPECTED_INT_VALUE(EXPR)                                    \
    INTERNAL_ERROR("%lld (0x%llX): unexpected value for " #EXPR "\n", \
            (long long)(EXPR), (unsigned long long)(EXPR))

/**
 * A special-case of fatal_error() that additionally prints the file, line,
 * and function name where an internal error occured.
 *
 * FMT - The printf() format string literal to use.
 * ... - The printf() arguments. */
#define INTERNAL_ERROR(FMT, ...)    \
    fatal_error("%s::%d::%s(): internal error: " FMT "", __FILE__, __LINE__, \
            __VA_OPT__(,) __VA_ARGS__)

/**
 * The macro to which FPRINTF dispatches in the absence of arguments. */
#define FPRINTF_II(STREAM, FMT) \
    fputs(FMT, STREAM)

/**
 * The macro to which FPRINTF dispatches in the presence of arguments. */
#define FPRINTF_III(STREAM, FMT, ...) \
    fprintf(STREAM, FMT "", __VA_ARGS__)

/**
 * Augments calls to fprintf() such that two types of problem are detected:
 * - If there is only a format argument and no others, we want to use fputs()
 *   to avoid scanning the format at execution time.
 * - If there are more than one arguments, it should be assured that the format
 *   is a string literal, such that the contents can be parsed at compiel time.
 *
 * STREAM - The stream to print to.
 * FMT    - The printf() format string to use. 
 *
 * If there were no arguments present beside FMT, then the return value is the
 * same as what fputs() would return, else if is what fprintf() would return. */
#define FPRINTF(STREAM, FMT, ...)                      \
    FPRINTF_II ## __VA_OPT__(I)                        \
    (STREAM + (STATIC_ASSERT_EXPR(IS_FILE_PTR(STREAM), \
                #STREAM " must be a FILE *") - 1),     \
     FMT __VA_OPT__(,) __VA_ARGS__)

/**
 * Increases cap by 2x and returns it.
 *
 * If cap is less than 8, bumps it up to 8.
 *
 * double_capacity() does not check for overflow. */
[[reproducible, gnu::always_inline, gnu::const]] static inline size_t 
double_capacity(size_t cap);

/**
 * Increases cap by 1.5x and returns it.
 *
 * If cap is less than, bumps it up to 8.
 *
 * grow_capacity() does not check for overflow. */
[[reproducible, gnu::always_inline, gnu::const]] static inline size_t 
grow_capacity(size_t cap);

/* The semantics of reproducible and gnu::const are a little different, but
 * that difference is not relevant here. 
 *
 * Fall back to gnu::const if reproducible is not available, or vice versa. If
 * neither are recognized, they shall be ignored. */
[[reproducible, gnu::always_inline, gnu::const]] static inline size_t 
double_capacity(size_t cap)
{
    return cap < 8 ? 8 : cap * 2;
}

[[reproducible, gnu::always_inline, gnu::const]] static inline size_t 
grow_capacity(size_t cap)
{
    return cap < 8 ? 8 : cap * 3 / 2;
}

/**
 * Trims the memory region pointed by p to n bytes with realloc().
 *
 * Returns the trimmed memory region on success, or p on failure. */
[[gnu::always_inline]] static inline void *safe_trim(void *p, size_t n)
{
    void *const p2 = realloc(p, n);

    return p2 ? p2 : p;
}

/* -------------------------------------------------------------------------- */

/**
 * The functions util_asprintf() and util_vasprintf() are analogs of sprintf() 
 * and vsprintf(), except that they allocate a string large enough to hold the 
 * output including the terminating null byte ('\0'), and return a pointer to 
 * it via the first argument. This pointer should be passed to free() to release
 * the allocated storage when it is no longer needed.
 * 
 * strp - a pointer to the pointer that will hold the string.
 * fmt  - format string.
 * ...  - any arguments to fmt.
 *
 * When successful, these functions return the number of bytes printed, just 
 * like sprintf(). If memory allocation was not possible, or some other error 
 * occurs, these functions will return -1, and the contents of strp are unde‐
 * -fined. */
[[gnu::format(printf, 2, 3)]] int util_asprintf(char **restrict strp,
                                                const char fmt[restrict static 1], 
                                                ...); 

/**
 * See util_asprintf(). */
int util_vasprintf(char **restrict strp,
                   const char fmt[restrict static 1], 
                   va_list ap);

/**
 * The util_strnlen() function returns the number of bytes in the string 
 * pointed to by s, excluding the terminating null byte ('\0'), but at most 
 * n. In doing this, strnlen() looks only at the first n characters in the 
 * string pointed to by s and never beyond s[n - 1].
 *
 * Returns strlen(s), if that is less than n, or n if there is no null termi‐
 * -nating ('\0') among the first n characters pointed to by s. */
size_t util_strnlen(size_t n, const char s[static n]);

/**
 * The util_stpcpy() function copies the string pointed to by src (including 
 * the terminating null byte ('\0')) to the array pointed to by dest. The 
 * strings may not overlap, and the destination string dest must be large 
 * enough to receive the copy.
 *
 * stpcpy() returns a pointer to the end of the string dest (that is, the 
 * address of the terminating null byte) rather than the beginning. */
[[gnu::returns_nonnull]] char *util_stpcpy(char dest[restrict static 1],
                                           const char src[restrict static 1]);

/* The util_basename() function break a null-terminated pathname string into 
 * filename component. 
 *
 * basename() returns the component following the final '/'. The behavior
 * is exactly the same as GNU's implementation of basename(). 
 *
 * The below function-like macro chooses which function to call based on the
 * type of s. If s is const-qualified, util_basename_const() is called and
 * a const-qualified pointer is returned. Else, util_basename_vanilla() is
 * called and a non-const-qualified pointer is returned. */
#define util_basename(s)                         \
    _Generic((s),                                \
            char *:       util_basename_vanilla, \
            const char *: util_basename_const)(s)

[[gnu::returns_nonnull]] char *util_basename_vanilla(char path[static 1]);

[[gnu::returns_nonnull]] const char *util_basename_const(const char path[static 1]);


/**
 * The util_strchrnul() function returns a pointer to the first occurrence of 
 * the character c in the string s.
 * If c is not found in s, then it returns a pointer to the null byte at the 
 * end of s, rather than nullptr. 
 *
 * See util_basename() for how the purpose of the function-like macro below. */
#define util_strchrnul(s, c)                      \
    _Generic((s),                                 \
            char *:       util_strchrnul_vanilla, \
            const char *: util_strchrnul_const)(s, c)
[[gnu::pure, gnu::returns_nonnull]] char *util_strchrnul_vanilla(
        char s[static 1], 
        int c);

[[gnu::pure, gnu::returns_nonnull]] const char *util_strchrnul_const(
        const char s[static 1], 
        int c);

/**
 * The util_strcasecmp() function performs a byte-by-byte comparison of the 
 * strings s and t, ignoring the case of the characters. 
 *
 * It returns an integer less than, equal to, or greater than zero if s is 
 * found, respectively, to be less than, to match, or be greater than t. */
[[gnu::pure]] int util_strcasecmp(const char s[restrict static 1], 
                                  const char t[restrict static 1]);

/**
 * The util_memswap() function swaps the contents of two memory blocks pointed
 * by p1 and p2. The first argument, psize, gives the size of the memory blocks.
 *
 * Note that memswap() can not swap variables whose address can not be taken. */
[[gnu::nonnull]] void util_memswap(size_t psize,
                                   void *restrict p1, 
                                   void *restrict p2);

/**
 * Swaps the contents of A and B.
 *
 * Properties:
 *  - It evaluates each of A and B only once (sizeof does not evaluate its
 *    operand, except for VLAs, and _Generic does not evaluate its controlling
 *    expression).
 *  - It has a compile-time check for the correct sizes, and prints a nice,
 *    user-friendly error message if the sizes are different.
 *  - It has a compile-time check for compatible types, and prints a nice,
 *    user-friendly error message if the types are different.
 *  - It has no naming issue with a hidden variable.
 *  - The size of the temporary variable is computed at compile time, so the 
 *    compound literal is not a dynamic array.
 *  - It does not rely on VLAs, so it is more portable.
 *
 * Note: The expressions must allow the & operator to be applicable. Thus it 
 * will not work on variables that are declared with the register storage class.
 * Moreover, it would also not work with VLAs, and would invoke undefined
 * behavior if A and B are the same. */
#define SWAP(A, B)                                                         \
    util_memswap((sizeof *(1 ? &(A) : &(B))                                \
        * STATIC_ASSERT_EXPR(sizeof (A) == sizeof (B),                     \
        "Arguments of SWAP() must have same size and compatible types.")), \
        &(A),                                                              \
        &(B))

/**
 * Swaps the contents of A and B.
 *
 * SWAP_GEN() from SWAP() in 2 ways:
 * - A VLA is a valid value for this macro.
 * - It does not have a compile-time check for same sizes, as the size of a VLA
 *   can not be computed at compile-time. */
#define SWAP_GENERIC(A, B) \
    util_memswap(sizeof *(1 ? &(A) : &B), &(A), &(B))

/**
 * Prints an error message to standard error and exists with EXIT_FAILURE.
 *
 * fmt - The printf() format string literal to use.
 * ... - The printf() arguments. */
[[noreturn, gnu::format(printf, 1, 2)]] void fatal_error(char fmt[static 1], ...);

#endif                          /* UTIL_H */
