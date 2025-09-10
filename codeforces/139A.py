def problem139A() -> int:
    n = int(input())
    days = list(map(int, input().split()))
    curr = 0

    while True:
        n -= days[curr]
        if n <= 0:
            return curr + 1
        curr = (curr + 1) % 7

print(problem139A())