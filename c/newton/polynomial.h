#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

typedef struct polynomial{
    double complex *roots;
    int order; 
} polynomial_t;

polynomial_t *polyonimal_create(int order);
void polyonimal_free(polynomial_t *p);
complex double polynomial_value(polynomial_t *p, double complex x);
complex double polynomial_slope(polynomial_t *p, double complex x);

#endif
