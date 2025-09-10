def problem1791A() -> None:
    test_cases = int(input())
    letter_set = set("codeforces")

    for _ in range(test_cases):
        char = input()
        if char in letter_set:
            print("YES")
        else:
            print("NO")

if __name__ == "__main__":
    problem1791A()