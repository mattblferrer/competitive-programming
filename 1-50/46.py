# determines if n is prime
def isprime(n):
    if n < 2:
        return False
    else:
        for i in range(2, int(n**0.5+1)):  # for odd numbers
            if n % i == 0:
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
    limit = int((0.5*num)**0.5)+1  # upper bound of squares to be checked

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
