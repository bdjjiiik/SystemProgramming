#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>

#define PADDING 2

#define FATAL(msg)    \
    { perror(msg), exit(EXIT_FAILURE); }

#define WARN(msg)     \
    { perror(msg); }

extern int alphasort();

int comparator(const struct direct *dir) {
    return strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..");
}

int is_dir(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

void print_dir(const char *path, int level) {
    char old_path[MAXPATHLEN];
    getcwd(old_path, MAXPATHLEN);

    if (chdir(path))
        FATAL("chdir failed: ");

    struct direct **files;
    int count;

    count = scandir(".", &files, comparator, alphasort);
    if (count == -1) {
        WARN("scandir failed: ");
    }

    if (count) {
        for (int i = 0; i < count; ++i) {
            printf("%*s%s\n", level, "", files[i]->d_name);
            if (is_dir(files[i]->d_name)) {
                print_dir(files[i]->d_name, level + PADDING);
            }
        }
    } else {
        printf("%*s\n", level, "No files in current directory");
    }

    chdir(old_path);
}

int main(int argc, char **argv) {
    const char *pathname = argc < 2 ? "." : argv[1];
    print_dir(pathname, 0);

    exit(EXIT_SUCCESS);
}
