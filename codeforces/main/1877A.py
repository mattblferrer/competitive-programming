def problem1877A() -> int:
    n = int(input())
    return -sum(map(int, input().split()))
 
test_cases = int(input())
for _ in range(test_cases):
    print(problem1877A())