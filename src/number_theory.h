#pragma once

#include <stdint.h>

static int64_t gcd(int64_t a, int64_t b) {
    return b != 0 ? gcd(b, a % b) : labs(a);
}
