#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, 
            "Usage: %s {-a|-r}\n"
            " -a : display all uname info\n"
            " -r : display only kernel version\n"
            , argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if (execlp("uname", argv[1], (char *)0) == -1)
        perror("execl failed\n");
    
    printf("This should never get executed!\n");
    exit(EXIT_SUCCESS);
}
