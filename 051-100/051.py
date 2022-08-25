from math import sqrt


# determines if num is prime
def isprime(num):
    if num == 2 or num == 3:  # for 2 and 3
        return True
    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(6, int(num**0.5)+3, 6):  # for 6k +- 1
        if num % (i-1) == 0:
            return False
        if num % (i+1) == 0:
            return False
    return True


# generate next prime
def next_prime(num):
    while True:
        num += 2
        if isprime(num):
            return num


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


# declare variables
n = 56993  # starting num

# calculate all possible values in prime family
isFound = False

while True:
    # create a sieve of Eratosthenes
    length = len(str(n))
    p10 = 10**length  # lowest power of 10 above n
    lp10 = 10**(length-1)  # highest power of 10 below n
    iterlimit = int(sqrt(p10)) + 1
    isPrimeList = [True]*(p10 + 1)
    soe(p10)

    # generate a list of primes
    primes = set()

    for i, prime in enumerate(isPrimeList):
        if prime:
            primes.add(i)

    # generate all possible ways to replace digits in num
    perms = [format(n, '0'+str(length-1)+'b') for n in range(1, 2**(length-1))]
    
    while n < p10:
        strN = str(n)

        # try all combinations and check whether it is part of an 8-prime family
        for perm in perms:
            pos = [i for i, d in enumerate(perm) if d == '1']
            ctr = 0  # counter of primes in family
            for i in range(10):
                temp = strN  # temporary variable for digit replacement
                for j in pos:  # positions of digits to be replaced
                    temp = temp[:j] + str(i) + temp[j+1:]

                # check if prime and has no leading zeroes
                if int(temp) in primes and temp[0] != '0':
                    ctr += 1

            if ctr == 8:
                for j in pos:  # get first entry in family
                    strN = strN[:j] + str(1) + strN[j+1:]
                
                isFound = True

        if isFound:  # if prime is found 
            # print result
            print("Prime:", strN)
            break

        n = next_prime(n) # move to next prime

    if isFound:
        break
    print(p10)  # progress tracker
