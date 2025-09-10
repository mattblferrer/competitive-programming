from functools import cache


@cache
# returns the n'th Stern-Brocot number (recursive formula)
def stern_brocot(n: int) -> int:
    if n == 0:
        return 0
    elif n == 1:
        return 1
    elif n % 2 == 0:
        return stern_brocot(n // 2)
    else:
        return stern_brocot(n // 2) + stern_brocot(n // 2 + 1)


def main():
    # Number of ways to express n as the sum of integer powers of 2 using each
    # power no more than twice = (n + 1)th Stern-Brocot number
    n = 10**25
    print(stern_brocot(n + 1))


if __name__ == "__main__":
    main()
