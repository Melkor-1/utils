#ifndef ATTRIB_H
#define ATTRIB_H 1

#if defined(__has_c_attribute)
#	if __has_c_attribute(maybe_unused)
#		define ATTRIBUTE_MAYBE_UNUSED				[[maybe_unused]]
#	endif                   /* maybe_unused */
#elif defined(__GNUC__) || defined(__clang__)
#		define ATTRIBUTE_MAYBE_UNUSED				__attribute__((maybe_unsued))
#else
#	define ATTRIBUTE_MAYBE_UNUSED   /* If only. */
#endif                          /* __has_c_attribute || __GNUC__ || __clang__ */

#if defined(__GNUC__) || defined(__clang__)
#	define ATTRIBUTE_PRINTF_LIKE(n, m) 			__attribute__((format(printf, n, m)))
#	define ATTRIBUTE_COLD						__attribute__((cold))
#	define ATTRIBUTE_HOT						__attribute__((hot))
#	define ATTRIBUTE_PURE						__attribute__((pure))
#	define ATTRIBUTE_RETURNS_NONNULL			__attribute__((returns_nonnull))
#	define ALWAYS_INLINE						static inline __attribute__((always_inline))
#	define NO_INLINE							__attribute__((noinline))
#else
#	define ATTRIBUTE_PRINTF_LIKE(n, m)      /* If only. */
#	define ATTRIBUTE_COLD   /* If only. */
#	define ATTRIBUTE_HOT    /* If only. */
#	define ATTRIBUTE_PURE   /* If only. */
#	define ATTRIBUTE_RETURNS_NONNULL        /* If only. */
#	define ALWAYS_INLINE    /* If only. */
#	define NO_INLINE        /* If only. */
#endif                          /* __GNUC__ || __clang__ */

#if defined(__GNUC__) || defined(__clang__)
#	define likely(x)		__builtin_expect((x), 1)
#	define unlikely(x)		__builtin_expect((x), 0)
#else
#	define likely(x)		(x)
#	define unlikely(x)		(x)
#endif                          /* __GNUC__ || __clang__ */

#endif                          /* ATTRIB_H */
