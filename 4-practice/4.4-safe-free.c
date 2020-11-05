#include <stdlib.h>

#define SAFE_FREE(ptr)               \
    {                                \
        if (ptr)                     \
            free(ptr), (ptr) = NULL; \
    }

int main(void) {
    char *ptr = NULL;

    int i = 0, n = 100;
    while (i != n) {
        if (!ptr)
            ptr = malloc(n);

        *(ptr + i) = (char)i;
        SAFE_FREE(ptr);

        i += 1;
    }

    return 0;
}
