# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = int(n**0.5) + 1
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


def main():
    # declare variables
    limit = 10**8
    is_prime_list = soe(limit)
    prime_list = [i for i, is_prime in enumerate(is_prime_list) if is_prime]
    prime_set = set(prime_list)
    abc_sum = 0

    # iterate through primes a, b and find c from geometric sequence
    for idxa, a in enumerate(prime_list):
        for b in prime_list[idxa + 1:]:
            a1, b1 = a + 1, b + 1
            c1 = b1*b1 / a1
            c = c1 - 1

            if c > limit:
                break

            if c in prime_set:
                abc_sum += int(a + b + c)

        print(idxa, a)

    # print result
    print(f"S({limit}) = {abc_sum}")


if __name__ == "__main__":
    main()
