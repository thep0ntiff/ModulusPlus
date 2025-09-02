/*
 * modplus.h
 * Author: Vincent Paul
 * Date created: August 6, 2025
*/


#ifndef MODPLUS_H
#define MODPLUS_H

#include <stdint.h>
#include "uint256.h"
#include "montgomery.h"



// TODO: Add a struct API to enforce encapsulation
typedef struct {
    uint256_t a;
    uint256_t b;  
    uint256_t modulus;
} MParams;

void mod_add(MParams* mp, uint256_t *result);
void mod_sub(MParams* mp, uint256_t *result);
void mod_mul(MParams* mp, montgomery_ctx_t *ctx, uint256_t *result);
void mod_div(MParams* mp, uint256_t *remainder, uint256_t *result);
void mod_inv(const montgomery_ctx_t *ctx, const uint256_t *a_mont, uint256_t *result);


#endif /* MODPLUS_H */
