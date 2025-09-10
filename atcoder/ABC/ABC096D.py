def ABC096D() -> int:
    def isPrime(n: int) -> bool:
        for i in range(2, int(n ** 0.5) + 1):
            if n % i == 0:
                return False       
        return True

    n = int(input())
    arr = []

    # since 5 (10k + 9) primes when added = 10m + 45 -> composite
    for k in range(9, 55556, 10):  
        if isPrime(k):
            arr.append(k)
        if len(arr) == n:
            return arr

print(*ABC096D())