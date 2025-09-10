from functools import cache
from math import factorial, floor, isqrt, log


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

    for i in range(5, isqrt(num) + 1, 6):  # for 6k +- 1
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
    @cache
    def s(n: int) -> int:
        """returns the smallest number m such that n divides m!"""
        def a(n: int) -> int:
            return (p ** n - 1) // (p - 1)


        if n in factorial_list:  # factorial
            return factorial_list.index(n)

        factors = prime_factorize(i)
        if len(factors) == 1:  # prime power
            (p, k), = factors.items()
            if k <= p:  # for p^k where k < p, s(n) = p * k
                return k * p

            # calculate multiplicity of factors present if k > p
            v = floor(log(1 + k * (p - 1), p))
            power = k
            x_sum = 0
            r = k % a(v)

            if r:  # if remainder is not 0 at first step
                while r != 0:  # Euclidean algorithm-like process
                    x = k // a(v)
                    r = k % a(v)
                    x_sum += x 
                    k = r
                    v -= 1

                return (p - 1) * power + x_sum
            return (p - 1) * power + k // a(v)  # if remainder = 0 first step

        # if product of prime powers
        return max(s(p ** k) for p, k in factors.items())


    # declare variables
    limit = 10**8
    sum_s = 0
    factorial_list = [factorial(i) for i in range(15)]

    # loop through i up to limit using cached prime factorizations
    for i in range(2, limit + 1):
        sum_s += s(i)
        if i % 100_000 == 0:  # progress tracker
            print(f"i: {i}, sum: {sum_s}")

    # print result
    print(sum_s)


if __name__ == "__main__":
    main()
