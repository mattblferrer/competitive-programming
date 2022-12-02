# uses the Tonelli-Shanks algorithm to return the solution to x^2 = n mod p
def tonelli_shanks(n: int, p: int) -> tuple[int, int]:
    if pow(n, (p - 1) // 2, p) == 1:  # check that n is a square mod p
        q = p - 1
        s = 0

        while q % 2 == 0:
            q //= 2
            s += 1

        if s == 1:  # if p = 3 mod 4
            ans = pow(n, (p + 1) // 4, p)
            return ans, -ans

        for z in range(2, p):
            if pow(z, (p - 1) // 2, p) == p - 1:  # check Legendre symbol of z
                m = s
                c = pow(z, q, p)
                r = pow(n, (q + 1) // 2, p)
                t = pow(n, q, p)
                break
        
        while t % p != 1:
            t2 = (t * t) % p
            for i in range(1, m):
                if t2 % p == 1:
                    b = pow(c, 1 << (m - i - 1), p)
                    m = i
                    c = (b * b) % p
                    r = (r * b) % p
                    t = (t * b * b) % p
                    break

                t2 = (t2 * t2) % p

        return r, p - r


# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = int(n ** 0.5) + 1
    isPrimeList = [True]*(n+1)

    # for 0 and 1 
    isPrimeList[0] = isPrimeList[1] = False

    # for 2 and 3
    for i in (2, 3):
        for multiple in range(i*i, n, i):
            # assign multiples of 2 or 3 as not being prime
            isPrimeList[multiple] = False  

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6): 
        for j in (0, 2): 
            for multiple in range((i+j) * (i+j), n, i+j):
                # assign multiples of i+j as not being prime
                isPrimeList[multiple] = False  

    return isPrimeList


def main():
    # declare variables
    limit = 50_000_000
    is_prime_list = soe(int(2 ** 0.5 * (limit + 1)))
    prime_list = [i for i, isprime in enumerate(is_prime_list) if isprime]
    prime_list.remove(2)
    is_square_prime = [True] * (limit + 1)
    is_square_prime[0] = is_square_prime[1] = False  # - 1 is not prime

    # test 2n^2 - 1 for primality using Tonelli-Shanks algorithm 
    for p in prime_list:
        roots = tonelli_shanks((p + 1) // 2, p)
        if roots:
            for root in roots:
                x = root
                while x < 0:
                    x += p
                while x <= limit:
                    if 2*x*x - 1 != p:
                        is_square_prime[x] = False
                    x += p

    primes = sum(is_square_prime)

    # print result
    print(f"Numbers t(n) up to {limit} that are prime: {primes}")


if __name__ == "__main__":
    main()
