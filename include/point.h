#pragma once

#include <stdint.h>

typedef struct {
    int64_t x, y;
} point2i;

int point2i_cmp(const void *a, const void *b, void *udata);
uint64_t point2i_hash(const void *p, uint64_t s0, uint64_t s1);

static point2i point2i_add(point2i a, point2i b) {
    return (point2i){a.x + b.x, a.y + b.y};
}

static point2i point2i_sub(point2i a, point2i b) {
    return (point2i){a.x - b.x, a.y - b.y};
}

static point2i point2i_neg(point2i p) { return (point2i){-p.x, -p.y}; }

static point2i point2i_mul(point2i p, int64_t n) {
    return (point2i){n * p.x, n * p.y};
}

void point2i_show(void *p_);

// TODO: point3i
