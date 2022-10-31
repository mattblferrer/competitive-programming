from math import isqrt


# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = isqrt(n) + 1
    isPrimeList = [True]*(n+1)

    # for 0 and 1 
    isPrimeList[0] = isPrimeList[1] = False

    # for 2 and 3
    for i in (2, 3):
        for multiple in range(i*i, n, i):
            # assign multiples of 2 or 3 as not being prime
            isPrimeList[multiple] = False  

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6): 
        for j in (0, 2): 
            for multiple in range((i+j) * (i+j), n, i+j):
                # assign multiples of i+j as not being prime
                isPrimeList[multiple] = False  

    return isPrimeList


# determines if num is prime
def isprime(num: int) -> bool:
    if num == 2 or num == 3:  # for 2 and 3
        return True

    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(5, int(num ** 0.5)+3, 6):  # for 6k +- 1
        if num % i == 0 or num % (i+2) == 0:
            return False
    return True


# generate next prime
def next_prime(num: int) -> int:
    while True:
        num += 2
        if isprime(num):
            return num


# generate triangular number of certain index
def triangular(ind: int) -> int:
    return ind * (ind + 1) // 2


# declare variables
limit = 999966663333
sqrtlimit = isqrt(limit)
is_prime_list = soe(sqrtlimit)
prime_list = [idx for idx, is_prime in enumerate(is_prime_list) if is_prime]
sum_semidiv = 0

# loop through all consecutive pairs of primes p1, p2 below sqrt(limit)
for p1, p2 in zip(prime_list, prime_list[1:]):
    ll_1 = p1  # lower limit of p1
    ll_2 = (p1*p1) // p2  # lower limit of p2
    ul_1 = (p2*p2) // p1  # upper limit of p1
    ul_2 = p2 - 1  # upper limit of p2

    # include divisible by p1 and divisible by p2, exclude divisible by both
    sum_p1 = (triangular(ul_1) - triangular(ll_1)) * p1
    sum_p2 = (triangular(ul_2) - triangular(ll_2)) * p2
    sum_semidiv += sum_p1 + sum_p2 - 2*p1*p2

# loop through p1^2 < i < limit for remaining pair p1, p2
p1 = prime_list[-1]
p2 = next_prime(p1)  # first prime greater than sqrt(limit)

for i in range(p1*p1 + 1, limit):
    if ((i % p1 == 0) ^ (i % p2 == 0)):
        sum_semidiv += i

# print result
print(f"Sum of all semidivisible numbers up to {limit}: {sum_semidiv}")

