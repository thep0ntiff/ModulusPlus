
p = 0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff
a = 0xffffffff00000001000000000000000000000000fffffffffffffffffffffffc
b = 0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b 

#result_mult = (a * b) % p
#print(f"Result: {result_mult:#x}")

result_add = (a + b) % p
print(f"Addition Result: {result_add:#x}")

result_sub = (a - b) % p
print(f"Subtraction Result: {result_sub:#x}")


result_mul = (a * b) % p
print(f"Mul result: {result_mul:#x}")

q, r = divmod(a, b)
print("Div result: ", hex(q))
print("remainder: ", hex(r))

result_inv = pow(a, b, p)
print(f"Exp Result: {result_inv:#x}")

res = 0xfffffffeffffffffffffffffffffffff000000001
resres = pow(res, 2)
print(f"{resres:#x}")
