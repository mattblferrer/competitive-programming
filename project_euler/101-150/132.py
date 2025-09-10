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
    # create a sieve of Eratosthenes
    limit = 1_000_000
    is_prime_list = soe(limit)  

    # declare variables
    k = 10**9  # repunit exponent
    factor_sum = 0
    factor_num = 0

    # main loop
    for i, isprime in enumerate(is_prime_list):
        if not isprime or i == 3:   # ignore if num is composite or 3
            continue
        if factor_num >= 40:
            break
        if pow(10, k, i) == 1:
            factor_sum += i
            factor_num += 1
            print(i)
        
    # print result
    print(f"Sum of factors: {factor_sum}")


if __name__ == "__main__":
    main()
