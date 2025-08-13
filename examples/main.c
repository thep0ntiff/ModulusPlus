// main.cpp
#include "modplus.h"
#include <stdio.h>
#include <stdint.h>

const uint256_t modulus = { .limb = { 
    0xffffffffffffffffULL,
    0x00000000ffffffffULL,
    0x0000000000000000ULL,
    0xffffffff00000001ULL
} };

const uint256_t A = { .limb = {
    0xfffffffffffffffcULL,
    0x00000000ffffffffULL,
    0x0000000000000000ULL,
    0xffffffff00000001ULL
} };

const uint256_t B = { .limb = {
    0x3bce3c3e27d2604bULL,
    0x651d06b0cc53b0f6ULL,
    0xb3ebbd55769886bcULL,
    0x5ac635d8aa3a93e7ULL
} };

MParams mp = {
    .a = A,
    .b = B,
    .modulus = modulus
};
/*
const uint64_t G[2][4] = {
    {0xf4a13945d898c296ULL, 0x77037d812deb33a0ULL, 0xf8bce6e563a440f2ULL, 0x6b17d1f2e12c4247ULL},
    {0xcbb6406837bf51f5ULL, 0x2bce33576b315eceULL, 0x8ee7eb4a7c0f9e16ULL, 0x4fe342e2fe1a7f9bULL}
};

const uint64_t n[4] = {
    0xf3b9cac2fc632551ULL,
    0xbce6faada7179e84ULL,
    0xffffffffffffffffULL,
    0xffffffff00000000ULL
};
*/

void print_uint256_hex(const uint256_t *num) {
    // Print from most significant limb (3) to least (0)
    for (int i = 3; i >= 0; i--) {
        printf("%016llx", (unsigned long long)num->limb[i]);
    }
    printf("\n");
}

int main() {
    printf("Testing secp256r1 modular arithmetic\n");
    uint256_t add_result = {0};
    mod_add(&mp, &add_result);
    print_uint256_hex(&add_result);

    uint256_t sub_result = {0};
    mod_sub(&mp, &sub_result);
    print_uint256_hex(&sub_result);
    return 0;
}