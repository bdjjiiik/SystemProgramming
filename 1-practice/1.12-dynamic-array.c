#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int size = 0;
    printf("Enter array size > ");
    scanf("%d", &size);
    if (size < 0) {
        fprintf(stderr, "Size cannot be below zero\n");
        exit(EXIT_FAILURE);
    }

    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i += 1)
        arr[i] = size;

    printf("-- Array (size = %d) --\n", size);
    for (int i = 0; i < size; i += 1)
        printf("%d  ", arr[i]);
    printf("\n----------------------\n");

    free(arr);
    exit(EXIT_SUCCESS);
}
