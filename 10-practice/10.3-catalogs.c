#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define FATAL_MSG(msg) fprintf(stderr, msg), exit(EXIT_FAILURE)

int main(void) {
    { /*    TEST OPENDIR START    */

        DIR *dir = opendir("/");
        if (!dir)
            FATAL_MSG("opendir failed!\n");

        int fd = dirfd(dir);
        if (fd < 0)
            closedir(dir), FATAL_MSG("dirfd failed!\n");

        int flags = fcntl(fd, F_GETFD);
        if (flags < 0)
            closedir(dir), FATAL_MSG("fcntl failed!\n");

        printf("Close-on-exec opendir > %s\n", (flags & FD_CLOEXEC) ? "set" : "unset");

        closedir(dir);

    } /*    TEST OPENDIR END      */

    { /*    TEST OPEN START    */

        int fd = open("/", O_RDONLY);
        if (fd < 0)
            FATAL_MSG("open failed!\n");

        int flags = fcntl(fd, F_GETFD);
        if (flags < 0)
            close(fd), FATAL_MSG("fcntl failed!\n");

        printf("Close-on-exec open    > %s\n", (flags & FD_CLOEXEC) ? "set" : "unset");

        close(fd);

    } /*    TEST OPEN END    */

    exit(EXIT_SUCCESS);
}
