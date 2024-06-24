#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "max.h"

#if defined(__has_c_attribute__) && __has_c_attribute__(noreturn)
    #define NORETURN    [[noreturn]]
#elif defined(_MSC_VER)
    #define NORETURN    __declspec(noreturn)
#elif defined(__GNUC__) || defined(__clang__) || defined(__INTEL_LLVM_COMPILER)
    #define NORETURN    __attribute__((noreturn))
#else
    #define NORETURN    _Noreturn
#endif

NORETURN static void cassert(const char cond[static 1], 
                             const char file[static 1],
                             size_t line)
{
    fflush(stdout);
    fprintf(stderr, "Assertion failed: '%s' at %s, line %zu.\n", cond, file, line);
    exit(EXIT_FAILURE);
}

#define test(cond) do { \
    if (!(cond)) { cassert(#cond, __FILE__, __LINE__); } } while (false)

/* Get the name of a type */
#define ctypename(x) _Generic((x),                                  \
                _Bool: "_Bool",                                     \
                unsigned char: "unsigned char",                     \
                char: "char",                                       \
                signed char: "signed char",                         \
                short: "short",                                     \
                unsigned short: "unsigned short",                   \
                int: "int",                                         \
                unsigned: "unsigned",                               \
                long: "long",                                       \
                unsigned long: "unsigned long",                     \
                long long: "long long",                             \
                unsigned long long: "unsigned long long",           \
                default: "other")

static const int imax = INT_MAX;
static const unsigned umax = UINT_MAX;
static const long lmax = LONG_MAX;
static const unsigned long ulmax = ULONG_MAX;
static const long long llmax = LLONG_MAX;
static const unsigned long long ullmax = LLONG_MAX;

static const long lmin = LONG_MIN;
static const int imin = INT_MIN;
static const long long llmin = LLONG_MIN;

void test_max_int(void) 
{
    test(MAX(3, 5) == 5 && strcmp(ctypename(MAX(3, 5)), "int") == 0);
    test(MAX(-1, 1) == 1 && strcmp(ctypename(MAX(-1, 1)), "int") == 0);
    test(MAX(0, 0) == 0 && strcmp(ctypename(MAX(0, 0)), "int") == 0);
    test(MAX(imax, imin) == imax && strcmp(ctypename(MAX(imax, imin)), "int") == 0);
    test(MAX(-5, -3) == -3 && strcmp(ctypename(MAX(-5, -3)), "int") == 0);
}

void test_max_unsigned_int(void) 
{
    test(MAX(3U, 5U) == 5U && strcmp(ctypename(MAX(3U, 5U)), "unsigned") == 0);
    test(MAX(0U, 0U) == 0U && strcmp(ctypename(MAX(0U, 0U)), "unsigned") == 0);
    test(MAX(umax, 0U) == UINT_MAX && strcmp(ctypename(MAX(umax, 0U)), "unsigned") == 0);
    test(MAX(65000U, 35000U) == 65000U && strcmp(ctypename(MAX(65000U, 35000U)), "unsigned") == 0);
}

void test_max_long(void) 
{
    test(MAX(3L, 5L) == 5L && strcmp(ctypename(MAX(3L, 5L)), "long") == 0);
    test(MAX(-1L, 1L) == 1L && strcmp(ctypename(MAX(-1L, 1L)), "long") == 0);
    test(MAX(0L, 0L) == 0L && strcmp(ctypename(MAX(0L, 0L)), "long") == 0);
    test(MAX(lmax, lmin) == lmax && strcmp(ctypename(MAX(lmax, lmin)), "long") == 0);
    test(MAX(-5L, -3L) == -3L && strcmp(ctypename(MAX(-5L, -3L)), "long") == 0);
}

void test_max_unsigned_long(void) 
{
    test(MAX(3UL, 5UL) == 5UL && strcmp(ctypename(MAX(3UL, 5UL)), "unsigned long") == 0);
    test(MAX(0UL, 0UL) == 0UL && strcmp(ctypename(MAX(0UL, 0UL)), "unsigned long") == 0);
    test(MAX(ulmax, 0UL) == ULONG_MAX && strcmp(ctypename(MAX(ulmax, 0UL)), "unsigned long") == 0);
    test(MAX(123456789UL, 987654321UL) == 987654321UL && strcmp(ctypename(MAX(123456789UL, 987654321UL)), "unsigned long") == 0);
}

void test_max_long_long(void) 
{
    test(MAX(3LL, 5LL) == 5LL && strcmp(ctypename(MAX(3LL, 5LL)), "long long") == 0);
    test(MAX(-1LL, 1LL) == 1LL && strcmp(ctypename(MAX(-1LL, 1LL)), "long long") == 0);
    test(MAX(0LL, 0LL) == 0LL && strcmp(ctypename(MAX(0LL, 0LL)), "long long") == 0);
    test(MAX(llmax, llmin) == llmax && strcmp(ctypename(MAX(llmax, llmin)), "long long") == 0);
    test(MAX(-5LL, -3LL) == -3LL && strcmp(ctypename(MAX(-5LL, -3LL)), "long long") == 0);
}

void test_max_unsigned_long_long(void) 
{
    test(MAX(3ULL, 5ULL) == 5ULL && strcmp(ctypename(MAX(3ULL, 5ULL)), "unsigned long long") == 0);
    test(MAX(0ULL, 0ULL) == 0ULL && strcmp(ctypename(MAX(0ULL, 0ULL)), "unsigned long long") == 0);
    test(MAX(ullmax, 0ULL) == ullmax && strcmp(ctypename(MAX(ullmax, 0ULL)), "unsigned long long") == 0);
    test(MAX(123456789ULL, 987654321ULL) == 987654321ULL && strcmp(ctypename(MAX(123456789ULL, 987654321ULL)), "unsigned long long") == 0);
}

void test_max_mixed(void) 
{
    test(MAX(3, 5U) == 5U && strcmp(ctypename(MAX(3, 5U)), "unsigned") == 0);
    test(MAX(-1, 1U) == 1U && strcmp(ctypename(MAX(-1, 1U)), "unsigned") == 0);
    test(MAX(0L, 0) == 0L && strcmp(ctypename(MAX(0L, 0)), "long") == 0);

    test(MAX(imax, lmax) == lmax && strcmp(ctypename(MAX(imax, lmax)), "long") == 0);
    test(MAX(lmin, llmin) == lmin && strcmp(ctypename(MAX(lmin, llmin)), "long long") == 0);

    #if LLONG_MAX >= ULONG_MAX
    test(MAX(-5LL, 3UL) == 3UL && strcmp(ctypename(MAX(-5LL, 3UL)), "long long") == 0);
    test(MAX(3LL, ulmax) == ulmax && strcmp(ctypename(MAX(3LL, ulmax)), "long long") == 0);
    #else
    test(MAX(-5LL, 3UL) == 3UL && strcmp(ctypename(MAX(-5LL, 3UL)), "unsigned long") == 0);
    test(MAX(3LL, ulmax) == ulmax && strcmp(ctypename(MAX(3LL, ulmax)), "unsigned long") == 0);
    #endif

    #if LLONG_MAX >= UINT_MAX
    test(MAX(3U, llmax) == llmax && strcmp(ctypename(MAX(3U, llmax)), "long long") == 0);
    #else
    test(MAX(3U, llmax) == llmax && strcmp(ctypename(MAX(3U, llmax)), "unsigned") == 0);
    #endif

    #if LONG_MAX >= UINT_MAX
    test(MAX(umax, lmax) == lmax && strcmp(ctypename(MAX(umax, lmax)), "long") == 0);
    #else
    test(MAX(umax, lmax) == lmax && strcmp(ctypename(MAX(umax, lmax)), "unsigned") == 0);
    #endif

    #if ULLONG_MAX >= LONG_MAX
    test(MAX(1000L, 500ULL) == 1000L && strcmp(ctypename(MAX(1000, 500ULL)), "unsigned long long") == 0);
    test(MAX(-5000L, 30000ULL) == 30000ULL && strcmp(ctypename(MAX(-5000L, 30000ULL)), "unsigned long long") == 0);
    test(MAX(lmax, 0ULL) == lmax && strcmp(ctypename(MAX(lmax, 0ULL)), "unsigned long long") == 0);
    #else
    test(MAX(1000L, 500ULL) == 1000L && strcmp(ctypename(MAX(1000, 500ULL)), "long") == 0);
    test(MAX(-5000L, 30000ULL) == 30000ULL && strcmp(ctypename(MAX(-5000L, 30000ULL)), "long") == 0);
    test(MAX(lmax, 0ULL) == lmax && strcmp(ctypename(MAX(lmax, 0ULL)), "long") == 0);
    #endif

    test(MAX(-1, 1ULL) == 1ULL && strcmp(ctypename(MAX(-1, 1ULL)), "unsigned long long") == 0);

    test(MAX(-1, umax) == umax && strcmp(ctypename(MAX(-1, umax)), "unsigned") == 0); 
    test(MAX(-1L, ulmax) == ulmax && strcmp(ctypename(MAX(-1L, ulmax)), "unsigned long") == 0); 
    test(MAX(-1LL, ullmax) == ullmax && strcmp(ctypename(MAX(-1LL, ullmax)), "unsigned long long") == 0); 
    test(MAX(0, umax) == umax && strcmp(ctypename(MAX(0, umax)), "unsigned") == 0); 
    test(MAX(0L, ulmax) == ulmax && strcmp(ctypename(MAX(0, ulmax)), "unsigned long") == 0); 
    test(MAX(0LL, ullmax) == ullmax && strcmp(ctypename(MAX(0LL, ullmax)), "unsigned long long") == 0); 

    test(MAX(5L, 5UL) == 5UL && strcmp(ctypename(MAX(5L, 5UL)), "unsigned long") == 0); 
    test(MAX(5LL, 5ULL) == 5ULL && strcmp(ctypename(MAX(5LL, 5ULL)), "unsigned long long") == 0); 

    test(MAX(imax, umax) == umax && strcmp(ctypename(MAX(imax, umax)), "unsigned") == 0); 
    test(MAX(lmax, ulmax) == ulmax && strcmp(ctypename(MAX(lmax, ulmax)), "unsigned long") == 0); 
    test(MAX(llmax, ullmax) == ullmax && strcmp(ctypename(MAX(llmax, ullmax)), "unsigned long long") == 0); 

    test(MAX(imin, umax) == umax && strcmp(ctypename(MAX(imin, umax)), "unsigned") == 0); 
    test(MAX(lmin, ulmax) == ulmax && strcmp(ctypename(MAX(lmin, ulmax)), "unsigned long") == 0);
    test(MAX(llmin, ullmax) == ullmax && strcmp(ctypename(MAX(llmin, ullmax)), "unsigned long long") == 0); 
}

int main(void) 
{
    test_max_int();
    test_max_unsigned_int();
    test_max_long();
    test_max_unsigned_long();
    test_max_long_long();
    test_max_unsigned_long_long();
    test_max_mixed();
    return EXIT_SUCCESS;
}
