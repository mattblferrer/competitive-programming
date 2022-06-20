def factors(num):  # returns the sum of the factors of num
    factor_sum = 1  # all numbers have a factor of 1

    for i in range(2, int(num ** 0.5) + 1):  # only have to check for factors up to sqrt(n)
        if num % i == 0:
            factor_sum += i
            if num//i != i:
                factor_sum += (num//i)

    return factor_sum


nonAbundantSum = 0  # sum of all the positive integers that can't be expressed as the sum of two abundant numbers
limit = 28123  # given parameter
canBeSum = [False for num in range(limit)]
abundantList = []

for i in range(2, limit):  # calculate all abundant numbers below limit
    if factors(i) > i:  # if i is abundant
        abundantList.append(i)

for i in abundantList:  # calculate all numbers that can be sum of two abundant numbers
    for j in abundantList:
        if i+j-1 < limit:
            canBeSum[i+j-1] = True

for i in range(limit):  # add False numbers to sum
    if not canBeSum[i]:
        nonAbundantSum += (i+1)

print("The sum of all positive integers that can't be written as the sum of two abundant numbers is", nonAbundantSum)
