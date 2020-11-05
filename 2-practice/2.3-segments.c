#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char etext, edata, end;
int g_data = 0;

void stack_grow() {
    static int count = 0;

    int *local_arr = (int *)alloca(1024 * sizeof(int));

    if (++count == 5)
        return;

    printf("Stack level - %d:\nLocal array address  > %p\n", count, local_arr);

    stack_grow();
}

int main(void) {
    {
        printf("--------------- Text ----------------\n");
        printf("Text segment address > 0x%lx\n", (unsigned long)&etext);
        printf("Main func address    > %p\n", main);
        printf("-------------------------------------\n");
    }

    {
        printf("--------------- Data ----------------\n");
        printf("Data segment address > 0x%lx\n", (unsigned long)&edata);
        printf("g_data var address   > %p\n", &g_data);
        printf("-------------------------------------\n");
    }

    {
        int *ptr;
        printf("--------------- Heap ----------------\n");
        printf("Heap segment address > 0x%lx\n", (unsigned long)&end);
        ptr = (int *)calloc(1, sizeof(int));
        if (ptr) {
            printf("Heap array address   > %p\n", ptr);
            free(ptr);
        }
        printf("-------------------------------------\n");
    }

    {
        printf("--------------- Stack ---------------\n");
        stack_grow();
        printf("-------------------------------------\n");
    }


    while(1) {};
    return 0;
}
