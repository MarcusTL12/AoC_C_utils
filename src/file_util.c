#include <stdlib.h>
#include <stdio.h>

#include <sys/stat.h>
#include <sys/types.h>

size_t file_size(char *filename) {
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

char *file_read_full(char *filename) {
    size_t s = file_size(filename);
    char *buffer = malloc(s + 1);
    
    FILE *fp = fopen(filename, "rb");
    fgets(buffer, s + 1, fp);
    fclose(fp);

    return buffer;
}
