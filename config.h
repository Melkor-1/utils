#ifndef CONFIG_H
#define CONFIG_H 1

#include <stddef.h>

#include "attrib.h"

ATTRIBUTE_COLD char *path_alloc(size_t *size_p);
ATTRIBUTE_COLD long open_max(void);
ATTRIBUTE_COLD void set_page_size(long *page_size);
ATTRIBUTE_COLD void set_path_max(long *path_max);

#endif                          /* CONFIG_H */
