#pragma once

#include <stdbool.h>
#include <stddef.h>

bool next_permstate(size_t *state, size_t n);
void get_perm(size_t *perm, size_t *state, size_t n);
