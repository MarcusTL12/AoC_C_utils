#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct {
    int64_t min, max;
} minmax_t;

minmax_t minmax(int64_t *array, size_t len);
minmax_t minmax_inds(int64_t *array, size_t len);

void memswap(void *a, void *b, size_t n);
