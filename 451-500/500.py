"""
Let a(n) be the smallest number with 2^n divisors. 
We can express a(n) as the product of n terms of the Fermi-Dirac primes:
numbers p^(2^k), for integer k and prime p. 

Source: https://oeis.org/A037992 
 """


from math import sqrt, log


# determines if num is a Fermi-Dirac prime
def is_fd_prime(num: int) -> bool:
    power = 0

    if num % 2 == 0:  # for even numbers
        while num % 2 == 0:
            num //= 2
            power += 1

        # check if power of 2 and exponent == 2^k
        return num == 1 and log(power, 2).is_integer()

    for i in range(3, int(sqrt(num))+1, 2):  # for odd numbers
        if num % i == 0:
            while num % i == 0:
                num //= i
                power += 1

            # check if exponent == 2^k
            return num == 1 and log(power, 2).is_integer()
        
    # if no factors below sqrt(n) divide n
    return True


def main():
    # declare variables
    limit = 500_500
    mod = 500_500_507
    x = 1  # output
    primes = 0
    n = 2  # number being checked

    while primes < limit:
        if is_fd_prime(n):
            primes += 1
            x *= n

            if x > mod:  # calculate mod
                x = x % mod

        n += 1
        
    # print result
    print(x)


if __name__ == "__main__":
    main()
