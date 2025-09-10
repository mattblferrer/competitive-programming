def problem1729A() -> int:
    a, b, c = map(int, input().split(" "))
    elevator_1_time = a - 1
    elevator_2_time = abs(b - c) + abs(c - 1)

    if elevator_1_time < elevator_2_time:
        return 1
    elif elevator_1_time > elevator_2_time:
        return 2
    else:
        return 3

test_cases = int(input())
for _ in range(test_cases):
    print(problem1729A())