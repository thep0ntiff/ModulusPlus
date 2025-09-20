/*
 * montgomery.h
 * Author: Vincent Paul
 * Date created: August 10, 2025
*/


#ifndef MONTGOMERY_H
#define MONTGOMERY_H

#include "uint256.h"

typedef struct {
    uint256_t n;            //Modulus N
    uint64_t n_inv;        //n^-1 (mod 2^k)
    uint256_t r2;    //r^2 (mod 2^256)
} montgomery_ctx_t;

void montgomery_update_ctx(const uint256_t *modulus);

void to_montgomery(const uint256_t *a, uint256_t *a_mont);
void from_montgomery(const uint256_t *a_mont, uint256_t *a);
void montgomery_REDC(uint512_t *T, uint256_t *result);

#endif /* MONTGOMERY_H */
