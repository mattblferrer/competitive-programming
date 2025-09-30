def problem1475A() -> str:
    n = int(input())
    if n.bit_count() == 1:  # test if power of 2 
        return "NO"
    return "YES"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1475A())