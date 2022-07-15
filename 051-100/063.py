"""
We only need to check a^b for a = 1 to a = 10.
"""
# declare variables
nthPowers = 0

# main loop
for a in range(1, 10):
    b = 1

    # shorter than b
    while len(str(a**b)) < b:
        b += 1

    # if bth power has b digits
    while len(str(a**b)) == b:
        nthPowers += 1
        print("{} = {}^{}".format(a**b, a, b))
        b += 1

# print result
print("The number of n-digit nth powers is", nthPowers)
