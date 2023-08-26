#include <stdlib.h>

#ifndef STDDEF_H
#include <stddef.h>
#endif

#include <errno.h>
#include <limits.h>
#include <stdint.h>

#include "attrib.h"

#define FAIL -1


#ifdef PATH_MAX
static long path_max = PATH_MAX;
#else
static long path_max = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

/* If PATH_MAX is indeterminate, no guarantee this is adequate */
#define PATH_MAX_GUESS 4096

/* Synopsis: Dynamically allocates space for a pathname. Stores the path size in *size_p.
*  Returns: The allocated size (if non-null), else returns NULL.
*/
ATTRIBUTE_COLD char *path_alloc(size_t *size_p) 
{
	size_t size;

	if (!posix_version) {
		posix_version = sysconf(_SC_VERSION);
	}
	
	if (!xsi_version) {
		xsi_version = sysconf(_SC_XOPEN_VERSION);
	}

	if (!path_max) {
		errno = 0;
		if ((path_max = pathconf("/", _PC_PATH_MAX)) < 0) {
			if (!errno) {
				path_max = PATH_MAX_GUESS;	/* errno is unchanged if limit is indeterminate */
			} else {
				perror("pathconf");
				return 0;
			}
		} else {
			path_max++; 	/* add one since it's relative to root */
		}
	}

	/* Before POSIX.1-2001, we aren't guaranteed that PATH_MAX includes
	*  the terminating null byte. Same goes for XPG3.
	*/
	if ((posix_version < 200112L) && (xsi_version < 4)) {
		size = path_max + 1;
	} else {
		size = path_max;
	}
	
	char *ptr;
	if (!(ptr = malloc(size))) {
		errno = ENOMEM;
		perror("malloc");
		return 0;
	}

	if (size_p) {
		*size_p = size;
	}
	return ptr;
}

#ifdef OPEN_MAX
static long open_max = OPEN_MAX;
#else
static long open_max = 0;
#endif

/* If OPEN_MAX is indeterminate, this might be inadequate 
*/
#define OPEN_MAX_GUESS 256

/* Returns the max limit of open files, or -1 in case of sysconf failure 
*/
ATTRIBUTE_COLD long open_max (void)
{
	if (!open_max) {
		errno = 0;
		if ((open_max = sysconf(_SC_OPEN_MAX)) < 0) {
			if (!errno) {
				open_max = OPEN_MAX_GUESS;	/* errno is unchanged if open_max is undeterminate */
			} else {
				perror("sysconf");
				return FAIL;
			}
		}
	}
	return open_max;
}

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
			++path_max;		/* Add one since it's relative to root. */
		}
	}
}

