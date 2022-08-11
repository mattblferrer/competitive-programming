from math import gcd, prod


# returns the prime factors of num (non-repeating)
def prime_factorize(num):
    factors = set()

    while num % 2 == 0:  # for only even prime
        factors.add(2)
        num //= 2

    while num % 3 == 0:  # for 3
        factors.add(3)
        num //= 3

    for i in range(6, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        while num % (i-1) == 0:
            factors.add(i-1)
            num //= (i-1)
            
        while num % (i+1) == 0:
            factors.add(i+1)
            num //= (i+1)

    if num != 1:
        factors.add(num)

    return factors


# initialize factorization list
limit = 120000
factorizeList = [0]*limit
factorizeList[1] = {1}

for i in range(2, limit):
    factorizeList[i] = prime_factorize(i)

# iterate through all abc triples
sumABC = 0

for a in range(1, limit):
    for b in range(a+1, limit-a):
        if gcd(a, b) == 1:
            c = a+b

            if gcd(a, c) == 1 and gcd(b, c) == 1:  # valid abc triple
                factorsABC = factorizeList[a].union(factorizeList[b]).union(factorizeList[c])
                radABC = prod(factorsABC)

                if radABC < c:
                    print(a, b, c, factorsABC)
                    sumABC += c

# print result
print("Sum of c's:", sumABC)
