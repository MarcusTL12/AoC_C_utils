#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

void bitfield_set(uint64_t *bitfield, size_t index, bool val) {
    lldiv_t index_split = lldiv(index, 64);

    uint64_t mask = ((uint64_t)1) << index_split.rem;

    if (val) {
        bitfield[index_split.quot] |= mask;
    } else {
        bitfield[index_split.quot] &= ~mask;
    }
}

bool bitfield_get(uint64_t *bitfield, size_t index) {
    lldiv_t index_split = lldiv(index, 64);

    uint64_t mask = ((uint64_t)1) << index_split.rem;

    return bitfield[index_split.quot] & mask;
}

size_t bitfield_count(uint64_t *bitfield, size_t amt_ints) {
    size_t acc = 0;

    for (size_t i = 0; i < amt_ints; i++) {
        size_t x;
        asm("popcnt %1, %0" : "=r"(x) : "r"(bitfield[i]));
        acc += x;
    }

    return acc;
}
