/**
 * cayley_table.h
 * 
 * Arthur Cayley multiplication table.
 * Defines the structure and methods to * find all groups of a given size.
 */

#ifndef CAYLEY_TABLE_H
#define CAYLEY_TABLE_H

#include <stdbool.h>
#include "jt_set.h"

/**
 * Cayley multiplication table
 */
typedef struct cayley_table{
    jt_set_t **rows;
    int ok;
    size_t n;
    int *buff; // reserved memory for duplicate checks
} cayley_table_t;

/**
 * Allocates memory and creates a new table.
 *
 * @param n Size of the table.
 * @return Pointer to the created table. 
 */
cayley_table_t *table_create(size_t n);

/**
 * Allocates memory and creates a deep clone
 * of a given table.
 *
 * @param t Table to be copied.
 * @return Copy of the table.
 */  
cayley_table_t *table_copy(cayley_table_t *t);

/**
 * Frees the memory a Cayley table and its sets.
 *
 * @param t Memory to be freed.
 */
void table_free(cayley_table_t *t);

/**
 * Evaluates the result of the expression a * b
 * based on the given Cayley table.
 *
 * @param t Cayley table.
 * @param a First operand.
 * @param b Seconds operand.
 * @return Result of the expression.
 */
int table_eval(cayley_table_t *t, int a, int b);

/**
 * Check whether the given Cayley table is associative.
 *
 * @param t Cayley table.
 * @return True if table is associative.
 */
bool table_is_associative(cayley_table_t *t);

/**
 * Check whether the given Cayley table is commutative.
 *
 * @param t Cayley table.
 * @return True if table is commutative.
 */
bool table_is_commutative(cayley_table_t *t);

/**
 * Check whether the two given Cayley tables are isomorph.
 *
 * @param t1 First table.
 * @param t2 Second table.
 * @return True if tables are isomorph.
 */
bool tables_are_isomorph(cayley_table_t *t1, cayley_table_t *t2);

/**
 * Prints the Cayley table.
 *
 * @param t Table to be printed.
 */
void table_print(cayley_table_t *t);

/**
 * Find the next group of the Cayley table.
 *
 * @param t Cayley table.
 * @return True after one complete cycle.
 */
bool table_next_group(cayley_table_t *t);

#endif
