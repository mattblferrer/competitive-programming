def e_term(n: int) -> int:
    """returns the term needed for the n'th term of continued fraction of e"""
    return ((n - 2) // 3 + 1) * 2 if n % 3 == 2 else 1


def e_convergent(n: int) -> tuple[int]:
    """returns the nth convergent of e"""
    n -= 1  # offset
    numerator = 1
    denominator = e_term(n)

    # if 1st term
    if n == 0:
        return 2, 1

    # iterate upwards in the continued fraction
    for i in range(n - 1, 0, -1):
        frac_term = e_term(i)

        # add current fraction to next term in continued fraction
        numerator += frac_term*denominator
        numerator, denominator = denominator, numerator  # reciprocal

    # add 2 to final fraction
    numerator += 2*denominator
    return numerator, denominator


def main():
    # declare variables
    sum_of_digits = sum(int(digit) for digit in str(e_convergent(100)[0]))

    # print output
    print("The sum of the digits of the 100th convergent of e is " \
        f"{sum_of_digits}")


if __name__ == "__main__":
    main()
