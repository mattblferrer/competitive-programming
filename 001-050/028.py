"""
PLAN:
After the spiral hits a perfect square number n^2, the sequence of numbers starts going up by n+1 per step
For example, after the number 9, the spiral hits 9+4, 9+2*4, 9+3*4, etc, until it hits the next square 25
The size of the spiral is n^2
"""
def main():
    diagonal_sum = 1
    spiral_size = 1001  # given parameter

    for i in range((spiral_size - 1) // 2):  # "rings" around central 1
        for j in range(4):  # for the 4 corners of the spiral
            # start in the top right corner and go counterclockwise
            diagonal_sum += (2 * i + 3) ** 2 - j * (2 * i + 2)  

    print(diagonal_sum)  # print result


if __name__ == "__main__":
    main()
