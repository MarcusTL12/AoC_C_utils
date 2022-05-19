#include "point.h"

#include <stdio.h>
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

void point2i_show(void *p_) {
    point2i *p = (point2i *)p_;
    printf("{%li, %li}", p->x, p->y);
}

int point3i_cmp(const void *a_, const void *b_, void *udata) {
    point3i *a = (point3i *)a_, *b = (point3i *)b_;

    return a->x != b->x || a->y != b->y || a->z != b->z;
}

uint64_t point3i_hash(const void *p_, uint64_t s0, uint64_t s1) {
    point3i *p = (point3i *)p_;

    return hashmap_sip(p, sizeof(point3i), s0, s1);
}

void point3i_show(void *p_) {
    point3i *p = (point3i *)p_;
    printf("{%li, %li, %li}", p->x, p->y, p->z);
}
