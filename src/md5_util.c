#include <openssl/evp.h>

static void md5(unsigned char *output, unsigned char *input, unsigned int len) {
    EVP_MD_CTX *mdctx;
    unsigned int md5_digest_len = EVP_MD_size(EVP_md5());

    // MD5_Init
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);

    // MD5_Update
    EVP_DigestUpdate(mdctx, input, len);

    // MD5_Final
    EVP_DigestFinal_ex(mdctx, output, &md5_digest_len);
    EVP_MD_CTX_free(mdctx);
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
