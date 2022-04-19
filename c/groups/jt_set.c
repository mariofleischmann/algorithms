/**
 * jt_set.c
 * Written by Mario Fleischmann
 */

#include <stdio.h>
#include <stdlib.h>

#include "jt_set.h"

jt_set_t *jt_create(size_t n)
{
  jt_set_t *s = malloc(sizeof(jt_set_t));

  s->arr = malloc(sizeof(int) * n);
  s->pos = malloc(sizeof(int) * n);
  s->dir = malloc(sizeof(int) * n);
  s->n = n;

  jt_init(s);

  return s;
}

void jt_free(jt_set_t *s)
{
  free(s->arr);
  free(s->pos);
  free(s->dir);
  free(s);
}

void jt_init(jt_set_t *s)
{
  for (size_t i = 0; i < s->n; i++) {
    s->arr[i] = i;
    s->pos[i] = i;
    s->dir[i] = 1;
  }
}

bool jt_assign_value(jt_set_t *s1, jt_set_t *s2)
{
    if (s1->n != s2->n) {
        return false;
    }

    for (size_t i = 0; i < s1->n; i++) {
        s1->arr[i] = s2->arr[i];
        s1->pos[i] = s2->pos[i];
        s1->dir[i] = s2->dir[i];
    }

    return true;
}

void jt_print(jt_set_t *s)
{
  for (size_t i = 0; i < s->n; i++) {
    printf("%d ", s->arr[i]);
  }   

  printf("\n");
}

bool jt_perm(jt_set_t *s)
{
  for (size_t i = 0; i < s->n; i++) {
    int p = s->pos[i];
    int d = s->dir[i];
    int n_pos = p+d;
    int neighbor = s->arr[n_pos];

    if (n_pos >= 0 && n_pos < (int)s->n && (int)i < neighbor) {
      // swap elements
      s->arr[p] = neighbor;
      s->arr[p+d] = i;

      // update positions
      s->pos[i] += d;
      s->pos[neighbor] -= d;
      return true;
    } else {
      s->dir[i] = (s->dir[i] == 1) ? -1 : 1;
    }
  }

  jt_init(s);
  return false;
}
