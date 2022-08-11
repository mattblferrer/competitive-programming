from math import sqrt


# returns the radical of num + whether it is prime
def radical_pr(num):
    radical = 1
    limit = sqrt(num)
    originalNum = num  # for prime check

    # calculate the radical
    for prime in primeList:
        if num % prime == 0:
            radical *= prime

            while num % prime == 0:
                num //= prime

        if prime > limit:  # we don't have to check these numbers
            break

    # check if prime
    if num != 1 and num != originalNum:
        radical *= num
        return radical, False

    return radical, True


# declare variables
primeList = [2]
radDict = {
        0: [0],
        1: [1]
    }  # radicals for 0 and 1, keys are rad(n), values are n
limit = 100000

for i in range(2, limit+1):
    raw_rad = radical_pr(i)
    rad = raw_rad[0]
    isPrime = raw_rad[1]

    if rad not in radDict.keys():
        radDict[rad] = []

    if rad == 1 and isPrime:  # prime number check
        if i not in radDict.keys():
            radDict[i] = []
        
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

        index += 1

    if isFound:
        break

# print result
print("E(10000) =", answer)
