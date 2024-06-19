#ifndef IO_H
#define IO_H 1

#include <sys/types.h>

/** 
 * These functions return -1 on failure, or a non-negative integer otherwise. */

/** 
 * Version of read() that retries when interrupted by EINTR (possibly by a 
 * SIGWINCH). */
[[nodiscard, gnu::nonnull]] ssize_t io_read_eintr(int fd, void *buf, size_t size);

/**
 * Version of write() that retries when interrupted by EINTR (possibly 
 * by a SIGWINCH). */
[[nodiscard, gnu::nonnull]] ssize_t io_write_eintr(int fd, 
                                                   const void *buf, 
                                                   size_t size);

/**
 * Version of read() that retries when interrupted by EINTR (possibly by a 
 * SIGWINCH). */
[[nodiscard, gnu::nonnull]] ssize_t io_read_all(int fd, void *buf, size_t size);

/** 
 * A wrapper around io_write_eintr() that's called in a loop until size bytes 
 * have been written. */ 
[[nodiscard, gnu::nonnull]] ssize_t io_write_all(int fd, 
                                              const void *buf, 
                                              size_t size);

/** 
 * Copies src_fd's mode bits to dest_fd. */
[[nodiscard]] ssize_t io_copy_file_perms(int src_fd, int dest_fd);

#endif /* IO_H */
