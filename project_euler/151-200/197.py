"""
As can be seen from the code's output, the sequence converges to an oscillating
cycle of length 2.
For even n, the sequence equals 0.681175878
For odd n, the sequence equals 1.029461839
"""

from math import floor


# declare variables
u = -1

# main loop
for n in range(1000):
    nextu = floor(2**(30.403243784 - u*u)) * 10**-9
    print(n, nextu)

    u = nextu

# print result
print(0.681175878 + 1.029461839)
