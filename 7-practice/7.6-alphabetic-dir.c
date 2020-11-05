#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <unistd.h>

#define FATAL(msg)    \
    { perror(msg), exit(EXIT_FAILURE); }

extern int alphasort();

int comparator(const struct direct *dir) {
    return strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..");
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

    printf("Current Directory > %s\n", pathname);
    count = scandir(pathname, &files, comparator, alphasort);

    if (count) {
        int dir_count = 0;
        for (int i = 0; i < count; ++i) {
            if (is_dir(files[i]->d_name)) {
                printf(" %s\n", files[i]->d_name);
                dir_count += 1;
            }
        }

        printf("Number of directories > %d\n", dir_count);
    } else {
        printf("No files in current directory\n");
    }

    exit(EXIT_SUCCESS);
}
