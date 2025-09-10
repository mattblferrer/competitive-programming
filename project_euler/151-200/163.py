"""
Formula taken from:
https://www.math.uni-bielefeld.de/~sillke/SEQUENCES/grid-triangles
"""
def t(n: int) -> int:
    """returns the number of cross-hatched triangles present in a triangle
    with side length n"""
    a = 2 * n**3 + 5 * n**2 + 2 * n
    b = 2 * n**3 + 3 * n**2 - 3 * n

    return int((a // 8) + (2 * (n ** 3 - n / 3) // 2)
        + 6 * ((n * (n + 1) * (n + 2) // 6)
            + ((2 * n**3 + 5 * n**2 + 2 * n) // 8) + (b // 18) + (b // 10))
        + 3 * ((22 * n**3 + 45 * n**2 - 4 * n) // 48))


def main():
    print(t(36))  # print result
    

if __name__ == "__main__":
    main()
