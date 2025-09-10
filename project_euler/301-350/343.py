from math import isqrt


# returns the prime factors of num with multiplicity (repeating)
def prime_factorize(num: int) -> dict[int]:
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
    # declare variables
    limit = 2 * 10**6
    sum_x = 1

    # f(i^3) = max prime factor of (i^3 + 1) - 1
    for i in range(2, limit + 1):
        factor1 = prime_factorize(i + 1)
        factor2 = prime_factorize(i*i - i + 1)
        max_factor = max(max(factor1), max(factor2))
        sum_x += max_factor - 1
        if i % 10_000 == 0:  # progress tracker
            print(i, sum_x)

    # print result
    print(sum_x)


if __name__ == "__main__":
    main()
