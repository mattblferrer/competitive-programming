# Python Templates

Modules for Project Euler, taken from the `# Contents` block at the top of each file. They import each other by
module name (`number_theory.py` uses `primes.py`), so this folder must be on `sys.path`: run
`python py_templates/install_pth.py` once to write a `py_templates.pth` into the user site-packages, after which
any script can `from primes import is_prime`. Delete that file to undo it.

- [`primes.py`](primes.py), [`number_theory.py`](number_theory.py), [`figurate.py`](figurate.py), [`digits.py`](digits.py), [`fractions_cf.py`](fractions_cf.py), [`new_file.py`](new_file.py)

## [`primes.py`](primes.py)

Primes, primality and factorization.

| Name | Description |
| --- | --- |
| `soe` | Sieve of Eratosthenes: s[i] is truthy iff i is prime, for 0 <= i < n, O(n log log n) |
| `primes_below` | list of the primes < n, O(n log log n) |
| `spf_sieve` | smallest prime factor of every i < n (spf[0] = spf[1] = 0), O(n log log n) |
| `is_prime` | deterministic Miller-Rabin for n < 3.3e24, a strong probable-prime test above that |
| `factorize` | {prime: exponent} of n >= 1 (trial division, then Pollard's rho) |
| `prime_factors` | distinct prime factors of n >= 1, increasing |
| `next_prime` | smallest prime > n |
| `prev_prime` | largest prime < n, None if n <= 2 |

`isprime` and `prime_factorize` are aliases of `is_prime` and `factorize`, so old Project Euler code can import them unchanged.

## [`number_theory.py`](number_theory.py)

Arithmetic functions, CRT and orders.

| Name | Description |
| --- | --- |
| `totient` | Euler's totient phi(n); uses factorize |
| `totient_sieve` | phi(i) for every i < n, O(n log log n) |
| `mobius` | Mobius function mu(n); uses factorize |
| `mobius_sieve` | mu(i) for every i < n, O(n log log n) |
| `divisors` | sorted divisors of n >= 1; uses factorize |
| `sigma` | sum of d^k over the divisors d of n (k = 0 counts them); uses factorize |
| `divisor_sieve` | sum of d^k over the divisors of every i < n, O(n log n) |
| `ext_gcd` | (g, x, y) with a x + b y = g = gcd(a, b), O(log) |
| `mod_inv` | inverse of a mod m, None if gcd(a, m) != 1, O(log m) |
| `crt` | x with x = r[i] (mod m[i]) for all i, moduli need not be coprime: (x, lcm) or None |
| `carmichael` | Carmichael function lambda(n), the largest multiplicative order mod n; uses factorize |
| `mult_order` | multiplicative order of a mod n, None if gcd(a, n) != 1; uses carmichael, factorize |

`mod_mult_inv(num, x)` is an alias of `mod_inv`, so old Project Euler code can import it unchanged.

## [`figurate.py`](figurate.py)

Polygonal numbers and Pythagorean triples.

| Name | Description |
| --- | --- |
| `polygonal` | n-th s-gonal number ((s - 2) n^2 - (s - 4) n) / 2: s = 3 triangular, 5 pentagonal, 6 hexagonal |
| `polygonal_index` | n with polygonal(s, n) = x, None if x is not s-gonal (exact integer arithmetic) |
| `triangular` | n-th triangular number n (n + 1) / 2 |
| `pentagonal` | n-th pentagonal number n (3n - 1) / 2 |
| `hexagonal` | n-th hexagonal number n (2n - 1) |
| `is_square` | whether x is a perfect square |
| `is_triangular` | whether x is triangular (x >= 1) |
| `is_pentagonal` | whether x is pentagonal (x >= 1) |
| `is_hexagonal` | whether x is hexagonal (x >= 1) |
| `pythagorean_triples` | every (or every primitive) triple a < b < c with c <= limit, or a + b + c <= limit |

## [`digits.py`](digits.py)

Digits, bases, palindromes, pandigitals.

| Name | Description |
| --- | --- |
| `digits` | digits of n >= 0 in base b, most significant first ([0] for 0) |
| `from_digits` | the number with these digits in base b, most significant first |
| `digit_sum` | sum of the digits of n >= 0 in base b |
| `reverse_digits` | n with its base-b digits reversed (trailing zeros of n are dropped) |
| `to_base` | n as a string in base 2..36 (digits 0-9 then a-z), with a minus sign if n < 0 |
| `is_palindrome` | whether the base-b digits of n >= 0 read the same both ways |
| `is_pandigital` | whether n uses each digit lo..hi exactly once and no others (1..9 by default) |

## [`fractions_cf.py`](fractions_cf.py)

Continued fractions and Pell equations.

| Name | Description |
| --- | --- |
| `cf` | continued fraction terms of a rational number (Fraction or int) |
| `from_cf` | the Fraction [a0; a1, a2, ...] equals |
| `convergents` | the convergents of a list of terms, as Fractions |
| `sqrt_cf` | continued fraction of sqrt(D): (a0, period), period empty if D is a perfect square |
| `sqrt_convergents` | the convergents of sqrt(D), as an endless stream of Fractions |
| `pell` | fundamental solution of x^2 - D y^2 = 1, or of = -1 if sign = -1 (None if it has none) |
| `pell_solutions` | every positive solution of x^2 - D y^2 = 1 (or -1), increasing, as an endless stream |
| `pell_general` | every solution of x^2 - D y^2 = N with 0 <= x <= limit, sorted (Lagrange-Matthews-Mollin) |
