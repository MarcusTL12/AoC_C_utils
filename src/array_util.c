#include "array_util.h"

#include <limits.h>

minmax_t minmax(int64_t *array, size_t len) {
    minmax_t mm;
    mm.min = INT64_MAX;
    mm.max = INT64_MIN;

    for (size_t i = 0; i < len; i++) {
        mm.min = array[i] < mm.min ? array[i] : mm.min;
        mm.max = array[i] > mm.max ? array[i] : mm.max;
    }

    return mm;
}

minmax_t minmax_inds(int64_t *array, size_t len) {
    minmax_t mm;
    mm.min = 0;
    mm.max = 0;

    for (size_t i = 0; i < len; i++) {
        mm.min = array[i] < array[mm.min] ? i : mm.min;
        mm.max = array[i] > array[mm.max] ? i : mm.max;
    }

    return mm;
}

void memswap(void *a, void *b, size_t n) {
    for (size_t i = 0; i < n; i++) {
        char tmp = ((char *)a)[i];
        ((char *)a)[i] = ((char *)b)[i];
        ((char *)b)[i] = tmp;
    }
}
