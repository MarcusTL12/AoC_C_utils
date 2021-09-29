#include "deque.h"

#include <stdlib.h>
#include <string.h>

#define GROWTH_FACTOR 2
#define INIT_CAP 8

deque_t deque_create(size_t el_size) {
    deque_t q;

    q.el_size = el_size;
    q.capacity = INIT_CAP;
    q.amt_elements = 0;
    q.start_ind = 0;
    q.first_free_ind = 0;

    q.data = malloc(q.capacity * el_size);

    return q;
}

void deque_free(deque_t *q) {
    free(q->data);
    q->data = NULL;
}

static void deque_realloc(deque_t *q) {
    if (q->first_free_ind == q->start_ind && q->amt_elements > 0) {
        deque_t new_q;

        new_q.el_size = q->el_size;
        new_q.capacity = q->capacity * GROWTH_FACTOR;
        new_q.amt_elements = q->amt_elements;
        new_q.start_ind = 0;
        new_q.first_free_ind = new_q.amt_elements;

        new_q.data = malloc(new_q.capacity * new_q.el_size);

        size_t amt_elements_before_split = q->amt_elements - q->first_free_ind;

        memcpy(new_q.data, q->data + q->start_ind * q->el_size,
               amt_elements_before_split * q->el_size);
        memcpy(new_q.data + amt_elements_before_split * q->el_size, q->data,
               q->first_free_ind * q->el_size);

        deque_free(q);

        *q = new_q;
    }
}

void deque_push_back(deque_t *q, void *element) {
    deque_realloc(q);

    memcpy(q->data + q->first_free_ind * q->el_size, element, q->el_size);
    q->amt_elements++;
    q->first_free_ind++;
    if (q->first_free_ind == q->capacity) {
        q->first_free_ind = 0;
    }
}

bool deque_pop_back(deque_t *q, void *dest) {
    if (!q->amt_elements) return false;

    q->amt_elements--;
    if (q->first_free_ind) {
        q->first_free_ind--;
    } else {
        q->first_free_ind = q->capacity - 1;
    }

    memcpy(dest, q->data + q->first_free_ind * q->el_size, q->el_size);

    return true;
}

void deque_push_front(deque_t *q, void *element) {
    deque_realloc(q);

    q->amt_elements++;
    if (q->start_ind) {
        q->start_ind--;
    } else {
        q->start_ind = q->capacity - 1;
    }

    memcpy(q->data + q->start_ind * q->el_size, element, q->el_size);
}

bool deque_pop_front(deque_t *q, void *dest) {
    if (!q->amt_elements) return false;

    memcpy(dest, q->data + q->start_ind * q->el_size, q->el_size);

    q->amt_elements--;
    q->start_ind++;
    if (q->start_ind == q->capacity) {
        q->start_ind = 0;
    }

    return true;
}
