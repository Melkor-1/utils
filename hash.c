#if 0
cc -Wall -Wextra -std=c17 "$0"; exit
#endif

#include <stdio.h>

#define TABLE_SIZE 8

/* Reference: www.cse.yorku.ca/~oz/hash.html */
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

#ifdef TEST_MAIN
int main(void)
{
    printf("a ==> %lu.\n", hash("a") % TABLE_SIZE);
    printf("b ==> %lu.\n", hash("b") % TABLE_SIZE);
    printf("g ==> %lu.\n", hash("g") % TABLE_SIZE);
    printf("%% ==> %lu.\n", hash("%") % TABLE_SIZE);
    printf("_ ==> %lu.\n", hash("_") % TABLE_SIZE);
    printf("n ==> %lu.\n", hash("n") % TABLE_SIZE);
    printf("q ==> %lu.\n", hash("q") % TABLE_SIZE);
}
#endif
