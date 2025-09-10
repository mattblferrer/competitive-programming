from math import log, sqrt


def soe(n: int) -> list[bool]:
    """creates a Sieve of Eratosthenes array of size n"""
    iterlimit = int(sqrt(n)) + 1
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
    limit = 20_000_000
    lower_limit = 15_000_000  # lower limit
    is_prime_list = soe(limit)  # create a sieve of Eratosthenes
    factor_sum = 0

    # calculate factors of factorials
    diff = limit - lower_limit
    for index, is_prime in enumerate(is_prime_list):
        if is_prime:
            for power in range(1, int(log(limit, index)) + 1):  # n!
                factor_sum += index*(limit // (index**power))
            for power in range(1, int(log(lower_limit, index)) + 1):  # r!
                factor_sum -= index*(lower_limit // (index**power))    
            for power in range(1, int(log(diff, index)) + 1):  # (n-r)!
                factor_sum -= index*(diff // (index**power))

    # print result
    print("Sum of terms in prime factorization:", factor_sum)


if __name__ == "__main__":
    main()
