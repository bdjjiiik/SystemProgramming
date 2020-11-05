#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define MAX_LINE_LENGTH 256

typedef struct node_t {
    char *string;
    struct node_t *next;
} node_t;

typedef struct dequeue_t {
    node_t *head;
    node_t *tail;
    int size;
} dequeue_t;

dequeue_t *init() {
    dequeue_t *dequeue = (dequeue_t *)malloc(sizeof(dequeue_t));
    if (!dequeue)
        return NULL;

    dequeue->size = 0;
    dequeue->head = NULL;
    dequeue->tail = NULL;

    return dequeue;
}

node_t *create_node(char *str) {
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->string = strdup(str);
    return node;
}

void add(dequeue_t *dequeue, node_t *node) {
    if (!dequeue || !node)
        return;

    node->next = NULL;
    if (dequeue->size == 0) {
        dequeue->head = dequeue->tail = node;
    } else {
        dequeue->tail->next = node;
        dequeue->tail = node;
    }

    ++dequeue->size;
    return;
}

int is_empty(dequeue_t *dequeue) {
    return dequeue && dequeue->size == 0;
}

node_t *pop(dequeue_t *dequeue) {
    node_t *node;
    if (is_empty(dequeue))
        return NULL;

    node = dequeue->head;
    dequeue->head = dequeue->head->next;
    --dequeue->size;

    return node;
}

void delete_node(node_t* node) {
    free(node->string);
    free(node);
}

void clear(dequeue_t *dequeue) {
    while (!is_empty(dequeue)) {
        node_t *tmp = pop(dequeue);
        free(tmp);
    }
    free(dequeue);
}

int main(int argc, char *argv[]) {
    opterr = 0; // remove getopt() output`s error
    int arg = 0;
    int n = 5;
    while ((arg = getopt(argc, argv, "n:")) != -1) {
        switch (arg) {
        case 'n':
            n = atoi(optarg);
            break;
        };
    };

    if (n < 0) {
        fprintf(stderr, "Lines cannot be less than zero\n");
        exit(EXIT_FAILURE);
    }

    dequeue_t *dq = init();

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, stdin)) {
        if (dq->size >= n) {
            delete_node(pop(dq));
        }

        add(dq, create_node(&buffer[0]));
    }

    printf("-- Last %d lines -------------\n", n);
    while (!is_empty(dq)) {
        node_t *tmp = pop(dq);
        printf("%s", tmp->string);
        delete_node(tmp);
    }
    printf("\n");

    clear(dq);
    exit(EXIT_SUCCESS);
}
