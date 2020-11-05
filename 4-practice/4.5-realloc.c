#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    void *ptr = NULL, *copy = NULL, *newptr = NULL;

    size_t size = 10;
    ptr = calloc(size, sizeof(char));
    copy = calloc(size, sizeof(char));
    if (!ptr || !copy)
        fprintf(stderr, "calloc failed!\n"), exit(EXIT_FAILURE);

    memset(ptr, '0', size);
    memcpy(copy, ptr, size);

    newptr = realloc(ptr, __PTRDIFF_MAX__);
    if (newptr) {
        printf("Where you find so memory?\n");
        free(newptr);
    } else {
        fprintf(stderr, "reallocarray failed!\n");

        if (!memcmp(ptr, copy, size))
            printf("Memory doesn`t change\n");
        else
            printf("Memory change after realloc!\n");

        free(ptr);
    }
    free(copy);

    exit(EXIT_SUCCESS);
}