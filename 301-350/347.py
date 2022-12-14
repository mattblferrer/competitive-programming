from math import isqrt


# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = isqrt(n) + 1
    isPrimeList = [True]*n

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


# returns the largest number k <= N only divisible by primes p, q 
def M(p: int, q: int, N: int) -> int:
    if p * q > N:
        return 0

    k = p * q
    largest = k

    while k <= N:
        m = k

        while m <= N:
            if largest < m:
                largest = m
            m *= q  
            
        k *= p
    
    return largest


def main():
    # declare variables
    n = 10_000_000
    is_prime_list = soe(n)
    prime_list = [i for i, isprime in enumerate(is_prime_list) if isprime]
    s = 0

    # loop through all p, q prime pairs, p < q
    for idxp, p in enumerate(prime_list):
        for idxq, q in enumerate(prime_list[idxp + 1:]):
            ans = M(p, q, n)
            
            if not ans:  # # break loop when p*q > N
                break
            s += ans
            
        if not idxq:  # break loop when p*q > N for first q (p > sqrt(n))
            break

    # print result
    print(s)


if __name__ == "__main__":
    main()
