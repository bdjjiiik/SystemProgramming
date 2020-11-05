#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    time_t t;
    time(&t);

    srand48((long)t);

    int n = 0.0;

    printf("Enter number > ");
    scanf("%d", &n);
    
    printf("%f ", (float) drand48() * n);
    printf("\n");

    exit(EXIT_SUCCESS);
}
