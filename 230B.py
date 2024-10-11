def problem230B() -> None:
    cache = {}  # dynamic programming cache of isPrime values

    def isPrime(n: int) -> bool:
        if n < 2:
            return False
        for i in range(2, int(n ** 0.5) + 1):
            if n % i == 0:
                return False
        return True

    _ = input()  # number of integers 
    test = list(map(int, input().split(' ')))

    for n in test:
        sqrt = int(n ** 0.5)

        if sqrt ** 2 != n:  # test if perfect square
            print("NO")
            continue

        if sqrt in cache:
            is_prime = cache[sqrt]
        else:
            is_prime = isPrime(sqrt)
            cache[sqrt] = is_prime
        if is_prime:  # test if square of prime
            print("YES")
        else:
            print("NO")

problem230B()