from math import gcd

def problem1789A() -> str:
    n = int(input())
    arr = list(map(int, input().split(" ")))
    min_pair_gcd = float('inf')

    for i in range(n):
        for j in range(i + 1, n):
            pair_gcd = gcd(arr[i], arr[j])
            min_pair_gcd = min(min_pair_gcd, pair_gcd)

    if min_pair_gcd < 3:
        return "Yes"
    else:
        return "No"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1789A())