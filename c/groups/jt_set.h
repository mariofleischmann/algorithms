/**
 * jt_set.h
 * 
 * Johnson-Trotter permutation algorithm.
 * Defines the structure and methods to
 * create all permutations for a set of elements.
 */

#ifndef JT_HANDLE_H
#define JT_HANDLE_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * Johnson-Trotter algorithm set 
 */
typedef struct jt_set{
  int *arr;
  int *pos;
  int *dir;
  size_t n;
} jt_set_t;

/**
 * Allocates memory and creates a new set.
 *
 * @param n Size of the set.
 * @return Pointer to the created set. 
 */
jt_set_t *jt_create(size_t n);

/**
 * Frees the memory a Johnson-Trotter set and its arrays.
 *
 * @param s Memory to be freed.
 */
void jt_free(jt_set_t *s);

/**
 * Sets the set to its default value.
 *
 * @param s Pointer to an existing set.
 */
void jt_init(jt_set_t *s);

/**
 * Assigns the value of set s2 to the set s1.
 *
 * @param s1 Set to be changed.
 * @param s2 Value of the set to change to.
 * @return True if assignment could be accomplished.
 */
bool jt_assign_value(jt_set_t *s1, jt_set_t *s2);

/**
 * Prints the elements of the set.
 *
 * @param s Set to be printed.
 */
void jt_print(jt_set_t *s);

/**
 * Creates the next permutation of the set.
 *
 * @param s Set to permute.
 * @return True after one complete cycle.
 */
bool jt_perm(jt_set_t *s);

#endif
