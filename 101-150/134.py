from math import sqrt


def soe(n: int) -> list[bool]:
    """creates a Sieve of Eratosthenes array of size n"""
    iterlimit = int(sqrt(n)) + 1
    is_prime_list = [True]*(n + 1)

    # for 0 and 1 
    is_prime_list[0] = is_prime_list[1] = False

    # for 2 and 3
    for i in (2, 3):
        for multiple in range(i*i, n, i):
            # assign multiples of 2 or 3 as not being prime
            is_prime_list[multiple] = False  

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6): 
        for j in (0, 2): 
            for multiple in range((i+j) * (i+j), n, i+j):
                # assign multiples of i+j as not being prime
                is_prime_list[multiple] = False  

    return is_prime_list


def mod_mult_inv(num: int, x: int) -> int:
    """returns the modular multiplicative inverse of num mod x"""
    r0, r1 = x, num
    t0, t1 = 0, 1

    # extended Euclidean algorithm
    while r1 != 0:
        q = r0 // r1
        r0, r1 = r1, r0 % r1  # remainders after Euclidean division
        t0, t1 = t1, (t0 - t1*q) % x
        
    return t0


def main():
    # declare variables
    limit = 1_000_000
    p1 = 5  # start at p1 = 5, p2 = 7
    s_sum = 0
    is_prime_list = soe(limit + 100)  # create a sieve of Eratosthenes

    # generate list of primes and iterate through it
    for p2, isprime in enumerate(is_prime_list[7:], start=7):
        if p1 > limit:
            break

        if isprime:
            p10 = 10**(len(str(p1)))  # power of 10 to add to p1

            # find q to multiply to power of 10 such that total s is
            # divisible by p2
            q = ((p2 - p1) * mod_mult_inv(p10, p2)) % p2
            s_sum += p10 * q + p1
            p1 = p2  # switch p1, p2 and find new p2

    # print result
    print(s_sum)


if __name__ == "__main__":
    main()
