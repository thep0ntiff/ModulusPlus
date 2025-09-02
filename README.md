# ModulusPlus
A high-performance C library for 256-bit unsigned integer arithmetic and modular operations, optimized for cryptographic applications.

## Overview

ModulusPlus provides efficient implementations of large integer arithmetic operations specifically designed for cryptographic use cases. The library supports 256-bit unsigned integers with optimized modular arithmetic operations using Montgomery reduction for enhanced performance.

## Features

- **256-bit Unsigned Integer Support**: Complete arithmetic operations for 256-bit integers
- **Montgomery Multiplication**: Optimized modular multiplication using Montgomery reduction
- **Modular Arithmetic**: Addition, subtraction, multiplication, and division in modular arithmetic
- **Bit Operations**: Bit testing, setting, and manipulation functions
- **GCD Computation**: Stein's algorithm for greatest common divisor calculation
- **Memory Efficient**: Uses limb-based representation for optimal memory usage

## Core Components

### 1. 256-bit Integer Operations (`uint256.h/c`)
- Basic arithmetic: addition, subtraction, multiplication
- Bit manipulation: shift operations, bit testing/setting
- Comparison operations and utility functions
- GCD computation using Stein's algorithm

### 2. Montgomery Arithmetic (`montgomery.h/c`)
- Montgomery context initialization
- Conversion to/from Montgomery form
- Montgomery reduction (REDC) algorithm
- Optimized for modular multiplication

### 3. Modular Operations (`modplus.h/c`)
- Modular addition and subtraction
- Modular multiplication using Montgomery arithmetic
- Modular division with quotient and remainder
- Modular inverse computation (in development)

## Data Structures

```c
// 256-bit unsigned integer
typedef struct {
    uint64_t limb[4];
} uint256_t;

// 512-bit unsigned integer (for intermediate calculations)
typedef struct {
    uint64_t limb[8];
} uint512_t;

// Montgomery arithmetic context
typedef struct {
    uint256_t n;            // Modulus N
    uint64_t n_inv;         // n^-1 (mod 2^64)
    uint256_t r_squared;    // r^2 (mod 2^256)
} montgomery_ctx_t;

// Modular operation parameters
typedef struct {
    uint256_t a;
    uint256_t b;
    uint256_t modulus;
} MParams;
```

## Building

### Prerequisites
- GCC or Clang with C99 support
- Make (optional, for build automation)

```bash
make
```

## Usage Examples

### Basic 256-bit Operations
```c
#include "uint256.h"

uint256_t a = {{0x123456789ABCDEF0, 0xFEDCBA0987654321, 0, 0}};
uint256_t b = {{0x1111111111111111, 0x2222222222222222, 0, 0}};
uint256_t result;

// Addition
uint64_t carry = uint256_add(&a, &b, &result);

// Comparison
int cmp = uint256_cmp(&a, &b);  // -1, 0, or 1

// Bit operations
int bit_set = uint256_test_bit(&a, 5);
uint256_set_bit(&result, 10);
```

### Modular Arithmetic
```c
#include "modplus.h"
#include "montgomery.h"

// Initialize parameters
MParams mp = {
    .a = {{0x123456789ABCDEF0, 0, 0, 0}},
    .b = {{0x987654321FEDCBA0, 0, 0, 0}},
    .modulus = {{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}}
};

uint256_t result;

// Modular addition
mod_add(&mp, &result);

// Modular multiplication (requires Montgomery context)
montgomery_ctx_t ctx;
if (montgomery_ctx_init(&ctx, &mp.modulus) == 0) {
    mod_mul(&mp, &ctx, &result);
}
```

### GCD Calculation
```c
#include "uint256.h"

uint256_t a = {{12345, 0, 0, 0}};
uint256_t b = {{67890, 0, 0, 0}};

uint256_t gcd_result = gcd_std(a, b);
```

## Performance Considerations

- **Montgomery Multiplication**: The library uses Montgomery reduction for efficient modular multiplication, particularly beneficial when performing multiple operations with the same modulus
- **Limb-based Representation**: Numbers are stored as arrays of 64-bit limbs for optimal performance on 64-bit systems
- **Carry Handling**: Efficient carry propagation using 128-bit intermediate calculations
- **Memory Layout**: Structures are designed for cache-friendly access patterns

## Current Development Status

### Completed Features
- ✅ 256-bit integer arithmetic
- ✅ Montgomery multiplication context
- ✅ Basic modular operations
- ✅ GCD computation
- ✅ Bit manipulation operations

### In Development
- 🔧 Extended GCD algorithm (`gcd_ext` function commented out due to infinite loop issue)
- 🔧 Modular inverse computation
- 🔧 Additional optimization passes

## Technical Notes

### Montgomery Arithmetic Requirements
- The modulus must be odd for Montgomery arithmetic to work correctly
- The library automatically validates this requirement during context initialization

### Precision and Overflow
- All operations handle carry/borrow propagation correctly
- 512-bit intermediate results are used for multiplication to prevent overflow
- Functions return appropriate error codes or carry flags

## Contributing

When contributing to ModulusPlus:

1. Follow the existing code style and naming conventions
2. Add appropriate error checking and validation
3. Include performance considerations in your implementations
4. Test thoroughly with edge cases (zero values, maximum values, etc.)
5. Document any new functions or significant changes
