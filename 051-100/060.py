from itertools import permutations
from functools import cache


@cache
# determines if num is prime
def isprime(num: int) -> bool:
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


# generate next prime
def next_prime(num: int) -> int:
    while True:
        num += 2
        if isprime(num):
            return num


# returns the set of all possible primes from concatenating 2 primes in the set
def conc_prime_set(prime_set: list) -> list:
    return [int(str(p1) + str(p2)) for p1, p2 in permutations(prime_set, 2)]


# generator that generates primes x, y, x < y
def prime_x_greater_y_gen(listOfPrimes: list) -> int:
    for i, x in enumerate(listOfPrimes[:-1]):
        for y in listOfPrimes[i+1:]:
            yield x, y


# builds a list of primes for which any two primes concatenate and make another
# prime
def build_conc_prime_set(limit: int, prime_set) -> None:
    if all(isprime(n) for n in conc_prime_set(prime_set)):
        if len(prime_set) == 5:
            # print prime sets found
            print(sum(prime_set), prime_set)
        
        else:
            # call function with one more prime
            max_prime = prime_set[-1]
            max_index = listOfPrimes.index(max_prime)

            for prime in listOfPrimes[max_index+1:]:
                prime_set.append(prime)
                build_conc_prime_set(limit, prime_set)

    else:
        prime_set.pop(-1)


# declare variables
listOfPrimes = []
primeSet = []
prime = 3
index = 0
limit = 10000  # arbitrary limit, can change

# generate list of primes up to limit
while prime < limit:
    listOfPrimes.append(prime)
    prime = next_prime(prime)

prime_length = len(listOfPrimes)

# main loop, iterate through all sets of 5 primes i, j, k, l, m building upwards
for i, j in prime_x_greater_y_gen(listOfPrimes):
    primeSet = build_conc_prime_set(limit, [i, j])
