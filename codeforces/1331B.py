def problem1331B() -> int:
    a = int(input())
    for i in range(2, a + 1):
        if a % i == 0:
            return int(str(i) + str(a // i))

print(problem1331B())