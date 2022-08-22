from collections import Counter
from math import sqrt


def sum_factors_sqr(num):  # returns the sums of the squares of the factors of num
    # factorize the number
    factors = []

    while num % 2 == 0:  # for only even prime
        factors.append(2)
        num //= 2

    while num % 3 == 0:  # for 3
        factors.append(3)
        num //= 3

    for i in range(6, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        while num % (i-1) == 0:
            factors.append(i-1)
            num //= (i-1)
            
        while num % (i+1) == 0:
            factors.append(i+1)
            num //= (i+1)

    if num != 1:
        factors.append(num)

    # calculate the sum of the squares of the factors of num
    sum_sf = 1
    freq = Counter(factors)  # get powers of prime factors of num
    for prime, power in freq.items():
        sum_sf *= (prime**(2*power + 2)-1) // (prime*prime - 1)

    return sum_sf


# declare variables
limit = 64000000
sumN = 0

# main loop
for i in range(1, limit):
    if sqrt(sum_factors_sqr(i)).is_integer():  # check if perfect square
        sumN += i

    if i % 100000 == 0:  # progress tracker
        print(i, sumN)

# print result
print("Sum of all n:", sumN)
