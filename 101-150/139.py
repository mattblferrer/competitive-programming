from math import gcd


# returns True if two numbers are coprime, False otherwise
def is_coprime(n1, n2):
    if gcd(n1, n2) == 1:
        return True
    return False


# returns True if the Pythagorean triangle allows a tiling, False otherwise
def is_possible_tile(a, b, c):
    if c % (b-a) == 0:
        return True
    return False


# declare variables
perimeter = 100000000
limit = int(perimeter ** 0.5)
tilesNum = 0

# iterate through all possible m, n, m > n > 0 to generate primitive triples
for m in range(1, limit+1):
    for n in range(1, m):
        k = 1  # multiplier
        a, b, c = 0, 0, 0  # reset a, b, c

        while a+b+c < perimeter:
            if is_coprime(m, n):  # only compute when m and n are coprime
                a = k*(m*m - n*n)
                b = k*2*m*n
                c = k*(m*m + n*n)

                if a+b+c <= perimeter:
                    if a % 2 == 0:  # pythagorean triple will have duplicate for even a
                        if a < b:  # return only one of the two triples returned
                            tilesNum += is_possible_tile(a, b, c)
                    else:
                        tilesNum += is_possible_tile(a, b, c)
            else:
                break
            k += 1
    print("m: ", m)  # to track progress

# print result
print("Number of Pythagorean tilings:", tilesNum)
