#ifndef GROUP_H
#define GROUP_H

#include <stdbool.h>
#include "jt_handle.h"

typedef struct {
    jt_handle **rows;
    // buffer for duplicate checks
    int *temp;
    int ok;
    size_t n;
} group_t;

group_t *group_create(size_t n);
group_t *group_copy(group_t *g);
void group_free(group_t *g);
int group_eval(group_t *g, int a, int b);
bool group_associative(group_t *g);
bool group_commutative(group_t *g);
bool group_equals(group_t *g1, group_t *g2);
void group_print(group_t *g);
bool group_next(group_t *g);
bool is_group(group_t *g);

#endif
