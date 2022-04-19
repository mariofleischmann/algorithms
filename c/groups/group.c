#include <stdio.h>
#include "group.h"

group_t *group_create(size_t n) {
    group_t *g = malloc(sizeof(group_t)); 
    g->n = n;
    g->ok = 1;
    g->temp = malloc(sizeof(int) * n);
    g->rows = malloc(sizeof(jt_handle*) * n);
    for (size_t i = 0; i < g->n; i++) {
        g->rows[i] = jt_create(n);
    }

    return g;
}

void group_free(group_t *g) {
    for (size_t i = 0; i < g->n; i++) {
        jt_free(g->rows[i]);
    }

    free(g->temp);
    free(g->rows);
    free(g);
}

void group_print(group_t *g) {
    printf("* |");
    for (int i = 0; i < (int)g->n; i++) {
        printf(" %d", i);
    }

    printf("\n--+");

    for (size_t i = 0; i < g->n; i++) {
        printf("--");
    }

    printf("\n");

    for (int i = 0; i < (int)g->n; i++) {
        printf("%d | ", i);
        jt_print(g->rows[i]);
    }
}

bool is_ok_until_row(group_t *g, int row) {
    for (int i = 0; i < (int)g->n; i++) {
        for (int j = 0; j < (int)g->n; j++) {
            g->temp[j] = 0;
        }

        for (int j = 0; j <= row; j++) {
            int e = g->rows[j]->arr[i];
            g->temp[e] += 1;
            if (g->temp[e] > 1) {
                return false;
            }
        }
    }

    return true; 
}

bool has_neutral(group_t *g, int row) {
    for (int i = 0; i < row; i++) {
        if (g->rows[i]->arr[0] != g->rows[0]->arr[i]) {
            return false;
        }
    }

    return true;
} 

bool group_next(group_t *g) {
    if (g->n == 1) {
        // trivial group
        return false;
    }

    if (is_group(g)) {
        g->ok--;
    }

    while (g->ok < g->n) {
        bool overflow;
        do {
            overflow = !jt_perm(g->rows[g->ok]);
            if (overflow) {
                break;
            }

        } while (!has_neutral(g, g->ok) || !is_ok_until_row(g, g->ok));

        if (overflow) {
            if (g->ok == 1) {
                return false;
            } else {
                g->ok--;
            }
        } else {
            g->ok++;
        }
    }  

    return true;
}

bool is_group(group_t *g) {
    return g->ok == g->n;
}
