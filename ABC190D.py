def ABC190D() -> int:
    n = int(input())
    while n % 2 == 0:
        n //= 2

    factors = 0
    for i in range(1, int(n ** 0.5) + 1):
        if n % i == 0:
            factors += 1
            if i != (n // i):
                factors += 1
    
    return factors * 2

print(ABC190D())