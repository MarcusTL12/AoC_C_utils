#include "bitfield.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        acc += __builtin_popcountll(bitfield[i]);
    }

    return acc;
}

uint64_t *bitfield_create(size_t bits) {
    size_t bytes = bitfield_ints(bits) * sizeof(uint64_t);
    void *p = malloc(bytes);
    memset(p, 0, bytes);
    return p;
}

void bitfield_free(uint64_t *bitfield) { free(bitfield); }

void bitfield_or(uint64_t *a, uint64_t *b, size_t n_ints) {
    for (size_t i = 0; i < n_ints; i++) {
        a[i] |= b[i];
    }
}

void bitfield_and(uint64_t *a, uint64_t *b, size_t n_ints) {
    for (size_t i = 0; i < n_ints; i++) {
        a[i] &= b[i];
    }
}

void bitfield_not(uint64_t *bitfield, size_t n_bits) {
    size_t n_ints = bitfield_ints(n_bits);
    size_t leftover = n_bits % 64;

    for (size_t i = 0; i < n_ints; i++) {
        bitfield[i] = ~bitfield[i];
    }

    uint64_t mask = ~0;
    mask <<= leftover;
    bitfield[n_ints - 1] &= ~mask;
}

void bitfield_xor(uint64_t *a, uint64_t *b, size_t n_ints) {
    for (size_t i = 0; i < n_ints; i++) {
        a[i] ^= b[i];
    }
}

size_t bitfield_findfirst_true(uint64_t *bitfield, size_t n_ints) {
    for (size_t i = 0; i < n_ints; i++) {
        if (bitfield[i]) {
            uint32_t *a = (uint32_t *)(bitfield + i);
            uint32_t n32_1 = a[0], n32_2 = a[1];

            size_t ind = 64 * i + n32_1 ? 0 : 32;
            uint32_t n32 = n32_1 ? n32_1 : n32_2;
            for (size_t subind = 0; subind < 32; subind++) {
                if ((n32 >> subind) & 1) {
                    return ind + subind;
                }
            }
        }
    }

    return -1;
}

void bitfield_show(uint64_t *bitfield, size_t n_bits) {
    for (size_t i = 0; i < n_bits; i++) {
        printf("%c", bitfield_get(bitfield, i) ? '1' : '0');
    }
}

void bitfield_set_n(uint64_t *bitfield, bool val, size_t start, size_t n) {
    lldiv_t start_split = lldiv(start, 64);

    if (start_split.rem + n <= 64) {
        uint64_t mask1 = (~((uint64_t)0)) << start_split.rem;
        uint64_t mask2 = (~((uint64_t)0)) >> (64 - start_split.rem - n);
        uint64_t mask = mask1 & mask2;

        if (val) {
            bitfield[start_split.quot] |= mask;
        } else {
            bitfield[start_split.quot] &= ~mask;
        }

        return;
    }

    if (start_split.rem) {
        uint64_t mask = (~((uint64_t)0)) << start_split.rem;

        if (val) {
            bitfield[start_split.quot] |= mask;
        } else {
            bitfield[start_split.quot] &= ~mask;
        }

        start_split.quot++;
        n -= start_split.rem;
    }

    lldiv_t n_split = lldiv(n, 64);
    memset(bitfield + start_split.quot, val ? ~((int)0) : 0, n_split.quot * 8);

    if (n_split.rem) {
        uint64_t mask = (~((uint64_t)0)) >> n_split.rem;

        if (val) {
            bitfield[start_split.quot + n_split.quot] |= mask;
        } else {
            bitfield[start_split.quot + n_split.quot] &= ~mask;
        }
    }
}

void bitfield_toggle_n(uint64_t *bitfield, size_t start, size_t n) {
    lldiv_t start_split = lldiv(start, 64);

    if (start_split.rem + n <= 64) {
        uint64_t mask1 = (~((uint64_t)0)) << start_split.rem;
        uint64_t mask2 = (~((uint64_t)0)) >> (64 - start_split.rem - n);
        uint64_t mask = mask1 & mask2;

        bitfield[start_split.quot] ^= mask;

        return;
    }

    if (start_split.rem) {
        uint64_t mask = (~((uint64_t)0)) << start_split.rem;

        bitfield[start_split.quot] ^= mask;

        start_split.quot++;
        n -= start_split.rem;
    }

    lldiv_t n_split = lldiv(n, 64);
    for (size_t i = 0; i < n_split.quot; i++) {
        bitfield[start_split.quot + i] ^= ~((uint64_t)0);
    }

    if (n_split.rem) {
        uint64_t mask = (~((uint64_t)0)) >> n_split.rem;

        bitfield[start_split.quot + n_split.quot] ^= mask;
    }
}
