#ifndef JT_HANDLE_H
#define JT_HANDLE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  int *arr;
  int *pos;
  int *dir;
  size_t n;
} jt_handle;

jt_handle *jt_create(size_t n);
void jt_free(jt_handle *h);
void jt_print(jt_handle *h);
void jt_init(jt_handle *h);
bool jt_perm(jt_handle *h);
bool jt_set(jt_handle *h, jt_handle *val);

#endif
