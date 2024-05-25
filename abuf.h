#ifndef ABUF_H
#define ABUF_H 1

#include "stddef.h"

/* We define a simple 'append buffer', that is a heap allocated string
 * where we can append to. This avoids calling write() every time we have
 * to print something (e.g. escape sequences) while refreshing the screen,
 * and any flickering effects. */
typedef struct abuf {
    char *buf;          /* A pointer to a chunk of allocated memory. */
    size_t count;       /* Total bytes occupied. */
    size_t capacity;    /* Total bytes allocated. */
} abuf;

/* Reserves initial_capacity bytes for ab.
 *
 * Returns true on success or false if memory allocation failed. */
[[nodiscard]] bool abuf_init(abuf ab[static 1], size_t initial_capacity);

/* s should a null-terminated string of length len. 
 * Passing ab->buf as s would invoke undefined behavior. 
 * 
 * Returns true on success, or false on integer overflow or memory allocation
 * failure. */
[[nodiscard]] bool abuf_append(abuf ab[restrict static 1],
                               size_t len,                   
                               const char s[restrict static len]);

/* The difference between abuf_reset() and abuf_free() is that the former does
 * not free the memory associated with ab; this can save on allocations. */

void abuf_reset(abuf ab[static 1]);

void abuf_free(abuf ab[static 1]);

#endif /* ABUF_H */
