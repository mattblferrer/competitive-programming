def factors(num):  # returns the sum of the factors of num
    factor_sum = 1  # all numbers have a factor of 1

    for i in range(2, int(num ** 0.5) + 1):  # only have to check for factors up to sqrt(n)
        if num % i == 0:
            factor_sum += i
            factor_sum += (num//i)

    return factor_sum


limit = 10000  # given parameter
amicSum = 0  # sum of amicable numbers up to limit

for b in range(2, limit):
    a = factors(b)
    if factors(a) == b and a != b:
        amicSum += b

print("The sum of all amicable numbers below", limit, "is", amicSum)
