from math import gcd


# generate Pythagorean triple using Euclid's formula
def pythagorean_triple(m: int, n: int) -> tuple[int]:
    a = m*m - n*n
    b = 2*m*n
    c = m*m + n*n

    return a, b, c


def main():
    # declare variables
    limit = 10**16
    triangles = 0

    # loop through all m, n that form perfect right triangles
    for n in range(1, 100_000):  # guess limit
        skip = 1 if n % 2 == 0 else 2  # skip m, n where both are odd

        for m in range((n + 1) // 2 * 2, 100_000, skip):
            if gcd(m, n) == 1:
                a1, b1, _ = pythagorean_triple(m, n)           
                a2, b2, c2 = pythagorean_triple(a1, b1)
                area = a2 * b2 // 2

                if area % 84 != 0:  # check if divisible by 6 and 28
                    triangles += 1
                    
                if c2 > limit:
                    break

    # print result
    print(f"The number of perfect right-angled triangles with c <= {limit} = \
{triangles}")


if __name__ == "__main__":
    main()
