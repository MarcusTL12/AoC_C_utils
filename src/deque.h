#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    size_t el_size, capacity, amt_elements, start_ind, first_free_ind;
    void *data;
} deque_t;

deque_t deque_create(size_t el_size);
void deque_free(deque_t *q);

void deque_push_back(deque_t *q, void *element);
bool deque_pop_back(deque_t *q, void *dest);

void deque_push_front(deque_t *q, void *element);
bool deque_pop_front(deque_t *q, void *dest);
