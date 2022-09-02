from math import sqrt


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
    counter = sum(subdivide_pair(i, M) for i in range(1, 2*M) if sqrt(i*i + M*M).is_integer())
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
print(f"The least value of M is {M}")
