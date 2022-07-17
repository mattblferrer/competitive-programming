"""
Algorithm source:
https://stackoverflow.com/questions/45224037/last-non-zero-digits-of-a-very-large-factorial
"""
from math import log


# generates a list of numbers divisible by 2 and 5 below n (unsorted)
def hamming(n):
    hamming_list = []
    mult = [2, 5]  # multipliers
    exps = [0, 0]  # prime exponents
    
    # loop through all combinations of i, j such that 2^i*5^k < n
    while mult[0]**exps[0] < n:  # i
        exps[1] = 0

        while mult[1]**exps[1] < n:  # k
            x = 1
            for i in range(2):
                x *= (mult[i]**exps[i])

            if x < n:
                hamming_list.append(x)

            exps[1] += 1
        exps[0] += 1

    return hamming_list


# counts how many times the factor f appears in the prime factorizations of
# 1 to n, including repeats
def count_range_sum(f, n):
    highest_power = int(log(n, f))
    count = 0

    for power in range(1, highest_power+1):
        count += n // (f ** power)

    return count


# creates a Sieve of Eratosthenes array of size n, coprime to 2 and 5
def coprime_25(n):
    multiple = 0
    coprime_list = []

    while multiple < n:
        # 10x + 1, 3, 7, 9 are coprime to 2 and 5
        coprime_list.append(multiple + 1)
        coprime_list.append(multiple + 3)
        coprime_list.append(multiple + 7)  
        coprime_list.append(multiple + 9)
        multiple += 10

    return coprime_list


# declare variables
n = 10**12
digits = 5
mod = 10**digits
iterlimit = 5*10**7  # cycle repeats every 5*10^7

# get numbers below 10^8 coprime to 2 and 5, since 2*5 = 10 and does not count
# towards the non-zero digits
coprimeList = coprime_25(iterlimit + 1)

# calculate factor of 2 with modulo to be multiplied
factors10 = count_range_sum(2, n) - count_range_sum(5, n)
multiplier2 = pow(2, factors10, mod)

# calculate product of coprime numbers up to n // hamming numbers (memoize)
hammingList = list(reversed(sorted(hamming(n))))
hammingIndex = 0
coprimeIndex = 1
productDict = {}
product = 1

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
print("f(1,000,000,000,000) =", answer)
