from itertools import permutations
from math import sqrt


# determines if num is prime
def isprime(num):
    if num % 2 == 0:  # for even numbers
        return False

    for i in range(3, int(sqrt(num))+1, 2):  # for odd numbers
        if num % i == 0:
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
