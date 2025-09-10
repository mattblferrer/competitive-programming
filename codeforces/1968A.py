from math import gcd

def problem1968A() -> int:
    x = int(input())
    maximum = 0
    
    for y in range(1, x):
        current = gcd(x, y) + y
        if maximum < current:
            maximum = current
            max_y = y

    return max_y

test_cases = int(input())
for _ in range(test_cases):
    print(problem1968A())