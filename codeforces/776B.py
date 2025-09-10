def problem776B() -> tuple[int, list[int]]:
    def isPrime(n: int) -> bool:
        for i in range(2, int(n ** 0.5) + 1):
            if n % i == 0:
                return False
        return True

    n = int(input())
    if n <= 2:
        return 1, [1] * n
    
    colors = []
    for i in range(2, n + 2):
        if isPrime(i):
            colors.append(1)
        else:
            colors.append(2)

    return 2, colors

result = problem776B()
print(result[0])  # k
print(*result[1])  # color of each piece of jewelry