def problem1033B() -> str:
    def isPrime(n: int) -> bool:
        if n < 2:
            return False
        for i in range(2, int(n ** 0.5) + 1):
            if n % i == 0:
                return False
        return True

    a, b = map(int, input().split(' '))
    if a - b == 1:  # since a^2 - b^2 = (a + b)(a - b), a - b has to be = 1
        if isPrime(a + b):
            return "YES"
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1033B())