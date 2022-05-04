#include <stdlib.h>
#include <complex.h>

#include "polynomial.h"

polynomial_t *polyonimal_create(int order)
{
    polynomial_t *p = malloc(sizeof(polynomial_t));
    p->roots = malloc(order * sizeof(double complex));
    p->order = order;
    
    for (int i = 0; i < order; i++) {
       p->roots[i] = 0; 
    }

    return p;
}

void polyonimal_free(polynomial_t *p)
{
    free(p->roots);
    free(p);
}

complex double polynomial_value(polynomial_t *p, double complex x)
{
    complex double y = 1;
    for (int i = 0; i < p->order; i++) {
        y *= (x - p->roots[i]);
    }

    return y;
}

static complex double polynomial_derivative(polynomial_t *p,
                                            double complex x,
                                            int root_start,
                                            int root_end)
{
    if (root_start == root_end) {
        return 1;
    }

    complex double f = x - p->roots[root_start];
    complex double df = 1;
    complex double g = 1;
    for (int i = root_start + 1; i <= root_end; i++) {
        g *= (x - p->roots[i]);
    }

    complex double dg = polynomial_derivative(p, x, root_start+1, root_end);

    return f * dg + g * df;
}

complex double polynomial_slope(polynomial_t *p, double complex x)
{
    return polynomial_derivative(p, x, 0, p->order-1);
}
