#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "attrib.h"

#define FAIL -1

/* If BUFSIZ is indeterminate, this might be inadequate. */
#define PAGE_SIZE_GUESS		4096

ATTRIBUTE_COLD void set_page_size (long *page_size)
{
    if (!*page_size) {
        errno = 0;
        if ((*page_size = sysconf (_SC_PAGE_SIZE)) == FAIL) {
            /*
             * errno is unchanged if _SC_PAGE_SIZE is indeterminate, or unsupported. 
             */
            if (!errno) {
                *page_size = PAGE_SIZE_GUESS;
            } else {
                perror ("sysconf()");
            }
        }
    }
}

/* If PATH_MAX is indeterminate, no guarantee this is adequate. */
#define PATH_MAX_GUESS 4096

ATTRIBUTE_COLD void set_path_max (long *path_max) 
{
	if (!*path_max) {
		errno = 0;
		if ((*path_max = pathconf ("/", _PC_PATH_MAX)) == FAIL) {
			if (!errno) {
				*path_max = PATH_MAX_GUESS;
			} else {
				perror ("pathconf()");
			}
		} else {
			path_max++;		/* Add one since it's relative to root. */
		}
	}
}

