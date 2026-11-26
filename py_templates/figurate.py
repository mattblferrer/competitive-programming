# Contents
#   polygonal            n-th s-gonal number ((s - 2) n^2 - (s - 4) n) / 2: s = 3 triangular, 5 pentagonal, 6 hexagonal
#   polygonal_index      n with polygonal(s, n) = x, None if x is not s-gonal (exact integer arithmetic)
#   triangular           n-th triangular number n (n + 1) / 2
#   pentagonal           n-th pentagonal number n (3n - 1) / 2
#   hexagonal            n-th hexagonal number n (2n - 1)
#   is_square            whether x is a perfect square
#   is_triangular        whether x is triangular (x >= 1)
#   is_pentagonal        whether x is pentagonal (x >= 1)
#   is_hexagonal         whether x is hexagonal (x >= 1)
#   pythagorean_triples  every (or every primitive) triple a < b < c with c <= limit, or a + b + c <= limit

from math import gcd, isqrt
from typing import Iterator


# n-th s-gonal number ((s - 2) n^2 - (s - 4) n) / 2 for s >= 3: s = 3 triangular, 4 square, 5 pentagonal, ...
def polygonal(s: int, n: int) -> int:
    return ((s - 2) * n * n - (s - 4) * n) // 2


# n >= 1 with polygonal(s, n) = x, or None if x is not s-gonal; solves (s - 2) n^2 - (s - 4) n - 2x = 0 exactly:
# n = ((s - 4) + sqrt(D)) / (2 (s - 2)) with D = (s - 4)^2 + 8 (s - 2) x
def polygonal_index(s: int, x: int) -> int | None:
    if x < 1:
        return None
    D = (s - 4) ** 2 + 8 * (s - 2) * x
    r = isqrt(D)
    if r * r != D or (r + s - 4) % (2 * (s - 2)):
        return None
    return (r + s - 4) // (2 * (s - 2))


def triangular(n: int) -> int:
    return n * (n + 1) // 2


def pentagonal(n: int) -> int:
    return n * (3 * n - 1) // 2


def hexagonal(n: int) -> int:
    return n * (2 * n - 1)


def is_square(x: int) -> bool:
    return x >= 0 and isqrt(x) ** 2 == x


def is_triangular(x: int) -> bool:
    return polygonal_index(3, x) is not None


def is_pentagonal(x: int) -> bool:
    return polygonal_index(5, x) is not None


def is_hexagonal(x: int) -> bool:
    return polygonal_index(6, x) is not None


# every Pythagorean triple (a, b, c) with a^2 + b^2 = c^2 and 0 < a < b, only the primitive ones (gcd(a, b) = 1) if
# primitive; bounded by c <= limit, or by the perimeter a + b + c <= limit if perimeter; Euclid's formula
# (m^2 - k^2, 2 m k, m^2 + k^2) for m > k > 0 coprime of opposite parity gives every primitive triple once, and the
# rest are their multiples; not in sorted order, O(limit log limit) plus the triples
def pythagorean_triples(limit: int, primitive: bool = False, perimeter: bool = False) -> Iterator[tuple[int, int, int]]:
    m = 2
    while (2 * m * (m + 1) if perimeter else m * m + 1) <= limit:
        for k in range(m % 2 + 1, m, 2):
            size = 2 * m * (m + k) if perimeter else m * m + k * k  # perimeter or hypotenuse of the primitive
            if size > limit:
                break
            if gcd(m, k) != 1:
                continue
            a, b, c = m * m - k * k, 2 * m * k, m * m + k * k
            if a > b:
                a, b = b, a
            for t in range(1, 2 if primitive else limit // size + 1):
                yield t * a, t * b, t * c
        m += 1
