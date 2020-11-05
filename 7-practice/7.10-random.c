#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    time_t t;
    time(&t);

    srand48((long)t);

    // A 0 - 1
    for (int i = 0; i < 10; i += 1)
        printf("%-10f ", (float)drand48());
    printf("\n");

    // B 0 - N
#define N 100
    for (int i = 0; i < 10; i += 1)
        printf("%-10f ", (float)drand48() * N);
    printf("\n");

    return 0;
}
