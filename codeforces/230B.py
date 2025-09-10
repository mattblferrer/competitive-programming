def problem230B() -> None:
    # generate list of all squares of primes up to 10^12
    limit = 10 ** 6
    sieve = [True] * (limit + 1)
    sieve[0] = sieve[1] = False

    for p in range(2, int(limit ** 0.5) + 1):
        for i in range(2 * p, limit + 1, p):
            sieve[i] = False

    prime_squares = set(i * i for i in range(limit + 1) if sieve[i])

    # get queries of T-primes (is T-prime if square of prime)
    _ = input()  # number of integers 
    x = list(map(int, input().split(' ')))

    for x_i in x:
        if x_i in prime_squares:
            print("YES")
        else:
            print("NO")

problem230B()