#ifndef IO_H
#define IO_H 1

#include <sys/types.h>

/* These functions return -1 on failure, or a non-negative integer otherwise. */

/* Version of read() that retries when interrupted by EINTR (possibly 
 * by a SIGWINCH).  */
[[nodiscard, gnu::nonnull]] ssize_t read_eintr(int fd, void *buf, size_t size);

/* Version of write() that retries when interrupted by EINTR (possibly 
 * by a SIGWINCH). */
[[nodiscard, gnu::nonnull]] ssize_t write_eintr(int fd, 
                                                const void *buf, 
                                                size_t size);

/* A wrapper around write_eintr() that's called in a loop until size bytes have 
 * been written. Sets *nwritten to the number of total bytes written. */
[[nodiscard, gnu::nonnull]] ssize_t write_all(int fd, 
                                              void *restrict buf, 
                                              size_t size, 
                                              size_t *restrict nwritten);

#endif /* IO_H */
