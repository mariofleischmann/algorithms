#include <stdio.h>

#define N_MAX 100

/*
 * increments a number by one
 *
 * returns 1 if overflow has happened
 * otherwise 0
 */
int increment(unsigned char *digits, unsigned char *bases, int n_digits) {
  for (int i = n_digits - 1; i >= 0; i--) {
    if (digits[i] >= bases[i]-1) {
      digits[i] = 0;
    } else {
      digits[i]++;
      return 0;
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
int decrement(unsigned char *digits, unsigned char *bases, int n_digits) {
  for (int i = n_digits - 1; i >= 0; i--) {
    if (digits[i] <= 0) {
      digits[i] = bases[i] - 1;
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
int is_zero(unsigned char *digits, int n_digits) {
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
int is_max(unsigned char *digits, unsigned char *bases, int n_digits) {
  int m = 1;
  for (int i = 0; i < n_digits; i++)
    m &= (digits[i] == bases[i]-1);

  return m;
}

/*
 * Prints a number.
 */
void print_number(unsigned char *digits, int n_digits) { 
  for (int i = 0; i < n_digits; i++)
    printf("%d", digits[i]);
  printf("\n");
}

int main(void) {
  unsigned char digits[N_MAX] = {0}; 
  unsigned char bases[N_MAX];

  int n_digits = 0;
  int base;
  while (fscanf(stdin, "%d", &base) == 1 && n_digits < N_MAX) {
    if (base <= 0) {
      printf("Base value <= 0 recognized. Program terminates.\n");
      return -1;
    }
    bases[n_digits++] = base; 
  }

  unsigned long n = 0;
  while (increment(digits, bases, n_digits) < 1) {
    n++;
  }

  printf("Limit reached. Amount of increments: %ld\n", n);
  return 0;
}

