#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static volatile sig_atomic_t gFlag = 0;

static void signal_handler(int signo) {
    gFlag = 1;
    signo = signo;
}

void foo() {
    sleep(5); // do some work
}

void bar(int sec_to_work) {
    for (int i = 0; i < sec_to_work; i += 1) {
        printf("Flag = %d\n", gFlag);
        sleep(1);
    }
}

// Use to share data between process
#define FILE_NAME "DATA"
int read_pid() {
    FILE *file = fopen(FILE_NAME, "r+");
    int temp;
    fscanf(file, "%d", &temp);
    fclose(file);
    return temp;
};
void write_pid(int i) {
    FILE *file = fopen(FILE_NAME, "w+");
    fprintf(file, "%d", i);
    fclose(file);
};

void process_A() {
    pid_t pid;
    switch (pid = fork()) {
    case -1:
        perror("fork failed: ");
        exit(EXIT_FAILURE);
    case 0: {
        foo();

        if (kill(read_pid(), SIGUSR1) < 0)
            exit(EXIT_FAILURE);

        exit(EXIT_SUCCESS);
    }
    default:;
    }
}

void process_B() {
    pid_t pid;
    switch (pid = fork()) {
    case -1:
        perror("fork failed: ");
        exit(EXIT_FAILURE);
    case 0: {
        write_pid(getpid());
        struct sigaction sigact;
        memset(&sigact, 0, sizeof(sigact));
        sigact.sa_handler = signal_handler;

        if (sigaction(SIGUSR1, &sigact, 0) < 0)
            exit(EXIT_FAILURE);

        bar(10);
        exit(EXIT_SUCCESS);
    }
    default:;
    }
}

int main(void) {
    int param = 0;
    pid_t pid;

    process_B();
    process_A();

    while ((pid = wait(&param)) != -1) {
    }

    exit(EXIT_SUCCESS);
}
