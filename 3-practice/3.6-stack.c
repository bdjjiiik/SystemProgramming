#include <stdio.h>

void recursion() {
    static int level = 0;

    int local_arr[512] = {0};

    level += 1;
    printf("Recursion level > %d\tLocal arr address > %p\n", level, local_arr);

    recursion();
}

int main(void) {
    recursion();
    return 0;
}
