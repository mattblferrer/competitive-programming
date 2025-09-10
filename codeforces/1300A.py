def problem1300A() -> int:
    _ = input()  # length of array arr
    arr = list(map(int, input().split(" ")))
    zeros = arr.count(0)
    new_sum = zeros + sum(arr)  # sum after making the product nonzero

    if new_sum == 0:
        return zeros + 1
    return zeros

test_cases = int(input())
for _ in range(test_cases):
    print(problem1300A())