#include "generic_map.h"

#include <stddef.h>

void *map_generic(map_func f,
                  size_t n,
                  void *dest,
                  size_t dest_elem_size, 
                  const void *src,
                  size_t src_elem_size)
{
    for (size_t i = 0; i < n; ++i) {
        const char *const srcp = (char *)src + src_elem_size * i;
        char *const destp = (char *)dest + dest_elem_size * i;
        f(destp, srcp);
    }

    return dest;
}

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ELEMS 101U

static inline void my_sqrt(void *destp, const void *srcp)
{
   double *const dest = destp;
   const unsigned *const src = srcp;

   *dest = sqrt((double)*src);
}

int main(void)
{
    unsigned int xs[ELEMS];
    double ys[ELEMS];

    for (unsigned i = 0; i < ELEMS; ++i) {
        xs[i] = i;
    }

    map_generic(my_sqrt,
                ELEMS,
                ys,
                sizeof ys[0],
                xs,
                sizeof xs[0]); 

    for (unsigned i = 0; i < ELEMS; ++i) {
        printf("%f\n", ys[i]);
    }

    return EXIT_SUCCESS;
}

#endif /* TEST_MAIN */
