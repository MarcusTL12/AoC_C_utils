#pragma once

#include <stdlib.h>

// output: pointer to 16-byte buffer
void md5(char *output, char *input, size_t len);

// hex: output pointer to 2 * len byte buffer
// raw: input pointer to len byte buffer
void raw2hex(char *hex, char *raw, size_t len);
