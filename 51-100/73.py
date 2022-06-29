from math import gcd, ceil


# declare variables
limit = 12000
counter = 0

# main loop
for denominator in range(5, limit+1):
    lowerLimit = ceil(denominator / 3)
    upperLimit = ceil(denominator / 2)

    for numerator in range(lowerLimit, upperLimit):
        if gcd(numerator, denominator) == 1:
            counter += 1

# print result
print("The number of fractions between 1/3 and 1/2 is", counter)
