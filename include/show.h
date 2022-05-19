#pragma once

#include <stdint.h>
#include <stdio.h>

static void show_int(void *i) { printf("%i", *(int *)i); }
static void show_int64(void *i) { printf("%ld", *(int64_t *)i); }

static void show_int64_arr(int64_t *v, size_t n) {
    printf("[%ld", *v);
    for (size_t i = 1; i < n; i++) {
        printf(", %ld", v[i]);
    }
    printf("]");
}

static void show_arr(void *arr, size_t n, size_t el_size,
                     void (*el_show)(void *)) {
    printf("[");
    el_show(arr);
    for (size_t i = 1; i < n; i++) {
        printf(", ");
        el_show(arr + el_size * i);
    }
    printf("]");
}
