# calculates the factorial of n
def factorial(n: int) -> int:
    fac = 1  # factorial
    for i in range(1, n + 1):
        fac *= i
    return fac


def main():
    # the function n choose r
    def combination(n: int, r: int) -> int:
        return factorials[n] // (factorials[r] * factorials[n - r])


    # declare variables
    limit = 1_000_000
    greater_values = 0  # number of values of nCr greater than limit

    # generate all factorial values from 1 to 100
    factorials = [factorial(i) for i in range(101)]

    # check all nCr values
    for n in range(10, 101):  # start at 10! > 1000000
        for r in range(1, n+1):
            if combination(n, r) > limit:
                greater_values += 1

    # print output
    print(f"The number of values of nCr greater than {limit} is "\
        f"{greater_values}")


if __name__ == "__main__":
    main()
