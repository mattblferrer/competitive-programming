def problem1421A() -> str:
    a, b = map(int, input().split())
    return ((a & b) ^ a) + ((a & b) ^ b)
 
test_cases = int(input())
for _ in range(test_cases):
    print(problem1421A())