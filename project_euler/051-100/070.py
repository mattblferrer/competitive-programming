from math import isqrt


# returns the prime factors of num (non-repeating)
def prime_factorize(num: int) -> set[int]:
    factors = set()

    for i in (2, 3):
        while num % i == 0:
            factors.add(i)
            num //= i

    for i in range(5, isqrt(num) + 1, 6):  # for 6k +- 1
        if i*i > num:
            break

        for j in (0, 2):
            while num % (i+j) == 0:
                factors.add(i+j)
                num //= (i+j)

    if num != 1:
        factors.add(num)

    return factors


# returns the Euler's totient of the number num using Euler's product formula
def totient(num: int, p_factors: set) -> int:
    phi = num  # totient
    for factor in p_factors:
        phi = phi * (factor-1)//factor

    return phi


def main():
    # declare variables
    limit = 10**7
    minimum_ratio = 100
    minimum_n = 0

    # main loop
    for n in range(3, limit, 2):  # min ratio num can't be even
        prime_factors = prime_factorize(n)

        # if i is prime, there is no need to calculate it
        if len(prime_factors) != 1:
            # count digits
            t = totient(n, prime_factors)
            t_digits, n_digits = sorted(str(t)), sorted(str(n))

            # if totient is a permutation of the original number
            if t_digits == n_digits:
                ratio = n/t
                if minimum_ratio > ratio:
                    minimum_ratio, minimum_n = ratio, n
                    minimum_n = n

    # print result
    print(f"The value of n for which phi(n) is a permutation and gives the \
minimum ratio is {minimum_n}")
    print(f"The ratio n/phi(n) is {minimum_ratio}")


if __name__ == "__main__":
    main()  

