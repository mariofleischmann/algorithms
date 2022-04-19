#include <stdio.h>
#include "group.h"

group_t *group_create(size_t n)
{
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

void group_free(group_t *g)
{
    for (size_t i = 0; i < g->n; i++) {
        jt_free(g->rows[i]);
    }

    free(g->temp);
    free(g->rows);
    free(g);
}

void group_print(group_t *g)
{
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

static bool is_ok_until_row(group_t *g, int row)
{
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

static bool has_neutral(group_t *g, int row)
{
    for (int i = 0; i < row; i++) {
        if (g->rows[i]->arr[0] != g->rows[0]->arr[i]) {
            return false;
        }
    }

    return true;
} 

bool group_next(group_t *g)
{
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

    if (!group_associative(g)) {
        return group_next(g);
    } 

    return true;
}

bool is_group(group_t *g)
{
    return g->ok == g->n;
}


int group_eval(group_t *g, int a, int b)
{
    return g->rows[a]->arr[b];
}

bool group_equals(group_t *g1, group_t *g2)
{
    if (g1->n != g2->n) {
        return false;
    }

    // Check if there is a mapping
    // {1, 2, ..., n-1} <-> {1, 2, ..., n-1}
    // such that for every a, b
    // a * b = map^-1((map(a) * map(b)) 

    jt_handle *jt = jt_create(g1->n);
    while (jt_perm(jt)) {
        bool isomorph = true;

        for (int a = 0; a < g1->n && isomorph; a++) {
            for (int b = 0; b < g1->n && isomorph; b++) {
                int _a = jt->arr[a];
                int _b = jt->arr[b];
                int res = group_eval(g1, a, b); 
                int _res = group_eval(g2, _a, _b); 

                if (res != jt->pos[_res]) {
                    isomorph = false;
                }
            }
        }

        if (isomorph) {
            jt_free(jt);
            return true;
        }
    }

    jt_free(jt);
    return false;
}

// check if for every a, b, c
// a * (b * c) = (a * b) * c
bool group_associative(group_t *g)
{
    for (int a = 0; a < g->n; a++) {
        for (int b = 0; b < g->n; b++) {
            for (int c = 0; c < g->n; c++) {
                int bc = group_eval(g, b, c); 
                int ab = group_eval(g, a, b); 
                int res1 = group_eval(g, a, bc);
                int res2 = group_eval(g, ab, c);
                if (res1 != res2) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool group_commutative(group_t *g)
{
    for (int a = 0; a < g->n; a++) {
        for (int b = 0; b < g->n; b++) {
            if (group_eval(g, a, b) != group_eval(g, b, a)) {
                return false;
            }
        }
    }

    return true;
}

group_t *group_copy(group_t *g) {
    group_t *new = group_create(g->n);
    new->ok = g->ok;
    for (size_t i = 0; i < g->n; i++) {
        jt_set(new->rows[i], g->rows[i]);
    }

    return new;
}
