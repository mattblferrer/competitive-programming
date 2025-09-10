def problem1790A() -> int:
    pi = "314159265358979323846264338327"
    n = input()  # string of digits remembered by Polycarp
    matching = 0

    for d1, d2 in zip(pi, n):  # compare digits d1, d2 from pi, n
        if d1 != d2:
            break
        matching += 1

    return matching

test_cases = int(input())
for _ in range(test_cases):
    print(problem1790A()) 