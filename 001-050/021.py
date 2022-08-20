from math import prod

def sum_factors(num):  # returns the sum of the factors of num
    check = num
    factors = []

    for i in [2, 3]:  # for 2 and 3
        power = 1
        cFactor = 1

        while num % i == 0:
            cFactor += i**power
            num //= i
            power += 1

        factors.append(cFactor)

    for i in range(6, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        # 6k - 1
        power = 1
        cFactor = 1
        while num % (i-1) == 0:
            cFactor += (i-1) ** power
            num //= (i-1)
            power += 1

        factors.append(cFactor)
            
        # 6k + 1
        power = 1
        cFactor = 1
        while num % (i+1) == 0:
            cFactor += (i+1) ** power
            num //= (i+1)
            power += 1

        factors.append(cFactor)

        if num == 1:
            break

    if num != 1:
        factors.append(num+1)

    return prod(factors) - check


limit = 10000  # given parameter
amicSum = 0  # sum of amicable numbers up to limit

for b in range(2, limit):
    a = sum_factors(b)
    if sum_factors(a) == b and a != b:
        amicSum += b

print("The sum of all amicable numbers below", limit, "is", amicSum)
