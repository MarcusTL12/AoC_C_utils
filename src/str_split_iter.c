#include <stdlib.h>

#include "string_util.h"

typedef struct {
    char *str, delim, terminator, *end;
} it_state;

iterator str_split_iter(char *str, char delim, bool terminated,
                        size_t len_or_terminator) {
    iterator it;
    it.next = it_next;
    it.free = free;

    it_state *state = malloc(sizeof(it_state));
    it.state = state;

    state->str = str;
    state->delim = delim;
    if (terminated) {
        state->terminator = len_or_terminator;
        state->end = NULL;
    } else {
        state->end = str + len_or_terminator;
    }

    return it;
}

static void it_next(void *_state, void *_dest) {
    it_state *state = _state;
    str_t *dest = _dest;

    while (*state->str == state->delim) state->str++;
    dest->start = state->str;

    dest->len = 0;
    if (state->end) {
        while (*state->str != state->delim && state->str != state->end) {
            state->str++;
            dest->len++;
        }
    } else {
        while (*state->str != state->delim &&
               *state->str != state->terminator) {
            state->str++;
            dest->len++;
        }
    }
}
