from math import e, gcd


# reduces fraction to its lowest terms
def reduce(numerator: int, denominator: int) -> tuple[int]:
    # divide numerator, denominator by their GCD
    frac_gcd = gcd(numerator, denominator)
    numerator //= frac_gcd
    denominator //= frac_gcd

    return numerator, denominator


# returns True if fraction's decimal expansion terminates, and False otherwise
def is_terminating(denominator: int) -> bool:
    for i in [2, 5]:
        while denominator % i == 0:
            denominator //= i

    if denominator == 1:
        return True
    return False


# declare variables
limit = 10000
Dn = 0

# main loop
for i in range(5, limit+1):
    maxParts = round(i/e)
    n, d = reduce(i, maxParts)  # reduced fraction
    
    # check if max parts evenly divide the number into integer parts
    if n == 1:
        Dn -= i

    # check if decimal expansion is terminating
    elif is_terminating(d):
        Dn -= i
    else:
        Dn += i

# print result
print(f"The sum of D(n) = {Dn}")
