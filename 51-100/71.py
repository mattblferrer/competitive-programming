"""
To generate the fraction in between two other fractions a/b and c/d in ascending order, in its lowest terms:
(a+c)/(b+d)
"""


# generates the fraction in between two other fractions
def in_between_frac(a, b, c, d):
    return (a+c), (b+d)


# declare variables
limit = 1000000
n1, d1, n2, d2 = 2, 5, 3, 7  # 2/5, 3/7 are next to each other ascending

# main loop
while d1 < limit - d2:
    n1, d1 = in_between_frac(n1, d1, n2, d2)

# print result
print("{}/{}".format(n1, d1))
