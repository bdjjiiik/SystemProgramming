#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int radix = -1;
    char str[256];

    printf("Enter radix       > ");
    scanf("%d", &radix);

    if (radix < 2 || radix > 10) {
        fprintf(stderr, "Radix can be in range [2, 10]\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter your string > ");
    scanf("%256s", str);

    char *ptr = str;
    long val = -1;
    while (*ptr) {
        if (isdigit(*ptr) && *ptr - '0' < radix) {
            val = strtol(ptr, &ptr, radix);
        } else {
            ++ptr;
        }
    }

    if (val != -1) {
        printf("Output            > %ld\n", val);
    } else {
        printf("No number");
    }

    exit(EXIT_SUCCESS);
}
