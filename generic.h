#ifndef GENERIC_H
#define GENERIC_H

#define Min(x, y) _Generic ((x) + (y),	\
					long double: min_ld,	\
					double:	min_d,	\
					float:	min_f,	\
					unsigned long long: min_ull,	\
					long long: min_ll,	\
					unsigned long: min_ul,	\
					long: min_l,	\
					unsigned: min_u,	\
					default: min_i	\
					)(x, y)
						
#define gen_min(_suffix, _type) \
	static inline _type min_##_suffix (_type x, _type y) \
	{	return x < y ? x : y;	}

gen_min (ld, long double)
gen_min (d, double)
gen_min (f, float)
gen_min (ull, unsigned long long)
gen_min (ll, long long)
gen_min (ul, unsigned long)
gen_min (l, long)
gen_min (u, unsigned)
gen_min (i, int)

#define Max(x, y) _Generic ((x) + (y),	\
					long double: max_ld,	\
					double:	max_d,	\
					float:	max_f,	\
					unsigned long long: max_ull,	\
					long long: max_ll,	\
					unsigned long: max_ul,	\
					long: max_l,	\
					unsigned: max_u,	\
					default: max_i	\
					)(x, y)
						
#define gen_max(_suffix, _type) \
	static inline _type max_##_suffix (_type x, _type y) \
	{	return x > y ? x : y;	}

gen_max (ld, long double)
gen_max (d, double)
gen_max (f, float)
gen_max (ull, unsigned long long)
gen_max (ll, long long)
gen_max (ul, unsigned long)
gen_max (l, long)
gen_max (u, unsigned)
gen_max (i, int)

ATTRIBUTE_COLD extern void set_page_size (long *page_size);
ATTRIBUTE_COLD extern void set_path_max (long *path_max); 

#endif /* GENERIC_H */

