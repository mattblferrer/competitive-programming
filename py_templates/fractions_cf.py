# Contents
#   cf                continued fraction terms of a rational number (Fraction or int)
#   from_cf           the Fraction [a0; a1, a2, ...] equals
#   convergents       the convergents of a list of terms, as Fractions
#   sqrt_cf           continued fraction of sqrt(D): (a0, period), period empty if D is a perfect square
#   sqrt_convergents  the convergents of sqrt(D), as an endless stream of Fractions
#   pell              fundamental solution of x^2 - D y^2 = 1, or of = -1 if sign = -1 (None if it has none)
#   pell_solutions    every positive solution of x^2 - D y^2 = 1 (or -1), increasing, as an endless stream
#   pell_general      every solution of x^2 - D y^2 = N with 0 <= x <= limit, sorted (Lagrange-Matthews-Mollin)

from fractions import Fraction
from itertools import count
from math import isqrt
from typing import Iterator


# continued fraction terms [a0; a1, ...] of a rational x (the last term is > 1 unless x is an integer), O(log)
def cf(x: Fraction | int) -> list[int]:
    x = Fraction(x)
    p, q, terms = x.numerator, x.denominator, []
    while q:
        a = p // q
        terms.append(a)
        p, q = q, p - a * q
    return terms


# the Fraction [a0; a1, a2, ...] equals (the last convergent)
def from_cf(terms: list[int]) -> Fraction:
    x = Fraction(terms[-1])
    for a in reversed(terms[:-1]):
        x = a + 1 / x
    return x


# the convergents p_k / q_k of the terms, as Fractions: p_k = a_k p_{k-1} + p_{k-2}, q_k likewise
def convergents(terms) -> Iterator[Fraction]:
    p0, q0, p1, q1 = 0, 1, 1, 0
    for a in terms:
        p0, q0, p1, q1 = p1, q1, a * p1 + p0, a * q1 + q0
        yield Fraction(p1, q1)


# continued fraction of sqrt(D) for D >= 0: (a0, period) with sqrt(D) = [a0; period, period, ...], period empty if D
# is a perfect square; m, d, a follow m' = d a - m, d' = (D - m'^2) / d, a' = (a0 + m') / d' until a' = 2 a0
def sqrt_cf(D: int) -> tuple[int, list[int]]:
    a0 = isqrt(D)
    period = []
    if a0 * a0 == D:
        return a0, period
    m, d, a = 0, 1, a0
    while a != 2 * a0:
        m = d * a - m
        d = (D - m * m) // d
        a = (a0 + m) // d
        period.append(a)
    return a0, period


# the convergents of sqrt(D) for D not a perfect square, as an endless stream of Fractions
def sqrt_convergents(D: int) -> Iterator[Fraction]:
    a0, period = sqrt_cf(D)
    yield from convergents(_sqrt_terms(a0, period))


def _sqrt_terms(a0: int, period: list[int]) -> Iterator[int]:
    yield a0
    for i in count():
        yield period[i % len(period)]


# fundamental (smallest positive) solution (x, y) of x^2 - D y^2 = 1 for D >= 2 not a perfect square: the convergent
# of sqrt(D) at index L - 1 if the period length L is even, 2L - 1 if odd; sign = -1 solves x^2 - D y^2 = -1, which
# is solvable iff L is odd (None otherwise); O(period) big-integer steps
def pell(D: int, sign: int = 1) -> tuple[int, int] | None:
    a0, period = sqrt_cf(D)
    L = len(period)
    if sign == -1 and L % 2 == 0:
        return None
    k = L - 1 if sign == -1 or L % 2 == 0 else 2 * L - 1
    for i, c in enumerate(convergents(_sqrt_terms(a0, period))):
        if i == k:
            return c.numerator, c.denominator


# every positive solution of x^2 - D y^2 = 1 (or -1 if sign = -1), increasing, as an endless stream: the powers
# (x1 + y1 sqrt(D))^k of the fundamental solution, odd powers only for -1
def pell_solutions(D: int, sign: int = 1) -> Iterator[tuple[int, int]]:
    f = pell(D, sign)
    if f is None:
        return
    x1, y1 = f
    ux, uy = (x1 * x1 + D * y1 * y1, 2 * x1 * y1) if sign == -1 else (x1, y1)  # step between solutions
    x, y = x1, y1
    while True:
        yield x, y
        x, y = x * ux + D * y * uy, x * uy + y * ux


# every solution (x, y) of x^2 - D y^2 = N with x, y >= 0 and x <= limit, sorted, for D >= 2 not a perfect square and
# N != 0 (Lagrange-Matthews-Mollin): for each f with f^2 | N and m = N / f^2, each z in (-|m| / 2, |m| / 2] with
# z^2 = D (mod |m|) runs the continued fraction of (z + sqrt(D)) / |m| until some Q_i = +-1, whose previous convergent
# (r, s) has r^2 - D s^2 = +-m; +m gives the class representative (f r, f s), -m needs a solution of the -1 equation;
# every solution is +-(r +- s sqrt(D)) (x1 + y1 sqrt(D))^k for k >= 0 and one representative, so each such sequence is
# walked until |x| passes limit and grows (|x| is convex in k); O(|N| log D + period * (number of z) + solutions)
def pell_general(D: int, N: int, limit: int) -> list[tuple[int, int]]:
    x1, y1 = pell(D)
    neg = pell(D, -1)
    s0, reps = isqrt(D), []
    for f in range(1, isqrt(abs(N)) + 1):
        if N % (f * f):
            continue
        m = N // (f * f)
        am = abs(m)
        for z in range(-((am - 1) // 2), am // 2 + 1):
            if (z * z - D) % am:
                continue
            P, Q, G0, G1, B0, B1 = z, am, -z, am, 1, 0  # G_{i - 2}, G_{i - 1}, B_{i - 2}, B_{i - 1}
            seen = set()
            while (P, Q) not in seen:
                seen.add((P, Q))
                a = (P + s0) // Q if Q > 0 else -((P + s0) // -Q + 1)  # floor((P + sqrt(D)) / Q)
                G0, G1, B0, B1 = G1, a * G1 + G0, B1, a * B1 + B0
                P = a * Q - P
                Q = (D - P * P) // Q
                if abs(Q) == 1:
                    r, s = G1, B1
                    v = r * r - D * s * s
                    if v == m:
                        reps.append((f * r, f * s))
                    elif v == -m and neg:
                        t, u = neg
                        reps.append((f * (r * t + s * D * u), f * (r * u + s * t)))
                    break
    res = set()
    for r, s in reps:
        for x, y in ((r, s), (r, -s)):
            prev = None
            while True:
                if abs(x) <= limit:
                    res.add((abs(x), abs(y)))
                elif prev is not None and abs(x) > prev:
                    break
                prev = abs(x)
                x, y = x * x1 + D * y * y1, x * y1 + y * x1
    return sorted(res)
