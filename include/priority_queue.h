#pragma once

#include "hashmap.h"
#include "vector.h"

typedef struct {
    // The size of the elements without index and key
    size_t el_size;
    // The array to contain the binary heap structure. Each element is contains
    // the priority (int64_t) and the element data (el_size)
    vec_t heap;
    // The hashmap from element (e_size) to index in heap (size_t)
    struct hashmap *map;
    // A buffer for putting an element into for inserting into the hashmap.
    // Allocated on creation, freed on free
    void *buffer;
} priqueue_t;

priqueue_t priqueue_create(size_t el_size,
                           uint64_t (*hash)(const void *item, uint64_t s0,
                                            uint64_t s1),
                           int (*cmp)(const void *a, const void *b,
                                      void *udata));

void priqueue_free(priqueue_t *queue);

bool priqueue_pop(priqueue_t *queue, void *dest, int64_t *keydist);
void priqueue_insert(priqueue_t *queue, const void *item, int64_t key);
void priqueue_insert_increase(priqueue_t *queue, const void *item, int64_t key);
