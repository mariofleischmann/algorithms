#include <stdio.h>
#include <stdlib.h>
#include "jt_handle.h"

jt_handle *jt_create(size_t n) {
  jt_handle *h = malloc(sizeof(jt_handle));

  h->arr = malloc(sizeof(int) * n);
  h->pos = malloc(sizeof(int) * n);
  h->dir = malloc(sizeof(int) * n);
  h->n = n;

  jt_init(h);

  return h;
}

void jt_free(jt_handle *h) {
  free(h->arr);
  free(h->pos);
  free(h->dir);
  free(h);
}

void jt_init(jt_handle *h) {
  for (size_t i = 0; i < h->n; i++) {
    h->arr[i] = i;
    h->pos[i] = i;
    h->dir[i] = 1;
  }
}

void jt_print(jt_handle *h) {
  for (size_t i = 0; i < h->n; i++) {
    printf("%d ", h->arr[i]);
  }   

  printf("\n");
}

bool jt_perm(jt_handle *h) {
  for (int i = 0; i < (int)h->n; i++) {
    int p = h->pos[i];
    int d = h->dir[i];
    int n_pos = p+d;
    int neighbor = h->arr[n_pos];

    if (n_pos >= 0 && n_pos < (int)h->n && i < neighbor) {
      // swap elements
      h->arr[p] = neighbor;
      h->arr[p+d] = i;

      // update positions
      h->pos[i] += d;
      h->pos[neighbor] -= d;
      return true;
    } else {
      h->dir[i] = (h->dir[i] == 1) ? -1 : 1;
    }
  }

  jt_init(h);
  return false;
}
