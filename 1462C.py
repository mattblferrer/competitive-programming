def problem1462C() -> int:
    x = int(input())
    if x > 45: 
        return -1
    
    number = ""
    numbers = set(range(9, 0, -1))
    while x > 0:
        can_use = min(x, max(numbers))
        number += str(can_use)
        x -= can_use

    return int(number[::-1])

test_cases = int(input())
for _ in range(test_cases):
    print(problem1462C())