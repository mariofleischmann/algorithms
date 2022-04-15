#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "util.h"

uint64_t next_fibbinary(uint64_t x) {
  uint64_t y = x | (x >> 1);

  // y now represents x in binary addition

  uint64_t z = y + 1;
  z = z & -z; // Lowest bit set

  // bit to change is now in z 

  x ^= z; // change bit
  return x & ~(z-1); // clear all lower bits
}

int main() {
  uint64_t i = 0, cnt = 0;

  do {
    cnt++;
#ifdef VERBOSE
    print_bin(i, 10);
#endif
    i = next_fibbinary(i);
  } while(!(i>>10));

  printf("%llu fibbinary numbers\n", cnt);

  return 0;
}

