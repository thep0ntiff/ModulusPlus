/*
 * modplus.c
 * Author: Vincent Paul
 * Date created: August 6, 2025
*/


#include "modplus.h"
#include "uint256.h"
#include "montgomery.h"

#include <stdio.h>
#include <string.h>

void mod_add(MParams *mp, uint256_t *result) {
    uint64_t carry = uint256_add(&mp->a, &mp->b, result);
    if (carry || uint256_cmp(result, &mp->modulus) >= 0) {
        uint256_sub(result, &mp->modulus, result);
    }
}

void mod_sub(MParams *mp, uint256_t *result) {
    if (uint256_sub(&mp->a, &mp->b, result)) {
        uint256_add(result, &mp->modulus, result);
    }
}

void mod_mul(MParams *mp, montgomery_ctx_t *ctx, uint256_t *result) {
    uint512_t T = {0};
    uint256_t a_mont, b_mont, temp_result;

    to_montgomery(ctx, &mp->a, &a_mont);
    to_montgomery(ctx, &mp->b, &b_mont);

    uint256_mul(&a_mont, &b_mont, &T);

    montgomery_REDC(ctx, &T, &temp_result);
    from_montgomery(ctx, &temp_result, result);
}

void mod_div(MParams *mp, uint256_t *remainder, uint256_t *result) {
    if (uint256_is_zero(&mp->b)) {
        fprintf(stderr, "Error: Subtraction by 0 is impossible.");
        return;
    }
    memset(result->limb, 0, sizeof(result->limb));
    memset(remainder->limb, 0, sizeof(remainder->limb));

    for (int i = 255; i >= 0; i--) {
        uint256_lshift1(remainder);

        if (uint256_test_bit(&mp->a, i)) {
            remainder->limb[0] |= 0x1ULL;
        }
        if (uint256_cmp(remainder, &mp->b) >= 0) {
            uint256_sub(remainder, &mp->b, remainder);
            uint256_set_bit(result, i);
        }
    }
}

    


void mod_inv(const montgomery_ctx_t *ctx, const uint256_t *a_mont, uint256_t *result) {
    
}


