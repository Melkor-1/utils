#include "utils.h"

#include <string.h>
#include <complex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Current versions of gcc and clang support -std=c2x which sets 
 * __STDC_VERSION__ to this placeholder value. GCC 14.1 does not set
 * __STDC_VERSION__ to 202311L with the std=c23 flag, but Clang 18.1 does. */
#define C23_PLACEHOLDER 202000L
    
#if defined(__STDC_VERSION__) && __STDC_VERSION >= C23_PLACEHOLDER
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

void test_charify(void) 
{
    test(CHARIFY(0) == '0');
    test(CHARIFY(1) == '1');
    test(CHARIFY(2) == '2');
    test(CHARIFY(3) == '3');
    test(CHARIFY(4) == '4');
    test(CHARIFY(5) == '5');
    test(CHARIFY(6) == '6');
    test(CHARIFY(7) == '7');
    test(CHARIFY(8) == '8');
    test(CHARIFY(9) == '9');
    test(CHARIFY(A) == 'A');
    test(CHARIFY(B) == 'B');
    test(CHARIFY(C) == 'C');
    test(CHARIFY(D) == 'D');
    test(CHARIFY(E) == 'E');
    test(CHARIFY(F) == 'F');
    test(CHARIFY(G) == 'G');
    test(CHARIFY(H) == 'H');
#undef I
    test(CHARIFY(I) == 'I');
    test(CHARIFY(J) == 'J');
    test(CHARIFY(K) == 'K');
    test(CHARIFY(L) == 'L');
    test(CHARIFY(M) == 'M');
    test(CHARIFY(N) == 'N');
    test(CHARIFY(O) == 'O');
    test(CHARIFY(P) == 'P');
    test(CHARIFY(Q) == 'Q');
    test(CHARIFY(R) == 'R');
    test(CHARIFY(S) == 'S');
    test(CHARIFY(T) == 'T');
    test(CHARIFY(U) == 'U');
    test(CHARIFY(V) == 'V');
    test(CHARIFY(W) == 'W');
    test(CHARIFY(X) == 'X');
    test(CHARIFY(Y) == 'Y');
    test(CHARIFY(Z) == 'Z');
    test(CHARIFY(_) == '_');
    test(CHARIFY(a) == 'a');
    test(CHARIFY(b) == 'b');
    test(CHARIFY(c) == 'c');
    test(CHARIFY(d) == 'd');
    test(CHARIFY(e) == 'e');
    test(CHARIFY(f) == 'f');
    test(CHARIFY(g) == 'g');
    test(CHARIFY(h) == 'h');
    test(CHARIFY(i) == 'i');
    test(CHARIFY(j) == 'j');
    test(CHARIFY(k) == 'k');
    test(CHARIFY(l) == 'l');
    test(CHARIFY(m) == 'm');
    test(CHARIFY(n) == 'n');
    test(CHARIFY(o) == 'o');
    test(CHARIFY(p) == 'p');
    test(CHARIFY(q) == 'q');
    test(CHARIFY(r) == 'r');
    test(CHARIFY(s) == 's');
    test(CHARIFY(t) == 't');
    test(CHARIFY(u) == 'u');
    test(CHARIFY(v) == 'v');
    test(CHARIFY(w) == 'w');
    test(CHARIFY(x) == 'x');
    test(CHARIFY(y) == 'y');
    test(CHARIFY(z) == 'z');
}

