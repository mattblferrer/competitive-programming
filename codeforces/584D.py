def problem584D() -> tuple[int, list[int]]:
    def isPrime(n: int) -> bool:
        for i in range(2, int(n ** 0.5) + 1):
            if n % i == 0:
                return False
        return n > 1

    n = int(input())
    if isPrime(n):
        return 1, [n]
    for diff in range(2, n, 2):
        for p1 in range(3, diff, 2):
            p2 = diff - p1
            p3 = n - diff
            if isPrime(p1) and isPrime(p2) and isPrime(p3):
                return 3, [p1, p2, p3]

result = problem584D()
print(result[0])
print(*result[1])