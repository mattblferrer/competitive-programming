# calculates the factorial of n
def factorial(n):
    fac = 1  # factorial
    for i in range(1, n+1):
        fac *= i
    return fac


# the function n choose r
def combination(n, r):
    return factorial(n)//(factorial(r)*factorial(n-r))


# declare variables
limit = 1000000
greaterValues = 0  # number of values of nCr greater than limit

for n in range(1, 101):
    for r in range(1, n+1):
        if combination(n, r) > limit:
            greaterValues += 1

# print output
print("The number of values of nCr greater than {} is {}".format(limit, greaterValues))
