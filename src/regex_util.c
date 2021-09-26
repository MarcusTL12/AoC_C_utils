#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>
#include <stdbool.h>

#include "regex_util.h"

void *regex_compile(char *reg_str) {
    size_t error_offset;
    int errcode;

    return pcre2_compile((const unsigned char *)reg_str, -1, 0, &errcode,
                         &error_offset, NULL);
}

void regex_free(void *reg) { pcre2_code_free(reg); }

void regex_match(void *reg, char *str, size_t *captures) {
    pcre2_match_data *match_data =
        pcre2_match_data_create_from_pattern(reg, NULL);

    int rc = pcre2_match(reg, (const unsigned char *)str, -1, 0, 0, match_data,
                         NULL);

    if (rc <= 0) {
        pcre2_match_data_free(match_data);
        *captures = -1;
    } else {
        size_t *off_vec = pcre2_get_ovector_pointer(match_data);

        for (int i = 0; i < rc; i++) {
            captures[2 * i] = off_vec[2 * i];
            captures[2 * i + 1] = off_vec[2 * i + 1] - off_vec[2 * i];
        }

        pcre2_match_data_free(match_data);
    }
}

regex_iter regex_iter_create(void *reg, char *str) {
    pcre2_match_data *match_data =
        pcre2_match_data_create_from_pattern(reg, NULL);

    regex_iter it;

    it.reg = reg;
    it.match_data = match_data;
    it.str = str;
    it.offset = 0;

    return it;
}

void regex_iter_free(regex_iter it) { pcre2_match_data_free(it.match_data); }

bool regex_next_match(regex_iter *it, size_t *captures) {
    int rc = pcre2_match(it->reg, (const unsigned char *)it->str, -1, 0, 0,
                         it->match_data, NULL);
    
    if (rc <= 0) {
        return false;
    } else {
        size_t *off_vec = pcre2_get_ovector_pointer(it->match_data);

        for (int i = 0; i < rc; i++) {
            captures[2 * i] = off_vec[2 * i] + it->offset;
            captures[2 * i + 1] = off_vec[2 * i + 1] - off_vec[2 * i];
        }

        size_t shift = *off_vec + captures[1];
        it->str += shift;
        it->offset += shift;

        return true;
    }
}
