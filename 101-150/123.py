# determines if num is prime
def isprime(num):
    if num % 2 == 0:  # for even numbers
        return False

    for i in range(3, int(num**0.5+1), 2):  # for odd numbers
        if num % i == 0:
            return False
    return True


# generate next prime
def next_prime(num):
    while True:
        num += 2
        if isprime(num):
            return num


# declare variables
pn = 5
n = 3
limit = 10**10

# main loop
while True:
    # (pn-1)^n + (pn+1)^n mod pn^2 = 2*n*pn mod pn^2 for odd n
    r = (2*n*pn) % (pn*pn)

    # check if remainder exceeded limit
    if r > limit:
        # print result
        print("The least value of n is", n)
        print("r:", r)
        break
    
    # only need to check odd n
    n += 2  
    pn = next_prime(next_prime(pn))
