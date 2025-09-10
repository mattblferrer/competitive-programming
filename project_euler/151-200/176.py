"""
Number of different integer-sided right-angled triangles a(n) w/ cathetus of n:
if n = (2 ^ k0) * (p1 ^ k1) * (p2 ^ k2) * ... * (px ^ kx), then:
    a(n) = ((2 * k0 - 1) * (2 * k1 + 1) * (2 * k2 + 1) * ... - 1) / 2
    For a(n) = 47547: ((2 * k0 - 1) * (2 * k1 + 1) * (2 * k2 + 1) * ... = 95095

    To minimize n, the smallest prime factor has to have the highest exponent,
    decreasing to the end. Also, the smallest primes: 2, 3, 5, 7, ... have 
    to be used. 

    Therefore:
    n = 2^10 * 3^6 * 5^5 * 7^3 * 11^2 = 96,818,198,400,000. 
"""


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
    print(prime_factorize(95095))


if __name__ == "__main__":
    main()

