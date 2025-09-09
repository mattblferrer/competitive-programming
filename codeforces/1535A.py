def problem1535A() -> str:
    s1, s2, s3, s4 = map(int, input().split(" "))
    if max(s1, s2) < min(s3, s4) or max(s3, s4) < min(s1, s2):
        return "NO"
    return "YES"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1535A())