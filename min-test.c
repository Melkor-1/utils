#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "min.h"

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
static const unsigned long long ullmax = ULLONG_MAX;

static const long lmin = LONG_MIN;
static const int imin = INT_MIN;
static const long long llmin = LLONG_MIN;

static void test_min_int(void) 
{
    test(MIN(3, 5) == 3 && strcmp(ctypename(MIN(3, 5)), "int") == 0);
    test(MIN(5, 3) == 3 && strcmp(ctypename(MIN(5, 3)), "int") == 0);
    test(MIN(imax, imin) == imin && strcmp(ctypename(MIN(imax, imin)), "int") == 0);
    test(MIN(imin, imax) == imin && strcmp(ctypename(MIN(imin, imax)), "int") == 0);
    test(MIN(0, imax) == 0 && strcmp(ctypename(MIN(0, imax)), "int") == 0);
    test(MIN(0, imin) == imin && strcmp(ctypename(MIN(0, imin)), "int") == 0);
}

static void test_min_unsigned_int(void) 
{
    test(MIN(3U, 5U) == 3U && strcmp(ctypename(MIN(3U, 5U)), "unsigned") == 0);
    test(MIN(5U, 3U) == 3U && strcmp(ctypename(MIN(5U, 3U)), "unsigned") == 0);
    test(MIN(umax, 0U) == 0U && strcmp(ctypename(MIN(umax, 0U)), "unsigned") == 0);
}

static void test_min_long(void) 
{
    test(MIN(3L, 5L) == 3L && strcmp(ctypename(MIN(3L, 5L)), "long") == 0);
    test(MIN(5L, 3L) == 3L && strcmp(ctypename(MIN(5L, 3L)), "long") == 0);
    test(MIN(lmax, lmin) == lmin && strcmp(ctypename(MIN(lmax, lmin)), "long") == 0);
    test(MIN(lmin, lmax) == lmin && strcmp(ctypename(MIN(lmin, lmax)), "long") == 0);
    test(MIN(0L, lmax) == 0L && strcmp(ctypename(MIN(0L, lmax)), "long") == 0);
    test(MIN(0L, lmin) == lmin && strcmp(ctypename(MIN(0L, lmin)), "long") == 0);
}

static void test_min_unsigned_long(void) 
{
    test(MIN(3UL, 5UL) == 3UL && strcmp(ctypename(MIN(3UL, 5UL)), "unsigned long") == 0);
    test(MIN(5UL, 3UL) == 3UL && strcmp(ctypename(MIN(5UL, 3UL)), "unsigned long") == 0);
    test(MIN(ulmax, 0UL) == 0UL && strcmp(ctypename(MIN(ulmax, 0UL)), "unsigned long") == 0);
    test(MIN(0UL, ulmax) == 0UL && strcmp(ctypename(MIN(0UL, ulmax)), "unsigned long") == 0);
}

static void test_min_long_long(void) 
{
    test(MIN(3LL, 5LL) == 3LL && strcmp(ctypename(MIN(3LL, 5LL)), "long long") == 0);
    test(MIN(5LL, 3LL) == 3LL && strcmp(ctypename(MIN(5LL, 3LL)), "long long") == 0);
    test(MIN(llmax, llmin) == llmin && strcmp(ctypename(MIN(llmax, llmin)), "long long") == 0);
    test(MIN(llmin, llmax) == llmin && strcmp(ctypename(MIN(llmin, llmax)), "long long") == 0);
    test(MIN(0LL, llmax) == 0LL && strcmp(ctypename(MIN(0LL, llmax)), "long long") == 0);
    test(MIN(0LL, llmin) == llmin && strcmp(ctypename(MIN(0LL, llmin)), "long long") == 0);
}

static void test_min_unsigned_long_long(void) 
{
    test(MIN(3ULL, 5ULL) == 3ULL && strcmp(ctypename(MIN(3ULL, 5ULL)), "unsigned long long") == 0);
    test(MIN(5ULL, 3ULL) == 3ULL && strcmp(ctypename(MIN(5ULL, 3ULL)), "unsigned long long") == 0);
    test(MIN(ullmax, 0ULL) == 0ULL && strcmp(ctypename(MIN(ullmax, 0ULL)), "unsigned long long") == 0);
    test(MIN(0ULL, ullmax) == 0ULL && strcmp(ctypename(MIN(0ULL, ullmax)), "unsigned long long") == 0);
}

static void test_min_mixed(void) 
{
    test(MIN(3, 5U) == 3 && strcmp(ctypename(MIN(3, 5U)), "int") == 0);
    test(MIN(5U, 3) == 3 && strcmp(ctypename(MIN(5U, 3)), "int") == 0);

    test(MIN(3L, 5) == 3L && strcmp(ctypename(MIN(3L, 5)), "long") == 0);
    test(MIN(5, 3L) == 3L && strcmp(ctypename(MIN(5, 3L)), "long") == 0);

    test(MIN(3LL, 5) == 3LL && strcmp(ctypename(MIN(3LL, 5)), "long long") == 0);
    test(MIN(5, 3LL) == 3LL && strcmp(ctypename(MIN(5, 3LL)), "long long") == 0);

    test(MIN(3ULL, 5) == 3ULL && strcmp(ctypename(MIN(3ULL, 5)), "int") == 0);
    test(MIN(5, 3ULL) == 3ULL && strcmp(ctypename(MIN(5, 3ULL)), "int") == 0);

    test(MIN(3UL, 5U) == 3UL && strcmp(ctypename(MIN(3UL, 5U)), "unsigned") == 0);
    test(MIN(5U, 3UL) == 3UL && strcmp(ctypename(MIN(5U, 3UL)), "unsigned") == 0);
}

int main(void) 
{
    test_min_int();
    test_min_unsigned_int();
    test_min_long();
    test_min_unsigned_long();
    test_min_long_long();
    test_min_unsigned_long_long();
    test_min_mixed();
    return EXIT_SUCCESS;
}

