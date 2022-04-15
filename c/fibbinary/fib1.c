#include <stdio.h>
#include <stdint.h>
#include "util.h"

#define IS_FIBBINARY(x) (!((x) & ((x) >> 1)))

int main(void) {
  uint32_t cnt = 0;
  for (uint32_t i = 0; i < (1 << 10); i++) {
    if (IS_FIBBINARY(i)) {
#ifdef VERBOSE
      cnt++;
      print_bin(i, 10);
#endif
    }
  }

  printf("%d fibbinary numbers\n", cnt);
}

