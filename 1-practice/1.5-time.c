#include <stdio.h>
#include <stdlib.h>

#define SEC_PER_MIN 60
#define MIN_PER_HOUR 60

int main(void) {
    int seconds = -1;

    printf("Enter seconds > ");
    scanf("%d", &seconds);

    if (seconds < 0) {
        fprintf(stderr, "Seconds cannot be less than zero\n");
        exit(EXIT_FAILURE);
    }

    printf("Output        > ");
    int hours = 0, minutes = 0;
    minutes = seconds / SEC_PER_MIN;
    seconds %= SEC_PER_MIN;
    hours = minutes / MIN_PER_HOUR;
    minutes %= MIN_PER_HOUR;

    if (hours > 0)
        printf("%d hour ", hours);
    if (minutes > 0)
        printf("%d minute ", minutes);

    printf("%d second ", seconds);
    printf("\n");

    exit(EXIT_SUCCESS);
}