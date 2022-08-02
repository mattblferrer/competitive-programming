from math import sqrt


# determines if num is prime
def isprime(num):
    if num % 2 == 0:  # for even numbers
        return False

    for i in range(3, int(sqrt(num))+1, 2):  # for odd numbers
        if num % i == 0:
            return False
    return True


# generate the next odd composite number
def next_odd_composite(num):
    while True:
        num += 2
        if not isprime(num):
            return num


# loops through all the squares and checks for prime difference
def square_check(num):
    limit = int(sqrt(num*0.5))+1  # upper bound of squares to be checked

    for i in range(1, limit):
        prime_cand = num - 2*(i**2)  # candidate for being prime
        if isprime(prime_cand):
            return True

    return False


# declare variables
composite = 33  # start at 33, given
isPossible = True  # does the number follow the conjecture?

print("The odd composites that can't be written as the sum of a prime and twice a square are: ")

# main loop
while isPossible:
    composite = next_odd_composite(composite)

    if not square_check(composite):
        print(composite)
        isPossible = False
