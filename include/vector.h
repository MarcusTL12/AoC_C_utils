#pragma once

#include <stddef.h>

typedef struct {
    size_t el_size, capacity, len;
    void *data;
} vec_t;

vec_t vec_create(size_t el_size);
void vec_free(vec_t *v);
void vec_clear(vec_t *v);

void vec_push(vec_t *v, void *value);
void vec_pop(vec_t *v, void *dest);

// Push n values of zeroed memory
void vec_expand_zeroed(vec_t *v, size_t n);

void *vec_get(vec_t *v, size_t ind);
void vec_set(vec_t *v, size_t ind, void *val);

void vec_show(vec_t *v, void (*el_show)(void *));

vec_t vec_clone(vec_t *v);
void vec_copy(vec_t *d, vec_t *s);
