from math import isqrt


# determines if num is prime
def isprime(num: int) -> bool:
    if num == 2 or num == 3:  # for 2 and 3
        return True

    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(5, isqrt(num)+3, 6):  # for 6k +- 1
        if num % i == 0 or num % (i+2) == 0:
            return False
    return True


# generate the next odd composite number
def next_odd_composite(num: int) -> int:
    while True:
        num += 2
        if not isprime(num):
            return num


# loops through all the squares and checks for prime difference
def square_check(num: int) -> bool:
    limit = isqrt(num // 2)+1  # upper bound of squares to be checked

    for i in range(1, limit):
        prime_cand = num - 2*i*i  # candidate for being prime
        if isprime(prime_cand):
            return True

    return False


# declare variables
composite = 33  # start at 33, given

print("The odd composites that can't be written as the sum of a prime and twice a square are: ")

# main loop
while True:
    composite = next_odd_composite(composite)

    if not square_check(composite):
        print(composite)
        break