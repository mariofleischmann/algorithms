#include <stdio.h>
#include <stdint.h>

#include "util.h"

void print_bin(uint64_t x, int n_bits) {
  uint64_t mask = 1 << n_bits;
  while (mask) {
    printf("%d", !!(x & mask));
    mask >>= 1;
  }
  printf("\n");
}
