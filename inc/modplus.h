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

void mod_add(const uint256_t *a, const uint256_t *b, const uint256_t *modulus, uint256_t *result);
void mod_sub(const uint256_t *a, const uint256_t *b, const uint256_t *modulus, uint256_t *result);
void mod_mul(const uint256_t *a, const uint256_t *b, const uint256_t *modulus, uint256_t *result);
void mod_exp(const uint256_t *base, const uint256_t *exp, const uint256_t *modulus, uint256_t *result);
void mod_inv(const uint256_t *base, const uint256_t *modulus, uint256_t *result);

#endif /* MODPLUS_H */
