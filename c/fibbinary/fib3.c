#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "util.h"

uint64_t next_fibbinary(uint64_t x) {
  uint64_t l = ~(x >> 1); // left neighbor 0
  uint64_t o = l & ~x; // options
  o &= -o;
  return (x|o) & ~(o-1);
}

int main(void) {
  uint64_t i = 0, cnt = 0;

  do {
    cnt++;
#ifdef VERBOSE
    print_bin(i, 10);
#endif
    i = next_fibbinary(i);
  } while(!(i >> 10));

  printf("%llu fibbinary numbers\n", cnt);

  return 0;
}

