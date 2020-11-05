#include <stdio.h>

#define swap(t, x, y)                                                                              \
    {                                                                                              \
        t(tmp) = (x);                                                                              \
        (x) = (y);                                                                                 \
        (y) = (tmp);                                                                               \
    }

int main(void) {
    int x_i = 0;
    int y_i = 3;

    printf("-- int -------------------\n");

    printf("Before > x_i = %d , y_i = %d\n", x_i, y_i);
    swap(int, x_i, y_i);
    printf("After  > x_i = %d , y_i = %d\n", x_i, y_i);

    printf("-- char ------------------\n");

    char x_c = 'x';
    char y_c = 'y';

    printf("Before > x_c = %c , y_c = %c\n", x_c, y_c);
    swap(char, x_c, y_c);
    printf("After  > x_c = %c , y_c = %c\n", x_c, y_c);

    return 0;
}
