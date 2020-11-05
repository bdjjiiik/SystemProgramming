#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/dir.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define FATAL(msg)                                                                                 \
    { perror(msg), exit(EXIT_FAILURE); }

#define MAX_STR_LENGTH 256

extern int alphasort();

int comparator(const struct direct *dir) {
    return strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..");
    ;
}

void date_format(time_t *t, char str[]) {
    struct tm time = *localtime(t);
    strftime(str, MAX_STR_LENGTH, "%b %e %R", &time);
}

int get_filetype(int mode) {
    return  S_ISREG(mode) ? '-' :
            S_ISDIR(mode) ? 'd' :
            S_ISBLK(mode) ? 'b' :
            S_ISCHR(mode) ? 'c' :
           S_ISFIFO(mode) ? 'p' :
            S_ISLNK(mode) ? 'l' : 
           S_ISSOCK(mode) ? 's' : '?';
}

void get_perms(int mode, char perms[]) {
    const char *rwx[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};

    perms[0] = get_filetype(mode);
    strcpy(&perms[1], rwx[(mode >> 6) & 7]);
    strcpy(&perms[4], rwx[(mode >> 3) & 7]);
    strcpy(&perms[7], rwx[(mode & 7)]);
    if (mode & S_ISUID)
        perms[3] = (mode & S_IXUSR) ? 's' : 'S';
    if (mode & S_ISGID)
        perms[6] = (mode & S_IXGRP) ? 's' : 'l';
    if (mode & S_ISVTX)
        perms[9] = (mode & S_IXOTH) ? 't' : 'T';

    perms[10] = '\0';
}

int main(int argc, char *argv[]) {
    const char *pathname = argc < 2 ? "." : argv[1];

    if (chdir(pathname))
        FATAL("chdir failed: ");

    struct direct **files;
    int count;
    count = scandir(pathname, &files, comparator, alphasort);

    struct stat buf;
    struct passwd pass;
    struct group group;
    char date[MAX_STR_LENGTH];
    char perms[11];

    if (count) {
        for (int i = 0; i < count; ++i) {
            stat(files[i]->d_name, &buf);
            pass = *getpwuid(buf.st_uid);
            group = *getgrgid(buf.st_gid);

            date_format(&buf.st_mtime, date);
            get_perms(buf.st_mode, perms);

            printf("%s  %ld %s %s  %6ld  %s %s\n", perms, buf.st_nlink, pass.pw_name, group.gr_name,
                   buf.st_size, date, files[i]->d_name);
        }

    } else {
        printf("No files in current directory\n");
    }

    exit(EXIT_SUCCESS);
}