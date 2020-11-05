#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(S) #S,

#define FOREACH_DAY(DAY)    \
    DAY(Monday)             \
    DAY(Tuesday)            \
    DAY(Wednesday)          \
    DAY(Thursday)           \
    DAY(Friday)             \
    DAY(Saturday)           \
    DAY(Sunday)             \
    DAY(D_SIZE)

enum DAY_ENUM { FOREACH_DAY(GENERATE_ENUM) };
static const char *DAY_STRING[] = {FOREACH_DAY(GENERATE_STRING)};

#define FOREACH_MONTH(MONTH)    \
    MONTH(January)              \
    MONTH(February)             \
    MONTH(March)                \
    MONTH(April)                \
    MONTH(May)                  \
    MONTH(June)                 \
    MONTH(July)                 \
    MONTH(August)               \
    MONTH(September)            \
    MONTH(October)              \
    MONTH(November)             \
    MONTH(December)             \
    MONTH(M_SIZE)

enum MONTH_ENUM { FOREACH_MONTH(GENERATE_ENUM) };
static const char *MONTH_STRING[] = {FOREACH_MONTH(GENERATE_STRING)};

static const char DAYS_IN_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

typedef struct {
    int day;
    enum DAY_ENUM days_of_week;
    enum MONTH_ENUM month;
} Date;

#include <stdio.h>
#include <stdlib.h>

void print_date(Date date) {
    printf("%10s, %2d %10s\n", DAY_STRING[date.days_of_week], date.day, MONTH_STRING[date.month]);
}

Date next_date(Date date) {
    Date next;

    next.days_of_week = (date.days_of_week + 1) % D_SIZE;
    if (date.day + 1 > DAYS_IN_MONTH[date.month]) {
        next.day = 1;
        next.month = (date.month + 1) % M_SIZE;
    } else {
        next.day = date.day + 1;
        next.month = date.month;
    }

    return next;
}

int is_date_valid(Date date) {
    return DAYS_IN_MONTH[date.month] >= date.day;
}

int main(void) {
    Date current = {28, Sunday, December};

    if (is_date_valid(current)) {
        Date next = next_date(current);
        printf("Current date > ");
        print_date(current);
        printf("Next date    > ");
        print_date(next);
    } else {
        printf("Date invalid\n");
    }

    exit(EXIT_SUCCESS);
}
