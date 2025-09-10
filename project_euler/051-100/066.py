"""
This uses the Chakravala method to calculate the value x in the Diophantine equation x^2 - Dy^2 = 1 for given D
"""
from math import sqrt


# returns x in the equation x^2 - Dy^2 = 1 for a given D
def diophantine_solve(d: int) -> int:
    # starting values of x and y
    x, y = int(sqrt(d)) + 1, 1

    while True:
        # substitute into equation to get x^2 - Dy^2 = k to get k
        k = x*x - d*y*y

        # check if equation is solved
        if k == 1:
            return x

        # finding next value of m for triple composition
        minimal_sqr_diff = float('inf')
        for i in range(int(sqrt(d))+2):
            if (x+y*i) % k == 0 and abs(i*i - d) < minimal_sqr_diff:
                minimal_sqr_diff = abs(i*i - d)
                m = i

        # new triple composition
        x, y, k = (x*m + d*y)//abs(k), (x + m*y)//abs(k), (m*m - d)//k


def main():
    # declare variables
    limit = 1000
    maximum_d = 0
    maximum_x = 0

    # main loop
    for i in range(1, limit + 1):
        if not sqrt(i).is_integer():  # perfect square check
            ans = diophantine_solve(i)
            if maximum_x < ans:
                maximum_x = ans
                maximum_d = i

    # print result
    print("The value of D for which the largest value of x is "\
        f"obtained is {maximum_d}")
    print(f"The largest value of x is {maximum_x}")


if __name__ == "__main__":
    main()
