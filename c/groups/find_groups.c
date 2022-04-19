#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "group.h"

#define N 4

int main(void) {
  int cnt = 0;
  for (int i = 1; i <= N; i++) {
    group_t *g = group_create(i);
    while(group_next(g)) {
      cnt++;
      group_print(g);
      printf("\n");
    }
    group_free(g);
  }
}
