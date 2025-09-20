from itertools import permutations
from functools import cache


@cache
def isprime(num: int) -> bool:
    """determines if num is prime"""
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
    """generate next prime"""
    while True:
        num += 2
        if isprime(num):
            return num


def conc_prime_set(prime_set: list) -> list:
    """returns the set of all possible primes from concatenating 2 primes 
    in the set"""
    return [int(str(p1) + str(p2)) for p1, p2 in permutations(prime_set, 2)]


def prime_x_greater_y_gen(prime_list: list):
    """generator that generates primes x, y, x < y"""
    for i, x in enumerate(prime_list[:-1]):
        for y in prime_list[i + 1:]:
            yield x, y


def main():
    def build_conc_prime_set(limit: int, prime_set) -> list[int]:
        """builds a list of primes for which any two primes concatenate and 
        make another prime"""
        if all(isprime(n) for n in conc_prime_set(prime_set)):
            if len(prime_set) == 5:
                # print prime sets found
                print(sum(prime_set), prime_set)
            
            else:
                # call function with one more prime
                max_prime = prime_set[-1]
                max_index = prime_list.index(max_prime)

                for prime in prime_list[max_index + 1:]:
                    prime_set.append(prime)
                    build_conc_prime_set(limit, prime_set)

        else:
            prime_set.pop(-1)


    # declare variables
    prime_list = []
    prime = 3
    limit = 10_000  # arbitrary limit, can change

    # generate list of primes up to limit
    while prime < limit:
        prime_list.append(prime)
        prime = next_prime(prime)

    # main loop, iterate through all sets of 5 primes building upwards
    for i, j in prime_x_greater_y_gen(prime_list):
        build_conc_prime_set(limit, [i, j])


if __name__ == "__main__":
    main()
