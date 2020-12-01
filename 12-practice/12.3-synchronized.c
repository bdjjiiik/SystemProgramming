#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static volatile sig_atomic_t sigflag;

static sigset_t newmask, oldmask, zeromask;
static void sig_usr(int signo) {
    sigflag = 1;
    signo = signo;
}
void TELL_WAIT(void) {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        perror("ошибка вызова функции signal(SIGUSR1)");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        perror("ошибка вызова функции signal(SIGUSR2)");
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        perror("ошибка выполнения операции SIG_BLOCK");
}
void TELL_PARENT(pid_t pid) {
    kill(pid, SIGUSR2);
}
void WAIT_PARENT() {
    while (sigflag == 0)
        sigsuspend(&zeromask);
    sigflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("ошибка выполнения операции SIG_SETMASK");
}
void TELL_CHILD(pid_t pid) {
    kill(pid, SIGUSR1);
}
void WAIT_CHILD() {
    while (sigflag == 0)
        sigsuspend(&zeromask);
    sigflag = 0;
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("ошибка выполнения операции SIG_SETMASK");
}

#define FILE_NAME "DATA"

void inc(char *source) {
    FILE *file = fopen(FILE_NAME, "r+");
    int i = 0;
    if (file == NULL) {
        perror("fopen failed: ");
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%d", &i);
    fseek(file, 0, SEEK_SET);

    i += 1;
    printf("%s increment number, now i = %d\n", source, i);
    fprintf(file, "%d", i);
    fclose(file);
}

void init_file() {
    FILE *file = fopen(FILE_NAME, "w+");
    if (file == NULL) {
        perror("fopen failed: ");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d", 0);
    fclose(file);
}

int main(void) {
    pid_t pid;

    init_file();
    TELL_WAIT();

    switch (pid = fork()) {
    case -1:
        perror("fork failed: ");
        exit(EXIT_FAILURE);
    case 0:
        while (1) {
            WAIT_PARENT();
            inc("child");
            TELL_PARENT(getppid());
        }
        break;
    default:
        while (1) {
            inc("parent");
            TELL_CHILD(pid);
            WAIT_CHILD();
        }
        break;
    }

    exit(EXIT_SUCCESS);
}
