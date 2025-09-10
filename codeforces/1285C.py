from math import gcd

def problem1285C() -> tuple[int, int]:
    x = int(input())
    for n in range(int(x ** 0.5), 0, -1):
        if x % n == 0 and gcd(n, x // n) == 1:
            return n, x // n

result = problem1285C()
print(result[0], result[1])
