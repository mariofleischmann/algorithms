#include <stdio.h>
#include <stdint.h>

#include "util.h"

#define BIT_SET(x, pos) (((x) >> (pos)) & 0x01)

// degree of polynomial x
int degree (uint64_t x) {
    for (int i = 63; i >= 0; i--) {
        if (BIT_SET(x, i)) {
            return i;
        }
    }

    return 0;
}

// a * b (mod m)
// a, b, m are polynomials with binary coefficients
uint32_t multiply (uint32_t a, uint32_t b, uint32_t m)
{
    uint64_t res = 0; 
    for (int i = 0; i < 32; i++) {
        if (BIT_SET(b, i)) {
            res ^= (a << i);
        }
    }

    int degree_m = degree(m);
    int degree_res = degree(res);

    for (int i = degree_res; i >= degree_m; i--) {
        if (BIT_SET(res, i)) {
            res ^= m << (i - degree_m);
        }
    }

    return (uint32_t)res;
}

// a^e (mod m)
// a, m are polynomials with binary coefficients
// e is an integer
uint32_t exponentiate (uint32_t a, uint32_t e, uint32_t m) {
    uint32_t res = 1;
    for (int i = 0; i < e; i++) {
        res = multiply(res, a, m);
    }

    return res;
}

// use binary exponentiation
uint32_t bin_exponentiate (uint32_t a, uint32_t e, uint32_t m) {
    uint32_t res = 1;
    while (e > 0) {
        if (e & 0x01) {
            res = multiply(res, a, m);
        }

        a = multiply(a, a, m);
        e >>= 1;
    }

    return res;
}

int main(void)
{
    uint32_t a = 0b01111; // x^3 + x^2 + x^1 + x^0
    uint32_t b = 0b01001; // x^3 + x^0
    uint32_t m = 0b10011; // x^4 + x^1 + x^0

    printf("a = ");
    print_bin(a, 5);

    printf("b = ");
    print_bin(b, 5);

    printf("m = ");
    print_bin(m, 5);

    printf("a * b (mod m) = ");
    print_bin(multiply(a, b, m), 5);

    printf("a ^ 99 (mod m) = ");
    print_bin(bin_exponentiate(a, 99, m), 5);

    printf("a ^ 99 (mod m) = ");
    print_bin(exponentiate(a, 99, m), 5);
    
    return 0;
}
