def problem2036A() -> str:
    n = int(input())
    a = list(map(int, input().split(' ')))
    for curr, next in zip(a, a[1:]):
        if abs(next - curr) not in [5, 7]:
            return "NO"
        
    return "YES"

test_cases = int(input())
for _ in range(test_cases):
    print(problem2036A())