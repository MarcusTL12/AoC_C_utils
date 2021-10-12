#pragma once

#include <stddef.h>

typedef struct {
    size_t el_size, capacity, len;
    void *data;
} vec_t;

vec_t vec_create(size_t el_size);
void vec_free(vec_t *v);

void vec_push(vec_t *v, void *value);
void vec_pop(vec_t *v, void *dest);

void *vec_get(vec_t *v, size_t ind);
void vec_set(vec_t *v, size_t ind, void *val);

void vec_show(vec_t *v, void (*el_show)(void *));
