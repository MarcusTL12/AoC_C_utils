#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "iterator.h"

size_t file_size(char *filename) {
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

char *file_read_full(char *filename) {
    size_t s = file_size(filename);
    char *buffer = malloc(s + 1);

    FILE *fp = fopen(filename, "rb");
    fread(buffer, 1, s + 1, fp);
    fclose(fp);

    return buffer;
}

// typedef struct {
//     FILE *fp;
// } buf_char_iter_state;

// static bool file_buf_char_iter_next(void *_state, void *_dest) {
//     buf_char_iter_state *state = _state;
//     char *dest = _dest;
//     return false;
// }

// static void file_buf_char_iter_free(void *_state) {
//     buf_char_iter_state *state = _state;
//     fclose(state->fp);
//     free(state);
// }

// iterator file_buf_char_iter(char *filename) {
//     iterator it;
//     it.state = malloc(sizeof(buf_char_iter_state));
//     it.next = file_buf_char_iter_next;
//     it.free = file_buf_char_iter_free;

//     return it;
// }
