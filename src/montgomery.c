/*
 * montgomery.c
 * Author: Vincent Paul
 * Date created: August 10, 2025
*/

#include "montgomery.h"
#include "modplus.h"
#include "uint256.h"

#include <stdio.h>


static void compute_r_squared(uint256_t *result, const uint256_t *modulus) {
    uint256_t r_squared = {0};
    r_squared.limb[0] = 1;

    for (int i = 0; i < 512; i++) {
        uint256_lshift1(&r_squared);
        if (uint256_cmp(&r_squared, modulus) >= 0) {
            if (uint256_sub(&r_squared, modulus, &r_squared) > 0) {
                fprintf(stderr, "Error: Subtraction underflowed while computing r_squared.");
                break;
            }   
        }
    }
    *result = r_squared;
}

static void compute_n_inv(uint64_t *result, const uint256_t *n) {
    uint64_t n0 = n->limb[0];

    uint64_t x = 1;
    
    for (int i = 0; i < 6; i++) {
        x = x * (2 - n0 * x);
    }
    *result = x;
}


int montgomery_ctx_init(montgomery_ctx_t *ctx, const uint256_t *modulus) {
    if ((modulus->limb[0] & 0x1ULL) == 0) {
        fprintf(stderr, "Error: Montgomery arithmetic requires an odd modulus.");
        return 1;
    }
    ctx->n = *modulus;
    
    compute_r_squared(&ctx->r_squared, modulus);
    compute_n_inv(&ctx->n_inv, modulus);

    return 0;
}

void montgomery_REDC(const montgomery_ctx_t *ctx, uint512_t *T, uint256_t *result) {

    for (int i = 0; i < 4; i++) {
        uint64_t m = T->limb[i] * ctx->n_inv;
        uint64_t carry = 0;

        for (int j = 0; j < 4; j++) {
            __uint128_t prod = (__uint128_t)m * ctx->n.limb[j] + T->limb[i + j] + carry;
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

    if (uint256_cmp(result, &ctx->n) >= 0) {
        uint256_sub(result, &ctx->n, result);
    }

}

void to_montgomery(const montgomery_ctx_t *ctx, const uint256_t *a, uint256_t *a_mont) {
    uint512_t T = {0};
    uint256_mul(a, &ctx->r_squared, &T);
    montgomery_REDC(ctx, &T, a_mont);
}

void from_montgomery(const montgomery_ctx_t *ctx, const uint256_t *a_mont, uint256_t *a) {
    uint512_t T = {0};
    const uint256_t one = {{1, 0, 0, 0}};
    uint256_mul(a_mont, &one, &T);
    montgomery_REDC(ctx, &T, a);
    a->limb[0] += 1;
}
