from math import sqrt


def soe(n: int) -> list[bool]:
    """creates a Sieve of Eratosthenes array of size n"""
    iterlimit = int(sqrt(n)) + 1
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


def main():
    # declare variables
    limit = 5 * 10**7  # 50 million
    is_prime_list = soe(int(sqrt(limit)) + 1)
    expressible_numbers = set()
    a = 0

    # create list of primes
    prime_list = [i for i, isp in enumerate(is_prime_list) if isp]

    # calculate root
    limit_4 = int(limit**(1/4)) + 1

    # iterate through all a, b, c for which a^4 + b^3 + c^2 < limit
    while prime_list[a] < limit_4:
        # calculate root, reset b
        limit_3 = int((limit - a**4)**(1/3)) + 1
        b = 0

        while prime_list[b] < limit_3:
            # calculate root, reset c
            limit_2 = int((limit - a**3)**(1/2)) + 1
            c = 0

            while prime_list[c] < limit_2:
                # calculate sum and compare against existing set
                n = prime_list[a]**4 + prime_list[b]**3 + prime_list[c]**2

                if n < limit:
                    expressible_numbers.add(n)
                c += 1
            b += 1
        a += 1

    # print result
    print(len(expressible_numbers))


if __name__ == "__main__":
    main()
