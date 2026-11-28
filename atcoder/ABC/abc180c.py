def ABC180C() -> list[int]:
    n = int(input())
    factors = set([1, n])
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            factors.add(i)
            factors.add(n // i)

    return sorted(factors)

print(*ABC180C(), sep="\n")