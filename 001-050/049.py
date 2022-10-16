from itertools import permutations
from math import sqrt


# determines if num is prime
def isprime(num: int) -> bool:
    if num == 2 or num == 3:  # for 2 and 3
        return True

    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(5, int(sqrt(num))+3, 6):  # for 6k +- 1
        if num % i == 0 or num % (i+2) == 0:
            return False
    return True


# generate next prime
def next_prime(num: int) -> int:
    while True:
        num += 2
        if isprime(num):
            return num


# generates a list of permutations of a given number num
def permutation_list(num: int) -> list[int]:
    digits = [digit for digit in str(num)]  # get digits of number
    perm_list = sorted(set(int(''.join(d)) for d in permutations(digits) 
        if d[0] != '0'))

    return perm_list


# returns the number formed from concatenating terms in permutation sequence
def permutation_sequence(perm_list: list[int]) -> int:
    # iterate through all combinations of a and b in list of permutations
    for ia, a in enumerate(perm_list):
        for b in perm_list[ia:]:
            if not isprime(a) or not isprime(b):
                continue
            
            difference = b-a  # difference between two elements in the list
            if difference == 0:  # if they are the same element
                continue

            c = b + difference
            if c in perm_list and isprime(c):
                # return the result in 12-digit concatenated format
                return 10**8*a + 10**4*b + c   


# declare variables
currentPrime = 1009

# main loop
while currentPrime < 10000:
    currentPerm = permutation_sequence(permutation_list(currentPrime))

    if currentPerm is not None and currentPerm != 148748178147: 
        print(f"The 12-digit number formed is {currentPerm}")
        break

    currentPrime = next_prime(currentPrime)
