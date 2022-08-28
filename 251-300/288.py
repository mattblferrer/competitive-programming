# declare variables
p = 61
q = 10**7
exp = 10  # exponent of modulus

# random number generator
s = 290797  # s0
n = 0
power = p  # prime power multiple

for i in range(1, q+1):  # exponent of modulus
    s = (s*s) % 50515093  # generate S(n)
    t = s % p  # generate T(n)
    
    # calculate NF(p,q)
    n += t*(power - 1)//(p-1)  # factors in (T(n)*p^n)!

    if i < exp:  # increment power when lower than modulus
        power *= p

# print result
print(n % (p**exp)) 
