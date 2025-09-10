from math import isqrt


def soe(n: int) -> list[bool]:
    """creates a Sieve of Eratosthenes array of size n"""
    iterlimit = isqrt(n) + 1
    is_prime_list = [True]*(n + 1)

    # for 0 and 1 
    is_prime_list[0] = is_prime_list[1] = False

    # for 2 and 3
    for i in (2, 3):
        for multiple in range(i*i, n, i):
            # assign multiples of 2 or 3 as not being prime
            is_prime_list[multiple] = False  

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6): 
        for j in (0, 2): 
            for multiple in range((i+j) * (i+j), n, i+j):
                # assign multiples of i+j as not being prime
                is_prime_list[multiple] = False  

    return is_prime_list


def is_progressive(n: int) -> bool:
    """returns True if a number n's square is progressive, or has a dividend,
    quotient, and remainder with a common ratio"""
    def prime_factorize(num: int) -> set[int]:
        """returns the prime factors of num (non-repeating)"""
        factors = set()

        for i in (2, 3):
            while num % i == 0:
                factors.add(i)
                num //= i

        for i in range(5, isqrt(num) + 1, 6):  # for 6k +- 1
            if i*i > num:
                break

            for j in (0, 2):
                while num % (i+j) == 0:
                    factors.add(i+j)
                    num //= (i+j)

        if num != 1:
            factors.add(num)

        return factors


    sqr = n*n
    factors = prime_factorize(n)
    iterlimit = int(n**(2/3))

    for fac in factors:
        for d in range(n - n % (fac*fac), iterlimit, -fac*fac):
            q, r = divmod(sqr, d)  # calculate remainder and quotient

            if r*q == d*d:  # check if geometric
                print(n, r, d, q, fac)  # print progressive n
                return True
    return False


def main():
    # declare variables
    limit = isqrt(10**12)
    progressive_sum = 9  # include 9 as given

    # create a sieve of Eratosthenes
    is_prime_list = soe(limit)

    # iterate through values of i
    for i in range(4, limit):
        if not is_prime_list[i] and is_progressive(i):
            progressive_sum += i*i

    # print result
    print(f"The sum of all progressive perfect squares is: {progressive_sum}")


if __name__ == "__main__":
    main()
