from math import isqrt


# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = isqrt(n) + 1
    isPrimeList = [True]*n

    # for 0 and 1 
    isPrimeList[0] = isPrimeList[1] = False

    # for 2 and 3
    for i in [2, 3]:
        for multiple in range(i*i, n, i):
            # assign multiples of 2 or 3 as not being prime
            isPrimeList[multiple] = False  

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6): 
        for j in [0, 2]: 
            for multiple in range((i+j) * (i+j), n, i+j):
                # assign multiples of i+j as not being prime
                isPrimeList[multiple] = False  

    return isPrimeList


# returns the modular multiplicative inverse of num mod x
def mod_mult_inv(num: int, x: int) -> int:
    r0, r1 = x, num
    t0, t1 = 0, 1

    # extended Euclidean algorithm
    while r1 != 0:
        q = r0 // r1
        r0, r1 = r1, r0 % r1  # remainders after Euclidean division
        t0, t1 = t1, (t0 - t1*q) % x
        
    return t0


# returns the sum of (p - k)! mod p, 1 <= k <= 5, (p - 1)! + (p - 2)! = 0 mod p
def s(p: int) -> int:
    x = p // 2  # (p - 3)! mod p
    y = -(p - x) * mod_mult_inv(p - 3, p) % p  # (p - 4)! mod p
    z = -(p - y) * mod_mult_inv(p - 4, p) % p  # (p - 5)! mod p
    return sum([x, y, z]) % p


def main():
    # declare variables
    limit = 10**8
    is_prime_list = soe(limit)
    prime_list = [i for i, isprime in enumerate(is_prime_list) if isprime]
    s_sum = sum([s(p) for p in prime_list[2:]])  # skip 2 and 3

    # print result
    print(s_sum)


if __name__ == "__main__":
    main()