void test_stringify(void)
{
    test(strcmp(STRINGIFY(0), "0") == 0);
    test(strcmp(STRINGIFY(1), "1") == 0);
    test(strcmp(STRINGIFY(2), "2") == 0);
    test(strcmp(STRINGIFY(3), "3") == 0);
    test(strcmp(STRINGIFY(4), "4") == 0);
    test(strcmp(STRINGIFY(5), "5") == 0);
    test(strcmp(STRINGIFY(6), "6") == 0);
    test(strcmp(STRINGIFY(7), "7") == 0);
    test(strcmp(STRINGIFY(8), "8") == 0);
    test(strcmp(STRINGIFY(9), "9") == 0);
    test(strcmp(STRINGIFY(A), "A") == 0);
    test(strcmp(STRINGIFY(B), "B") == 0);
    test(strcmp(STRINGIFY(C), "C") == 0);
    test(strcmp(STRINGIFY(D), "D") == 0);
    test(strcmp(STRINGIFY(E), "E") == 0);
    test(strcmp(STRINGIFY(F), "F") == 0);
    test(strcmp(STRINGIFY(G), "G") == 0);
    test(strcmp(STRINGIFY(H), "H") == 0);
    test(strcmp(STRINGIFY(I), "I") == 0);
    test(strcmp(STRINGIFY(J), "J") == 0);
    test(strcmp(STRINGIFY(K), "K") == 0);
    test(strcmp(STRINGIFY(L), "L") == 0);
    test(strcmp(STRINGIFY(M), "M") == 0);
    test(strcmp(STRINGIFY(N), "N") == 0);
    test(strcmp(STRINGIFY(O), "O") == 0);
    test(strcmp(STRINGIFY(P), "P") == 0);
    test(strcmp(STRINGIFY(Q), "Q") == 0);
    test(strcmp(STRINGIFY(R), "R") == 0);
    test(strcmp(STRINGIFY(S), "S") == 0);
    test(strcmp(STRINGIFY(T), "T") == 0);
    test(strcmp(STRINGIFY(U), "U") == 0);
    test(strcmp(STRINGIFY(V), "V") == 0);
    test(strcmp(STRINGIFY(W), "W") == 0);
    test(strcmp(STRINGIFY(X), "X") == 0);
    test(strcmp(STRINGIFY(Y), "Y") == 0);
    test(strcmp(STRINGIFY(Z), "Z") == 0);
    test(strcmp(STRINGIFY(_), "_") == 0);
    test(strcmp(STRINGIFY(a), "a") == 0);
    test(strcmp(STRINGIFY(b), "b") == 0);
    test(strcmp(STRINGIFY(c), "c") == 0);
    test(strcmp(STRINGIFY(d), "d") == 0);
    test(strcmp(STRINGIFY(e), "e") == 0);
    test(strcmp(STRINGIFY(f), "f") == 0);
    test(strcmp(STRINGIFY(g), "g") == 0);
    test(strcmp(STRINGIFY(h), "h") == 0);
    test(strcmp(STRINGIFY(i), "i") == 0);
    test(strcmp(STRINGIFY(j), "j") == 0);
    test(strcmp(STRINGIFY(k), "k") == 0);
    test(strcmp(STRINGIFY(l), "l") == 0);
    test(strcmp(STRINGIFY(m), "m") == 0);
    test(strcmp(STRINGIFY(n), "n") == 0);
    test(strcmp(STRINGIFY(o), "o") == 0);
    test(strcmp(STRINGIFY(p), "p") == 0);
    test(strcmp(STRINGIFY(q), "q") == 0);
    test(strcmp(STRINGIFY(r), "r") == 0);
    test(strcmp(STRINGIFY(s), "s") == 0);
    test(strcmp(STRINGIFY(t), "t") == 0);
    test(strcmp(STRINGIFY(u), "u") == 0);
    test(strcmp(STRINGIFY(v), "v") == 0);
    test(strcmp(STRINGIFY(w), "w") == 0);
    test(strcmp(STRINGIFY(x), "x") == 0);
    test(strcmp(STRINGIFY(y), "y") == 0);
    test(strcmp(STRINGIFY(z), "z") == 0);
    test(strcmp(STRINGIFY(abcdefghijklmnopqrstuvwxyz), "abcdefghijklmnopqrstuvwxyz") == 0);
}

void test_range(void) 
{
    test(RANGE(5, 1, 10) == 1);
    test(RANGE(1, 1, 10) == 1);
    test(RANGE(9, 1, 10) == 1);
    test(RANGE(10, 1, 10) == 1);
    test(RANGE(0, 1, 10) == 0);
    test(RANGE(11, 1, 10) == 0);
}

void test_rangem1(void)
{
    test(RANGEM1(5, 1, 10) == 1);
    test(RANGEM1(1, 1, 10) == 1);
    test(RANGEM1(9, 1, 10) == 1);
    test(RANGEM1(10, 1, 10) == 0);
    test(RANGEM1(0, 1, 10) == 0);
    test(RANGEM1(11, 1, 10) == 0);
}

