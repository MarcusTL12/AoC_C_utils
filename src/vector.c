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

void vec_expand_zeroed(vec_t *v, size_t n) {
    size_t n_len = v->len + n;
    if (n_len > v->capacity) {
        size_t n_cap = v->capacity;

        while (n_len > n_cap) n_cap *= 2;

        void *n_data = malloc(v->el_size * n_cap);
        memcpy(n_data, v->data, v->len * v->el_size);
        free(v->data);
        v->data = n_data;
        v->capacity = n_cap;
    }
    memset(v->data + v->el_size * v->len, 0, n * v->el_size);
    v->len = n_len;
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

vec_t vec_clone(vec_t *v) {
    vec_t new_v;

    new_v.el_size = v->el_size;
    new_v.capacity = v->capacity;
    new_v.len = v->len;

    new_v.data = malloc(v->capacity * v->el_size);
    memcpy(new_v.data, v->data, v->len * v->el_size);

    return new_v;
}

void vec_copy(vec_t *d, vec_t *s) {
    if (d->el_size != s->el_size) {
        printf("Type mismatch in vector copy!\n");
        exit(0);
    }
    d->len = s->len;
    if (d->capacity < s->len) {
        size_t factor = 2;

        while (d->capacity * factor < s->len) factor *= 2;

        d->capacity *= factor;

        free(d->data);
        d->data = malloc(d->el_size * d->capacity);
    }

    memcpy(d->data, s->data, d->el_size * d->len);
}
