from math import sqrt


# creates a Sieve of Eratosthenes array of size n
def soe(n):
    # for 0 and 1
    isPrimeList[0] = False
    isPrimeList[1] = False

    # for even numbers
    multiple = 4

    while multiple < n:
        # assign multiples of 2 as not being prime
            isPrimeList[multiple] = False  
            multiple += 2

    # for 3
    multiple = 9
    
    while multiple < n:
        # assign multiples of 3 as not being prime
            isPrimeList[multiple] = False  
            multiple += 3

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6):  
        multiple = i*i  # initialize to i^2 for optimization

        while multiple < n:
            # assign multiples of i as not being prime
            isPrimeList[multiple] = False  
            multiple += i

        multiple = (i+2)*(i+2)  # initialize to i^2 for optimization

        while multiple < n:
            # assign multiples of i as not being prime
            isPrimeList[multiple] = False  
            multiple += (i+2)


# create a sieve of Eratosthenes
limit = 1000000
iterlimit = int(sqrt(limit)) + 1
isPrimeList = [True]*(limit + 1)
soe(limit)  

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
print("Sum of factors:", factorSum)
