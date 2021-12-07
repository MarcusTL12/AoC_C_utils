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
