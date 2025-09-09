def problem1716A() -> int:
    n = int(input())
    if n == 1:  # (x + 3, x - 2)
        return 2
    if n == 2 or n == 3:  # x + 2, x + 3 reachable in 1 move
        return 1
    return (n + 2) // 3
    

test_cases = int(input())
for _ in range(test_cases):
    print(problem1716A())