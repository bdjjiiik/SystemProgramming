#define _GNU_SOURCE
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FATAL(msg)                                                                                 \
    { perror(msg), exit(EXIT_FAILURE); }

#define CHUNK_SIZE 512

int g_fd_write, g_fd_read;

void cleanup() {
    close(g_fd_write);
    close(g_fd_read);

    exit(EXIT_SUCCESS);
}

static void siggy(int signum) {
    switch (signum) {
    case SIGXFSZ:
        printf("File size exceeds soft limit!\n"
               "Copy stoped\n");
        cleanup();
    default:
        return;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Filenames does not provided\n"
               "Usage %s <destination> <source>\n",
               argv[0]);

        exit(EXIT_FAILURE);
    }

    struct sigaction act;

    memset(&act, 0, sizeof(act));
    act.sa_handler = siggy;

    if (sigaction(SIGXFSZ, &act, 0) < 0)
        FATAL("sigaction failed! ");

    char buffer[CHUNK_SIZE];

    g_fd_write = open(argv[1], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (g_fd_write < 0)
        FATAL("open to write failed! ");

    g_fd_read = open(argv[2], O_RDONLY);
    if (g_fd_read < 0)
        FATAL("open to read failed! ");

    ssize_t count = 0;
    while ((count = read(g_fd_read, buffer, CHUNK_SIZE)) > 0)
        write(g_fd_write, buffer, count);

    printf("Copy succesfully!\n");
    cleanup();
}
