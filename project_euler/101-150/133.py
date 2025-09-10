from math import log2, sqrt


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


def main():
    # create a sieve of Eratosthenes
    limit = 100_000
    is_prime_list = soe(limit)

    # declare variables
    non_prime_sum = 3  # count 3 as it will not be tested in loop

    # main loop
    for i, isprime in enumerate(is_prime_list):
        if not isprime or i == 3:  # ignore if num is composite or 3
            continue

        for j in range(1, int(log2(i)) + 1): 
            if pow(10, 10**j, i) == 1:  # check for prime factors of repunits
                break

        else:  # if prime did not divide any repunits
            non_prime_sum += i

    # print result
    print("Sum of all the primes that will never be a factor: "\
        f"{non_prime_sum}")


if __name__ == "__main__":
    main()
