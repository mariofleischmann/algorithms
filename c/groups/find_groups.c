#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "group.h"

#define N 6

struct node {
    group_t *data;
    struct node *next;
};

struct node *node_create(group_t *data)
{
    struct node *n = malloc(sizeof(struct node));
    n->data = data;
    n->next = NULL;
    return n;
}

bool is_unique(group_t *g, struct node *head)
{
    while (head) {
        if (group_equals(head->data, g)) {
            return false;
        }

        head = head->next;
    }

    return true;
}

void list_append(struct node **head, struct node *n)
{
    while ((*head)->next != NULL) {
        head = &((*head)->next); 
    }

    (*head)->next = n;
}

int main(void)
{
    struct node *head = node_create(group_create(1)); // trivial group

    for (int i = 2; i <= N; i++) {
        group_t *g = group_create(i);
        while(group_next(g)) {
            if (is_unique(g, head)) {
                struct node *new = node_create(group_copy(g));
                list_append(&head, new);
            }
        }

        group_free(g);
    }

    while (head) {
        group_print(head->data);
        seq[head->data->n-1]++;
        printf("\n");
       
        if (!group_commutative(head->data)) {
            printf("^^^^^^^^^^^^^^^\n");
            printf("Non-Commutative\n\n");
        } 

        // cleanup
        struct node *temp = head;
        head = head->next;
        group_free(temp->data);
        free(temp);
    }
}