void test_for_n_times(void)
{
    size_t sum = 0;
    size_t i = 1;

    FOR_N_TIMES(5) { sum += i++; }
    test(sum == 15); 

    int count = 0;

    FOR_N_TIMES(7) { count++; }
    test(count == 7);

    count = 0;

    FOR_N_TIMES(0) { count++; }
    test(count == 0);

    [[maybe_unused]] int values[5] = {};

    int j = 0;
    FOR_N_TIMES(5) { values[j] = j; ++j; }
    
    j = 0;
    FOR_N_TIMES(5) { test(values[j] == j); ++j; }
}

int func(int)
{
    return 0;
}

void test_is_compatible(void)
{
    int *i;

    test(IS_COMPATIBLE(i, int *));
    test(!IS_COMPATIBLE(i, float *));

    int (*f)(int); 
    test(IS_COMPATIBLE(func, int (*)(int)));
    test(IS_COMPATIBLE(f, int (*)(int)));
    test(IS_COMPATIBLE(func, typeof(f)));
    test(!IS_COMPATIBLE(func, void (*)(int)));

    struct A { int x; int y; } A;
    struct B { double a; double b; } B;

    test(IS_COMPATIBLE(A, struct A));
    test(IS_COMPATIBLE(B, struct B));
    test(!IS_COMPATIBLE(A, struct B));
    test(!IS_COMPATIBLE(B, struct A));

    typedef const char *string;
    typedef int VAL;

    string greeting; 
    VAL a; 
    
    test(IS_COMPATIBLE(greeting, string));
    test(IS_COMPATIBLE(greeting, const char *));

    test(IS_COMPATIBLE(a, int));
    test(IS_COMPATIBLE(a, VAL));
    test(IS_COMPATIBLE((VAL){10}, int));
    test(IS_COMPATIBLE((int){10}, VAL));
    test(IS_COMPATIBLE(a, typeof((int){10})));
}

void test_is_nullptr(void)
{
    char *c = nullptr;
    test(IS_NULLPTR(nullptr));
    test(!IS_NULLPTR(NULL));
    test(!IS_NULLPTR(c));
}

void test_is_file_ptr(void)
{
    FILE *f; 
    test(IS_FILE_PTR(f));
    test(!IS_FILE_PTR(0));
    test(!IS_FILE_PTR(NULL));
}

void test_is_array(void)
{
    int n = 5;
    char VLA[n];
    int FLA[10];
    extern char ULA[];

    int *p = FLA;
    char *c; 

    test(IS_ARRAY(VLA));
    test(IS_ARRAY(FLA));
    test(IS_ARRAY(ULA));

    test(!IS_ARRAY(p));
    test(!IS_ARRAY(c));
}

void test_is_pointer(void)
{
    int n = 5;
    char VLA[n];
    int FLA[10];
    extern char ULA[];

    int *p = FLA;
    char *c;

    test(!IS_POINTER(VLA));
    test(!IS_POINTER(FLA));
    test(!IS_POINTER(ULA));

    test(IS_POINTER(p));
    test(IS_POINTER(c));
}

void test_is_signed(void)
{
    test(IS_CHAR_SIGNED ? IS_SIGNED((char){0}) : !IS_SIGNED((char){0}));

    test(!IS_SIGNED((unsigned char){0}));
    test(!IS_SIGNED((unsigned int){0}));
    test(!IS_SIGNED((unsigned long int){0}));
    test(!IS_SIGNED((unsigned long long int){0}));

    test(IS_SIGNED((short int){0}));
    test(IS_SIGNED((int){0}));
    test(IS_SIGNED((long int){0}));
    test(IS_SIGNED((long long int){0}));
}

