from itertools import permutations
from math import sqrt


# determines if num is prime
def isprime(num):
    if num == 2 or num == 3:  # for 2 and 3
        return True

    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(6, int(sqrt(num))+3, 6):  # for 6k +- 1
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


# generates a list of permutations of a given number num
def permutation_list(num):
    digits = [digit for digit in str(num)]  # get digits of number
    perm_list = sorted(set(int(''.join(d)) for d in list(permutations(digits)) if d[0] != '0'))

    # iterate through all combinations of a and b in list of permutations
    for a in perm_list:
        for b in perm_list:
            if isprime(a) and isprime(b):
                difference = abs(b-a)  # difference between two elements in the list

                if difference != 0:  # if they are not the same element
                    c = max(a, b) + difference

                    if c in perm_list and c != b and c != a and isprime(c):
                        return 10**8*a + 10**4*b + c   # return the result in 12-digit concatenated format


# declare variables
currentPrime = 1009

# main loop
while currentPrime < 10000:
    currentPerm = permutation_list(currentPrime)

    if currentPerm is not None:
        print(currentPerm)

    currentPrime = next_prime(currentPrime)
