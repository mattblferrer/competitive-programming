from math import gcd

def problem854A() -> tuple[int, int]:
    n = int(input())
    for a in range(n // 2, 0, -1):  # for proper fraction, a < b
        if gcd(a, n - a) == 1:  # if gcd == 1, fraction irreducible
            return a, n - a

print(*problem854A())