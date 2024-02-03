#if 0
cc -Wall -Wextra -std=c17 "$0"; exit
#endif

#include "size.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>

#define ARRAY_CARDINALITY(x) (sizeof(x) / sizeof (*(x)))

static const char *const sizes[] =
    { "EiB", "PiB", "TiB", "GiB", "MiB", "KiB", "B" };
static const uint64_t exbibytes =
    1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL;

/* Acknowledgements:
 * @Jonathan Leffer - [Converting a number of bytes into a file size in C]
 * (https://stackoverflow.com/q/3898840/20017547)
 */
char *calculate_size(uint64_t size)
{
    char *const result = malloc(32);

    if (!result) {
        return NULL;
    }

    uint64_t multiplier = exbibytes;

    for (size_t i = 0; i < ARRAY_CARDINALITY(sizes); ++i, multiplier /= 1024) {
        if (size < multiplier) {
            continue;
        }

        if (size % multiplier == 0) {
            sprintf(result, "%" PRId64 " %s", size / multiplier, sizes[i]);
        } else {
            sprintf(result, "%.1lf %s", (double) size / (double) multiplier,
                sizes[i]);
        }
        return result;
    }

    return strcpy(result, "0");
}

#ifdef TEST_MAIN
int main(void)
{
    static const uint64_t list[] = {
        0, 1, 2, 34, 900, 1023, 1024, 1025, 2048, 1024 * 1024,
        1024 * 1024 * 1024 + 1024 * 1024 * 400
    };

    for (size_t i = 0; i < ARRAY_CARDINALITY(list); ++i) {
        char *const str = calculate_size(list[i]);

        if (!str) {
            perror("malloc()");
            return EXIT_FAILURE;
        }

        printf("%18" PRId64 " = %s\n", list[i], str);
        free(str);
    }

    return EXIT_SUCCESS;
}
#endif
