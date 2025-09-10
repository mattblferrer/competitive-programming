"""
Length of Farey sequence n = 1 + sum of totient functions from 1 to n
"""

def mobius(n: int) -> int:
    """returns the Mobius function of n"""
    if n == 1:
        return 1

    factors = 0
    for i in (2, 3):
        if n % i == 0:  # for 2 and 3
            factors += 1
            n //= i

            if n % i == 0:  # if divisible again
                return 0

    # only have to check for odd factors up to sqrt(n)
    for i in range(5, int(n ** 0.5) + 1, 6):
        if i*i > n:
            break
        for j in (0, 2):  # 6k +- 1
            if n % (i + j) == 0:
                factors += 1
                n //= i + j

                if n % (i + j) == 0:
                    return 0

    # check if prime
    if n != 1:
        factors += 1

    return 1 if factors % 2 == 0 else -1  # check for sign of function result


def main():
    # declare variables
    d = 1_000_000
    totient_sum = 1

    # main loop
    for i in range(1, d + 1):
        div = d // i
        totient_sum += mobius(i) * div * (1 + div)

    # print result
    print((totient_sum - 2) // 2)  # not counting 0/1, 1/1


if __name__ == "__main__":
    main()
