def ABC144C() -> int:
    n = int(input())
    for i in range(int(n ** 0.5), 0, -1):
        if n % i == 0:
            return i + n // i - 2

print(ABC144C())