#undef POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#define _POSIX_C_SOURCE 2008'19L
#define _XOPEN_SOURCE   700

#include "io.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

ssize_t io_read_eintr(int fd, void *buf, size_t size)
{
    ssize_t ret = 0;

    do {
        errno = 0;
        ret = read(fd, buf, size);
    } while (ret == -1 && errno == EINTR);

    return ret;
}

ssize_t io_write_eintr(int fd, const void *buf, size_t size)
{
    ssize_t ret = 0;

    do {
        errno = 0;
        ret = write(fd, buf, size);
    } while (ret == -1 && errno == EINTR);

    return ret;
}

ssize_t io_read_all(int fd, void *buf, size_t size)
{
    size_t rcount = 0;
    size_t bytes_left = size;
    ssize_t ret;

    for (ret = 0; rcount < size && ret != -1; rcount += (size_t) ret) {
        ret = io_read_eintr(fd, (char *) buf + rcount, bytes_left);
        bytes_left -= (size_t) ret;
    }

    return ret == -1 ? -1 : rcount;
}

ssize_t io_write_all(int fd, const void *buf, size_t size)
{
    size_t wcount = 0;
    size_t bytes_left = size;
    ssize_t ret;

    for (ret = 0; wcount < size && ret != -1; wcount += (size_t) ret) {
        ret = io_write_eintr(fd, (char *) buf + wcount, bytes_left);
        bytes_left -= (size_t) ret;
    }

    return ret == -1 ? -1 : wcount;
}

ssize_t io_copy_file_perms(int src_fd, int dest_fd)
{
    struct stat st;

    return fstat(src_fd, &st) != -1 && fchmod(dest_fd, st.st_mode) != -1 ? 0 : -1;
}
