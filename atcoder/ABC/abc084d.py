def ABC084D() -> None:
    def isPrime(n: int) -> bool:
        if n < 2:
            return False
        for i in range(2, int(n ** 0.5) + 1):
            if n % i == 0:
                return False
        return True

    def is2017Like(n: int) -> bool:
        return n in primes and (n + 1) // 2 in primes

    # generate all primes, 2017-like numbers below bound (10**5)
    bound = 10**5 + 1
    primes = set(i for i in range(2, bound) if isPrime(i))
    like_numbers = [i for i in range(3, bound, 2) if is2017Like(i)]
    like_numbers.append(bound)
    like_below = {}  # (n: number of 2017-like numbers below n) pairs

    # generate like_below
    count = 0
    for i in range(1, bound + 2, 2):
        like_below[i] = count
        if like_numbers[count] == i:
            count += 1

    # answer [l_i, r_i] queries
    q = int(input())
    for _ in range(q):
        l_i, r_i = map(int, input().split())
        print(like_below[r_i + 2] - like_below[l_i])

ABC084D()