#include <stdio.h>
#include <stdbool.h>
#include <complex.h>
#include <SDL2/SDL.h>

#include "polynomial.h"

#define MAX_IT 1000
#define TOL 0.00001

bool find_root(polynomial_t *p, double complex z0, double complex *r)
{
    double complex z = z0;

    for (int i = 0; i < MAX_IT; i++) {
        double complex dz = polynomial_value(p, z) / polynomial_slope(p, z);
        if (cabs(dz) < TOL) {
            *r = z;
            return true;
        }

        z = z - dz;
    }

    return false;
}

bool get_root_index(polynomial_t *p, double complex r, int *i)
{
    for (int j = 0; j < p->order; j++) {
        double complex d = p->roots[j] - r;
        if (cabs(d) < TOL) {
            *i = j;
            return true;
        }
    }

    return false;
}

int main(void)
{
    polynomial_t *p = polyonimal_create(4);
    p->roots[0] = CMPLX(-1,0);
    p->roots[1] = CMPLX(0, 1);
    p->roots[2] = CMPLX(0, -1);
    p->roots[3] = CMPLX(1, 0);

    SDL_Surface *canvas = SDL_CreateRGBSurface(0, 2000, 2000, 32, 0, 0, 0, 0);

    uint32_t colors[4];
    colors[0] = SDL_MapRGB(canvas->format, 219, 7, 61);
    colors[1] = SDL_MapRGB(canvas->format, 219, 165, 7);
    colors[2] = SDL_MapRGB(canvas->format, 142, 199, 210);
    colors[3] = SDL_MapRGB(canvas->format, 7, 72, 91);
    
    for (double i = -1; i < 1; i += 0.001) {
        for (double j = -1; j < 1; j += 0.001) {
            double complex z0 = CMPLX(i,j); 
            double complex r;
            if (find_root(p, z0, &r)) {
                int idx;
                get_root_index(p, r, &idx);

                int x = (int)((double)(i + 1) * 1000);
                int y = (int)((double)(j + 1) * 1000);

                uint32_t *pixels = (uint32_t *)canvas->pixels;
                pixels[ ( y * canvas->w ) + x ] = colors[idx];
            }
        }
    }

    SDL_SaveBMP(canvas, "fractal.bmp");
    SDL_FreeSurface(canvas);
    SDL_Quit();
}
