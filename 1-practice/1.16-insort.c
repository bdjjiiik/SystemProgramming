#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *insort(void *base, size_t size, size_t size_el,
             int (*compare_fn)(const void *, const void *)) {
    if (!base || !size || !size_el || !compare_fn)
        return NULL;

    int i = 0, j = 0;
    void *temp;
    if (!(temp = calloc(1, size_el)))
        return NULL;
    void *key;
    if (!(key = calloc(1, size_el)))
        return NULL;

#define _AT(arr, p, s) (((char *)arr) + ((p) * (s)))
    for (i = 1; (size_t)i < size; i += 1) {
        memcpy(key, _AT(base, i, size_el), size_el);
        j = i - 1;
        while (j >= 0 && (compare_fn(_AT(base, j, size_el), key) > -1)) {
            memcpy(_AT(base, j + 1, size_el), _AT(base, j, size_el), size_el);
            j -= 1;
        }
        memcpy(_AT(base, j + 1, size_el), key, size_el);
    }
#undef _AT

    free(temp);
    free(key);
    return base;
}

typedef struct {
    char keyword[10];
    int other_data;
} Record;

size_t read_record(Record **records) {
    FILE *file = fopen("data/records.dat", "r+");

    if (!file) {
        fprintf(stderr, "Error to open file");
        exit(EXIT_FAILURE);
    }

    int size = 0;
    fread(&size, sizeof(int), 1, file);

    if (size > 0) {
        if (!*records)
            free(*records);

        if (!(*records = (Record *)malloc(size * sizeof(Record)))) {
            fprintf(stderr, "Error to allocate memory");
            exit(EXIT_FAILURE);
        }

        fread(*records, sizeof(Record), size, file);
    }

    fclose(file);

    return size;
}

int comparator(const void *lhs, const void *rhs) {
    return strcmp(((const Record *)lhs)->keyword, ((const Record *)rhs)->keyword);
}

int main(void) {
    Record *records = NULL;
    size_t size = read_record(&records);

    printf("---------- Before sort ----------\n");
    for (size_t i = 0; i < size; i += 1)
        printf("keyword : %8s; data : %5d;\n", records[i].keyword, records[i].other_data);

    insort(records, size, sizeof(Record), comparator);

    printf("---------- After sort -----------\n");
    for (size_t i = 0; i < size; i += 1)
        printf("keyword : %8s; data : %5d;\n", records[i].keyword, records[i].other_data);

    free(records);
    exit(EXIT_SUCCESS);
}
