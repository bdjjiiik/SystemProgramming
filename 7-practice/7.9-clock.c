#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void) {
    time_t start, stop;
    time(&start);

    sleep(3);

    time(&stop);
    printf("Execution time > %ds \n", (int)(stop - start));

    exit(EXIT_SUCCESS);
}
