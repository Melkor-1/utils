#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <termios.h>
#include <unistd.h>

#include "term.h"

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

static struct termios old;

bool test_term_enable_raw_mode(void)
{
    test(term_enable_raw_mode(&old) == TERM_SUCCESS);

    struct termios curr;

    if (tcgetattr(STDIN_FILENO, &curr) == -1) {
        perror("tcgetattr()");
        return false;
    }

    test((curr.c_iflag & IGNBRK) == 0);
    test((curr.c_iflag & BRKINT) == 0);
    test((curr.c_iflag & PARMRK) == 0);
    test((curr.c_iflag & INPCK) == 0);
    test((curr.c_iflag & ISTRIP) == 0);
    test((curr.c_iflag & ICRNL) == 0);
    test((curr.c_iflag & INLCR) == 0);
    test((curr.c_iflag & IGNCR) == 0);
    test((curr.c_iflag & IXON) == 0);

    test((curr.c_lflag & ISIG) == 0);
    test((curr.c_lflag & IEXTEN) == 0);
    test((curr.c_lflag & ECHO) == 0);
    test((curr.c_lflag & ICANON) == 0);

    test((curr.c_cflag & CS8) != 0);

    test((curr.c_oflag & OPOST) == 0);

    test(curr.c_cc[VMIN] == 1);
    test(curr.c_cc[VTIME] == 0);

    return true;
}

bool test_term_disable_raw_mode(void)
{
    test(term_disable_raw_mode(&old) == TERM_SUCCESS);

    struct termios curr;

    if (tcgetattr(STDIN_FILENO, &curr) == -1) {
        perror("tcgetattr()");
        return false;
    }

    test(memcmp(&old, &curr, sizeof curr) == 0);
    return true;
}

int main(void)
{
    return test_term_enable_raw_mode() && test_term_disable_raw_mode() 
           ? EXIT_SUCCESS
           : EXIT_FAILURE;
}
