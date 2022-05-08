#pragma once

#include <stdbool.h>
#include <stddef.h>

// Takes in the permutation state and updates it to the next one.
// example for n = 5:
// First state = {0, 0, 0, 0, 0}
// Last state = {4, 3, 2, 1, 0}
// returns false if the last state is given, true otherwise
bool next_permstate(size_t *state, size_t n);

// Takes the permutation state, genrerated by next_permstate,
// and writes the permutation into *perm
void get_perm(size_t *perm, size_t *state, size_t n);
