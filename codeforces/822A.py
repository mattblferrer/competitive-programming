def problem822A() -> int:
    def factorial(n: int) -> int:
        f = 1
        for i in range(1, n + 1):
            f *= i
        return f
    
    a, b = map(int, input().split(" "))
    return factorial(min(a, b))

print(problem822A())