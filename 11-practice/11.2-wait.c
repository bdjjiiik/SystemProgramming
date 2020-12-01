#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void print_child_status(int param, pid_t pid) {
    printf("Child %d PID end\tExit code %d\n", pid, WEXITSTATUS(param));
}

void create_child(int sleep_time) {
    pid_t pid;
    switch (pid = fork()) {
    case -1:
        perror("fork failed: ");
        exit(EXIT_FAILURE);
    case 0:
        printf("Child %d PID sleeping\n", getpid());
        sleep(sleep_time);
        exit(EXIT_SUCCESS);
    default:;
    }
}

int main(void) {
    int param = 0;
    pid_t pid;

    create_child(2);
    create_child(8);

    while ((pid = wait(&param)) != -1) {
        print_child_status(param, pid);
    }

    exit(EXIT_SUCCESS);
}