void test_is_unsigned(void)
{
    test(IS_CHAR_SIGNED ? !IS_UNSIGNED((char){0}) : IS_UNSIGNED((char){0}));

    test(!IS_UNSIGNED((char){0}));
    test(!IS_UNSIGNED((short int){0}));
    test(!IS_UNSIGNED((int){0}));
    test(!IS_UNSIGNED((long int){0}));
    test(!IS_UNSIGNED((long long int){0}));

    test(IS_UNSIGNED((_Bool){0}));
    test(IS_UNSIGNED((unsigned char){0}));
    test(IS_UNSIGNED((unsigned int){0}));
    test(IS_UNSIGNED((unsigned long int){0}));
    test(IS_UNSIGNED((unsigned long long int){0}));
}

void test_is_integral(void)
{
    test(IS_INTEGRAL((_Bool){0}));
    test(IS_INTEGRAL((char){0}));
    test(IS_INTEGRAL((unsigned char){0}));
    test(IS_INTEGRAL((short){0}));
    test(IS_INTEGRAL((int){0}));
    test(IS_INTEGRAL((long){0}));
    test(IS_INTEGRAL((long long){0}));
    test(IS_INTEGRAL((unsigned int){0}));
    test(IS_INTEGRAL((unsigned long){0}));
    test(IS_INTEGRAL((unsigned long long){0}));

    test(!IS_INTEGRAL((float){0}));
    test(!IS_INTEGRAL((double){0}));
    test(!IS_INTEGRAL((long double){0}));
}

void test_is_floating_point(void)
{
    test(IS_FLOATING_POINT((float){0}));
    test(IS_FLOATING_POINT((double){0}));
    test(IS_FLOATING_POINT((long double){0}));

#ifdef __STDC_IEC_60559_DFP__
    test(IS_FLOATING_POINT((_Decimal32) {0}));
    test(IS_FLOATING_POINT((_Decimal64) {0}));
    test(IS_FLOATING_POINT((_Decimal128) {0}));
#endif

#ifdef __STDC_IEC_60559_COMPLEX__
    test(IS_FLOATING_POINT((float _Complex){0}));
    test(IS_FLOATING_POINT((double _Complex){0}));
    test(IS_FLOATING_POINT((long double _Complex){0}));
#endif

#ifdef _Imaginary_I
    test(IS_FLOATING_POINT((float _Imaginary){0}));
    test(IS_FLOATING_POINT((double _Imaginary){0}));
    test(IS_FLOATING_POINT((long double _Imaginary){0}));
#endif

    test(!IS_FLOATING_POINT((int){0}));
    test(!IS_FLOATING_POINT((unsigned int){0}));
}

void test_is_arithmetic(void)
{
    test(IS_ARITHMETIC((_Bool){0}));
    test(IS_ARITHMETIC((char){0}));
    test(IS_ARITHMETIC((unsigned char){0}));
    test(IS_ARITHMETIC((short){0}));
    test(IS_ARITHMETIC((int){0}));
    test(IS_ARITHMETIC((long){0}));
    test(IS_ARITHMETIC((long long){0}));
    test(IS_ARITHMETIC((unsigned int){0}));
    test(IS_ARITHMETIC((unsigned long){0}));
    test(IS_ARITHMETIC((unsigned long long){0}));
    test(IS_ARITHMETIC((float){0}));
    test(IS_ARITHMETIC((double){0}));
    test(IS_ARITHMETIC((long double){0}));

#ifdef __STDC_IEC_60559_DFP__
    test(IS_ARITHMETIC((_Decimal32){0}));
    test(IS_ARITHMETIC((_Decimal64){0}));
    test(IS_ARITHMETIC((_Decimal128){0}));
#endif

#ifdef __STDC_IEC_60559_COMPLEX__
    test(IS_ARITHMETIC((float _Complex){0}));
    test(IS_ARITHMETIC((double _Complex){0}));
    test(IS_ARITHMETIC((long double _Complex){0}));
#endif

#ifdef _Imaginary_I
    test(IS_FLOATING_POINT((float _Imaginary){0}));
    test(IS_FLOATING_POINT((double _Imaginary){0}));
    test(IS_FLOATING_POINT((long double _Imaginary){0}));
#endif

    test(!IS_ARITHMETIC(NULL));
    test(!IS_ARITHMETIC(nullptr));

    char c[] = {'1', '2', '3'};
    test(!IS_ARITHMETIC(c));
}

