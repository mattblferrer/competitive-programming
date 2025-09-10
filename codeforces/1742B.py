def problem1742B() -> str:
    _ = input()  # length of array
    arr = sorted(list(map(int, input().split(" "))))
    for a, b in zip(arr, arr[1:]):  # check if adjacent elements equal
        if a == b:
            return "NO"
    
    return "YES"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1742B())