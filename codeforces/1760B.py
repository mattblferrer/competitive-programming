def problem1760B() -> int:
    _ = input()  # length of string
    string = input()
    max_size = max((ord(char) - 96) for char in string)
    return max_size

test_cases = int(input())
for _ in range(test_cases):
    print(problem1760B())