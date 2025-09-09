def problem1660A() -> int:
    a, b = map(int, input().split(" "))  # 1 burles, 2 burles respectively
    if a == 0:  # if no 1 burle coins, can't pay 1 burle
        return 1
    return 2 * b + a + 1

test_cases = int(input())
for _ in range(test_cases):
    print(problem1660A())