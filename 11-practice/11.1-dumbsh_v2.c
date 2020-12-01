#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define CMD_MAXLEN 128
#define SAFE_FREE(ptr)         \
    {                          \
        if ((ptr) != NULL)     \
            free((void *)ptr); \
        (ptr) = NULL;          \
    }

int IS_ERROR = 0;
#define SET_ERROR  \
    IS_ERROR = 1;  \
    goto _end

static int gVerbose = 0;
const char *PromptStr = ">> ";

static char *getcmd(char *cmdstr) {
    printf("%s", PromptStr);
    fflush(stdout);

    if (!fgets(cmdstr, CMD_MAXLEN - 1, stdin))
        return NULL;
    cmdstr[strlen(cmdstr) - 1] = '\0';

    return cmdstr;
}

int tokenize(char *str, char del, char ***output) {
    if ((*output) != NULL)
        return -1;

    int len = strlen(str);

    int ntokens = 1;
    for (int i = 0; i < len; i += 1) {
        if (str[i] == del) {
            str[i] = '\0';
            ntokens += 1;
        }
    }

    (*output) = malloc(sizeof(char *) * (ntokens + 1));
    if (*output == NULL) {
        perror("malloc failed!\n");
        return -1;
    }

    char **cur_token = *output;
    *cur_token = str;
    cur_token[ntokens] = NULL;

    for (int i = 0; i < len; i += 1) {
        if (str[i] == '\0') {
            cur_token++;
            *cur_token = &(str[i + 1]);
        }
    }

    return ntokens;
}

static void run_dumbsh(void) {
    pid_t ret;
    char *cmd;
    char **param = NULL;

    cmd = calloc(CMD_MAXLEN, sizeof(char));
    if (!cmd)
        perror("calloc failed!\n");

    while (1) {
        if (!getcmd(cmd)) {
            perror("getcmd(): EOF or failed\n");
            SET_ERROR;
        }

        /* Stopping condition */
        if (!strncmp(cmd, "quit", 4))
            break;

        /* user pressed [Enter] */
        if (cmd[0] == 0)
            continue;

        SAFE_FREE(param);
        if (tokenize(cmd, ' ', &param) == -1) {
            SET_ERROR;
        }

        switch ((ret = fork())) {
        case -1:
            perror("fork failed, aborting!\n");
            SET_ERROR;
        case 0: /* Child */
            if (execvp(*param, param) == -1) {
                perror("child: execv failed\n");
                SET_ERROR;
            }

            exit(EXIT_FAILURE);
        default: /* Parent */
            if (wait(0) < 0)
                perror("wait failed, aborting..\n");
        } // switch
    }     // while(1)

_end:
    SAFE_FREE(cmd);
    SAFE_FREE(param);

    if (IS_ERROR)
        exit(EXIT_FAILURE);
}

static inline void usage(char *name) {
    printf("Usage: %s [-v]|[--help]\n"
           " -v : verbose mode\n"
           " --help : display this help screen.\n",
           name);
}

int main(int argc, char **argv) {
    if (argc >= 2) {
        if (!strncmp(argv[1], "--help", 6)) {
            usage(argv[0]);
            exit(EXIT_SUCCESS);
        }
        if (!strncmp(argv[1], "-v", 2))
            gVerbose = 1;
    }

    run_dumbsh();
    exit(EXIT_SUCCESS);
}