def problem1829A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        s = input()
        different = 0  # number of indices i where s[i] differs

        for char1, char2 in zip(s, "codeforces"):
            if char1 != char2:
                different += 1

        print(different)

problem1829A()