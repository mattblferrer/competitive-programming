def s(n: int) -> int:
    """returns the smallest number with a digit sum of n"""
    remainder = n % 9
    nines = n // 9
    return int(str(remainder) + "9" * nines)


def fibonacci(n: int) -> int:
    """returns the nth fibonacci number"""
    ctr = 1
    a, b = 0, 1

    while ctr < n:
        a, b = b, a+b
        ctr += 1

    return b


# declare variables
sum_s = 0
fib_numbers = {fibonacci(i) for i in range(2, 91)}

for i in range(1, 10001):
    sum_s += s(i)
    if i in fib_numbers:
        print(i, sum_s % 1_000_000_007, s(i) % 1_000_000_007)

    # TODO find closed formula for s(n) 

# print result
print(sum_s)


