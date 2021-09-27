#include <openssl/md5.h>

void md5(char *output, const char *input, size_t len) {
    MD5_CTX c;

    MD5_Init(&c);
    MD5_Update(&c, input, len);
    MD5_Final((unsigned char *)output, &c);
}

void raw2hex(char *hex, const char *raw, size_t len) {
    static const char symbols[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    for (int i = 0, j = 0; i < len; i++) {
        int hi = (raw[i] >> 4) & 0xf;
        int lo = raw[i] & 0xf;

        hex[j++] = symbols[hi];
        hex[j++] = symbols[lo];
    }
}
