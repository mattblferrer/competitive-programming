def soe(n: int) -> list[bool]:
    """creates a Sieve of Eratosthenes array of size n"""
    iterlimit = int(n ** 0.5) + 1
    is_prime_list = [True]*n

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
    # declare variables
    limit = 10**8
    iterlimit = int(limit ** 0.5) + 1  # only check primes below this point
    is_prime_list = soe(limit // 2 + 1)  # create a sieve of Eratosthenes

    # calculate prime list up to sqrt(limit)
    prime_list = []

    for index, is_prime in enumerate(is_prime_list):
        if is_prime:
            prime_list.append(index)
        if index > iterlimit:
            break

    # calculate semiprimes
    ctr = len(prime_list)
    semiprimes = 0
    pi = 0  # current prime counting function
    lower_limit = 2

    for prime in reversed(prime_list):
        upper_limit = limit // prime + 1

        # count primes below limit / prime
        for i in range(lower_limit, upper_limit):
            if is_prime_list[i]:
                pi += 1

        # calculate semiprime partial sum
        semiprimes += (pi - ctr + 1)

        lower_limit = upper_limit
        ctr -= 1

    # print result
    print(f"Number of semiprimes: {semiprimes}")


if __name__ == "__main__":
    main()
