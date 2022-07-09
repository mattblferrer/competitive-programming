"""
This uses a recurrence relation to calculate the next term of the series of 
almost equilateral triangles
Sources: 
https://oeis.org/A102341
https://web.archive.org/web/20060830154134/https://www.uwgb.edu/dutchs/RECMATH/rmpowers.htm/#almost30
"""


# returns the next in sequence of almost 30-60-90 integer triangles, given a, b
# of previous term and index of current term
def almost_30_60(a0, b0, ctr):
    if ctr % 2 == 0:  # correction factor
        corr = 1
    else:
        corr = -1

    # calculate next term in sequence
    c0 = 2*a0 - corr
    a1 = b0 + c0 - corr
    b1 = c0 + 2*b0 + a0 - corr
    c1 = 2*b0 + 2*c0 - corr

    return a1, b1, c1


# declare variables
limit = 1000000000
totalPerimeter = 0
a, b, c, ctr = 0, 1, 1, 1  # basic triangle of area 0

# main loop
# to get almost equilateral triangle perimeter, we put two of these almost 
# 30-60-90 triangles together (removing b = height of triangle)
while True:  
    a, b, c = almost_30_60(a, b, ctr)

    if 2*(a+c) > limit:
        break

    totalPerimeter += 2*(a+c)
    ctr += 1 

# print result
print("The sum of the perimeters of all almost equilateral triangles with", 
    "integral side lengths and area is", totalPerimeter)
