print("Multiplication in Montgomery form:")

p = 0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff
a = 0xffffffff00000001000000000000000000000000fffffffffffffffffffffffc
b = 0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b 

result_mult = (a * b) % p
print(f"Result: {result_mult:#x}")

result_add = (a + b) % p
print(f"Addition Result: {result_add:#x}")

result_sub = (a - b) % p
print(f"Subtraction Result: {result_sub:#x}")

result_exp = pow(a, b, p)
print(f"Exponentiation Result: {result_exp:#x}")
result_inverse = pow(a, -1, p)
print(f"Inverse Result: {result_inverse:#x}")