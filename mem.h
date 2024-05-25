#ifndef MEM_H
#define MEM_H 1

#define Fn_apply(type, fn, ...) do {	\
		type **list = (type*[]){ __VA_ARGS__, nullptr};	\
		for (size_t i = 0; list[i]; i++)	\
			fn(list[i]);	\
		} while (false)

#define Free_all(...) Fn_apply(void, free, __VA_ARGS__)


[[gnu::always_inline, gnu::const]] static inline size_t double_capacity(size_t cap)
{
    return cap < 8 ? 8 : cap * 2;
}

[[gnu::always_inline, gnu::const]] static inline size_t grow_capacity(size_t cap)
{
    return cap < 8 ? 8 : cap * 3 / 2;
}

#endif                          /* MEM_H */
