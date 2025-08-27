/*
 * uint256.c
 * Author: Vincent Paul
 * Date created: August 16, 2025
*/


#include "uint256.h"


void uint256_rshift1(uint256_t *x) {
    uint64_t carry = 0;
    for (int i = 3; i >= 0; i--) {  //MSB first
        uint64_t new_carry = x->limb[i] & 0x1ULL;
        x->limb[i] = (x->limb[i] >> 1) | (carry << 63);
        carry = new_carry;
    }
}

void uint256_lshift1(uint256_t *x) {
    uint64_t carry = 0;
    for (int i = 0; i < 4; i++) {
        uint64_t new_carry = (x->limb[i] >> 63) & 1ULL;
        x->limb[i] = (x->limb[i] << 1) | carry;
        carry = new_carry;
    }
}

void uint256_swap(uint256_t *x, uint256_t *y) {
    uint256_t temp = *x;
    *x = *y;
    *y = temp;
}   

void uint256_copy(uint256_t *x, uint256_t *y) {
    for (int i = 0; i < 4; i++) {
        x->limb[i] = y->limb[i];
    }
}

int uint256_cmp(const uint256_t *x, const uint256_t *y) {
    for (int i = 3; i >= 0; i--) {
        if (x->limb[i] < y->limb[i]) return -1;
        if (x->limb[i] > y->limb[i]) return 1;
    }
    return 0;
}

uint64_t uint256_add(const uint256_t *x, const uint256_t *y, uint256_t *res) {
    uint64_t carry = 0;
    for (int i = 0; i < 4; i++) {
        __uint128_t sum = (__uint128_t)x->limb[i] + (__uint128_t)y->limb[i] + carry;

        res->limb[i] = (uint64_t)sum;
        carry = (uint64_t)(sum >> 64);
    }
    return carry; // Hacky way of adding and returning the overflown carry
}

uint64_t uint256_sub(const uint256_t *x, const uint256_t *y, uint256_t *res) {
    uint64_t borrow = 0;
    for (int i = 0; i < 4; i++) {
        __uint128_t diff = (__uint128_t)x->limb[i] - y->limb[i] - borrow;

        res->limb[i] = (uint64_t)diff;
        borrow = (x->limb[i] < (y->limb[i] + borrow)) ? 1 : 0; //Maybe shift here 127 to the right
    } 
    return borrow;
}

void uint256_mul(const uint256_t *x, const uint256_t *y, uint512_t *T) {
    for (int i = 0; i < 8; i++) T->limb[i] = 0;
    for (int i = 0; i < 4; i++) {
        uint64_t carry = 0;
        for (int j = 0; j < 4; j++) {
            __uint128_t prod = (__uint128_t)x->limb[i] * y->limb[j] + T->limb[i + j] + carry;
            T->limb[i + j] = (uint64_t)prod;
            carry = (uint64_t)(prod >> 64);
        }
        int k = i + 4;
        while (carry && k < 8) {
            __uint128_t sum = (__uint128_t)T->limb[k] + carry;
            T->limb[k] = (uint64_t)sum;
            carry = (uint64_t)(sum >> 64);
            k++;
        }
    }
    //REDC at the end is needed, call this at mod_mul()
}