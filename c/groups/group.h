#ifndef GROUP_H
#define GROUP_H

#include <stdbool.h>
#include "jt_handle.h"

typedef struct {
  jt_handle **rows;
  int *temp;
  int ok;
  size_t n;
} group_t;

group_t *group_create(size_t n);
void group_free(group_t *g);
void group_print(group_t *g);
bool group_next(group_t *g);
bool is_group(group_t *g);

#endif
