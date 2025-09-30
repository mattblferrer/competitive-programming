def problem80A() -> str:
    def isPrime(n: int) -> bool:
        for i in range(2, int(n ** 0.5) + 1):
            if n % i == 0:
                return False
            
        return True

    a, b = map(int, input().split(" "))
    primes = [n for n in range(2, 100) if isPrime(n)]  # generate list of primes
    i = primes.index(a)
    if primes[i + 1] == b:
        return "YES"
    return "NO"

print(problem80A())