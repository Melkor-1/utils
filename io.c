#undef POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#define _POSIX_C_SOURCE 2008'19L
#define _XOPEN_SOURCE   700

#include "io.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

ssize_t read_eintr(int fd, void *buf, size_t size)
{
    ssize_t ret = 0;

    do {
        errno = 0;
        ret = read(fd, buf, size);
    } while (ret == -1 && errno == EINTR);

    return ret;
}

ssize_t write_eintr(int fd, const void *buf, size_t size)
{
    ssize_t ret = 0;

    do {
        errno = 0;
        ret = write(fd, buf, size);
    } while (ret == -1 && errno == EINTR);

    return ret;
}

ssize_t write_all(int fd, 
                  void *restrict buf, 
                  size_t size, 
                  size_t *restrict nwritten)
{
    size_t total_written = 0;
    size_t bytes_left = size;
    ssize_t ret;

    for (ret = 0; total_written < size && ret != -1;
        total_written += (size_t) ret) {
        ret = write_eintr(fd, buf + total_written, bytes_left);
        bytes_left -= (size_t) ret;
    }
    *nwritten = total_written;
    return ret;
}
