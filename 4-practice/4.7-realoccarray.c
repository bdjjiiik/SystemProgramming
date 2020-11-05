#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    struct bar {
        char buf[512];
    };

    struct bar *ptr = NULL, *newptr = NULL;
    size_t bar_size = sizeof(struct bar);

    ptr = calloc(10, bar_size);
    if (!ptr)
        fprintf(stderr, "malloc failed!"), exit(EXIT_FAILURE);

    newptr = (struct bar *)reallocarray(ptr, 50, bar_size);

    if (!newptr)
        fprintf(stderr, "reallocarray failed!"), exit(EXIT_FAILURE);

    free(newptr);

    exit(EXIT_SUCCESS);
}
