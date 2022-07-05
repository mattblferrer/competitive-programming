"""
The shortest path on the surface of a cuboid x * y * z has length sqrt((x+y)^2 + z^2) where x <= y <= z

For any given integer m and n, m > n > 0: and integer k
a = k*(m^2 - n^2)
b = k*(2mn)
c = k*(m^2 + n^2),

generates all Pythagorean triples if m and n are coprime and are not both odd
"""
import math


# returns the number of solutions to (x+y)^2 + z^2 given x+y and z
def subdivide_pair(xy, z):
    if 2*z < xy:
        return 0
    elif z >= xy:
        return xy // 2
    else:
        return z - (xy-1) // 2


# returns the number of cuboids from side length M-1 to side length M with the shortest path as integer TODO
def shortest_path_num(M):
    counter = 0

    for i in range(1, 2*M):
        if math.sqrt(i**2 + M**2).is_integer():
            counter += subdivide_pair(i, M)

    return counter


# main loop
totalSolutions = 0
M = 1

while True:
    totalSolutions += shortest_path_num(M)

    if totalSolutions > 1000000:
        break
    M += 1

# print result
print("The least value of M is", M)
