#if 0
cc -Wall -Wextra -std=c17 "$0"; exit
#endif

#include <stdint.h>

int32_t safe_add(int32_t a, int32_t b)
{
    if (a >= 0) {
        if (b > (INT32_MAX - a)) {
            return -1;
        }
    } else {
        if (b < (INT32_MIN - a)) {
            return -1;
        }
    }
    return a + b;
}
