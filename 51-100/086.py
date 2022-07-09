import math


# returns the number of solutions to (x+y)^2 + z^2 given x+y and z
def subdivide_pair(xy, z):
    if 2*z < xy:
        return 0
    elif z >= xy:
        return xy // 2
    else:
        return z - (xy-1) // 2


# returns the number of cuboids from side length M-1 to side length M with the shortest path as integer
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
