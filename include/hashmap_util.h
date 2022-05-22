#pragma once

#include <string.h>

#define MAKE_HASH_AND_CMP(NAME, SIZE)                                         \
    static uint64_t NAME##_hash(const void *item, uint64_t s0, uint64_t s1) { \
        return hashmap_sip(item, SIZE, s0, s1);                               \
    }                                                                         \
    static int NAME##_cmp(const void *a, const void *b, void *udata) {        \
        return memcmp(a, b, SIZE);                                            \
    }
