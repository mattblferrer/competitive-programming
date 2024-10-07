from math import gcd

def problem1498A() -> int:
    n = int(input())
    x = n
    while True:
        sum_of_digits = sum(int(digit) for digit in str(x))
        gcd_sum = gcd(x, sum_of_digits)
        if gcd_sum > 1:
            return x
            
        x += 1


test_cases = int(input())
for _ in range(test_cases):
    print(problem1498A())