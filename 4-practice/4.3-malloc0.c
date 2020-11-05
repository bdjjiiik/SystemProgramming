#include <stdio.h>
#include <stdlib.h>

int main(void) {
    void *ptr;
    ptr = malloc(0);

    if (ptr) {
        printf("ptr does not NULL\n");
    }
    free(ptr);
    
    exit(EXIT_SUCCESS);
}
