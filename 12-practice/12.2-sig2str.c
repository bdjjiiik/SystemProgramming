#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SIG2STR_MAX
#define SIG2STR_MAX 8
#endif

#define SIGNAME(name)  \
    { SIG##name, #name }

static struct signame {
    int num;
    char const name[SIG2STR_MAX];
} signame_table[] = {SIGNAME(HUP),  SIGNAME(INT), SIGNAME(QUIT), SIGNAME(ILL),  SIGNAME(TRAP),
                     SIGNAME(ABRT), SIGNAME(FPE), SIGNAME(KILL), SIGNAME(SEGV), {0, "EXIT"}};

int sig2str(int signum, char *signame) {
    size_t signame_table_len = (sizeof signame_table / sizeof signame_table[0]);

    for (size_t i = 0; i < signame_table_len; i++) {
        if (signame_table[i].num == signum) {
            strcpy(signame, signame_table[i].name);
            return 0;
        }
    }

    int rtmin = SIGRTMIN;
    int rtmax = SIGRTMAX;

    if (!(rtmin <= signum && signum <= rtmax))
        return -1;

    if (signum <= rtmin + (rtmax - rtmin) / 2) {
        int delta = signum - rtmin;
        sprintf(signame, delta ? "RTMIN+%d" : "RTMIN", delta);
    } else {
        int delta = rtmax - signum;
        sprintf(signame, delta ? "RTMAX-%d" : "RTMAX", delta);
    }

    return 0;
}

int main(void) {
    char buffer[SIG2STR_MAX];

    sig2str(0, buffer);
    printf("%s = %d\n", buffer, 0);

    sig2str(9, buffer);
    printf("%s = %d\n", buffer, 9);

    sig2str(63, buffer);
    printf("%s = %d\n", buffer, 63);

    exit(EXIT_SUCCESS);
}
