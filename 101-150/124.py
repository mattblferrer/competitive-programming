from math import sqrt
from collections import defaultdict


# returns the radical of num + whether it is prime
def radical_pr(num: int) -> tuple:
    if num in [0, 1]:
        return num, False
    
    radical = 1
    originalNum = num  # for prime check

    # calculate the radical
    for prime in primeList:
        if num % prime == 0:
            radical *= prime

            while num % prime == 0:
                num //= prime

        if prime > sqrt(num):  # we don't have to check these numbers
            break

    # check if prime
    if num != 1 and num != originalNum:
        radical *= num
        return radical, False

    return radical, True


# declare variables
primeList = [2]
radDict = defaultdict(list)  # keys are rad(n), values are n
limit = 100000

for i in range(limit+1):
    rad, isPrime = radical_pr(i)

    if i != 1 and rad == 1:  # prime number check
        radDict[i].append(i)
        primeList.append(i)
    else:
        radDict[rad].append(i)

# iterate through dict and find 10000th element
index = 0
isFound = False

for key in radDict:
    for value in radDict[key]:
        if index == 10000:
            answer = value
            isFound = True
            break            
        index += 1

    if isFound:
        break

# print result
print(f"E(10000) = {answer}")
