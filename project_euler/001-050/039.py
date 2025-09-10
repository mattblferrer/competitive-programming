from math import isqrt


def main():
    sum_abc = 1000  # given a+b+c = 1000
    solutions = [0]*(sum_abc + 1)

    # generating a, b, c
    for a in range(1, sum_abc // 2):
        for b in range(1, sum_abc // 2):
            c2 = a*a + b*b
            c = isqrt(c2)
            if a + b + c > sum_abc:
                break
            if c*c == c2:  # check for pythagorean triple
                solutions[a + b + c] += 1

    # finding maximum value p
    maximum_index = solutions.index(max(solutions))

    # final output
    print("The value of p where the number of solutions is maximized"\
        f" is {maximum_index}")


if __name__ == "__main__":
    main()