void test_is_c_str(void)
{
    char *str1;
    char *const str2;
    const char *str3;
    char str4[10]; 
    int *c;

    test(IS_C_STR(str1));
    test(IS_C_STR(str2));
    test(IS_C_STR(str3));
    test(IS_C_STR(str4));

    test(!IS_C_STR((int){0}));
    test(!IS_C_STR((double){0}));
    test(!IS_C_STR(c));

}

void test_is_compatible_with_array_of_length_n(void)
{
    char array[10];
    char array2[20];

    test(IS_COMPATIBLE_WITH_ARRAY_OF_LENGTH_N(array, 10));
    test(IS_COMPATIBLE_WITH_ARRAY_OF_LENGTH_N(array2, 20));

    test(!IS_COMPATIBLE_WITH_ARRAY_OF_LENGTH_N(array, 20));
    test(!IS_COMPATIBLE_WITH_ARRAY_OF_LENGTH_N(array2, 10));
}

void test_is_ula_or_vla(void)
{
    extern char ULA[];
    int x = 1;
    int VLA[x];
    int FLA[10];

    test(IS_VLA_OR_ULA(ULA));
    test(IS_VLA_OR_ULA(VLA));
    test(!IS_VLA_OR_ULA(FLA));
}

void test_is_function(void)
{
    int (*fptr)(void);
    int array[10];
    int x;

    test(IS_FUNCTION(test_is_function));
    test(IS_FUNCTION(test_is_ula_or_vla));

    test(!IS_FUNCTION(fptr));
    test(!IS_FUNCTION(array));
    test(!IS_FUNCTION(x));
    test(!IS_FUNCTION(nullptr));
}

void test_array_cardinality(void) 
{
    test(ARRAY_CARDINALITY(((int []){1, 2, 3, 4, 5})) == 5);
    test(ARRAY_CARDINALITY(((char []){'a', 'b', 'c'})) == 3);
    test(ARRAY_CARDINALITY(((double []){1.1, 2.2, 3.3, 4.4})) == 4);
    test(ARRAY_CARDINALITY(((int [][3]){{1, 2, 3}, {4, 5, 6}})) == 2);
}

void test_strip_lf(void)
{
    char str1[] = "Hello\n";
    STRIP_LF(str1);
    test(strcmp(str1, "Hello") == 0);

    char str2[] = "World\r";
    STRIP_LF(str2);
    test(strcmp(str2, "World") == 0);

    char str3[] = "Hello World\n\r";
    STRIP_LF(str3);
    test(strcmp(str3, "Hello World") == 0);

    char str4[] = "No linefeed";
    STRIP_LF(str4);
    test(strcmp(str4, "No linefeed") == 0);

    char str5[] = "";
    STRIP_LF(str5);
    test(strcmp(str5, "") == 0);

    char str6[] = "\n";
    STRIP_LF(str6);
    test(strcmp(str6, "") == 0);

    char str7[] = "\r";
    STRIP_LF(str7);
    test(strcmp(str7, "") == 0);

    char str8[] = "\r\r\n\n\r\n";
    STRIP_LF(str8);
    test(strcmp(str8, "") == 0);
}

void test_strlitlen(void)
{
    test(STRLITLEN((char []) {"hello"}) == 5);    
    test(STRLITLEN((char []) {"hello world"}) == 11);    
    test(STRLITLEN("hello") == 5);    
    test(STRLITLEN("hello world") == 11);    
}

void test_skip_chars(void) 
{
    char *result1 = (char []){"abcdef"};
    test(strcmp(SKIP_CHARS(result1, "a"), "bcdef") == 0);

    char *result2 = (char []){"Hello World"};
    test(strcmp(SKIP_CHARS(result2, "elo"), "Hello World") == 0);

    char *result3 = (char []){"12345"};
    test(strcmp(SKIP_CHARS(result3, ""), "12345") == 0);

    char *result4 = (char []){"abcdef"};
    test(strcmp(SKIP_CHARS(result4, "abcdef"), "") == 0);

    char *result5 = (char []){"abcdef"};
    test(strcmp(SKIP_CHARS(result5, "xyz"), "abcdef") == 0);

    char *result6 = (char []){""};
    test(strcmp(SKIP_CHARS(result6, "abc"), "") == 0);
}

