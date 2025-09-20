from sympy.ntheory.residue_ntheory import quadratic_congruence # type: ignore


def legendre(a: int, p: int) -> int:
    """returns the Legendre symbol for a and p"""
    return pow(a, (p - 1) // 2, p)


def isprime(num: int) -> bool:
    """returns True if num is prime"""
    if num == 2 or num == 3:  # for 2 and 3
        return True
    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(6, int(num**0.5)+3, 6):  # for 6k +- 1
        if num % (i-1) == 0:
            return False
        if num % (i+1) == 0:
            return False
    return True


def next_prime(num: int) -> int:
    """return the smallest prime larger than num"""
    while True:
        num += 2
        if isprime(num):
            return num


def main():
    # declare variables
    p = 3
    sum_n = 0
    limit = 10**7

    while p < limit:
        # check if integer n exists that satisfies f(n) mod p^2 = 0
        if legendre(p, 13) == 1:  
            # find n such that n^2 - 3n = 1 mod p^2
            n = quadratic_congruence(1, -3, -1, p*p)[0]
            sum_n += n     

        p = next_prime(p)  # increment prime

    # print result
    print(sum_n)


if __name__ == "__main__":
    main()
