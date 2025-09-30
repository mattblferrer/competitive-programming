def problem1992A() -> int:
    a, b, c = map(int, input().split(" "))
    for _ in range(5):
        minimum = min(a, b, c)
        if minimum == a:
            a += 1
        elif minimum == b:
            b += 1
        else:
            c += 1
    
    return a * b * c

test_cases = int(input())
for _ in range(test_cases):
    print(problem1992A())