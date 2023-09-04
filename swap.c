#include <string.h>

static inline void swap_detail (void *p1, void *p2, void *tmp, size_t psize)
{
    memcpy (tmp, p1, psize);
    memcpy (p1, p2, psize);
    memcpy (p2, tmp, psize);
}

/**
*   Properties:
*   It evaluates each of a and b only once.
*   It has a compile time check for the correct sizes.
*   It has no naming issue with a hidden variable.
*   The size of the temporary variable is computed at compile time, so the compound literal is not a dynamic array.
*
*   Drawbacks:
*   It is not type safe. It only checks for the sizes of the types, not their semantics. 
*   If the types differ, say a double of size 8 and a uint64_t, you are in trouble.
*   The expressions must allow the & operator to be applicable. Thus it will not work on variables that are 
*   declared with the register storage class.
*/
#define SWAP(a, b) swap_detail (&(a), &(b), (char[(sizeof(a) == sizeof(b)) ? (ptrdiff_t)sizeof(a) : -1]){0}, sizeof(a))


