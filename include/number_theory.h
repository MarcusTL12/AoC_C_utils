#pragma once

#include <stdint.h>
#include <stdlib.h>

#define signum(x) x >= 0 ? x > 0 ? 1 : 0 : -1

static int64_t gcd(int64_t a, int64_t b) {
    return b != 0 ? gcd(b, a % b) : llabs(a);
}

static int64_t lcm(int64_t a, int64_t b) { return a * b / gcd(a, b); }

typedef struct {
    int64_t g, x, y;
} gcdx_t;

gcdx_t gcdx(int64_t a, int64_t b);

static int64_t invmod(int64_t a, int64_t b) { return gcdx(a, b).x; }

int64_t modmul(int64_t a, int64_t b, int64_t n);
int64_t modexp(int64_t a, int64_t b, int64_t n);
