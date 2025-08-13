/*
 * modplus.c
 * Author: Vincent Paul
 * Date created: August 6, 2025
*/


#include "modplus.h"



static int cmp256(const uint256_t *x, const uint256_t *y) {
    for (int i = 3; i >= 0; i--) {
        if (x->limb[i] < y->limb[i]) return -1;
        if (x->limb[i] > y->limb[i]) return 1;
    }
    return 0;
}

static uint64_t add256(const uint256_t *x, const uint256_t *y, uint256_t *res) {
    uint64_t carry = 0;
    for (int i = 0; i < 4; i++) {
        __uint128_t sum = (__uint128_t)x->limb[i] + (__uint128_t)y->limb[i] + carry;

        res->limb[i] = (uint64_t)sum;
        carry = (uint64_t)(sum >> 64);
    }
    return carry;
}

static uint64_t sub256(const uint256_t *x, const uint256_t *y, uint256_t *res) {
    uint64_t borrow = 0;
    for (int i = 0; i < 4; i++) {
        __uint128_t diff = (__uint128_t)x->limb[i] - y->limb[i] - borrow;

        res->limb[i] = (uint64_t)diff;
        borrow = (diff >> 127) & 0x1;
    }
    return borrow;
}

void mod_add(MParams* mp, uint256_t *result) {
    uint64_t carry = add256(&mp->a, &mp->b, result);
    if (carry || cmp256(result, &mp->modulus) >= 0) {
        sub256(result, &mp->modulus, result);
    }
}

void mod_sub(MParams *mp, uint256_t *result) {
    if (sub256(&mp->a, &mp->b, result)) {
        add256(result, &mp->modulus, result);
    }
}