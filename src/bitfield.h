#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

void bitfield_set(uint64_t *bitfield, size_t index, bool val);
bool bitfield_get(uint64_t *bitfield, size_t index);
