# returns the nth fibonacci number
def fibonacci(n: int) -> int:
    ctr = 1
    a, b = 0, 1

    while ctr < n:
        a, b = b, a+b
        ctr += 1

    return b


# number of positive integers with X(n, 2n, 3n) <= 2**k = fibonacci(k+2)
zero_count = fibonacci(32)

# print result
print(f"The number of positive integers with X(n, 2n, 3n) = 0 is {zero_count}")
