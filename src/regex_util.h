#pragma once

#include <stddef.h>
#include <stdbool.h>

void *regex_compile(char *reg_str);
void regex_free(void *reg);

void regex_match(void *reg, char *str, size_t *captures);

typedef struct {
    void *reg;
    void *match_data;
    char *str;
    size_t offset, remaining;
} regex_iter;

regex_iter regex_iter_create(void *reg, char *str);
void regex_iter_update(regex_iter *it, char *str, size_t len);
void regex_iter_free(regex_iter it);
bool regex_next_match(regex_iter *it, size_t *captures);
