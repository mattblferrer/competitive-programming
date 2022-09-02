from math import e, gcd


# reduces fraction to its lowest terms
def reduce(numerator, denominator):
    # divide numerator, denominator by their GCD
    frac_gcd = gcd(numerator, denominator)
    numerator //= frac_gcd
    denominator //= frac_gcd

    return numerator, denominator


# returns True if fraction's decimal expansion terminates, and False otherwise
def is_terminating(denominator):
    for i in [2, 5]:
        while denominator % i == 0:
            denominator //= i

    if denominator == 1:
        return True
    return False


# declare variables
limit = 10000
i = 5
Dn = 0

# main loop
while i <= limit:
    maxParts = round(i/e)
    reducedFrac = reduce(i, maxParts)
    n = reducedFrac[0]  # numerator
    d = reducedFrac[1]  # denominator
    
    # check if max parts evenly divide the number into integer parts
    if n == 1:
        Dn -= i

    # check if decimal expansion is terminating
    elif is_terminating(d):
        Dn -= i
    else:
        Dn += i

    i += 1

# print result
print("The sum of D(n) =", Dn)
