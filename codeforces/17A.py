def problem17A() -> str:
    def isPrime(n: int) -> bool:
        if n < 2:
            return False
        for i in range(2, int(n ** 0.5) + 1):
            if n % i == 0:
                return False
        return True
    
    n, k = map(int, input().split(' '))
    primes = [i for i in range(2, 1000) if isPrime(i)]
    satisfy = 0  # number of prime numbers that satisfy equation

    for p in primes:
        if p > n:
            break
        for p1, p2 in zip(primes, primes[1:]):  # iterate adjacent primes
            if p1 + p2 + 1 == p:
                satisfy += 1
                break
    
    if satisfy >= k:
        return "YES"
    return "NO"

print(problem17A())