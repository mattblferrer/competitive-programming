from functools import cache


@cache
def factorial(num: int) -> int:
    """returns the factorial of num"""
    fac = 1 
    for i in range(1, num + 1):
        fac *= i
    return fac


def a(n: int, mod: int) -> int:
    """returns the number of integers less than 10^n for which more than half
    of its digits are equal (with modulo mod)"""
    return sum(sum(factorial(m) // (factorial(k) * factorial(m - k))
        * pow(9, m - k + 1, mod)  # ordering and choice of digits 
        for k in range(m // 2 + 1, m + 1))  # for k equal digits
        for m in range(1, n + 1)) % mod  # for m total digits from 1 to n + 1


def main():
    mod = 1_000_000_007
    print(a(2022, mod))  # print result


if __name__ == "__main__":
    main()
