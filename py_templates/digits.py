# Contents
#   digits          digits of n >= 0 in base b, most significant first ([0] for 0)
#   from_digits     the number with these digits in base b, most significant first
#   digit_sum       sum of the digits of n >= 0 in base b
#   reverse_digits  n with its base-b digits reversed (trailing zeros of n are dropped)
#   to_base         n as a string in base 2..36 (digits 0-9 then a-z), with a minus sign if n < 0
#   is_palindrome   whether the base-b digits of n >= 0 read the same both ways
#   is_pandigital   whether n uses each digit lo..hi exactly once and no others (1..9 by default)

_SYMBOLS = "0123456789abcdefghijklmnopqrstuvwxyz"


# digits of n >= 0 in base b, most significant first, [0] for 0, O(number of digits)
def digits(n: int, b: int = 10) -> list[int]:
    if b == 10:
        return [int(c) for c in str(n)]
    res = []
    while True:
        n, r = divmod(n, b)
        res.append(r)
        if n == 0:
            return res[::-1]


# the number with these digits in base b, most significant first
def from_digits(ds: list[int], b: int = 10) -> int:
    n = 0
    for d in ds:
        n = n * b + d
    return n


# sum of the digits of n >= 0 in base b
def digit_sum(n: int, b: int = 10) -> int:
    if b == 10:
        return sum(map(int, str(n)))
    s = 0
    while n:
        n, r = divmod(n, b)
        s += r
    return s


# n >= 0 with its base-b digits reversed, so trailing zeros of n are dropped (reverse_digits(120) = 21)
def reverse_digits(n: int, b: int = 10) -> int:
    if b == 10:
        return int(str(n)[::-1])
    return from_digits(digits(n, b)[::-1], b)


# n as a string in base 2..36, digits 0-9 then a-z, with a minus sign if n < 0; int(s, b) converts back
def to_base(n: int, b: int) -> str:
    if n < 0:
        return "-" + to_base(-n, b)
    return "".join(_SYMBOLS[d] for d in digits(n, b))


# whether the base-b digits of n >= 0 read the same both ways
def is_palindrome(n: int, b: int = 10) -> bool:
    s = str(n) if b == 10 else digits(n, b)
    return s == s[::-1]


# whether n uses each digit lo..hi exactly once and no other digit: 1..9 pandigital by default, (0, 9) for 0..9;
# also takes a string, so concatenated products can be checked as is_pandigital(f"{a}{b}{a * b}")
def is_pandigital(n: int | str, lo: int = 1, hi: int = 9) -> bool:
    s = str(n)
    return len(s) == hi - lo + 1 and sorted(s) == [str(d) for d in range(lo, hi + 1)]
