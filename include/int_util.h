#pragma once

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

static int64_t parse_push_int64(char **c) {
    int64_t ans = atoll(*c);
    while (isdigit(**c)) (*c)++;
    return ans;
}
