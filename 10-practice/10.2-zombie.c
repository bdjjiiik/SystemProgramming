#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define PRINT_PID(src)  \
    { printf("%-8s pid > %d\n", (src), getpid()); }

int main(void) {
    pid_t p;

    switch (p = fork()) {
    case -1:
        exit(EXIT_FAILURE);
    case 0:
        PRINT_PID("Child");

        exit(EXIT_SUCCESS);
    default:
        PRINT_PID("Parent");

        sleep(5), system("ps -l");
        exit(EXIT_SUCCESS);
    }
}
