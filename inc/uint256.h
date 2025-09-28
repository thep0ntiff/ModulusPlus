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



void uint256_rshift1(uint256_t *x);
void uint256_lshift1(uint256_t *x);

void uint256_swap(uint256_t *x, uint256_t *y);
void uint256_clear(uint256_t *x);
void uint256_copy(uint256_t *x, uint256_t *y);
int uint256_cmp(const uint256_t *x, const uint256_t *y);
int uint256_is_even(const uint256_t *x);
int uint256_is_zero(const uint256_t *x);

int uint256_test_bit(const uint256_t *a, int bit_index);
void uint256_set_bit(uint256_t *a, int bit_index);

uint256_t gcd_std(uint256_t a, uint256_t b);

uint64_t uint256_add(const uint256_t *x, const uint256_t *y, uint256_t *res);
uint64_t uint256_sub(const uint256_t *x, const uint256_t *y, uint256_t *res);
void uint256_mul(const uint256_t *x, const uint256_t *y, uint512_t *T);
void uint256_div(const uint256_t *x, const uint256_t *y, uint256_t *remainder, uint256_t *result);

#endif /* UINT256_H */
