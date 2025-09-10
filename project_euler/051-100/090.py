from itertools import combinations


squares = ((0, 1),(0, 4),(0, 9),(1, 6),(2, 5),(3, 6),(4, 9),(6, 4),(8, 1))
def check_cubes(cube_1: tuple[int], cube_2: tuple[int]) -> bool:
    """returns True if all squares can be made using arrangements of the two
    cubes' digits, and False otherwise"""
    # if cube has 6, add 9 and vice versa
    cube_1, cube_2 = set(cube_1), set(cube_2)
    for cube in (cube_1, cube_2):
        if (6 in cube) ^ (9 in cube):
            cube.update({6, 9})

    for square in squares:  # iterate through squares to see if they're formed
        if square[0] in cube_1 and square[1] in cube_2:
            continue
        elif square[1] in cube_1 and square[0] in cube_2:
            continue
        return False
    return True  # if tests passed for all squares
        

def main():
    # generate all possible cube arrangements
    arrangements = 0
    for cube_1, cube_2 in combinations(combinations(range(10), 6), 2):
        if check_cubes(cube_1, cube_2):
            arrangements += 1

    # print result
    print(arrangements)


if __name__ == "__main__":
    main()
