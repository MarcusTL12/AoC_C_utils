#include "point.h"

#include <string.h>

#include "hashmap.h"

int point2i_cmp(const void *a_, const void *b_, void *udata) {
    point2i *a = (point2i *)a_, *b = (point2i *)b_;

    return a->x != b->x || a->y != b->y;
}

uint64_t point2i_hash(const void *p_, uint64_t s0, uint64_t s1) {
    point2i *p = (point2i *)p_;

    return hashmap_sip(p, sizeof(point2i), s0, s1);
}
