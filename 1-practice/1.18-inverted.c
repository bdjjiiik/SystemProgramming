#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define UNSIGNED_CHAR_MAX 255
#define UNSIGNED_CHAR_MIN 0

void dec8_to_bin_inverted(unsigned char number) {
    printf("Bin inverted > ");
    for (unsigned char i = 128; i; i >>= 1)
        printf("%c", number & i ? '0' : '1');

    printf("\n");
}

int main(int argc, char *argv[]) {
    int arg = 0;
    opterr = 0; // remove getopt() output`s error
    long val = -1;
    while ((arg = getopt(argc, argv, "d:b:")) != -1) {
#define PRINT_VAL(TYPE) printf("Your value   > %-10s (%s)\n", optarg, (TYPE))
#define SET_VAL(RADIX) val = strtol(optarg, &optarg, (RADIX));
        switch (arg) {
        case 'd':
            PRINT_VAL("dec");
            SET_VAL(10);
            break;
        case 'b':
            PRINT_VAL("bin");
            SET_VAL(2);
            break;
        };
#undef PRINT_VAL
#undef SET_VAL
    };

    if (val < UNSIGNED_CHAR_MIN || val > UNSIGNED_CHAR_MAX) {
        fprintf(stderr, "Value overflow or did not provide\n");
        exit(EXIT_FAILURE);
    }

    dec8_to_bin_inverted((unsigned char)val);

    exit(EXIT_SUCCESS);
}