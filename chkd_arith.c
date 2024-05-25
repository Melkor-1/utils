#include <stdint.h>

bool chkd_add(int32_t result[static 1], int32_t a, int32_t b)
{
    if (a >= 0) {
        if (b > (INT32_MAX - a)) {
            return false;
        }
    } else {
        if (b < (INT32_MIN - a)) {
            return false;
        }
    }

    *result = a + b;
    return true;
}

bool chkd_mul(unsigned char result[static 1], unsigned char a, unsigned char b)
{
    if (a != 0 && b > UCHAR_MAX / a) {
        return false;
    }
}
    *result = a * b;
    return true;
}
