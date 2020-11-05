#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void fill(void *base, size_t size, size_t el_size, void *(*randomizer)()) {
    char *cp = base;
    for (size_t i = 0; i < size; i += 1, cp += el_size) {
        void *val = randomizer();
        memcpy(cp, val, size);
        free(val);
    }
}

int search(int *base, size_t size, int to_search) {
    for (size_t i = 0; i < size; i += 1) {
        if (base[i] == to_search)
            return i;
    }
    return -1;
}

void *randomizer() {
    int *val = (int *)malloc(sizeof(int));
    *val = rand();
    return (void *)val;
}

int main(void) {
    srand(time(NULL));
    size_t size = 5;
    int arr[size];
    fill(arr, size, sizeof(int), randomizer);

    printf("-- Array (size = %zu) --\n", size);
    for (size_t i = 0; i < size; i += 1)
        printf("%d  ", arr[i]);
    printf("\n----------------------\n");

    int to_search = 0;
    printf("Enter number to find > ");
    scanf("%d", &to_search);
    int pos = search(arr, size, to_search);
    if (pos != -1) {
        printf("Number find on pos   > arr[%d] = %d", pos, arr[pos]);
    } else {
        printf("Number din not find");
    }
    printf("\n");

    return 0;
}
