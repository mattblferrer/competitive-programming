def problem1490C() -> str:
    x = int(input())
    limit = int(x ** (1/3)) + 1

    for a in range(1, limit):  # iterate for each a
        left, right = a, limit  # binary search for b in a^3 + b^3 = x

        while left < right:
            b = (left + right) // 2
            if a ** 3 + b ** 3 == x:
                return "YES"
            elif a ** 3 + b ** 3 > x:  # b is lower than expected
                right = b 
            else:  # b is higher than expected
                left = b + 1
            
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1490C())