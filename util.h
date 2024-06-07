#ifndef UTIL_H
#define UTIL_H 1

/**
 * Author: Harith
 * Date: Friday, June 7, 2024
 * 
 * Declares utility constants, macros, and functions. */

#include <stdarg.h>
#include <string.h>

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
 * All uses for a given PREFIX that refer to the same name must be on the same
 * line. This is not a problem within macro definitions, but would not work
 * outside of them since there is no way to refer to a previously used unique
 * name. */
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
 * Expands to true if val_ is within the range of lo_ to hi_ (inclusive). */
#define RANGE(val_, lo_, hi_)   \
    (((val_) >= (lo_)) && ((val_) <= (hi_)))

/**
 * Expands to true if val_ is within the range of lo_ to hi_ (exclusive). */
#define RANGEM1(val_, lo_, hi_) \
    (((val_) >= (lo_)) && ((val_) < (hi_)))

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
 * message, source file name, line number, and function name. */
#define TRACE(fmt, ...)                                             \
    BLOCK(                                                          \
        if (TRACE_ON) {                                             \
            fprintf(stderr, "%s::%d::%s():: " fmt, __FILE__,        \
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
 */
#ifndef NDEBUG
    #define ASSERT_RUN_ONCE()                   \
        BLOCK(                                  \
            static bool UNIQUE_NAME(called);    \
            assert(!UNIQUE_NAME(called));       \
            UNIQUE_NAME(called) = true;         \
        )
#else
    #define ASSERT_RUN_ONCE()   (void)0
#endif  /* NDEBUG */

/**
 * Convenience macro for iterating N times. */
#define FOR_N_TIMES(N)                              \
    for (size_t UNIQUE_NAME(i) = 0;                 \
         UNIQUE_NAME(i) < STATIC_CAST(size_t, (N)); \
         ++UNIQUE_NAME(i))

/**
 * Like C11's _Static_assert() except that it can be used in an expression.
 *
 * EXPR - The expression to check.
 * MSG  - The string literal of the error message to print only if EXPR evalutes
 *        to false.
 *
 * Always return true. */
#define STATIC_ASSERT_EXPR(EXPR, MSG)   \
    (!!sizeof( struct { static_assert ( (EXPR), MSG ); char c; } ))

/**
 * Checks (at compile-time) whether A is an array.
 *
 * Returns true only if A is an array; false elsewise. 
 *
 * See also: https://stackoverflow.com/a/77881417/99089 */
#define IS_ARRAY(T)                 \
    _Generic( &(A),                 \
        typeof(*T) (*)[]    : true, \
        default             : false \
    )

/**
 * Gets the number of elements of the given array. */
#define ARRAY_SIZE(ARRAY) (             \
    sizeof(ARRAY) / sizeof(0[ARRAY])    \
    * STATIC_ASSERT_EXPR( IS_ARRAY(ARRAY), #ARRAY "must be an array" ))

/**
 * Convenience macro for iterating over the elements of a static array.
 *
 * TYPE  - The type of element.
 * VAR   - The element loop variable.
 * ARRAY - The array to iterate over. */
#define FOREACH_ARRAY_ELEMENT(TYPE, VAR, ARRAY) \
    for (TYPE const *VAR = (ARRAY); VAR < (ARRAY) + ARRAY_SIZE(ARRAY); ++VAR)

/* Repeatedly calls the function FN with each argument of type TYPE *. */
#define FN_APPLY(TYPE, FN, ...)                         \
    BLOCK(                                              \
		TYPE **list = (TYPE*[]){ __VA_ARGS__, nullptr};	\
		for (size_t i = 0; list[i]; i++)	            \
			FN(list[i]);	                            \
		} while (false)                                 \
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
#define FREE_ALL(...) FN_APPLY(void, free, __VA_ARGS__)

/**
 * Takes two type names (or expressions representing types) and evalutes to the
 * size (in bytes) of the larget type. */
#define MAXSIZE(X, Y)   (sizeof(X) > sizeof(Y) ? sizeof(X) : sizeof(Y))

/**
 * Takes two type names (or expressions representing types) and evalutes to the
 * size (in bytes) of the smaller type. */
#define MINSIZE(X, Y)   (sizeof(X) < sizeof(Y) ? sizeof(X) : sizeof(Y))

/**
 * Copies the minimum of the sizes of T and S from S to T. */
#define BYTECOPY(T, S)  memcpy(&(T), &(S), MINSIZE(T, S))

[[gnu::always_inline]] static inline void swap_internal(size_t psize,
                                                        void *restrict tmp, 
                                                        void *restrict p1, 
                                                        void *restrict p2)
{
    memcpy(tmp, p1, psize);
    memcpy(p1, p2, psize);
    memcpy(p2, tmp, psize);
}

/**
 * Swaps the contents of A and B.
 *
 * Properties:
 *  - It evaluates each of A and B only once.
 *  - It has a compile-time check for the correct sizes, and prints a nice,
 *    user-friendly error message if the sizes are different.
 *  - It has a compile-time check for compatible types.
 *  - It has no naming issue with a hidden variable.
 *  - The size of the temporary variable is computed at compile time, so the 
 *    compound literal is not a dynamic array.
 *  - It does not rely on VLAs, so it is more portable.
 *
 *
 * Note: The expressions must allow the & operator to be applicable. Thus it 
 * will not work on variables that are declared with the register storage class.
 * 
 * SWAP() would invoke undefined behavior if A and B are the same. */
#define SWAP(A, B)                                                            \
    swap_internal(                                                            \
        (sizeof (A) * STATIC_ASSERT_EXPR(sizeof (A) == sizeof (B),            \
            "Arguments of SWAP() must have same size and compatible types.")),\
        (char [sizeof *(1 ? &(A) : &(B))]) {0},                               \
        &(A),                                                                 \
        &(B))

/**
 * Increases cap by 2x and returns it.
 *
 * double_capacity() does not check for overflow. */
[[reproducible, gnu::always_inline, gnu::const]] static inline size_t 
double_capacity(size_t cap);

/**
 * Increases cap by 1.5x and returns it.
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

#endif                          /* UTIL_H */
