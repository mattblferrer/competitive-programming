from math import isqrt, log


def soe(n: int) -> list[bool]:
    """creates a Sieve of Eratosthenes array of size n"""
    iterlimit = isqrt(n) + 1
    is_prime_list = [True]*n

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
    limit = int(log(800_800, 2) * 800_800) + 1  # limit for prime sieve
    log_limit = log(800_800) * 800_800  # ln(800,800 ^ 800,800)
    is_prime_list = soe(limit)
    prime_list = [i for i, isprime in enumerate(is_prime_list) if isprime]
    log_list = [log(p) for p in prime_list]
    hybrid_integers = 0
    idx_q = len(prime_list) - 1  # starting index for prime q

    # loop through p^q * q^p for primes p, q, p != q
    for idx_p, p in enumerate(prime_list):
        # search backwards through q as log increases for higher p, q
        while idx_p < idx_q:
            hybrid_log = log_list[idx_p] * prime_list[idx_q] + \
            log_list[idx_q] * p  # p^q * q^p

            if hybrid_log <= log_limit:
                hybrid_integers += idx_q - idx_p
                break

            idx_q -= 1  
                
    # print result
    print(hybrid_integers)


if __name__ == "__main__":
    main()
