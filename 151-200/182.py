# returns the prime factors of num (non-repeating)
def prime_factorize(num):
    factors = set()

    while num % 2 == 0:  # for only even prime
        factors.add(2)
        num //= 2

    while num % 3 == 0:  # for 3
        factors.add(3)
        num //= 3

    for i in range(6, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        while num % (i-1) == 0:
            factors.add(i-1)
            num //= (i-1)
            
        while num % (i+1) == 0:
            factors.add(i+1)
            num //= (i+1)

    if num != 1:
        factors.add(num)

    return factors


# declare variables
p = 1009
q = 3643
n = p*q
phi = (p-1)*(q-1)
unconc = [0]*phi  # number of unconcealed messages
sumE = 0  # sum of all minimal values of e
factors = prime_factorize(phi)

# sieve through all e where gcd(e, phi) = 1
isCoprime = [True]*phi
for fac in factors:
    mult = fac

    while mult < phi:
        isCoprime[mult] = False
        mult += fac

# find e where the number of unconcealed messages are at a minimum
minimum = []
minUnconc = 9

for e in range(3, phi, 2):  # since (p-1)*(q-1) is always even
    if isCoprime[e]:
        for m in range(n):
            if pow(m, e, n) == m:  # compute m^e mod n
                unconc[e] += 1
            if unconc[e] > minUnconc:  # if unconcealed > minimum, no need to compute
                break
        if unconc[e] == minUnconc:  # check if minimum
            minimum.append(e)
            sumE += e

    if len(minimum) == 2:  # calculate difference in arithmetic progression
        minDiff = minimum[1] - minimum[0]
        break

for e in range(minimum[1] + minDiff, phi, minDiff):  # check arithmetic progression of mins
    if isCoprime[e]:
        isPossible = True  # if e is a possible candidate for minimum
        for fac in factors:
            if fac != 2 and (e-1) % fac == 0:  # check divisibility of e-1
                isPossible = False
                break

        if isPossible:
            sumE += e

# print result
print("Sum of all valid values of e:", sumE)
