#pragma once

#include <stddef.h>

#include "iterator.h"

iterator str_split_iter(char *str, char delim, bool terminated,
                        size_t len_or_terminator, bool get_len);

void str_split_iter_refresh(iterator it, char *nstr, size_t nlen);

typedef struct {
    char *start;
    size_t len;
} str_t;
