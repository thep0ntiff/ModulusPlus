# ModulusPlus
A high-performance C library for 256-bit unsigned integer arithmetic and modular operations, optimized for cryptographic applications.

## Overview

ModulusPlus provides efficient implementations of large integer arithmetic operations specifically designed for cryptographic use cases. The library supports 256-bit unsigned integers with optimized modular arithmetic operations using Montgomery reduction for enhanced performance.

## Features

- **256-bit Unsigned Integer Support**: Complete arithmetic operations for 256-bit integers
- **Montgomery Multiplication**: Optimized modular multiplication using Montgomery reduction
- **Modular Arithmetic**: Addition, subtraction, multiplication, division and exponentiation in modular arithmetic
- **Bit Operations**: Bit testing, setting, and manipulation functions
- **GCD Computation**: Stein's algorithm for greatest common divisor calculation

## Core Components

### 1. 256-bit Integer Operations (`uint256.h/c`)
- Basic arithmetic: addition, subtraction, multiplication and division
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
- Modular exponentiation
- Modular inverse computation

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

```

## Building

### Prerequisites
- GCC or Clang
- Make 

```bash
make install
```

## Performance Considerations

- **Montgomery Multiplication**: The library uses Montgomery reduction for efficient modular multiplication, particularly beneficial when performing multiple operations with the same modulus
- **Limb-based Representation**: Numbers are stored as arrays of 64-bit limbs for optimal performance on 64-bit systems
- **Memory Layout**: Structures are designed for cache-friendly access patterns


### Important
- The modulus must be odd for Montgomery arithmetic to work correctly
- Your modulus needs to be prime for mod_inv to work


## Contributing

When contributing to ModulusPlus:

1. Follow the existing code style and naming conventions
2. Add appropriate error checking and validation
3. Include performance considerations in your implementations
4. Test thoroughly with edge cases (zero values, maximum values, etc.)
5. Document any new functions or significant changes
