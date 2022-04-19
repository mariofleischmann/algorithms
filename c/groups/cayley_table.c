/**
 * cayley_table.c
 * Written by Mario Fleischmann
 */

#include <stdio.h>

#include "cayley_table.h"

static bool no_duplicates_until_row(cayley_table_t *t, int row)
{
    // Find duplicates by hashing
    for (size_t i = 0; i < t->n; i++) {
        for (size_t j = 0; j < t->n; j++) {
            t->buff[j] = 0;
        }

        for (int j = 0; j <= row; j++) {
            int e = t->rows[j]->arr[i];
            if (t->buff[e]++ > 1) {
                return false;
            }
        }
    }

    return true; 
}

static bool neutral_until_row(cayley_table_t *t, int row)
{
    for (int i = 0; i < row; i++) {
        if (t->rows[i]->arr[0] != t->rows[0]->arr[i]) {
            return false;
        }
    }

    return true;
} 

cayley_table_t *table_create(size_t n)
{
    cayley_table_t *t = malloc(sizeof(cayley_table_t)); 
    t->n = n;
    t->ok = 1;
    t->buff = malloc(sizeof(int) * n);
    t->rows = malloc(sizeof(jt_set_t *) * n);
    for (size_t i = 0; i < t->n; i++) {
        t->rows[i] = jt_create(n);
    }

    return t;
}

cayley_table_t *table_copy(cayley_table_t *t)
{
    cayley_table_t *new = table_create(t->n);
    new->ok = t->ok;
    for (size_t i = 0; i < t->n; i++) {
        jt_assign_value(new->rows[i], t->rows[i]);
    }

    return new;
}

void table_free(cayley_table_t *t)
{
    for (size_t i = 0; i < t->n; i++) {
        jt_free(t->rows[i]);
    }

    free(t->buff);
    free(t->rows);
    free(t);
}

int table_eval(cayley_table_t *t, int a, int b)
{
    return t->rows[a]->arr[b];
}

bool table_is_associative(cayley_table_t *t)
{
    for (int a = 0; a < (int)t->n; a++) {
        for (int b = 0; b < (int)t->n; b++) {
            for (int c = 0; c < (int)t->n; c++) {
                int bc = table_eval(t, b, c); 
                int ab = table_eval(t, a, b); 
                int res1 = table_eval(t, a, bc);
                int res2 = table_eval(t, ab, c);
                if (res1 != res2) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool table_is_commutative(cayley_table_t *t)
{
    for (int a = 0; a < (int)t->n; a++) {
        for (int b = 0; b < (int)t->n; b++) {
            if (table_eval(t, a, b) != table_eval(t, b, a)) {
                return false;
            }
        }
    }

    return true;
}

bool tables_are_isomorph(cayley_table_t *t1, cayley_table_t *t2)
{
    if (t1->n != t2->n) {
        return false;
    }

    // Check every possible mapping with existing permutation algorithm
    jt_set_t *jt = jt_create(t1->n);
    while (jt_perm(jt)) {
        bool isomorph = true;

        for (int a = 0; a < (int)t1->n && isomorph; a++) {
            for (int b = 0; b < (int)t1->n && isomorph; b++) {
                int _a = jt->arr[a];
                int _b = jt->arr[b];
                int res = table_eval(t1, a, b); 
                int _res = table_eval(t2, _a, _b); 

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

void table_print(cayley_table_t *t)
{
    printf("* |");
    for (int i = 0; i < (int)t->n; i++) {
        printf(" %d", i);
    }

    printf("\n--+");

    for (size_t i = 0; i < t->n; i++) {
        printf("--");
    }

    printf("\n");

    for (int i = 0; i < (int)t->n; i++) {
        printf("%d | ", i);
        jt_print(t->rows[i]);
    }
}

bool table_next_group(cayley_table_t *t)
{
    if (t->n == 1) {
        // trivial group
        return false;
    }

    if (t->ok == (int)t->n) {
        t->ok--;
    }

    while (t->ok < (int)t->n) {
        bool cycle;
        do {
            cycle = !jt_perm(t->rows[t->ok]);
            if (cycle) {
                break;
            }
        } while (!neutral_until_row(t, t->ok) ||
                 !no_duplicates_until_row(t, t->ok));

        if (cycle) {
            if (t->ok == 1) {
                // complete cycle
                return false;
            } else {
                t->ok--;
            }
        } else {
            t->ok++;
        }
    }

    if (!table_is_associative(t)) {
        return table_next_group(t);
    } 

    return true;
}
