from math import sqrt


# returns the number of solutions to (x+y)^2 + z^2 given x+y and z
def subdivide_pair(xy: int, z: int) -> int:
    if 2*z < xy:
        return 0
    elif z >= xy:
        return xy // 2
    return z - (xy-1) // 2


# returns the number of cuboids from side length M-1 to side length M with the shortest path as integer
def shortest_path_num(m: int):
    counter = sum(subdivide_pair(i, m) for i in range(1, 2*m) if sqrt(i*i + m*m).is_integer())
    return counter


# main loop
totalSolutions = 0
m = 0

while totalSolutions < 1000000:
    m += 1
    totalSolutions += shortest_path_num(m)

# print result
print(f"The least value of M is {m}")
