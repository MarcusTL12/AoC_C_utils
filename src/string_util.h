#pragma once

#include <stddef.h>

#include "iterator.h"

iterator str_split_iter(char *str, char delim, bool terminated,
                        size_t len_or_terminator);

typedef struct {
    char *start;
    size_t len;
} str_t;
