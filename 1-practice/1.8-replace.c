#include <stdio.h>
#include <string.h>

int replace(char *s) {
    int n = 0;
    if (s) {
        for (size_t i = 0; i < strlen(s); ++i) {
            if (s[i] == ' ') {
                s[i] = '-';
                n += 1;
            }
        }
    }
    return n;
}

int main() {
    char *str = NULL;
    printf("After  > %s\n", str);
    int n = replace(str);
    printf("Before > %s", str);
    printf("\tspaces replaced - %d\n", n);
    return 0;
}
