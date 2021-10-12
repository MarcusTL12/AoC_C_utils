#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAP 8

vec_t vec_create(size_t el_size) {
    vec_t v;
    v.el_size = el_size;
    v.capacity = 0;
    v.len = 0;

    v.data = NULL;

    return v;
}

void vec_free(vec_t *v) { free(v->data); }

void vec_clear(vec_t *v) { v->len = 0; }

static void reallocate(vec_t *v) {
    if (v->len == v->capacity) {
        if (v->capacity == 0) {
            v->capacity = INIT_CAP;
            v->data = malloc(INIT_CAP * v->el_size);
        } else {
            void *n_data = malloc(2 * v->capacity * v->el_size);
            memcpy(n_data, v->data, v->el_size * v->capacity);
            free(v->data);
            v->data = n_data;
            v->capacity *= 2;
        }
    }
}

void vec_push(vec_t *v, void *value) {
    reallocate(v);
    memcpy(v->data + v->el_size * v->len++, value, v->el_size);
}

void vec_pop(vec_t *v, void *dest) {
    memcpy(dest, v->data + v->el_size * --v->len, v->el_size);
}

void *vec_get(vec_t *v, size_t ind) { return v->data + v->el_size * ind; }

void vec_set(vec_t *v, size_t ind, void *val) {
    memcpy(vec_get(v, ind), val, v->el_size);
}

void vec_show(vec_t *v, void (*el_show)(void *)) {
    printf("[");
    if (v->len > 0) {
        el_show(vec_get(v, 0));
        for (size_t i = 1; i < v->len; i++) {
            printf(", ");
            el_show(vec_get(v, i));
        }
    }
    printf("]");
}
