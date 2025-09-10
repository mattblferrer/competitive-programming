def problem1788A() -> int:
    _ = input()  # length of array
    a = list(map(int, input().split(" ")))
    left_2, right_2 = 0, a.count(2)

    if right_2 % 2 == 1:  # if odd 2's in a, no way to distribute evenly
        return -1
    
    index = 0
    while True:
        if a[index] == 2:
            left_2 += 1
            right_2 -= 1
        if left_2 == right_2:
            return index + 1  # since 1-indexed array
        index += 1

test_cases = int(input())
for _ in range(test_cases):
    print(problem1788A())