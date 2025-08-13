/*
 * modplus.h
 * Author: Vincent Paul
 * Date created: August 6, 2025
*/


#ifndef MODPLUS_H
#define MODPLUS_H

#include <stdint.h>

typedef struct {
    uint64_t limb[4];
} uint256_t;

typedef struct {
    uint64_t limb[8];
} uint512_t;

typedef struct {
    const uint256_t a;
    const uint256_t b;  
    const uint256_t modulus;
} MParams;


void mod_add(MParams* mp, uint256_t *result);
void mod_sub(MParams* mp, uint256_t *result);
void mod_mul(MParams* mp, uint256_t *result);
void mod_exp(MParams* mp, uint256_t *result);

#endif /* MODPLUS_H */