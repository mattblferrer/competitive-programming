def ABC180C() -> list[int]:
    n = int(input())
    factors = []
    for i in range(1, int(n ** 0.5) + 1):
        if n % i == 0:
            factors.append(i)
            factors.append(n // i)
            while n % i == 0:
                n //= i

        if i * i > n:
            break

    return sorted(factors)

print(*ABC180C(), sep="\n")