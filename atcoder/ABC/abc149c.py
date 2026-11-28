def ABC149C() -> int:
    def isPrime(n: int) -> bool:
        for i in range(2, int(n ** 0.5) + 1):
            if n % i == 0:
                return False
        return n > 1

    x = int(input())
    while True:
        if isPrime(x):
            return x
        x += 1

print(ABC149C())