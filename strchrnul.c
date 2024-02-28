#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define _GNU_SOURCE

char *strchrnul(const char *p, int ch);

const char *io_strchrnul(const char *p, char c)
{
    for (;; ++p) {
        if (*p == c || *p == '\0') {
            return p;
        }
    }

    /* UNREACHED */
}

int main(void)
{
    const char *const s = "hello world";
    puts(io_strchrnul(s, 'w'));
    puts(strchrnul(s, 'w'));

    puts(io_strchrnul(s, 'g'));
    puts(strchrnul(s, 'g'));

    assert(io_strchrnul(s, 'h') == strchrnul(s, 'h'));
    assert(io_strchrnul(s, 'g') == strchrnul(s, 'g'));
    return EXIT_SUCCESS;
}
