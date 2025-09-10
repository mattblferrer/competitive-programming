from functools import cache


@cache
def S(n: int) -> int:
    """returns the sum S(n) of all f(n) from 1 to n"""
    # base cases
    if n == 0:
        return 0
    elif n == 1:
        return 1
    elif n == 2:
        return 2
    elif n == 3:
        return 5

    # recursive cases
    q, r = divmod(n, 4)
    if r == 0:
        return 6 * S(2 * q) - 5 * S(q) - 3 * S(q - 1) - 1
    elif r == 1:
        return 2 * S(2 * q + 1) + 4 * S(2 * q) - 6 * S(q) - 2 * S(q - 1) - 1
    elif r == 2:
        return 3 * S(2 * q + 1) + 3 * S(2 * q) - 6 * S(q) - 2 * S(q - 1) - 1
    return 6 * S(2 * q + 1) - 8 * S(q) - 1


def main():
    print(S(3 ** 37) % (10**9))  # print result


if __name__ == "__main__":
    main()
