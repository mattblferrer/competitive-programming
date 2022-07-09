"""
For any given integer m and n, m > n > 0: and integer k
a = k*(m^2 - n^2)
b = k*(2mn)
c = k*(m^2 + n^2),

generates all Pythagorean triples if m and n are coprime and are not both odd
"""
from math import gcd


# returns True if two numbers are coprime, False otherwise
def is_coprime(n1, n2):
    if gcd(n1, n2) == 1:
        return True
    return False


# declare variables
sumABC = 1500000
triangle_array = [0]*(sumABC+1)
limit = int(sumABC ** 0.5) + 1  # loop iteration limit

# iterate through all possible m, n, m > n > 0 to generate primitive triples
for m in range(1, limit+1):
    for n in range(1, m):
        k = 1  # multiplier
        a, b, c = 0, 0, 0  # reset a, b, c

        while a+b+c <= sumABC:
            if is_coprime(m, n):  # only compute when m and n are coprime
                a = k*(m**2 - n**2)
                b = k*2*m*n
                c = k*(m**2 + n**2)

                if a+b+c <= sumABC:
                    if a % 2 == 0:  # pythagorean triple will have duplicate for even a
                        if a < b:  # return only one of the two triples returned
                            triangle_array[a + b + c] += 1
                    else:
                        triangle_array[a + b + c] += 1
            else:
                break
            k += 1

# count 1s in array
singles = triangle_array.count(1)

# print result
print("The number of values of L for which exactly one right triangle can be formed is", singles)
