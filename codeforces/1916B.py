from math import gcd

def problem1916B() -> int:
    a, b = map(int, input().split())
    if b % a == 0:
        return b * b // a
    else:
        return b * a // gcd(a, b)

test_cases = int(input())
for _ in range(test_cases):
    print(problem1916B())