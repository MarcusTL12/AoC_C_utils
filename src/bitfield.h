#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void bitfield_set(uint64_t *bitfield, size_t index, bool val);
bool bitfield_get(uint64_t *bitfield, size_t index);
size_t bitfield_count(uint64_t *bitfield, size_t amt_ints);
static size_t bitfield_ints(size_t bits) { return 1 + (bits - 1) / 64; }
uint64_t *bitfield_create(size_t bits);
void *bitfield_free(uint64_t *bitfield);
