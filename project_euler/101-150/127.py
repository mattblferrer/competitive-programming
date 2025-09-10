from math import gcd, isqrt, prod


# returns the prime factors of num without multiplicity (non-repeating)
def prime_factorize(num: int) -> set[int]:
    factors = set()

    if num == 0:
        return {}

    elif num == 1:
        return {1}

    for i in (2, 3):
        while num % i == 0:
            factors.add(i)
            num //= i

    for i in range(5, isqrt(num) + 1, 6):  # for 6k +- 1
        if i*i > num:
            break

        for j in (0, 2):
            while num % (i+j) == 0:
                factors.add(i+j)
                num //= (i+j)
            
    if num != 1:
        factors.add(num)

    return factors


# initialize factorization list
limit = 120000
factorizeList = [prime_factorize(i) for i in range(limit)]

# iterate through all abc triples
sumABC = 0

for a in range(1, limit):
    for b in range(a+1, limit-a):
        c = a+b

        if gcd(a, b, c) == 1:  # valid abc triple
            factorsABC = factorizeList[a].union(factorizeList[b], factorizeList[c])
            radABC = prod(factorsABC)

            if radABC < c:
                print(a, b, c, factorsABC)
                sumABC += c

# print result
print(f"Sum of c's ({limit}): {sumABC}")