void test_skip_ws(void) 
{
    char *s1 = (char []){"    Hello"};
    test(strcmp(SKIP_WS(s1), "Hello") == 0);

    char *s2 = (char []){"\t\n\t\tWorld"};
    test(strcmp(SKIP_WS(s2), "World") == 0);

    char *s3 = (char []){"\t  \n\r\f\vMixed Whitespace"};
    test(strcmp(SKIP_WS(s3), "Mixed Whitespace") == 0);

    char *s4 = (char []){"NoWhitespace"};
    test(strcmp(SKIP_WS(s4), "NoWhitespace") == 0);

    char *s5 = (char []){" \t\n\r\f\v"};
    test(strcmp(SKIP_WS(s5), "") == 0);

    char *s6 = (char []){""};
    test(strcmp(SKIP_WS(s6), "") == 0);
}

void test_foreach_array_element(void) 
{
    size_t sum = 0;

    FOREACH_ARRAY_ELEMENT(elem, ((size_t []){1, 2, 3, 4, 5})) { sum += *elem; }
    test(sum == 15); 

    char result[6] = ""; 
    char *ptr = result;

    FOREACH_ARRAY_ELEMENT(elem, ((char []){'a', 'b', 'c', 'd', 'e'})) { *ptr++ = *elem; }
    test(strcmp(result, "abcde") == 0); 
}

void test_init(void) 
{
    int *ip = (int [5]){};

    INIT(ip, int, 5, 1, 2, 3, 4, 5);

    for (int i = 0; i < 5; ++i) {
        test(ip[i] == i + 1);
    }

    char *cp = (char [6]){};
    INIT(cp, char, 6, 'a', 'b', 'c', 'd', 'e', '\0');
    test(strcmp(cp, "abcde") == 0); 
}

void test_maxsize(void) 
{
    struct sample{
        char a;
        int b;
        double c;
    };

    test(MAXSIZE(short, int) == sizeof(int));
    test(MAXSIZE(int*, char*) == sizeof(int*));
    test(MAXSIZE(int*, int[5]) == sizeof(int[5]));
    test(MAXSIZE(char, float) == sizeof(float));
    test(MAXSIZE(struct sample, double) == sizeof(struct sample));
}

void test_minsize(void) 
{
    struct sample {
        char a;
        int b;
        double c;
    };

    test(MINSIZE(short, int) == sizeof(short));
    test(MINSIZE(int*, char*) == sizeof(char*));
    test(MINSIZE(int*, int[5]) == sizeof(int*));
    test(MINSIZE(char, float) == sizeof(char));
    test(MINSIZE(struct sample, double) == sizeof(double));
}

void test_bytecopy(void)
{
    char s[10] = "hello";
    char t[12] = "world";

    BYTECOPY(s, t);
    test(strcmp(s, "world") == 0);

    char *u = (char []) {"wretched"};
    char *v = (char []) {"pride"};
    
    BYTECOPY(u, v);
    test(strcmp(u, "pride") == 0);
}

void test_double_capacity(void) 
{
    test(double_capacity(0) == 8);
    test(double_capacity(1) == 8);
    test(double_capacity(1024) == 2048);
    test(double_capacity(SIZE_MAX) == SIZE_MAX * 2);
}

void test_grow_capacity(void) 
{
    test(grow_capacity(0) == 8);
    test(grow_capacity(1) == 8);
    test(grow_capacity(10) == 15);
    test(grow_capacity(SIZE_MAX) == SIZE_MAX * 3 / 2);
}

void test_util_vasprintf(void)
{
    char *formatted;
    int len = util_asprintf(&formatted, "%d %s %d", 10, "hello", 20);
    test(len == 11);
    test(formatted);
    test(strcmp(formatted, "10 hello 20") == 0);
    free(formatted);
}

void test_util_asprintf(void)
{
    char *formatted;
    int len = util_asprintf(&formatted, "%d", 10);
    test(len == 2);
    test(formatted);
    test(strcmp(formatted, "10") == 0);
    free(formatted);
}

