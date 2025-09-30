def problem1296A() -> str:
    _ = input()  # length of array
    arr = list(map(int, input().split(" ")))
    parity = [n % 2 for n in arr]
    arr_sum = sum(arr)
    
    if arr_sum % 2 == 1:  # array sum is already odd
        return "YES"
    if len(set(parity)) == 2:  # both even and odd parity available
        return "YES"
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1296A())