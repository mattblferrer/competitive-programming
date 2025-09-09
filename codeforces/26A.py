def problem26A() -> int:
    def isPrime(n: int) -> bool:
        if n < 2:
            return False
        for i in range(2, int(n ** 0.5) + 1):
            if n % i == 0:
                return False
        return True

    def isAlmostPrime(n: int) -> bool:
        if n < 2:
            return False
        
        factors = set()
        for i in range(2, int(n ** 0.5) + 1):
            while n % i == 0:
                factors.add(i)
                n //= i
        if n in primes:
            factors.add(n)
        return len(factors) == 2

    n = int(input())
    primes = set(i for i in range(1, n + 1) if isPrime(i))
    almost_primes = 0
    for i in range(1, n + 1):
        if isAlmostPrime(i):
            almost_primes += 1

    return almost_primes

print(problem26A())