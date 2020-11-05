#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum mode { DESC, INSC } Mode;

int desc_comp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int insc_comp(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main(int argc, char *argv[]) {
    int arg = 0;

    Mode mode = DESC;
    while ((arg = getopt(argc, argv, "r")) != -1) {
        switch (arg) {
        case 'r':
            mode = INSC;
            break;
        };
    };

    int arr[] = {34, 12, 21, 212, 1, 8, 1};
    size_t size = sizeof(arr) / sizeof(int);

    printf("---------- Before sort ----------\n");
    for (size_t i = 0; i < size; i += 1)
        printf("%d  ", arr[i]);
    printf("\n");

    qsort(arr, size, sizeof(int), (mode == INSC ? insc_comp : desc_comp));

    printf("---------- After sort -----------\n");
    for (size_t i = 0; i < size; i += 1)
        printf("%d  ", arr[i]);
    printf("\n");

    exit(EXIT_SUCCESS);
}