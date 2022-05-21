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

// Even inds: positive, odd: negative
// 0-1: x, 2-3: y
// i ^ 1 => reverse
const static point2i DIRS2i4[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

typedef struct {
    int64_t x, y, z;
} point3i;

int point3i_cmp(const void *a, const void *b, void *udata);
uint64_t point3i_hash(const void *p, uint64_t s0, uint64_t s1);

static point3i point3i_add(point3i a, point3i b) {
    return (point3i){a.x + b.x, a.y + b.y, a.z + b.z};
}

static point3i point3i_sub(point3i a, point3i b) {
    return (point3i){a.x - b.x, a.y - b.y, a.z - b.z};
}

static point3i point3i_neg(point3i p) { return (point3i){-p.x, -p.y, -p.z}; }

static point3i point3i_mul(point3i p, int64_t n) {
    return (point3i){n * p.x, n * p.y, n * p.z};
}

void point3i_show(void *p_);
