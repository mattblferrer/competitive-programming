from collections import Counter

def problem1616A() -> int:
    _ = input()  # length of array
    counts = Counter(map(int, input().split(" ")))
    diff_values = 0

    for n, c in counts.items():
        if n != 0 and c > 1:  # can be -n, +n
            if -n in counts:
                diff_values += 1
            else:
                diff_values += 2
        else:
            diff_values += 1

    return diff_values

test_cases = int(input())
for _ in range(test_cases):
    print(problem1616A())