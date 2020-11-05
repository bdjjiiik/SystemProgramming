#include <stdio.h>
#include <stdlib.h>

#define FATAL(msg)    \
    { perror(msg), exit(EXIT_FAILURE); }

int main(void) {
    FILE *fp_r = popen("ls -l", "r");
    FILE *fp_w = popen("more -2", "w");
    if (!fp_r || !fp_w)
        FATAL("popen failed: ");

    char ch;
    do {
        ch = fgetc(fp_r);
        fputc(ch, fp_w);
    } while (ch != EOF);

    if (pclose(fp_r) == -1 || pclose(fp_w) == -1)
        FATAL("pclose failed: ");

    exit(EXIT_SUCCESS);
}
