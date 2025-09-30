def problem1760C() -> None:
    _ = input()  # length of array
    strengths = list(map(int, input().split(" ")))
    sorted_strengths = sorted(strengths)

    for s in strengths:
        if s == sorted_strengths[-1]:  # maximum
            print(s - sorted_strengths[-2], end=" ")
        else:
            print(s - sorted_strengths[-1], end=" ")
    print(" ")  # new line for formatting

test_cases = int(input())
for _ in range(test_cases):
    problem1760C()