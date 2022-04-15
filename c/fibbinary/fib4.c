#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "util.h"

uint64_t next_fibbinary(uint64_t x) {
  uint64_t y = ~(x >> 1); // y: 1 if left neighbor is zero

  //   x - y
  // = x + (-y)
  // = x + (~y + 1)
  // = (x | ~y) + 1
  // = (x | (x>>1)) + 1
  // x + ~y = x | ~y because no overflow can happen
  // a digit cannot be 1 while its left neighbor is also 1
  uint64_t z = x - y;

  //   (x | (x >> 1)) & ~(x >> 1)
  // = (x & ~(x >> 1)) | ((x >> 1) & ~(x >> 1))
  // = x & ~(x >> 1)
  // = x
  // for each fibbinary number's digit which is 1,
  // its neighbors have to be 0.
  // therefore x = x & ~(x >> 1)
  return z & y;
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

