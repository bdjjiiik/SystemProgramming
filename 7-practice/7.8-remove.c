#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <unistd.h>

#define FATAL(msg)    \
    { perror(msg), exit(EXIT_FAILURE); }

int choise(const char *msg) {
    char ch;

    printf("%s (y)\n> ", msg);
    do {
        ch = getchar();
    } while (!isprint(ch));
    return ch == 'y';
}

extern int alphasort();

int comparator(const struct direct *dir) {
    return strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..");
    ;
}

int is_dir(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int main(int argc, char *argv[]) {
    const char *pathname = argc < 2 ? "." : argv[1];

    if (chdir(pathname))
        FATAL("chdir failed: ");

    struct direct **files;
    int count;
    char *ptr = rindex(argv[0], '/');
    ++ptr;

    printf("Current Directory > %s\n", pathname);
    count = scandir(pathname, &files, comparator, alphasort);

    int allRemove = choise("You want to remove all files?");

    if (count) {
        if (allRemove) {
            printf("Deleted files\n");
        }

        for (int i = 0; i < count; ++i) {
            if (is_dir(files[i]->d_name))
                continue;

            if (strcmp(ptr, files[i]->d_name) == 0)
                continue;

            printf("%s\n", files[i]->d_name);
            if (allRemove || choise("You want to delete it?"))
                remove(files[i]->d_name);
        }

    } else {
        printf("No files in current directory\n");
    }

    exit(EXIT_SUCCESS);
}