#pragma once

#include <stdint.h>
#include <stdlib.h>

static int64_t gcd(int64_t a, int64_t b) {
    return b != 0 ? gcd(b, a % b) : labs(a);
}

static int64_t lcm(int64_t a, int64_t b) { return a * b / gcd(a, b); }
