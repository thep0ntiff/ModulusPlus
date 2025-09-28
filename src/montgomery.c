/*
 * montgomery.c
 * Author: Vincent Paul
 * Date created: August 10, 2025
*/

#include "montgomery.h"
#include "modplus.h"
#include "uint256.h"

#include <stdio.h>


static const uint64_t PRECOMP_N_INV = 0x1;        // Precomputed value of n_inv for 256 bit modulus, which will always be the case
static const uint256_t PRECOMP_R2 = { .limb = {   // Precomputed value of R2 for 256 bit modulus
    0x0000000000000003ULL,
    0xfffffffbffffffffULL,
    0xfffffffffffffffeULL,
    0x00000004fffffffdULL
} };

montgomery_ctx_t MONTGOMERY_CTX = {
    .n = {{0}},              // modulus filled later
    .n_inv = PRECOMP_N_INV,
    .r2 = PRECOMP_R2
};

void montgomery_update_ctx(const uint256_t *modulus) {
    MONTGOMERY_CTX.n = *modulus;
}


void montgomery_REDC(uint512_t *T, uint256_t *result) {
    uint64_t carry;
    for (int i = 0; i < 4; i++) {
        uint64_t m = T->limb[i] * MONTGOMERY_CTX.n_inv;
        carry = 0;

        for (int j = 0; j < 4; j++) {
            __uint128_t prod = (__uint128_t)m * MONTGOMERY_CTX.n.limb[j] + T->limb[i + j] + carry;
            T->limb[i + j] = (uint64_t)prod;
            carry = (uint64_t)(prod >> 64);
        }
        int k = i + 4;
        while (carry && k < 8) {
            __uint128_t sum = (__uint128_t)T->limb[k] + carry;
            T->limb[k] = (uint64_t)sum;
            carry = (uint64_t)(sum >> 64);
            k++;
        }
        

    }

    uint256_copy(result, (uint256_t *)&T->limb[4]);

    if (uint256_cmp(result, &MONTGOMERY_CTX.n) >= 0) {
        uint256_sub(result, &MONTGOMERY_CTX.n, result);
    }

    if (carry) {
            uint256_t carry_uint256 = {.limb = {carry, 0, 0, 0}};
            uint256_t carry_mont = {{0}};
            to_montgomery(&carry_uint256, &carry_mont);
            uint256_add(result, &carry_mont, result);
    }
    
}

void to_montgomery(const uint256_t *a, uint256_t *a_mont) {
    uint512_t T = {0};
    uint256_mul(a, &MONTGOMERY_CTX.r2, &T);
    montgomery_REDC(&T, a_mont);
}

void from_montgomery(const uint256_t *a_mont, uint256_t *a) {
    uint512_t T = {0};
    for (int i = 0; i < 4; i++) T.limb[i] = a_mont->limb[i];
    montgomery_REDC(&T, a);
}
