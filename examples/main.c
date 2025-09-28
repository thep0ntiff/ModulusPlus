// main.c
#include "modplus.h"
#include "montgomery.h"

#include <stdio.h>
#include <stdint.h>

//Little endian

const uint256_t modulus = { .limb = { 
    0xffffffffffffffffULL,
    0x00000000ffffffffULL,
    0x0000000000000000ULL,
    0xffffffff00000001ULL
} };

const uint256_t A = { .limb = {
    0xfffffffffffffffcULL,
    0x00000000ffffffffULL,
    0x0000000000000000ULL,
    0xffffffff00000001ULL
} };

const uint256_t B = { .limb = {
    0x3bce3c3e27d2604bULL,
    0x651d06b0cc53b0f6ULL,
    0xb3ebbd55769886bcULL,
    0x5ac635d8aa3a93e7ULL
} };


void print_uint256_hex(const uint256_t *num) {
    for (int i = 3; i >= 0; i--) {
        printf("%016llx", (unsigned long long)num->limb[i]);
    }
    printf("\n");
}




int main() {
    
    printf("Testing secp256r1 modular arithmetic\n");
    uint256_t add_result = {0};
    mod_add(&A, &B, &modulus, &add_result);
    print_uint256_hex(&add_result);

    uint256_t sub_result = {0};
    mod_sub(&A, &B, &modulus, &sub_result);
    print_uint256_hex(&sub_result);

    uint256_t mul_result = {0};
    //montgomery_ctx_init(&montctx, &modulus);  
    mod_mul(&A, &B, &modulus, &mul_result);
    print_uint256_hex(&mul_result);
    
    uint256_t div_result = {{0}};
    uint256_t remainder = {{0}};
    uint256_div(&A, &B, &remainder, &div_result);
    printf("Div Result: ");
    print_uint256_hex(&div_result);
    printf("remainder: ");
    print_uint256_hex(&remainder);
    
    uint256_t exp_result = {0};
    mod_exp(&A, &B, &modulus, &exp_result);
    print_uint256_hex(&exp_result);
    
    
    uint256_t inv_result = {0};
    mod_inv(&A, &modulus, &inv_result);
    print_uint256_hex(&inv_result);

    return 0;
}
