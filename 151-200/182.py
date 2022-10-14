# returns the prime factors of num (non-repeating)
def prime_factorize(num: int) -> set:
    factors = set()

    for i in [2, 3]:
        while num % i == 0:
            factors.add(i)
            num //= i

    for i in range(6, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        for j in [-1, 1]:
            while num % (i+j) == 0:
                factors.add(i+j)
                num //= (i+j)

    if num != 1:
        factors.add(num)

    return factors


# yields every e such that the number of unconcealed messages is at a minimum
def arithmetic_progression_rsa() -> int:
    for e in range(minimum[1] + minDiff, phi, minDiff):
        if isCoprime[e]:
            # check divisibility of e-1
            if all((fac == 2 or (e-1) % fac) for fac in factors): 
                yield e


# declare variables
p, q = 1009, 3643
n, phi = p*q, (p-1)*(q-1)
unconc = [0]*phi  # number of unconcealed messages
sumE = 0  # sum of all minimal values of e
factors = prime_factorize(phi)

# sieve through all e where gcd(e, phi) = 1
isCoprime = [True]*phi
for fac in factors:
    for mult in range(fac, phi, fac):
        isCoprime[mult] = False

# find e where the number of unconcealed messages are at a minimum
minimum = []
minUnconc = 9

for e in range(3, phi, 2):  # since (p-1)*(q-1) is always even
    if isCoprime[e]:
        for m in range(n):
            if pow(m, e, n) == m:  # compute m^e mod n
                unconc[e] += 1
            if unconc[e] > minUnconc:  # no need to compute
                break
        if unconc[e] == minUnconc:  # check if minimum
            minimum.append(e)
            sumE += e

    if len(minimum) == 2:  # calculate difference in arithmetic progression
        minDiff = minimum[1] - minimum[0]
        break

sumE += sum(e for e in arithmetic_progression_rsa())

# print result
print(f"Sum of all valid values of e: {sumE}")
