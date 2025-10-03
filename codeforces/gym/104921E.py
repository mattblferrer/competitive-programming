def problem1899A() -> str:
    n = int(input())
    if n % 3 == 0:
        return "Second"
    return "First"
 
test_cases = int(input())
for _ in range(test_cases):
    print(problem1899A())