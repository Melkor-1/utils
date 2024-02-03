#include <stdio.h>
#include <stdlib.h>

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

/* The level of indirection is needed, INDIRECT(MAX_LEN) would expand to "MAX_LEN".
*/
#define STRINGIFY(X) INDIRECT(X)
#define INDIRECT(X) #X

#define MINSIZE(X, Y) (sizeof(X) < sizeof(Y) ? sizeof(X) : sizeof(Y))
#define BYTECOPY(T, S) memcpy(&(T), &(S), MINSIZE(T, S))

int main(void)
{
    printf("%d\n", MIN(65, 472));       /* Might avoid runtime overhead of function calls */
    printf("%f\n", MIN(65.58, 382.9));  /* Flexibility */
    printf("%lf\n", MIN(65.58, "hey")); /* But no type-checking */

    puts("%" STRINGIFY(MAX_LEN) "d");

    char *t = "To be or not to be?";
    char *s = "That is the question.";

    fprintf(stderr, "sizeof (s): %zu | sizeof (t): %zu\n", sizeof (s),
        sizeof (t));
    BYTECOPY(t, s);
    printf("%s", t);            /* This overwrites t with s */

    return EXIT_SUCCESS;
}
