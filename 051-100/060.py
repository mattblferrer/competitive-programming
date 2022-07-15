from itertools import permutations


# determines if num is prime
def isprime(num):
    if num % 2 == 0:  # for even numbers
        return False

    for i in range(3, int(num**0.5+1), 2):  # for odd numbers
        if num % i == 0:
            return False
    return True


# generate next prime
def next_prime(num):
    while True:
        num += 2
        if isprime(num):
            return num


# returns the set of all possible primes from concatenating 2 primes in the set
def conc_prime_set(prime_set):
    return [int(str(p1) + str(p2)) for p1, p2 in list(permutations(prime_set, 2))]


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
for i in range(prime_length - 4):
    # 1st prime (starting prime) in list
    prime = listOfPrimes[i]

    for j in range(i + 1, prime_length - 3):
        # 2nd prime in list
        prime_2 = listOfPrimes[j]
        primeSet.append(prime)
        primeSet.append(prime_2)

        if all(isprime(n) for n in conc_prime_set(primeSet)):
            # 3rd prime in list
            for k in range(j + 1, prime_length - 2):
                prime_3 = listOfPrimes[k]
                primeSet.append(prime_3)

                if all(isprime(n) for n in conc_prime_set(primeSet)):
                    # 4th prime in list
                    for l in range(k + 1, prime_length - 1):
                        prime_4 = listOfPrimes[l]
                        primeSet.append(prime_4)

                        if all(isprime(n) for n in conc_prime_set(primeSet)):
                            # 5th prime in list
                            for m in range(l + 1, prime_length):
                                prime_5 = listOfPrimes[m]
                                primeSet.append(prime_5)

                                if all(isprime(n) for n in conc_prime_set(primeSet)):
                                    print(primeSet, sum(primeSet))
                                else:
                                    primeSet.pop(-1)
                                    continue
                        else:
                            primeSet.pop(-1)
                            continue
                else:
                    primeSet.pop(-1)
                    continue
        else:
            primeSet = []
            continue
