"""
For any given integer m and n, m > n > 0: and integer k
a = k*(m^2 - n^2)
b = k*(2mn)
c = k*(m^2 + n^2),

generates all Pythagorean triples if m and n are coprime and are not both odd
"""
from math import gcd


def main():
    # declare variables
    sum_abc = 1_500_000
    triangle_array = [0]*(sum_abc + 1)
    limit = int(sum_abc ** 0.5) + 1  # loop iteration limit

    # iterate through all possible m, n, m > n > 0 to generate primitive triples
    for m in range(1, limit+1):
        for n in range(1, m):
            k = 1  # multiplier
            a, b, c = 0, 0, 0  # reset a, b, c

            while a+b+c <= sum_abc:
                if gcd(m, n) != 1:  # only compute when m and n are coprime
                    break
                a = k*(m*m - n*n)
                b = k*2*m*n
                c = k*(m*m + n*n)

                if a+b+c <= sum_abc:
                    if a % 2 == 0:  # triple will have duplicate for even a
                        if a < b:  # return only one of the two triples returned
                            triangle_array[a + b + c] += 1
                    else:
                        triangle_array[a + b + c] += 1
                k += 1

    # count 1s in array
    singles = triangle_array.count(1)

    # print result
    print("The number of values of L for which exactly one right "\
        f"triangle can be formed is {singles}")


if __name__ == "__main__":
    main()
