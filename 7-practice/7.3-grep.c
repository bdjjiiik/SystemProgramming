#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

#define FATAL(msg)    \
    { perror(msg), exit(EXIT_FAILURE); }

int main(int argc, char const *argv[]) {
    if (argc < 3)
        printf("Usage %s <pattern> <file>\n", argv[0]), exit(EXIT_FAILURE);

    FILE *fp = fopen(argv[2], "r");
    if (!fp)
        FATAL("fopen failed: ");

    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (!feof(fp)) {
        count += 1;
        if (fgets(line, MAX_LINE_LENGTH, fp)) {
            if (strcasestr(line, argv[1])) {
                printf("%4d %s", count, line);
            }
        }
    }

    fclose(fp);

    exit(EXIT_SUCCESS);
}
