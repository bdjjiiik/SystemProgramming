#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FATAL(msg)                                                                                 \
    { perror(msg), exit(EXIT_FAILURE); }

int main(void) {
    int fd = open("bytes", O_RDONLY);
    if (fd < 0)
        FATAL("open to read failed! ");

    int buffer = -1;
    lseek(fd, 3, SEEK_SET);
    read(fd, &buffer, 4);

    printf("%d\n", buffer);

    close(fd);

    exit(EXIT_SUCCESS);
}
