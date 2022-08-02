# generates a list of rotations of a given number num
def rotation_list(num):
    output = set()
    length = len(str(num))  # number of digits in num

    # shift to the left
    for i in range(length-1):
        first_digit = num // 10 ** (length - 1)
        num = (10*num + first_digit) - first_digit*10**length  # move first digit to the ones place
        output.add(num)

    return output


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


# declare variables
circularPrimes = 1  # initialize with prime 2
nonCircularList = set()  # set of primes that aren't circular
n = 3
limit = 1000000

# main loop
while n < limit:
    if n not in nonCircularList:
        isCircular = True
        perms = rotation_list(n)  # set of permutations (rotations) of n
        nonCircularPerms = set()  # assume that prime is not circular until proven otherwise

        # iterate through all rotations
        for perm in perms:
            if not isprime(perm):
                isCircular = False
                nonCircularList = nonCircularList | nonCircularPerms  # add prime rotations to non-circular prime set
                break
            else:
                nonCircularPerms.add(perm)  # add prime to possible non-circular prime set

        # if n is circular, increment count
        if isCircular:
            circularPrimes += 1
            print(circularPrimes, n)

    n = next_prime(n)

# print result
print("The number of circular primes below {} is {}".format(limit, circularPrimes))
