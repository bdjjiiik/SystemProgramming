#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <unistd.h>

#define FATAL(msg)    \
    { perror(msg), exit(EXIT_FAILURE); }

extern int alphasort();

int choise(const char *msg) {
    char ch;

    printf("%s (y)\n> ", msg);
    do {
        ch = getchar();
    } while (!isprint(ch));
    return ch == 'y';
}

int comparator(const struct direct *dir) {
    char *ptr = rindex(dir->d_name, '.');

    return ptr && strcmp(ptr, ".c") == 0;
}

int main(int argc, char *argv[]) {
    const char *pathname = argc < 2 ? "." : argv[1];

    if (chdir(pathname))
        FATAL("chdir failed: ");

    struct direct **files;
    int count;

    printf("Current Directory > %s\n", pathname);
    count = scandir(pathname, &files, comparator, alphasort);

    if (count) {
        for (int i = 0; i < count; ++i) {
            printf("%s\n", files[i]->d_name);

            if (choise("You want give read permission to others?")) {
                chmod(files[i]->d_name, 644);
            }
        }

    } else {
        printf("No files in current directory\n");
    }

    exit(EXIT_SUCCESS);
}
