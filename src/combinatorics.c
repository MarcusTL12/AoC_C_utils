#include "combinatorics.h"

#include <stdio.h>

bool next_permstate(size_t *state, size_t n) {
    for (size_t i = 0; i < n - 1; i++) {
        if (++state[i] < n - i) {
            return true;
        } else {
            state[i] = 0;
        }
    }

    return false;
}

void get_perm(size_t *perm, size_t *state, size_t n) {
    size_t used = 0;
    for (size_t i = 0; i < n; i++) {
        size_t j = 0, counter = 0;
        do {
            counter += ((~used) >> j) & 1;
            j++;
        } while (counter < state[i] + 1);
        j -= 1;
        used |= 1 << j;
        perm[i] = j;
    }
}
