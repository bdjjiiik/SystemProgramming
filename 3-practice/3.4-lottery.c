#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define FATAL(msg)      \
    { perror(msg), exit(EXIT_FAILURE); }

int g_generate_number = 0;

void summary() {
    printf("In genearl generates %d numbers\n", g_generate_number);
}

static void siggy(int signum) {
    switch (signum) {
    case SIGXCPU:
        printf("CPU is limited!\n"
               "Stop generation\n");

        summary();
        exit(EXIT_FAILURE);
    default:
        return;
    }
}

void generate(int count, int a, int b) {
    printf("Generate %d number (%d to %d) > \n", count, a, b);
    for (int i = 0; i < count; i += 1) {
        int roll = a + (rand() % b + 1);
        roll = roll;
        // printf("%3d ", roll);

        g_generate_number += 1;
    }
    printf("\n");
}

int main(void) {
    struct sigaction act;

    memset(&act, 0, sizeof(act));
    act.sa_handler = siggy;

    if (sigaction(SIGXCPU, &act, 0) < 0)
        FATAL("sigaction failed! ");

    srand(time(NULL));

    generate(1000000000, 1, 49);
    generate(1000000000, 1, 36);

    summary();
    exit(EXIT_SUCCESS);
}
