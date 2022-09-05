"""
Algorithm source:
https://stackoverflow.com/questions/45224037/last-non-zero-digits-of-a-very-large-factorial

This is slightly modified to lower the iteration limit 10^8 to 1.5625*10^6.
"""
from math import log, prod


# generates a list of numbers divisible by 2 and 5 below n (unsorted)
def hamming(n: int) -> list[int]:
    hamming_list = []
    mult = [2, 5]  # multipliers
    exps = [0, 0]  # prime exponents
    
    # loop through all combinations of i, j such that 2^i*5^j < n
    while mult[0]**exps[0] < n:  # i
        exps[1] = 0

        while mult[1]**exps[1] < n:  # j
            x = prod(mult[i]**exps[i] for i in range(2))

            if x < n:
                hamming_list.append(x)

            exps[1] += 1
        exps[0] += 1

    return hamming_list


# counts how many times the factor f appears in the prime factorizations of
# 1 to n, including repeats
def count_range_sum(f: int, n: int) -> int:
    highest_power = int(log(n, f))
    count = sum(n // (f ** power) for power in range(1, highest_power+1))

    return count


# creates a Sieve of Eratosthenes array of size n, coprime to 2 and 5
def coprime_25(n: int) -> list[int]:
    coprime_list = []

    for multiple in range(0, n, 10):
        for i in [1, 3, 7, 9]:  # 10x + 1, 3, 7, 9 are coprime to 2 and 5
            coprime_list.append(multiple + i)

    return coprime_list


# declare variables
n = 10**12
digits = 5
mod = 10**digits
iterlimit = 15625*10**2  # cycle repeats every 1.5625*10^6

# get numbers below 10^8 coprime to 2 and 5, since 2*5 = 10 and does not count
# towards the non-zero digits
coprimeList = coprime_25(iterlimit + 1)

# calculate factor of 2 with modulo to be multiplied
factors10 = count_range_sum(2, n) - count_range_sum(5, n)
multiplier2 = pow(2, factors10, mod)

# calculate product of coprime numbers up to (including) n // hamming numbers
hammingList = reversed(hamming(n))
coprimeIndex = 1
productDict = {}
product = 1

# memoization of product of coprime numbers up to and including n
for i in range(1, iterlimit+1):
    if coprimeList[coprimeIndex] == i:
        product = (product * i) % (iterlimit)
        coprimeIndex += 1
    productDict[i] = product

# calculate final 5 digits
answer = multiplier2
for currentHamming in hammingList:
    q = (n // currentHamming) % (iterlimit)
    if q == 0:
        q = mod

    answer = (answer * productDict[q]) % mod

# print result
print(f"f(1,000,000,000,000) = {answer}")
