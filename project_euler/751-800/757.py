"""
A number n is stealthy if and only if it can be expressed as xy(x + 1)(y + 1) 
for integers x, y. Since the equation is symmetric, we only have to check x < y
a, b = xy, (x + 1)(y + 1), sum = 2xy + x + y + 1
c, d = x (y + 1), y (x + 1), sum = 2xy + x + y
a + b = c + d + 1
"""


def main():
    # declare variables
    limit = 10**14
    iterlimit = int(limit ** 0.25) + 1  # until (i*(i + 1)) ^ 2 > limit
    stealthy_set = []

    # iterate through i, j pairs to generate stealthy numbers with duplicates
    for i in range(1, iterlimit):
        for j in range(i, limit):
            stealthy_num = i * (i + 1) * j * (j + 1)

            if stealthy_num < limit:
                stealthy_set.append(stealthy_num)
            else:  # if stealthy number is too big, break and increment i
                break

    # print result
    print(len(set(stealthy_set)))  # remove duplicates


if __name__ == "__main__":
    main()
