"""
For 16-digit string, 10 has to be on the outside. If it is in the inside, it would be repeated, and so it would be a
17-digit string.
We only need to look for possibilities for the inner ring, as the numbers for the outer rings can be deduced
For the sake of simplicity, the 10 will always be the top left node of the 5-gon ring
"""


from itertools import permutations


# returns a list of 5 digit permutations of numbers 1 to 9 for the inner ring
def five_d_permutations():
    perm_list = list(permutations(range(1, 10), 5))
    return perm_list


# returns a permutation of the outer ring based on the permutation of inner ring
def outer_ring_perm(inner_ring):
    # define outer ring
    possible_outer_ring = set(range(1, 10)) - set(inner_ring)
    outer_ring = [10]

    # clone inner ring
    ring_sum = 0  # this sum has to stay constant

    # assign permutation to inner ring clockwise, starting from top
    for i in range(5):
        a, b = inner_ring[i], inner_ring[(i+1) % 5]

        # for first
        if i == 0:
            ring_sum = a+b+10

        # for 2nd to 5th
        else:
            for j in possible_outer_ring:
                if a+b+j == ring_sum:
                    outer_ring.append(j)
                    possible_outer_ring.remove(j)
                    # print(inner_ring[0:5], outer_ring, possible_outer_ring)
                    break

    if len(outer_ring) != 5:
        # if no solution of outer ring is found
        return 0

    return outer_ring


# returns the string representation of a solution
def ring_string(inner_ring, outer_ring):
    string = ""

    # start from numerically lowest external (outer) node, go clockwise
    while outer_ring[0] != min(outer_ring):
        # rotate both rings
        outer_ring.append(outer_ring.pop(0))
        inner_ring.append(inner_ring.pop(0))

    # add each "line" to final string
    for i in range(5):
        string += str(outer_ring[i]) + str(inner_ring[i]) + str(inner_ring[(i+1) % 5])

    return string


# main loop
maximumString = 0
for ring in five_d_permutations():
    ring = list(ring)

    # if solution is found
    solution = outer_ring_perm(ring)
    if solution != 0:
        solutionString = int(ring_string(ring, solution))
        if maximumString < solutionString:
            maximumString = solutionString
        print(ring, solution, solutionString)

# print result
print("\nThe maximum 16-digit string for a 5-gon ring is", maximumString)