void test_util_strnlen(void)
{
    const char s[50] = "To be or not to be? That is the question.";
    test(util_strnlen(50, s) == strlen(s));
    test(util_strnlen(20, s) == 20);
}

void test_util_stpcpy(void)
{
    char s[10];
    char t[5] = "none";
    char *cp = util_stpcpy(s, t);

    test(*cp == '\0');
    test(strcmp(s, "none") == 0);

    test(*util_stpcpy(t, "bone") == '\0');
    test(*util_stpcpy(cp, t) == '\0');
    test(strcmp(s, "nonebone") == 0);
}

void test_util_basename(void) 
{
    test(strcmp(util_basename("/usr/lib"), "lib") == 0);
    test(strcmp(util_basename("/usr/"), "") == 0);
    test(strcmp(util_basename("usr"), "usr") == 0);
    test(strcmp(util_basename("/"), "") == 0);
    test(strcmp(util_basename("."), ".") == 0);
    test(strcmp(util_basename(".."), "..") == 0);
}

void test_util_strhcrnul(void)
{
    static const char haystack[] = "hello there";
    test(util_strchrnul(haystack, 'o') == strchr(haystack, 'o'));
    test(*util_strchrnul(haystack, 'p') == '\0');

#if defined(__GNUC__) || defined(__clang__) || defined(__INTEL_LLVM_COMPILER)
    /* Specify the prototype, because defining _GNU_SOURCE doesn't seem to. */
    char *strchrnul(const char *p, int ch);

    static const char s[] = "hair"; 
    static const char t[] = "gown"; 
    test(util_strchrnul(s, 'h') == strchrnul(s, 'h'));
    test(util_strchrnul(t, 'g') == strchrnul(t, 'g'));
#endif 
}

void test_util_strcasecmp(void)
{
    test(util_strcasecmp("aPplE", "APPLE") == 0);
    test(util_strcasecmp("apple", "apple") == 0);
    test(util_strcasecmp("HELLO", "HELLO") == 0);
    test(util_strcasecmp("", "") == 0);
    test(util_strcasecmp("HrLLO", "HELLO"));
}

void test_util_memswap(void)
{
    struct { 
        const char *name;
        size_t serial_no; 
    } x = {"Polyphemus", 1},  y = {"nobody", 2};

    util_memswap(sizeof x, &x, &y);
    test(strcmp(x.name, "nobody") == 0);
    test(x.serial_no == 2);
    test(strcmp(y.name, "Polyphemus") == 0);
    test(y.serial_no == 1);
}

void test_swap(void)
{
    int a = 10;
    int b = 20;

    SWAP(a, b);
    test(a == 20);
    test(b == 10);

    char s[10] = "hello";
    char t[10] = "world";

    SWAP(s, t);
    test(strcmp(s, "world") == 0);
    test(strcmp(t, "hello") == 0);

    const char *u = "mango";
    const char *v = "banana";

    SWAP(u, v);
    test(strcmp(u, "banana") == 0);
    test(strcmp(v, "mango") == 0);
}

int main(void) 
{
    test_charify();
    test_stringify();
    test_range();
    test_rangem1();
    test_for_n_times();
    test_is_compatible();
    test_is_nullptr();
    test_is_file_ptr();
    test_is_array();
    test_is_pointer();
    test_is_signed();
    test_is_unsigned();
    test_is_integral();
    test_is_floating_point();
    test_is_arithmetic();
    test_is_c_str();
    test_is_compatible_with_array_of_length_n();
    test_is_ula_or_vla();
    test_is_function();
    test_array_cardinality();
    test_strip_lf();
    test_strlitlen();
    test_skip_chars();
    test_skip_ws();
    test_for_n_times();
    test_init();
    test_maxsize();
    test_minsize();
    test_bytecopy();
    test_double_capacity();
    test_grow_capacity();

    test_util_vasprintf();
    test_util_asprintf();
    test_util_strnlen();
    test_util_stpcpy();
    test_util_strhcrnul();
    test_util_basename();
    test_util_strcasecmp();
    test_util_memswap();
    test_swap();

    return EXIT_SUCCESS;
}
