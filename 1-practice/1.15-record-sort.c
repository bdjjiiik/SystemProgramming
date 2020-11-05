#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    qsort(records, size, sizeof(Record), comparator);

    printf("---------- After sort -----------\n");
    for (size_t i = 0; i < size; i += 1)
        printf("keyword : %8s; data : %5d;\n", records[i].keyword, records[i].other_data);

    free(records);
    exit(EXIT_SUCCESS);
}
