#include "number_theory.h"

gcdx_t gcdx(int64_t a, int64_t b) {
    if (!b) {
        return (gcdx_t){llabs(a), signum(a), 0};
    }

    lldiv_t ld = lldiv(a, b);

    gcdx_t g = gcdx(b, ld.rem);
    return (gcdx_t){g.g, g.y, g.x - g.y * ld.quot};
}

int64_t modmul(int64_t a, int64_t b, int64_t n) {
    int64_t acc = 0;

    if (b < 0) {
        b += n;
    }

    while (b) {
        acc = (acc + (b & 1 ? a : 0)) % n;
        a = (a + a) % n;
        b >>= 1;
    }

    return acc;
}

int64_t modexp(int64_t a, int64_t b, int64_t n) {
    int64_t acc = 1;

    while (b) {
        acc = modmul(acc, (b & 1 ? a : 1), n);
        a = modmul(a, a, n);
        b >>= 1;
    }

    return acc;
}
