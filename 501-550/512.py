from numba import njit


@njit
# returns the prime factors of num (non-repeating)
def prime_factorize(num: int) -> set:
    factors = set()

    for i in (2, 3):
        while num % i == 0:
            factors.add(i)
            num //= i

    for i in range(5, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        if i*i > num:
            break

        for j in (0, 2):
            while num % (i+j) == 0:
                factors.add(i+j)
                num //= (i+j)

    if num != 1:
        factors.add(num)

    return factors


@njit
# returns the Euler's totient of the number num using Euler's product formula
def totient(num: int) -> int:
    p_factors = prime_factorize(num)
    phi = num  # totient
    for factor in p_factors:
        phi = phi*(factor-1)//factor

    return phi


def main():
    # declare variables
    limit = 5 * 10**8
    g = 0

    # only calculate totients for odds, as for even n's: g(n) will equal 0
    for n in range(1, limit + 1, 2):
        g += totient(n)

        if n % 1_000_000 == 1:  # progress tracker
            print(f"n: {n - 1}, g: {g}")

    # print result
    print(f"g({limit}) = {g}")


if __name__ == "__main__":
    main()
