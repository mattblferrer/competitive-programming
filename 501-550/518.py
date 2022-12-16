from itertools import product
from math import prod


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


def prime_factorize(num: int) -> dict[int]:
    """returns the prime factors of num with multiplicity (repeating)"""
    factors = {}

    for i in (2, 3):
        count = 0
        while num % i == 0:  # for only even prime
            count += 1
            num //= i
        if count:
            factors[i] = count

    for i in range(5, int(num ** 0.5) + 1, 6):  # for 6k +- 1
        if i*i > num:
            break

        for j in (0, 2):
            count = 0
            while num % (i+j) == 0:
                count += 1
                num //= (i+j)
            if count:
                factors[i+j] = count

    if num != 1:
        factors[num] = 1

    return factors


def main():
    # declare variables
    limit = 10**8
    is_prime_list = soe(limit)
    prime_list = [i for i, is_prime in enumerate(is_prime_list) if is_prime]
    prime_set = set(prime_list)
    abc_sum = 0

    # iterate through primes a and find b and c from geometric sequence
    for a in prime_list:
        # get square factors of a + 1 as ratio for geometric sequence
        a1 = a + 1
        prog_factors = {x: val // 2 for x, val in prime_factorize(a1).items() 
            if val > 1}
        powers = [
            [base**power for power in range(count+1)]
            for base, count in prog_factors.items()
        ]
        factors = [prod(power_combo) for power_combo in product(*powers)]
        c_set = set()

        for d in factors:  # denominator of ratio
            n = d + 1  # numerator of ratio
    
            while True:
                # calculate b and c, b + 1 and c + 1
                b1 = a1 * n // d
                b = b1 - 1
                c1 = b1 * b1 // a1
                c = c1 - 1
                
                if c > limit:
                    break

                # check if b and c are primes, and c is unique
                if b in prime_set and c in prime_set and c not in c_set:
                    c_set.add(c)
                    abc_sum += int(a + b + c)

                n += 1

    # print result
    print(f"S({limit}) = {abc_sum}")


if __name__ == "__main__":
    main()