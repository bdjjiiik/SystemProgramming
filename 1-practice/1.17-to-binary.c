#include <stdio.h>
#include <stdlib.h>

#define UNSIGNED_CHAR_MAX 255

void dec8_to_bin(unsigned char number) {
    printf("Dec > %u\n", number);
    printf("Bin > ");
    for (unsigned char i = (UNSIGNED_CHAR_MAX + 1) / 2; i; i >>= 1)
        printf("%c", number & i ? '1' : '0');
    printf("\n");
}

int main(void) {
    dec8_to_bin(56);

    exit(EXIT_SUCCESS);
}
