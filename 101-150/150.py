"""
CODE FOR TESTING:
triangle = [15, -14, -7, 20, -13, -5, -3, 8, 23, -26, 1, -4, -5, -18, 5, -16,
    31, 2, 9, 28, 3]

This code is slow, and may take hours to run
"""


# returns the terms of a linear congruential generator with n terms
def linear_con_gen(n: int):
    t = 0
    terms = []
    p20 = 2**20
    p19 = 2**19

    for _ in range(n):
        t = (615949*t + 797807) % p20
        terms.append(t-p19)

    return terms


def main():
    # declare variables
    limit = 500500
    rows = 1000  # number of rows on the triangle
    triangle = linear_con_gen(limit)
    minimumSum = 0

    # iterate through all possible subtriangle vertices
    index = 0

    for row in range(rows):
        for c in range(row+1):
            currentSum = 0
            index_2 = index

            # iterate through all sizes of subtriangles
            for row_2 in range(row, rows):
                value = 0

                # calculate value of each row of subtriangle
                for c_2 in range(row_2 - row + 1):
                    value += triangle[index_2]
                    index_2 += 1

                index_2 += row  # move to next row
                currentSum += value

                # check for minimum sum subtriangle
                if currentSum < minimumSum:
                    minimumSum = currentSum

            index += 1
            print(index)

    # print result
    print("Minimum sum:", minimumSum)


if __name__ == "__main__":
    main()
