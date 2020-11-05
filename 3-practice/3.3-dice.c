#define _GNU_SOURCE
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define FATAL(msg) \
    { perror(msg), exit(EXIT_FAILURE); }

int g_fd;

void cleanup() {
    close(g_fd);
    exit(EXIT_SUCCESS);
}

static void siggy(int signum) {
    switch (signum) {
    case SIGXFSZ:
        printf("File size exceeds soft limit!\n"
               "Stop generation\n");
        cleanup();
    default:
        return;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3)
        FATAL("No file-name or rolls count provided\n");

    struct sigaction act;

    memset(&act, 0, sizeof(act));
    act.sa_handler = siggy;

    if (sigaction(SIGXFSZ, &act, 0) < 0)
        FATAL("sigaction failed! ");

    time_t t;
    srand(time(&t));

    g_fd = open(argv[1], O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
    if (g_fd < 0)
        FATAL("open failed! ");

    for (int i = 0, rools = atoi(argv[2]); i < rools; i += 1) {
        int roll = (rand() % 6 + 1);
        write(g_fd, &roll, sizeof(int));
    }

    cleanup();
}
