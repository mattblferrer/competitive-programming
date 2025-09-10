from math import gcd


def recurring_cycle(n: int) -> int:
    """get length of recurring cycle of decimal fraction with denominator n"""
    if n == 1:  # base case
        return 1

    qr_list = []  # declare quotient, remainder list
    dividend = 10  # starting dividend

    # continued long division
    for i in range(n + n // 10):  # only have to check up to n + # of decimal 0s
        if dividend // n == 0:  # multiply dividend by 10 and move to the right
            dividend *= 10
            qr_list.append((0, dividend % n))

        else:
            # long division step
            quotient, remainder = divmod(dividend, n)
            dividend = remainder * 10

            # check for recurring cycle
            if remainder == 0:  # if expansion terminates
                return 0

            qr_list.append((quotient, remainder))
            for j in range(len(qr_list)-1):
                if qr_list[j][0] == quotient and qr_list[j][1] == remainder:
                    return i-j


def reduce(numerator: int, denominator: int) -> tuple[int, int]:
    """reduces fraction to its lowest terms"""
    # divide numerator, denominator by their GCD
    frac_gcd = gcd(numerator, denominator)
    numerator //= frac_gcd
    denominator //= frac_gcd

    return numerator, denominator


def generate_parasitic_number(n: int, k: int) -> int:
    """generates an n-parasitic number with parameter k, n <= k"""
    denom = 10 * n - 1
    k, denom = reduce(k, denom)
    period = recurring_cycle(denom)

    return k * (10 ** period - 1) // denom


def main():
    # declare variables
    sum_parasitic = 0
    mod = 10**5
    length_limit = 100  # 10^100

    # generate all base parasitic numbers
    for n in range(1, 10):
        for k in range(n, 10):
            p = generate_parasitic_number(n, k)
            length = len(str(p))

            # for example: 142857, 142857142857, ... to length limit
            for repeat in range(1, length_limit // length + 1):
                if int(str(p) * repeat) > 10:
                    sum_parasitic += int(str(p) * repeat)

    # print result
    print(sum_parasitic % mod)


if __name__ == "__main__":
    main()
    