#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PRESICION 1E-2

int search(double *arr, int size, double to_search) {
    for (int i = 0; i < size; i += 1) {
        if (fabs(arr[i] - to_search) < PRESICION)
            return i;
    }
    return -1;
}

int main(void) {
    time_t t;
    srand(time(&t));
    int size = 0;
    printf("Enter array size > ");
    scanf("%d", &size);
    if (size < 0) {
        fprintf(stderr, "Size cannot be below zero\n");
        exit(EXIT_FAILURE);
    }

    double *arr = (double *)malloc(size * sizeof(double));
    for (int i = 0; i < size; i += 1)
        arr[i] = (double)rand() / RAND_MAX * size;

    printf("-- Array (size = %d) --\n", size);
    for (int i = 0; i < size; i += 1)
        printf("%lf  ", arr[i]);
    printf("\n----------------------\n");

    double to_search = 0.0;
    printf("Enter number to find > ");
    scanf("%lf", &to_search);
    int pos = search(arr, size, to_search);
    if (pos != -1) {
        printf("Number find on pos   > arr[%d] = %lf", pos, arr[pos]);
    } else {
        printf("Number din not find");
    }
    printf("\n");

    free(arr);
    exit(EXIT_SUCCESS);
}