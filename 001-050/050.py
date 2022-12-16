from math import sqrt


# creates a Sieve of Eratosthenes array of size n
def soe(n: int) -> list:
    iterlimit = int(sqrt(n)) + 1
    isPrimeList = [True]*n

    # for 0 and 1 
    isPrimeList[0] = isPrimeList[1] = False

    # for 2 and 3
    for i in [2, 3]:
        for multiple in range(i*i, n, i):
            # assign multiples of 2 or 3 as not being prime
            isPrimeList[multiple] = False  

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6): 
        for j in [0, 2]: 
            for multiple in range((i+j) * (i+j), n, i+j):
                # assign multiples of i+j as not being prime
                isPrimeList[multiple] = False  

    return isPrimeList


def main():
    # declare variables
    limit = 1_000_000
    maximum_length = 0  # length of longest sum of consecutive primes
    maximum_prime = 0

    # create list and set of primes for faster searching
    is_prime_list = soe(limit)
    primes = [idx for idx, isprime in enumerate(is_prime_list) if isprime]
    prime_set = set(primes)

    # main loop
    for idx, prime in enumerate(primes): # iterate through starting primes
        sum_primes = prime
        length = 0
        
        # calculate sums of consecutive primes
        while sum_primes < limit:
            length += 1
            sum_primes += primes[idx + length]

        # backtrack to find highest lower than limit
        sum_primes -= primes[idx + length]  

        # check if chain of primes is the longest
        if sum_primes in prime_set and length > maximum_length:
            maximum_length = length  # find length of chain 
            maximum_prime = sum_primes

        if length < maximum_length:  # if no longer chain can be made
            break

    # print result
    print(f"The prime below {limit} that can be written as the sum of the "\
    f"most consecutive primes is {maximum_prime}, length: {maximum_length}")


if __name__ == "__main__":
    main()
