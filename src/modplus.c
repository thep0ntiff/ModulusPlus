/*
 * modplus.c
 * Author: Vincent Paul
 * Date created: August 6, 2025
*/


#include "modplus.h"
#include "uint256.h"
#include "montgomery.h"

#include <stdio.h>

void mod_add(const uint256_t *a, const uint256_t *b, const uint256_t *modulus, uint256_t *result) {
    uint64_t carry = uint256_add(a, b, result);
    if (carry || uint256_cmp(result, modulus) >= 0) {
        uint256_sub(result, modulus, result);
    }
}

void mod_sub(const uint256_t *a, const uint256_t *b, const uint256_t *modulus, uint256_t *result) {
    if (uint256_sub(a, b, result)) {
        uint256_add(result, modulus, result);
    }
}

void mod_mul(const uint256_t *a, const uint256_t *b, const uint256_t *modulus, uint256_t *result) {
    
    uint512_t T = {0};
    uint256_t a_mont, b_mont, temp_result;

    montgomery_update_ctx(modulus);

    to_montgomery(a, &a_mont);
    to_montgomery(b, &b_mont);

    uint256_mul(&a_mont, &b_mont, &T);

    montgomery_REDC(&T, &temp_result);
    from_montgomery(&temp_result, result);
}

void mod_exp(const uint256_t *base, const uint256_t *exp, const uint256_t *modulus, uint256_t *result) {
    uint256_t res_mont, base_mont;
    uint256_t one = {{1, 0, 0, 0}};
    
    montgomery_update_ctx(modulus);

    to_montgomery(&one, &res_mont);
    to_montgomery(base, &base_mont);
    
    for (int i = 255; i >= 0; i--) {
        uint512_t T;
        uint256_t temp;
        uint256_mul(&res_mont, &res_mont, &T);
        montgomery_REDC(&T, &temp);
        res_mont = temp;
        
        if (uint256_test_bit(exp, i)) {
            uint256_mul(&res_mont, &base_mont, &T);
            montgomery_REDC(&T, &temp);
            res_mont = temp;
        }
    }
    
    from_montgomery(&res_mont, result);
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

    mod_exp(base, &exp, modulus, result);
    
}

