#include <stdio.h>
#include <stdlib.h>

#define FAILURE 1
#define SUCCESS 0

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int id;
    int age;
    Date date;
    char address[32];
} Person;

int add_person(Person *person) {
    FILE *file = fopen("data/persons.dat", "a+b");

    if (!file) {
        fprintf(stderr, "Error to open file");
        return FAILURE;
    }

    fwrite(person, sizeof(Person), 1, file);
    fclose(file);

    return SUCCESS;
}

int get_persons() {
    FILE *file = fopen("data/persons.dat", "r+b");

    if (!file) {
        fprintf(stderr, "Error to open file");
        return FAILURE;
    }

    int count = 0;
    Person person;
    while (fread(&person, sizeof(Person), 1, file)) {
        printf("-- Person --------------\n");
        printf("Id      : %d\n", person.id);
        printf("Age     : %d\n", person.age);
        printf("Date    : %d.%d.%d\n", person.date.day, person.date.month, person.date.year);
        printf("Address : %s\n", person.address);

        count += 1;
    }

    if (count) {
        printf("-- Total persons = %d --\n", count);
    } else {
        printf("Database empty\n");
    }

    fclose(file);
    return SUCCESS;
}

int main(void) {
    Person a = {1, 20, {12, 5, 2000}, "Kyiv"};
    Person b = {2, 44, {5, 2, 1976}, "Odessa"};

    add_person(&a);
    add_person(&b);

    printf("-- All persons ---------\n");
    get_persons();

    exit(EXIT_SUCCESS);
}
