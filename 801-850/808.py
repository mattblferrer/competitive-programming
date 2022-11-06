from math import isqrt


# function that tells if a number num is a palindrome
def is_palindrome(num: int) -> bool:
    if str(num) == str(num)[::-1]:  # if num == reverse(num)
        return True
    return False


# determines if num is prime
def isprime(num: int) -> bool:
    if num < 2:  # inputs can be negative
        return False

    if num == 2 or num == 3:  # for 2 and 3
        return True

    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(5, isqrt(num)+3, 6):  # for 6k +- 1
        if num % i == 0 or num % (i+2) == 0:
            return False
    return True


# generate next prime
def next_prime(num: int) -> int:
    if num % 2 == 0:
        num -= 1

    while True:
        num += 2
        if isprime(num):
            return num


def main():
    # declare variables
    square_sum = 0
    n = 13  # first non-palindrome, two digit square
    ctr = 0
    pow10 = 2

    # loop through squares in ascending order
    while ctr < 50:
        if not is_palindrome(n):
            # calculate square of prime, square of reverse of prime
            n_rev = int(str(n)[::-1])
            n_sqr = n * n
            n_revsqr = n_rev * n_rev

            # check for primality
            if n_sqr == int(str(n_revsqr)[::-1]) and isprime(n_rev):
                print(ctr, n_sqr, pow10)
                square_sum += n_sqr
                ctr += 1

        # reversible square primes can only start with 1 or 9
        if n_sqr > 2 * 10**pow10:  
            pow10 += 1
            n = next_prime(isqrt(10**pow10 - 10**(pow10 - 1)))

        else:
            n = next_prime(n)

    # print result
    print(f"The sum of the first 50 reversible prime squares is {square_sum}")


if __name__ == "__main__":
    main()
