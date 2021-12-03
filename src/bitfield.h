#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void bitfield_set(uint64_t *bitfield, size_t index, bool val);
bool bitfield_get(uint64_t *bitfield, size_t index);
size_t bitfield_count(uint64_t *bitfield, size_t n_ints);
static size_t bitfield_ints(size_t bits) { return 1 + (bits - 1) / 64; }
uint64_t *bitfield_create(size_t bits);
void bitfield_free(uint64_t *bitfield);

// a |= b
void bitfield_or(uint64_t *a, uint64_t *b, size_t n_ints);

// a &= b
void bitfield_and(uint64_t *a, uint64_t *b, size_t n_ints);

// a = ~a
void bitfield_not(uint64_t *bitfield, size_t n_bits);

// a ^= b
void bitfield_xor(uint64_t *a, uint64_t *b, size_t n_ints);

// returns (size_t)-1 if none are found
size_t bitfield_findfirst_true(uint64_t *bitfield, size_t n);

void bitfield_show(uint64_t *bitfield, size_t n_bits);
