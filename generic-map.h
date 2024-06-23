#ifndef GENERIC_MAP_H
#define GENERIC_MAP_H 1

#include <stddef.h>

typedef void (*map_func)(void *, const void *);

/* Fills the destination array dest with the image of the source array src
 * under the map function f.
 *
 * The source array must contain at least n elements of size src_elem_size.
 * The destination array must contain at least n elements of size
 * dest_elem_size.
 * Both arrays must be correctly-aligned, and must not overlap. 
 *
 * Returns a pointer to the destination array. */
[[gnu::nonnull, gnu::returns_nonnull]] void *map_generic(map_func f,
                                                         size_t n,
                                                         void *dest,
                                                         size_t dest_elem_size, 
                                                         const void *src,
                                                         size_t src_elem_size);

#endif /* GENERIC_MAP_H */
