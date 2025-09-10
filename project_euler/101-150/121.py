"""
Probability for n discs:
0 red: 1/(n+1)!
1 red: 1/(n+1)! + 2/(n+1)! + ... + n/(n+1)!
2 red: 1*2/(n+1)! + 1*3/(n+1)! + 1*4/(n+1)! + ... + 1*n/(n+1)!
+ ...
... - floor(n/2) red discs
"""
from itertools import combinations
from math import prod


# returns the factorial of a number num
def factorial(num):
    fac = 1  # factorial
    for i in range(1, num + 1):
        fac *= i
    return fac


# generate triangular number of certain index
def triangular(ind):
    return ind*(ind+1)//2


# declare variables
discs = 15
discList = list(range(1, discs+1))
winCombs = 1 + triangular(discs)  # for 0 and 1 red discs

# main loop, for even discs, you need n/2 + 1 blue discs to win; for odd: n//2+1
for redDiscs in range(2, int(discs / 2 + 0.5)):
    for comb in combinations(discList, redDiscs):
        winCombs += prod(comb)  # compute product of numbers in combination

# print result
prizeFund = factorial(discs+1) // winCombs
print("Maximum prize fund:", prizeFund, "pounds")
