/**
 * find_groups.c
 * Find all groups until a specific order.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cayley_table.h"

#define N 6

struct node {
    cayley_table_t *data;
    struct node *next;
};

static struct node *node_create(cayley_table_t *data)
{
    struct node *n = malloc(sizeof(struct node));
    n->data = data;
    n->next = NULL;
    return n;
}

static void node_free(struct node *n) {
    table_free(n->data);
    free(n);
}

static bool list_is_unique(struct node *head, cayley_table_t *t)
{
    while (head) {
        if (tables_are_isomorph(head->data, t)) {
            return false;
        }

        head = head->next;
    }

    return true;
}

static void list_append(struct node **head, struct node *n)
{
    while ((*head)->next != NULL) {
        head = &((*head)->next); 
    }

    (*head)->next = n;
}

int main(void)
{
    struct node *head = node_create(table_create(1)); // trivial group

    for (int i = 2; i <= N; i++) {
        cayley_table_t *t = table_create(i);
        while(table_next_group(t)) {
            if (list_is_unique(head, t)) {
                struct node *new = node_create(table_copy(t));
                list_append(&head, new);
            }
        }

        table_free(t);
    }

    while (head) {
        table_print(head->data);
        printf("\n");

        if (!table_is_commutative(head->data)) {
            printf("^^^^^^^^^^^^^^^\n");
            printf("Non-Commutative\n\n");
        } 

        struct node *temp = head;
        head = head->next;
        node_free(temp);
    }
}
