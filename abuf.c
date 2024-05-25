#include <stdlib.h>
#include <string.h>

#include "abuf.h"
#include "mem.h"

bool abuf_init(abuf ab[static 1], size_t initial_capacity)
{
    ab->count = 0;
    ab->buf = malloc(initial_capacity);
    return ab->buf != nullptr ? (ab->capacity = initial_capacity) : false;
}

bool abuf_append(abuf ab[restrict static 1],
                 size_t len,
                 const char s[restrict static len])
                           
{
    if ((ab->count + len) >= ab->capacity) {
        size_t new_capacity = grow_capacity(ab->capacity);
        void *const tmp = realloc(ab->buf, new_capacity);

        if (tmp == nullptr) {
            return false;
        }
        ab->capacity = new_capacity;
        ab->buf = tmp;
    }

    memcpy(ab->buf + ab->count, s, len + 1);
    ab->count += len;
    return true;
}

void abuf_clear(abuf ab[static 1])
{
    ab->count = 0u; 
}

void abuf_free(abuf ab[static 1]) 
{
    free(ab->buf);
    ab->buf = nullptr;
    ab->count = ab->capacity = 0u;
}

#ifdef TEST_MAIN

#include <assert.h>
#include <stdio.h>

int main(void)
{
    abuf ab;
    assert(abuf_init(&ab, 100));
    assert(abuf_append(&ab, 5, "hello"));
    assert(abuf_append(&ab, 7, ", world!"));
    assert(abuf_append(&ab, 13, " How are you?"));
    assert(abuf_append(&ab, 23, " Greetings from C-land."));
    puts(ab.buf);
    abuf_free(&ab);
}

#endif  /* TEST_MAIN */
