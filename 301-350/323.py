'''
CODE FOR CHECKING:

from random import getrandbits

ctr = 0
n = 100_000
for i in range(n):
    x = 0  # x0
    while x != 2 ** 32 - 1:
        y = getrandbits(32)
        x = x | y
        ctr += 1

print(ctr / n)
'''
