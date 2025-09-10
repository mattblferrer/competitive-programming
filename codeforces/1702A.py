def problem1702A() -> int:
    m = input()  # take input as string so length can be taken
    power_of_10 = 10 ** (len(m) - 1)
    return int(m) - power_of_10

test_cases = int(input())
for _ in range(test_cases):
    print(problem1702A())