from math import e, gcd


# reduces fraction to its lowest terms
def reduce(numerator: int, denominator: int) -> tuple[int]:
    # divide numerator, denominator by their GCD
    frac_gcd = gcd(numerator, denominator)
    numerator //= frac_gcd
    denominator //= frac_gcd

    return numerator, denominator


# returns True if fraction's decimal expansion terminates, and False otherwise
def is_terminating(denominator: int) -> bool:
    for i in (2, 5):
        while denominator % i == 0:
            denominator //= i

    return denominator == 1


def main():
    # declare variables
    limit = 10000
    d_n = 0

    # main loop
    for i in range(5, limit + 1):
        n, d = reduce(i, round(i / e))  # maximum of (i/k) ^ k -> k = i/e
        
        # check if max parts evenly divide the number into integer parts or
        # if decimal expansion terminates
        if n == 1 or is_terminating(d):
            d_n -= i
        else:
            d_n += i

    # print result
    print(f"The sum of D(n) = {d_n}")


if __name__ == "__main__":
    main()
