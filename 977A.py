def problem977A() -> int:
    n, k = map(int, input().split(" "))
    while k > 0:  # subtract k times
        if n % 10 == 0:  # last digit 0
            n //= 10
        else:  # last digit nonzero
            n -= 1
        k -= 1

    return n

print(problem977A())