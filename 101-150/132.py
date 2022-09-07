from math import sqrt


# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = int(sqrt(n)) + 1
    isPrimeList = [True]*(n+1)

    # for 0 and 1 
    isPrimeList[0] = isPrimeList[1] = False

    # for 2 and 3
    for i in [2, 3]:
        for multiple in range(i*i, n, i):
            # assign multiples of 2 or 3 as not being prime
            isPrimeList[multiple] = False  

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6): 
        for j in [0, 2]: 
            for multiple in range((i+j) * (i+j), n, i+j):
                # assign multiples of i+j as not being prime
                isPrimeList[multiple] = False  

    return isPrimeList


# create a sieve of Eratosthenes
limit = 1000000
isPrimeList = soe(limit)  

# declare variables
k = 10**9  # repunit exponent
factorSum = 0
factorNum = 0

# main loop
for i, bool in enumerate(isPrimeList):
    if bool:   # if num is prime
        if i == 3:
            continue  # we do not count 3 as a factor
        if pow(10, k, i) == 1:
            factorSum += i
            print(i)
            factorNum += 1

        if factorNum >= 40:
            break

# print result
print(f"Sum of factors: {factorSum}")
