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

void mod_mul(MParams *mp, uint256_t *result) {
    
    uint512_t T = {0};
    uint256_t a_mont, b_mont, temp_result;

    montgomery_update_ctx(&mp->modulus);

    to_montgomery(&mp->a, &a_mont);
    to_montgomery(&mp->b, &b_mont);

    uint256_mul(&a_mont, &b_mont, &T);

    montgomery_REDC(&T, &temp_result);
    from_montgomery(&temp_result, result);
}

void mod_div(MParams *mp, uint256_t *remainder, uint256_t *result) {
    if (uint256_is_zero(&mp->b)) {
        fprintf(stderr, "Error: division by 0 is impossible.");
        return;
    }
        
    uint256_clear(result);
    uint256_clear(remainder);

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


void mod_exp(MParams *mp, uint256_t *result) {
    uint256_t res, base;
    uint256_t one = {{1, 0, 0, 0}};
    
    montgomery_update_ctx(&mp->modulus);

    to_montgomery(&one, &res);
    to_montgomery(&mp->a, &base);
    
    for (int i = 255; i >= 0; i--) {
        uint512_t T;
        uint256_t temp;
        uint256_mul(&res, &res, &T);
        montgomery_REDC(&T, &temp);
        res = temp;
        
        if (uint256_test_bit(&mp->b, i)) {
            uint256_mul(&res, &base, &T);
            montgomery_REDC(&T, &temp);
            res = temp;
        }
    }
    
    from_montgomery(&res, result);
}

 
void mod_inv(const uint256_t *base, const uint256_t *modulus, uint256_t *result) {
    uint256_t gcd = gcd_std(*base, *modulus);
    if (gcd.limb[0] != 1 || gcd.limb[1] != 0 || gcd.limb[2] != 0 || gcd.limb[3] != 0) {
        fprintf(stderr, "Error: Your modulus must be prime for Fermat's inversion.\n");
        return;
    }
    // a^p-2 = a^-1 (mod p)
    uint256_t two = {{2, 0, 0, 0}};
    uint256_t exp;
    uint256_sub(modulus, &two, &exp);
    MParams inv = {
        .a = *base,
        .b = exp,
        .modulus = *modulus
    };

    mod_exp(&inv, result);
    
}


