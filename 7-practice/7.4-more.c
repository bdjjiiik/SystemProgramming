#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256
#define LINES_TO_SHOW 3

#define FATAL(msg)    \
    { perror(msg), exit(EXIT_FAILURE); }

int main(int argc, char *argv[]) {
    if (argc < 2)
        printf("Usage %s <file>\n", argv[0]), exit(EXIT_FAILURE);

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
        FATAL("fopen failed: ");

    char ch, line[MAX_LINE_LENGTH];
    int count = 0;

    while (!feof(fp)) {
        count += 1;
        count %= LINES_TO_SHOW;

        if (count == 0) {
            printf("More (q to quit)\n");
            if ((ch = getchar()) == 'q')
                goto exit;
        }

        if (fgets(line, MAX_LINE_LENGTH, fp))
            printf("%s", line);
    }

exit:
    fclose(fp);
    exit(EXIT_SUCCESS);
}