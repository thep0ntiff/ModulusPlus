/*
 * uint256.c
 * Author: Vincent Paul
 * Date created: August 16, 2025
*/


#include "uint256.h"

#include <stdio.h>
#include <string.h>

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

void uint256_clear(uint256_t *x) {
    memset(x->limb, 0, sizeof(x->limb));
}

void uint256_copy(uint256_t *x, uint256_t *y) {
    for (int i = 0; i < 4; i++) {
        x->limb[i] = y->limb[i];
    }
}

uint256_t gcd_std(uint256_t a, uint256_t b) {
    //Stein's Algorithm
    if (uint256_is_zero(&a)) return b;
    if (uint256_is_zero(&b)) return a;
    int k = 0;
    while (uint256_is_even(&a) && uint256_is_even(&b)) {
        k++;
        uint256_rshift1(&a);
        uint256_rshift1(&b);
    }
    while (!uint256_is_zero(&a) && !uint256_is_zero(&b)) {
        while((a.limb[0] & 0x1ULL) == 0) uint256_rshift1(&a);
        while((b.limb[0] & 0x1ULL) == 0) uint256_rshift1(&b);
        
        if (uint256_cmp(&a, &b) == 1) {
            uint256_swap(&a, &b); // To make sure b >= a
        }
        
        if (uint256_sub(&b, &a, &b) > 0) {
            fprintf(stderr, "Error: Subtraction underflowed in gcd().\nPlease check if you have submitted your numbers in the correct format.\n");
            break;
        }
    }   

    uint256_t result = uint256_is_zero(&a) ? b : a;                                                                 

    for (int i = 0; i < k; i++) {
        uint256_lshift1(&result);
    }

    return result;

}


int uint256_test_bit(const uint256_t *a, int bit_index) {
    if ((unsigned)bit_index >= 256) return 1;
    int limb = bit_index / 64;
    int offset = bit_index % 64;
    return (a->limb[limb] >> offset) & 0x1ULL;
}

void uint256_set_bit(uint256_t *a, int bit_index) {
    if ((unsigned)bit_index >= 256) return;
    int limb = bit_index / 64;
    int offset = bit_index % 64;
    a->limb[limb] |= (0x1ULL << offset);
}

int uint256_cmp(const uint256_t *x, const uint256_t *y) {
    for (int i = 3; i >= 0; i--) {
        if (x->limb[i] < y->limb[i]) return -1;
        if (x->limb[i] > y->limb[i]) return 1;
    }
    return 0;
}

int uint256_is_even(const uint256_t *x) {
    return !(x->limb[0] & 0x1ULL);
}

int uint256_is_zero(const uint256_t *x) {
    return (x->limb[0] == 0 && x->limb[1] == 0 && x->limb[2] == 0 && x->limb[3] == 0);
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
        __uint128_t xi = x->limb[i];
        __uint128_t yi = y->limb[i];
        __uint128_t diff = xi - yi - borrow;

        res->limb[i] = (uint64_t)diff;
        borrow = (diff >> 64) ? 1 : 0; //Maybe shift here 127 to the right
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
}

void uint256_div(const uint256_t *x, const uint256_t *y, uint256_t *remainder, uint256_t *result) {
    if (uint256_is_zero(y)) {
        fprintf(stderr, "Error: division by 0 is impossible.");
        return;
    }
    
    uint256_clear(remainder);
    uint256_clear(result);

    for (int i = 255; i >= 0; i--) {
        uint256_lshift1(remainder);

        if (uint256_test_bit(x, i)) {
            remainder->limb[0] |= 0x1ULL;
        }
        if (uint256_cmp(remainder, y) >= 0) {
            uint256_sub(remainder, y, remainder);
            uint256_set_bit(result, i);
        }
    }
}
