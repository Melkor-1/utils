/*
 * Date: 13th June, 2024
 * Author: Melkor-1
 */

#ifndef STD_H
#define STD_H 1

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined __STDC__ && defined __STDC_VERSION__
    #if __STDC_VERSION__ >= 199409
        #include <iso646.h>
        #include <wchar.h>
        #include <wctype.h>
    #endif

    #if __STDC_VERSION__ >= 199901
        #ifndef __STDC_NO_COMPLEX__
            #include <complex.h>
        #endif

        #include <fenv.h>
        #include <inttypes.h>
        #include <stdbool.h>
        #include <stdint.h>
        #include <tgmath.h>
    #endif

    #if __STDC_VERSION__ >= 201112
        #include <stdalign.h>
        
        #ifndef __STDC_NO_ATOMICS__
            #include <stdatomic.h>
        #endif

        #include <stdnoreturn.h>
        
        #ifndef __STDC_NO_THREADS__
            #include <threads.h>
        #endif
        
        #include <uchar.h>
    #endif

    #if __STDC_VERSION__ >= 201710
        /* None added */
    #endif

    # if __STDC_VERSION__ >= 202000
        #include <stdbit.h>
        #include <stdckdint.h>
    #endif
#endif  /* defined __STDC__ && defined __STDC_VERSION__ */

#endif /* STD_H_ */
