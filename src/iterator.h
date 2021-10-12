#pragma once
#include <stdbool.h>

typedef struct {
    void *state;
    bool (*next)(void *, void *);
    void (*free)(void *);
} iterator;

static bool iter_next(iterator it, void *dest) {
    return it.next(it.state, dest);
}

static void iter_free(iterator it) { it.free(it.state); }
