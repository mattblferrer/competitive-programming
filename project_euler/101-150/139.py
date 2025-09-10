from math import gcd


# returns True if the Pythagorean triangle allows a tiling, False otherwise
def is_possible_tile(a: int, b: int, c: int) -> int:
    return c % (b-a) == 0


def main():
    # declare variables
    perimeter = 100_000_000
    limit = int(perimeter ** 0.5)
    tiles_count = 0

    # iterate through all possible m, n, m > n > 0 to generate primitive triples
    for m in range(1, limit+1):
        for n in range(1, m):
            k = 1  # multiplier
            a, b, c = 0, 0, 0  # reset a, b, c

            while a+b+c < perimeter:
                if gcd(m, n) != 1:  # only compute when m and n are coprime
                    break
                a = k*(m*m - n*n)
                b = k*2*m*n
                c = k*(m*m + n*n)

                if a+b+c <= perimeter:
                    if a % 2 == 0:  # triple will have duplicate for even a
                        if a < b:  # return only one of the two triples returned
                            tiles_count += is_possible_tile(a, b, c)
                    else:
                        tiles_count += is_possible_tile(a, b, c)

                k += 1
        print("m: ", m)  # to track progress

    # print result
    print("Number of Pythagorean tilings:", tiles_count)


if __name__ == "__main__":
    main()
