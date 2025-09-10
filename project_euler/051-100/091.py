from itertools import product


# returns the square of the distance between two points (x1, y1) and (x2, y2)
def sqr_distance(x1: int, y1: int, x2: int, y2: int) -> int:
    return (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)


# returns True if triangle that is joined to the origin is a right triangle
def is_right_triangle(x1: int, y1: int, x2: int, y2: int) -> bool:
    # get squares of sides of triangle
    a, b, c = sorted([sqr_distance(x1, y1, x2, y2), sqr_distance(x1, y1, 0, 0), 
        sqr_distance(0, 0, x2, y2)])

    # check if any points are equal to origin
    return a + b == c and a != 0 and b != 0 and c != 0


def main():
    # declare variables
    limit = 50
    right_triangles = 0

    # main loop
    for x1, x2, y1, y2 in product(range(limit + 1), repeat=4):
        if y2 - x2 > y1 - x1 and is_right_triangle(x1, x2, y1, y2):
            right_triangles += 1

    # print result
    print(f"Number of right triangles that can be formed: {right_triangles}")


if __name__ == "__main__":
    main()
