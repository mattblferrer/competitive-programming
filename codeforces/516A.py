def problem516A() -> int:
    def factorial(n: int) -> int:
        fac = 1
        for i in range(1, n + 1):
            fac *= i
        return fac

    n = int(input())
    a = list(map(int, list(input())))
    factorials = [factorial(i) for i in [7, 5, 3, 2]]

    product = 1
    for a_i in a:
        product *= factorial(a_i)

    digits = ""
    for i, f in zip([7, 5, 3, 2], factorials):  # only need factorials of primes
        while product % f == 0:
            digits += str(i)
            product //= f     

    return int(digits)

print(problem516A())