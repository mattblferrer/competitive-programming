from math import sqrt


# determines if num is prime
def isprime(num: int) -> bool:
    if num == 2 or num == 3:  # for 2 and 3
        return True

    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(6, int(sqrt(num))+3, 6):  # for 6k +- 1
        if num % (i-1) == 0:
            return False
        if num % (i+1) == 0:
            return False
    return True


# generate next prime
def next_prime(num: int) -> int:
    while True:
        num += 2
        if isprime(num):
            return num


# determine if prime is truncatable from left to right
def is_left_truncatable(num: int) -> bool:
    while num > 10:
        length = len(str(num)) - 1  # highest power of 10 smaller than num

        # truncating number from left
        if not isprime(num):
            return False
        num = num % (10**length)      

    return num in [2, 3, 5, 7]


# determine if prime is truncatable from right to left
def is_right_truncatable(num: int) -> bool:
    while num > 10:
        # truncating number from right
        if not isprime(num):
            return False
        num = num // 10
        
    return num in [2, 3, 5, 7]


def main():
    # define variables
    current_prime = 11
    truncatable_sum = 0  # output
    number_of_primes = 0  # we need to have 11 primes

    while number_of_primes < 11:
        # iterate through primes
        current_prime = next_prime(current_prime)

        # check if prime is truncatable from left and from right
        if (is_left_truncatable(current_prime)) and (
            is_right_truncatable(current_prime)):
            number_of_primes += 1
            truncatable_sum += current_prime

    print("The sum of all eleven left and right truncatable primes is " \
        f"{truncatable_sum}")


if __name__ == "__main__":
    main()
