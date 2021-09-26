#include <stdio.h>

#include <openssl/md5.h>

void md5(char *output, const char *input, size_t len) {
    MD5_CTX c;
    unsigned char buf[MD5_DIGEST_LENGTH];

    MD5_Init(&c);
    MD5_Update(&c, input, len);
    MD5_Final(buf, &c);

    char *p = output;
    for (int i = 0; i < 16; i++) {
        sprintf(p, "%02x", buf[i]);
        p += 2;
    }
}
