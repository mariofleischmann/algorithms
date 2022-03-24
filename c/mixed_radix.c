#include <stdio.h>

#define N_MAX 100

/*
 * increments a number by one
 *
 * returns 1 if overflow has happened
 * otherwise 0
 */
int increment(unsigned int *digits, unsigned int *radix, int n_digits) {
  for (int i = n_digits-1; i >= 0; i--) {
    if (digits[i] >= radix[i]-1) {
      digits[i] = 0;
    } else {
      digits[i]++;
      return 0;
    }
  }

  return 1;
}

/*
 * increments a number by one
 * according to gray code
 *
 * returns 1 if overflow has happened
 * otherwise 0
 */
int increment_gray(unsigned int *digits, unsigned int *radix, char *is_decreasing, int n_digits) {
  for (int i = n_digits-1; i >= 0; i--) {
    if (is_decreasing[i]) {
      if (digits[i] <= 0) {
        is_decreasing[i] = 0;
      } else {
        digits[i]--;
        return 0;
      }
    } else {
      if (digits[i] >= radix[i]-1) {
        is_decreasing[i] = 1;
      } else {
        digits[i]++;
        return 0;
      }
    }
  }

  return 1;
}

/*
 * decrements a number by one
 *
 * returns 1 if underflow has happened
 * otherwise 0
 */
int decrement(unsigned int *digits, unsigned int *radix, int n_digits) {
  for (int i = n_digits - 1; i >= 0; i--) {
    if (digits[i] <= 0) {
      digits[i] = radix[i] - 1;
    } else {
      digits[i]--;
      return 0;
    }
  }

  return 1;
}

/*
 * checks whether a given number equals zero
 *
 * returns 1 if number is zero
 * otherwise 0
 */
int is_zero(unsigned int *digits, int n_digits) {
  int z = 1;
  for (int i = 0; i < n_digits; i++)
    z &= (digits[i] == 0);

  return z;
}

/*
 * checks whether a given number
 * represents the maximal possible value
 *
 * returns 1 if number is zero
 * otherwise 0
 */
int is_max(unsigned int *digits, unsigned int *radix, int n_digits) {
  int m = 1;
  for (int i = 0; i < n_digits; i++)
    m &= (digits[i] == radix[i]-1);

  return m;
}

/*
 * Prints a number.
 */
void print_number(unsigned int *digits, int n_digits) { 
  for (int i = 0; i < n_digits; i++)
    printf("%d", digits[i]);
  printf("\n");
}

int main(void) {
  unsigned int digits[N_MAX] = {0}; 
  unsigned int radix[N_MAX];
#ifdef USE_GRAY
  char is_decreasing[N_MAX] = {0};
#endif

  int n_digits = 0;
  int base;
  while (fscanf(stdin, "%d", &base) == 1 && n_digits < N_MAX) {
    if (base <= 0) {
      printf("Base value <= 0 recognized. Program terminates.\n");
      return -1;
    }
    radix[n_digits++] = base; 
  }

  unsigned long n = 0;
  do {
    n++;

#ifdef VERBOSE
    print_number(digits, n_digits);
#endif

  }
#ifdef USE_GRAY
  while (!increment_gray(digits, radix, is_decreasing, n_digits));
#else
  while (!increment(digits, radix, n_digits));
#endif

  printf("Limit reached. Amount of increments: %ld\n", n);
  return 0;
}

