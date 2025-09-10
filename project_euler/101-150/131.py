"""
If n, p is a valid solution, then n is always a cube k.
k^3+p is always equal to (k+1)^3. 
Therefore, we can look for prime solutions by checking numbers of the form
(k+1)^3 - k^3 for primality.

(k+1)^3 - k^3
k^3 + 3*k^2 + 3*k + 1 - k^3
= 3*k^2 + 3*k + 1
"""
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


# declare variables
limit = 1000000
numPrimes = 0

# calculate n for value of p
k, p = 1, 7

while p < limit:
    if isprime(p):
        numPrimes += 1

    k += 1
    p += 6*k  # calculate next 3k^2 + 3k + 1 for p

# print result
print(numPrimes)
