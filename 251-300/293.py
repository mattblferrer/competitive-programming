def isprime(num: int) -> bool:
    """returns True if num is prime"""
    if num == 2 or num == 3:  # for 2 and 3
        return True
    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(6, int(num**0.5)+3, 6):  # for 6k +- 1
        if num % (i-1) == 0:
            return False
        if num % (i+1) == 0:
            return False
    return True


def next_prime(num: int) -> int:
    """return the smallest prime larger than num"""
    if num % 2 == 0:  # if even
        num -= 1
    while True:
        num += 2
        if isprime(num):
            return num


def main():
    def generate_admissible_numbers(n: int, limit: int, factors: set[int]) -> \
        None:
        """adds admissible numbers, or numbers with consecutive distinct prime 
        factors, to a list recursively by multiplying the number n to given 
        factors"""
        if n > limit:
            return
        admissible_numbers.append(n)  # add n to list if admissible
        prime = next_prime(factors[-1])

        generate_admissible_numbers(n * factors[-1], limit, factors)
        generate_admissible_numbers(n * prime, limit, factors + [prime])


    # declare variables
    admissible_numbers = []
    fortunate_numbers = set()
    limit = 10**9

    # generate sorted list of admissible numbers below limit
    generate_admissible_numbers(2, limit, [2])

    # find psuedo-Fortunate numbers for each admissible number
    for n in sorted(admissible_numbers):
        k = 3  # fortunate number check
        while not isprime(n + k):
            k += 2
        
        fortunate_numbers.add(k)

    # print result
    print(sum(fortunate_numbers))
    

if __name__ == "__main__":
    main()
