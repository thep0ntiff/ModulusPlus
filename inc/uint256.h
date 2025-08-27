/*
 * uint256.h
 * Author: Vincent Paul
 * Date created: August 16, 2025
*/


#ifndef UINT256_H
#define UINT256_H

#include <stdint.h>

typedef struct {
    uint64_t limb[4];
} uint256_t;

typedef struct {
    uint64_t limb[8];
} uint512_t;

static inline int uint256_is_zero(uint256_t *x) {
    return (x->limb[0] | x->limb[1] | x->limb[2] | x->limb[3]) == 0;
}

void uint256_rshift1(uint256_t *x);
void uint256_lshift1(uint256_t *x);
void uint256_swap(uint256_t *x, uint256_t *y);
void uint256_copy(uint256_t *x, uint256_t *y);
int uint256_cmp(const uint256_t *x, const uint256_t *y);
uint64_t uint256_add(const uint256_t *x, const uint256_t *y, uint256_t *res);
uint64_t uint256_sub(const uint256_t *x, const uint256_t *y, uint256_t *res);
void uint256_mul(const uint256_t *x, const uint256_t *y, uint512_t *T);

#endif /* UINT256_H */