from collections import Counter
from math import sqrt


def sum_factors_sqr(num):  # returns the sums of the squares of the factors of num
    # factorize the number
    factors = []

    for i in [2, 3]:  # for 2 and 3
        while num % i == 0: 
            factors.append(i)
            num //= i


    for i in range(6, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        for j in [-1, 1]:
            while num % (i + j) == 0:
                factors.append(i + j)
                num //= (i + j)

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
